.. _resource-manager-linuxhost:

LinuxHost Adapter
=================

.. warning::

   This is an experimental feature right now that may change drastically in the
   future. So always revisit this documentation after upgrading OnDemand.

First Setup cgroups
********************

By default the adapter does not limit the user's CPU or memory utilization, only their "walltime". The following are two examples of ways to implement resource limits for the LinuxHost Adapter using cgroups.

Approach #1: Systemd user slices
--------------------------------

With systemd it is possible to manage the resource limits of user logins through each user's "slice_". The limits applied to a user slice are shared by all processes belonging to that user, this is not a per-job or per-node resource limit but a per-user limit. When setting the limits keep in mind the sum of all user limits is the max potential resource consumption on a single host.

First update the PAM stack to include the following line:

.. code-block:: none

   session     required      pam_exec.so type=open_session /etc/security/limits.sh

The following example of ``/etc/security/limits.sh`` is used by OSC on interactive login nodes. Adjust ``MemoryLimit`` and ``CPUQuota`` to meet the needs of your site. See ``man systemd.resource-control``

.. code-block:: bash

   #!/bin/bash
   set -e

   PAM_UID=$(id -u "${PAM_USER}")

   if [ "${PAM_SERVICE}" = "sshd" -a "${PAM_UID}" -ge 1000 ]; then
           /usr/bin/systemctl set-property "user-${PAM_UID}.slice" \
                   MemoryAccounting=true MemoryLimit=64G \
                   CPUAccounting=true \
                   CPUQuota=700%
   fi

Approach #2: libcgroup cgroups
------------------------------

The libcgroup cgroups rules and configurations are a per-group resource limit where the group is defined in the examples at ``/etc/cgconfig.d/limits.conf``. The following examples limit resources of all tmux processes launched for the LinuxHost Adapter so they all share 700 CPU shares and 64GB of RAM. This requires setting ``tmux_bin`` to a wrapper script that in this example will be ``/usr/local/bin/ondemand_tmux``.

Example of ``/usr/local/bin/ondemand_tmux``:

.. code-block:: bash

   #!/bin/bash
   exec tmux "$@"

Setup the cgroup limits at ``/etc/cgconfig.d/limits.conf``:

.. code-block:: none

   group linuxhostadapter {
           memory {
                   memory.limit_in_bytes="64G";
                   memory.memsw.limit_in_bytes="64G";
           }
           cpu {
                   cpu.shares="700";
           }
   }

Setup the cgroup rules at ``/etc/cgrules.conf``:

.. code-block:: none

   *:/usr/local/bin/ondemand_tmux memory linuxhostadapter/
   *:/usr/local/bin/ondemand_tmux cpu linuxhostadapter/

Start the necessary services:

.. code-block:: sh

   sudo systemctl start cgconfig
   sudo systemctl start cgred
   sudo systemctl enable cgconfig
   sudo systemctl enable cgred

How To Configure The Adapter
****************************

A YAML cluster configuration file for a Linux host looks like:

.. code-block:: yaml
   :emphasize-lines: 10-

   # /etc/ood/config/clusters.d/my_cluster.yml
   ---
   v2:
     metadata:
       title: "Owens"
       url: "https://www.osc.edu/supercomputing/computing/owens"
       hidden: true
     login:
       host: "owens.osc.edu"
     job:
       adapter: "linux_host"
       submit_host: "owens.osc.edu"  # This is the head for a login round robin
       ssh_hosts: # These are the actual login nodes
         - owens-login01.hpc.osc.edu
         - owens-login02.hpc.osc.edu
         - owens-login03.hpc.osc.edu
       site_timeout: 7200
       debug: true
       singularity_bin: /usr/bin/singularity
       singularity_bindpath: /etc,/media,/mnt,/opt,/run,/srv,/usr,/var,/users
       singularity_image: /opt/ood/linuxhost_adapter/centos_7.6.sif
       # Enabling strict host checking may cause the adapter to fail if the user's known_hosts does not have all the roundrobin hosts
       strict_host_checking: false  
       tmux_bin: /usr/bin/tmux

with the following configuration options:

adapter
  This is set to ``linux_host``.
submit_host
  The target execution host for jobs. May be the head for a login round robin. May also be "localhost".
ssh_hosts
  Either the submit_host again, or a list of all nodes in the round robin if one is being used.
site_timeout
  The number of seconds that a user's job is allowed to run. Distinct from the length of time that a user selects.
debug
  When set to ``true`` job scripts are written to ``$HOME/tmp.UUID_tmux`` and ``$HOME/tmp.UUID_sing`` for debugging purposes. When ``false`` those files are written to ``/tmp`` and deleted as soon as they have been read.
singularity_bin
  The absolute path to the ``singularity`` executable on the execution host(s).
singularity_bindpath
  The comma delimited list of paths to bind mount into the host; cannot simply be ``/`` because Singularity expects certain dot files in its containers' root; defaults to: ``/etc,/media,/mnt,/opt,/run,/srv,/usr,/var,/users``.
singularity_image
  The absolute path to the Singularity image used when simply PID namespacing jobs; expected to be a base distribution image with no customizations.
strict_host_checking
  When ``false`` the SSH options include ``StrictHostKeyChecking=no`` and ``UserKnownHostsFile=/dev/null`` this prevents jobs from failing to launch.
tmux_bin
  The absolute path to the ``tmux`` executable on the execution host(s).

But, Why? A User Story
**********************

As an HPC user working in ``R`` I want to be able to be able to launch RStudio so that I can use it as an IDE; because I am limited I will not run anything that takes up more than N CPUs, X memory, or Z hours.

A Non-traditional Job Launcher
******************************

The LinuxHost adapter facilitates launching jobs immediately without using a traditional scheduler or resource manager. Use cases for this non-traditional job adapter include:

- Launching desktop environments
- Launching code editors
- Using OnDemand on systems that do not have a supported scheduler installed

The adapter pieces together several common Linux/HPC technologies to achieve behavior similar to what a scheduler offers.

- ``ssh`` connects from the web node to a configured host such as a login node.
- Specially named ``tmux`` sessions offer the ability to rediscover running jobs
- ``singularity`` containerization provides a PID namespace without requiring elevated privileges that ensures that all child processes are cleaned up when the job either times out or is killed
- ``timeout`` is used to set a 'walltime' after which the job is killed
- ``pstree`` is used to detect the job's parent ``sinit`` process so that it can be killed

A Non-traditional Use of Singularity
************************************

Singularity is a containerization technology similar to Docker which can be safely used on multi-tenant systems. The LinuxHost adapter can use these containers in two different ways.

The first way to use Singularity is to simply use it as an unprivileged PID namespace. In this case most/all of the host file system is bind-mounted into the running container and the fact that the job is inside a container should not be visible. For this reason many existing BatchConnect applications will just work when launched by the LinuxHost adapter. A base CentOS image should be installed on the target compute hosts, we suggest ``/opt/ood/linuxhost_adapter/$IMAGE_NAME.sif`` but any path may be configured.

The second way to use Singularity is the designed use of containers: launch a self contained applications with only the bare minimum host directories mounted into the running container. In this method you would likely want access to application inputs, an output directory and possibly nothing else. A job's container is set by providing values for the ``native`` attribute ``singularity_container`` and ``singularity_bindpath``. In Batch Connect applications these attributes may be set in the file ``submit.yml``:


.. code-block:: yaml
   
   ---
   batch_connect:
     template: vnc
     native:
        singularity_bindpath: /etc,/media,/mnt,/opt,/run,/srv,/usr,/var,/fs,/home
        singularity_container: /usr/local/modules/netbeans/netbeans_2019.sif

.. note::

   Subsequent versions of the adapter are expected to use unshare_ for PID namespacing as the default method instead of Singularity. Singularity will continue to be supported.

.. _slice: https://www.freedesktop.org/software/systemd/man/systemd.slice.html
.. _unshare: man7.org/linux/man-pages/man1/unshare.1.html
