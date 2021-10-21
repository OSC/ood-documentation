.. _app-development-tutorials-interactive-apps-k8s-jupyter:

Add a Jupyter App on a Kubernetes Cluster
=========================================

This tutorial will walk you through creating an interactive Jupyter app that
your users will use to launch a `Jupyter Notebook Server`_ in a kubernetes cluster.

It assumes you have a working understanding of app development already. The purpose of
this document is to describe how to write apps specifically for a kubernetes cluster,
so it skips a lot of important details about app development that may be found in
other tutorials like :ref:`app-development-tutorials-interactive-apps-add-jupyter`.


We're going to be looking at the `bc k8s jupyter`_ app which you can fork, clone
and modify for your site.  This page also holds the `submit yml in full`_ for reference.


container spec
--------------

Let's look at this section first.  Here you must specify the ``name``, ``image``
and ``command``.  The name determines the Pod Id (the job name in HPC parlance).

``working_dir`` is the working directory of the container. This is optional as
a container may specify this.  ``restart_policy`` is also optional and is Never
by default.

Next you can specify additional environment variables in ``env``. 

.. code-block:: yaml

  container:
    name: "jupyter"
    image: "docker-registry.osc.edu/ondemand/scipy-notebook:python-3.9.2"
    command: "/usr/local/bin/start.sh /opt/conda/bin/jupyter notebook --config=/ood/ondemand_config.py"
    working_dir: "<%= Etc.getpwnam(ENV['USER']).dir %>"
    restart_policy: 'OnFailure'
    env:
      NB_UID: "<%= user.uid %>"
      NB_USER: "<%= user.name %>"
      NB_GID: "<%= user.group.id %>"
      HOME: "<%= user.home %>"


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

configmap
---------

A `Kubernetes configmap`_ is a way to apply configurations to a container.
In this example, we're using a configmap to generate the config file for
Jupyter.  We'll see later how we use init containers to update it, but let's
see how we initialize it.

You need to specify ``filename`` which is the name of the file. ``data`` is
the contents of the file.  ``mount_path`` is the directory in the container
the file will be mounted to.  ``files`` here is an array so you can add many
files to a single configmap.

.. code-block:: yaml

    configmap:
      files:
        - filename: "<%= configmap_filename %>"
          data: |
            c.NotebookApp.port = 8080
            c.NotebookApp.ip = '0.0.0.0'
            c.NotebookApp.disable_check_xsrf = True
            c.NotebookApp.allow_origin = '*'
            c.Application.log_level = 'DEBUG'
          mount_path: '/ood'

.. _kubernetes-mounts:

mounts
------

This example mounts the host's directory into the container.
Even though these are containers, users often want to persist
the files they work on.  This example mounts the home directory,
but could mount any project or scratch space just the same.

When mounting a host directory ``host_type`` must alwasy be Directory.
This example shows how to mount host directories and nfs storage locations.

.. code-block:: yaml

    mounts:
      - type: host
        name: home
        host_type: Directory
        path: <%= user.home %>
        destination_path: <%= user.home %>
      - type: nfs
        name: cold-storage
        server: some.nfs.host:3333
        path: /some/location
        destination_path: /some/container/location


init containers
---------------

If you're app needs some work to be done before the app itself
(the container) starts up, we provide a way to specify init containers.

We provide ``docker.io/ohiosupercomputer/ood-k8s-utils`` for some simple
reusable functionality.

You must specify a ``name``, an ``image`` and the ``command`` to be run.

.. code-block:: yaml

    init_containers:
    - name: "init-secret"
      image: "<%= utility_img %>"
      command: 
      - "/bin/save_passwd_as_secret"
      - "user-<%= user.name %>"

.. tip::
  If you're mounting a users ``$HOME`` directory into the container, you
  likely don't need init containers.  They're provided for sites & use cases
  where you're not mounting the users ``$HOME`` directory.  This example
  does both because it is just an example.

Let's walk through these init containers and what they're doing.

``init-secret`` does just that. It initialzies a `kubernetes secret`_.
``add-passwd-to-cfg`` then reads that secret and creates a salt and
sha1 of this secret (these are needed specifically for Jupyter).  Lastly
it adds a single line to our configmap, which is the ``c.NotebookApp.password``.
``add-hostport-to-cfg`` does something similar, reading the host and port
of the pod and sets the ``c.NotebookApp.base_url`` of the same configmap.

submit yml in full
------------------

.. code-block:: yaml

  # submit.yml.erb
  <%
   pwd_cfg = "c.NotebookApp.password=u\'sha1:${SALT}:${PASSWORD_SHA1}\'"
   host_port_cfg = "c.NotebookApp.base_url=\'/node/${HOST_CFG}/${PORT_CFG}/\'"

   configmap_filename = "ondemand_config.py"
   configmap_data = "c.NotebookApp.port = 8080"
   utility_img = "docker.io/ohiosupercomputer/ood-k8s-utils:v1.0.0"

   user = OodSupport::User.new
  %>
  ---
  script:
  accounting_id: "<%= account %>"
  wall_time: "<%= wall_time.to_i * 3600 %>"
  native:

    # here's the bulk of setting up the container. You'll likely need to specify all of these.
    container:
      name: "jupyter"
      image: "docker-registry.osc.edu/ondemand/scipy-notebook:python-3.9.2"
      command: "/usr/local/bin/start.sh /opt/conda/bin/jupyter notebook --config=/ood/ondemand_config.py"
      working_dir: "<%= Etc.getpwnam(ENV['USER']).dir %>"
      restart_policy: 'OnFailure'
      env:
        NB_UID: "<%= user.uid %>"
        NB_USER: "<%= user.name %>"
        NB_GID: "<%= user.group.id %>"
        HOME: "<%= user.home %>"
      port: "8080"
      cpu: "<%= cpu %>"
      memory: "<%= memory %>Gi"
    configmap:
      files:
        - filename: "<%= configmap_filename %>"
          data: |
            c.NotebookApp.port = 8080
            c.NotebookApp.ip = '0.0.0.0'
            c.NotebookApp.disable_check_xsrf = True
            c.NotebookApp.allow_origin = '*'
            c.Application.log_level = 'DEBUG'
          mount_path: '/ood'
    mounts:
      - type: host
        name: home
        host_type: Directory
        path: <%= user.home %>
        destination_path: <%= user.home %>
    init_containers:
    - name: "init-secret"
      image: "<%= utility_img %>"
      command: 
      - "/bin/save_passwd_as_secret"
      - "user-<%= user.name %>"
    - name: "add-passwd-to-cfg"
      image: "<%= utility_img %>"
      command:
      - "/bin/bash"
      - "-c"
      - "source /bin/passwd_from_secret; source /bin/create_salt_and_sha1; /bin/add_line_to_configmap \\\"<%= pwd_cfg %>\\\" <%= configmap_filename %>"
    - name: "add-hostport-to-cfg"
      image: "<%= utility_img %>"
      command:
      - "/bin/bash"
      - "-c"
      - "source /bin/find_host_port; /bin/add_line_to_configmap \\\"<%= host_port_cfg %>\\\" <%= configmap_filename %>"

.. _jupyter notebook server: http://jupyter.readthedocs.io/en/latest/
.. _bc k8s jupyter: https://github.com/OSC/bc_k8s_jupyter
.. _kubernetes pod memory: https://kubernetes.io/docs/tasks/configure-pod-container/assign-memory-resource/
.. _kubernetes pod cpu: https://kubernetes.io/docs/tasks/configure-pod-container/assign-memory-resource/
.. _kubernetes configmap: https://kubernetes.io/docs/concepts/configuration/configmap/\
.. _kubernetes secret: https://kubernetes.io/docs/concepts/configuration/secret/