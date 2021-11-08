.. _app-development-tutorials-interactive-apps-k8s-like-hpc-jupyter:

Add a Jupyter App on a Kubernetes Cluster that behaves like HPC compute
=======================================================================

This tutorial will walk you through creating an interactive Jupyter app that
your users will use to launch a `Jupyter Notebook Server`_ in a kubernetes cluster.
The container will behave much like a HPC compute node. This has the benefit that
a single app can serve both traditional HPC as well as Kubernetes.

It assumes you have a working understanding of app development already. The purpose of
this document is to describe how to write apps specifically for a kubernetes cluster,
so it skips a lot of important details about app development that may be found in
other tutorials like :ref:`app-development-tutorials-interactive-apps-add-jupyter`.


We're going to be looking at the `bc osc jupyter`_ app which is OSC's production Jupyter app. You can fork, clone
and modify for your site.  This page also holds the `submit yml in full`_ for reference.

The container
-------------

The container to make Kubernetes pods look like HPC compute would end up needing all
the OS packages present on the HPC environment.  The OS of the container itself would also
need to compatible with packages installed on HPC environment so if you run RHEL 8 on HPC
you would also need to run RHEL 8 inside the container.

Things like Lmod and HPC applications will need to be run inside the Pod's container just like
if a job was spawned in a traditional HPC resource manager.


Switch between SLURM and Kubernetes
-----------------------------------

The first big change from a traditional HPC interactive app is the main YAML structure is wrapped
in a large ``if`` statement based on the cluster choice. If a user choose one of the HPC clusters,
the SLURM submit YAML is rendered, otherwise the Kubernetes YAML is rendered.

Here is the beginning of the block:

.. code-block:: text

  <% if cluster =~ /owens|pitzer/ -%>
  ---
  batch_connect:
    template: "basic"
    conn_params:
      - jupyter_api
  script:
  ...SLURM specific...


Here is the logic to select Kubernetes:

.. code-block:: text

  <% elsif cluster =~ /kubernetes/
  ...Ruby variables setup here...

container spec
--------------

Let's look at this section first of the Kubernetes block.  Here you must specify the ``name``, ``image``
and ``command``.  The name determines the Pod Id (the job name in HPC parlance).

The ``image`` should be the HPC container image and ``command`` will be the job script that has been adapted to
work with both SLURM and Kubernetes.  The ``command`` will be run from the user's home directory and will cover mount
requirements in :ref:`mount requirements <kubernetes-mount-requirements>`.

Next you can specify additional environment variables in ``env``. 

.. code-block:: yaml

  native:
    container:
      name: "jupyter"
      image: "docker-registry.osc.edu/ondemand/ondemand-base-rhel7:0.3.1"
      image_pull_policy: "IfNotPresent"
      command: ["/bin/bash","-l","<%= staged_root %>/job_script_content.sh"]
      restart_policy: 'OnFailure'
      env:
        NB_UID: "<%= Etc.getpwnam(ENV['USER']).uid %>"
        NB_USER: "<%= ENV['USER'] %>"
        NB_GID: "<%= Etc.getpwnam(ENV['USER']).gid %>"
        CLUSTER: "<%= compute_cluster %>"


Here is the default environment. You can use a ``null`` here to unset any of these.

.. code-block:: text

  USER: username,
  UID: run_as_user,
  HOME: home_dir,
  GROUP: group,
  GID: run_as_group,
  KUBECONFIG: '/dev/null'


resource requests
-----------------

``port`` is is the port the container is going to listen on.  ``cpu`` and ``memory``
are the cpu and memory request. Note that memory here has ``Gi`` which is the unit.

.. code-block:: yaml

    container:
      # ...
      port: "8080"
      cpu: "<%= cpu %>"
      memory: "<%= memory %>Gi"

Kubernetes has some flexibility in requests. One can make _requests_ and _limits_
which are like hard and soft limits. In the example above, they're both the same.

Here's an example utilizing requests and limits for both memory and cpu. Note that
we're using millicores in the ``cpu_request``.

.. code-block:: yaml

    container:
      # ...
      port: "8080"
      cpu_request: "0.200"
      cpu_request: "4"
      memory_request: "500Mi"
      memory_limit: "4Gi"

See `kubernetes pod memory`_ and `kubernetes pod cpu`_ for more details.

.. _kubernetes-mount-requirements:

mounts
------

For a pod to look like an HPC environment the home directory of the user and any shared filesystems would
need to be mounted on Kubernetes worker nodes and then made available to the pod.

In the example a Ruby structure is created to streamline some of the direct mounts where the path outside
the container is the same as the path inside the container:

.. code-block:: ruby

   mounts = {
     'home'    => OodSupport::User.new.home,
     'support' => OodSupport::User.new('support').home,
     'project' => '/fs/project',
     'scratch' => '/fs/scratch',
     'ess'     => '/fs/ess',
   }

These mounts are defined in the YAML using a loop:

.. code-block:: text

    mounts:
    <%- mounts.each_pair do |name, mount| -%>
      - type: host
        name: <%= name %>
        host_type: Directory
        path: <%= mount %>
        destination_path: <%= mount %>
    <%- end -%>

Additional mounts are needed to make the pod behave like a HPC compute node. Following are mounted into the container

- MUNGE socket so SLURM commands inside the pod can work
- SLURM configuration so SLURM commands inside the pod know about scheduler host
- SSSD pipes and configuration as well as nsswitch.conf so ID lookups inside the pod will work
- Lmod initialization script
- Lmod HPC applications

.. code-block:: yaml

      - type: host
        name: munge-socket
        host_type: Socket
        path: /var/run/munge/munge.socket.2
        destination_path: /var/run/munge/munge.socket.2
      - type: host
        name: slurm-conf
        host_type: Directory
        path: /etc/slurm
        destination_path: /etc/slurm
      - type: host
        name: sssd-pipes
        host_type: Directory
        path: /var/lib/sss/pipes
        destination_path: /var/lib/sss/pipes
      - type: host
        name: sssd-conf
        host_type: Directory
        path: /etc/sssd
        destination_path: /etc/sssd
      - type: host
        name: nsswitch
        host_type: File
        path: /etc/nsswitch.conf
        destination_path: /etc/nsswitch.conf
      - type: host
        name: lmod-init
        host_type: File
        path: /apps/<%= compute_cluster %>/lmod/lmod.sh
        destination_path: /etc/profile.d/lmod.sh
      - type: host
        name: intel
        host_type: Directory
        path: /nfsroot/<%= compute_cluster %>/opt/intel
        destination_path: /opt/intel
      - type: host
        name: apps
        host_type: Directory
        path: /apps/<%= compute_cluster %>
        destination_path: <%= apps_path %>


submit yml in full
------------------

.. code-block:: yaml

  # submit.yml.erb
  <%-
    cores = num_cores.to_i

    if cores == 0 && cluster == "pitzer"
      # little optimization for pitzer nodes. They want the whole node, if they chose 'any',
      # it can be scheduled on p18 or p20 nodes. If not, they'll get the constraint below.
      base_slurm_args = ["--nodes", "1", "--exclusive"]
    elsif cores == 0
      # full node on owens
      cores = 28
      base_slurm_args = ["--nodes", "1", "--ntasks-per-node", "28"]
    else
      base_slurm_args = ["--nodes", "1", "--ntasks-per-node", "#{cores}"]
    end

    slurm_args = case node_type
                when "gpu-40core"
                  base_slurm_args + ["--constraint", "40core"]
                when "gpu-48core"
                  base_slurm_args + ["--constraint", "48core"]
                when "any-40core"
                  base_slurm_args + ["--constraint", "40core"]
                when "any-48core"
                  base_slurm_args + ["--constraint", "48core"]
                when "hugemem"
                  base_slurm_args + ["--partition", "hugemem", "--exclusive"]
                when "largemem"
                  base_slurm_args + ["--partition", "largemem", "--exclusive"]
                when "debug"
                  base_slurm_args += ["--partition", "debug", "--exclusive"]
                else
                  base_slurm_args
                end

  -%>
  <% if cluster =~ /owens|pitzer/ -%>
  ---
  batch_connect:
    template: "basic"
    conn_params:
      - jupyter_api
  script:
    accounting_id: "<%= account %>"
  <% if node_type =~ /gpu/ -%>
    gpus_per_node: 1
  <% end -%>
    native:
      <%- slurm_args.each do |arg| %>
      - "<%= arg %>"
      <%- end %>
  <% elsif cluster =~ /kubernetes/
     if node_type =~ /owens/
       compute_cluster = "owens"
       apps_path = "/usr/local"
       # Memory per core with hyperthreading enabled
       memory_mb = num_cores.to_i * 2200
     elsif node_type =~ /pitzer/
       compute_cluster = "pitzer"
       apps_path = "/apps"
       # Memory per core with hyperthreading enabled
       memory_mb = num_cores.to_i * 4000
     end
     mounts = {
       'home'    => OodSupport::User.new.home,
       'support' => OodSupport::User.new('support').home,
       'project' => '/fs/project',
       'scratch' => '/fs/scratch',
       'ess'     => '/fs/ess',
     }
  -%>
  ---
  script:
    accounting_id: "<%= account %>"
    wall_time: "<%= bc_num_hours.to_i * 3600 %>"
    <%- if node_type =~ /gpu/ -%>
    gpus_per_node: 1
    <%- end -%>
    native:
      container:
        name: "jupyter"
        image: "docker-registry.osc.edu/ondemand/ondemand-base-rhel7:0.3.1"
        image_pull_policy: "IfNotPresent"
        command: ["/bin/bash","-l","<%= staged_root %>/job_script_content.sh"]
        restart_policy: 'OnFailure'
        env:
          NB_UID: "<%= Etc.getpwnam(ENV['USER']).uid %>"
          NB_USER: "<%= ENV['USER'] %>"
          NB_GID: "<%= Etc.getpwnam(ENV['USER']).gid %>"
          CLUSTER: "<%= compute_cluster %>"
          KUBECONFIG: "/dev/null"
        labels:
          osc.edu/cluster: "<%= compute_cluster %>"
        port: "8080"
        cpu: "<%= num_cores %>"
        memory: "<%= memory_mb %>Mi"
      mounts:
      <%- mounts.each_pair do |name, mount| -%>
        - type: host
          name: <%= name %>
          host_type: Directory
          path: <%= mount %>
          destination_path: <%= mount %>
      <%- end -%>
        - type: host
          name: munge-socket
          host_type: Socket
          path: /var/run/munge/munge.socket.2
          destination_path: /var/run/munge/munge.socket.2
        - type: host
          name: slurm-conf
          host_type: Directory
          path: /etc/slurm
          destination_path: /etc/slurm
        - type: host
          name: sssd-pipes
          host_type: Directory
          path: /var/lib/sss/pipes
          destination_path: /var/lib/sss/pipes
        - type: host
          name: sssd-conf
          host_type: Directory
          path: /etc/sssd
          destination_path: /etc/sssd
        - type: host
          name: nsswitch
          host_type: File
          path: /etc/nsswitch.conf
          destination_path: /etc/nsswitch.conf
        - type: host
          name: lmod-init
          host_type: File
          path: /apps/<%= compute_cluster %>/lmod/lmod.sh
          destination_path: /etc/profile.d/lmod.sh
        - type: host
          name: apps
          host_type: Directory
          path: /apps/<%= compute_cluster %>
          destination_path: <%= apps_path %>
      node_selector:
        osc.edu/role: ondemand
  <% end -%>

.. _jupyter notebook server: http://jupyter.readthedocs.io/en/latest/
.. _bc osc jupyter: https://github.com/OSC/bc_osc_jupyter
.. _kubernetes pod memory: https://kubernetes.io/docs/tasks/configure-pod-container/assign-memory-resource/
.. _kubernetes pod cpu: https://kubernetes.io/docs/tasks/configure-pod-container/assign-memory-resource/
.. _kubernetes configmap: https://kubernetes.io/docs/concepts/configuration/configmap/\
.. _kubernetes secret: https://kubernetes.io/docs/concepts/configuration/secret/