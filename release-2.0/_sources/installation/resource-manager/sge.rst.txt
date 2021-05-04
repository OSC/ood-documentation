.. _resource-manager-sge:

Configure Grid Engine
=====================

A YAML cluster configuration file for a Grid Engine (Sun Grid Engine, Son of Grid Engine, Univa Grid Engine) resource manager on an HPC
cluster looks like:

.. code-block:: yaml
   :emphasize-lines: 8-

   # /etc/ood/config/clusters.d/my_cluster.yml
   ---
   v2:
     metadata:
       title: "My Cluster"
     login:
       host: "my_cluster.my_center.edu"
     job:
       adapter: "sge"
       cluster: "my_cluster"
       bin: "/usr/lib/gridengine"
       conf: "/etc/default/gridengine"
       sge_root: "/var/lib/gridengine"
       libdrmaa_path: "/var/lib/gridengine/drmaa/libdrmaa.so"
       # bin_overrides:
         # qsub: "/usr/local/bin/qsub_wrapper"
         # qstat: ""
         # qhold: ""
         # qrls: ""
         # qdel: ""

with the following configuration options:

adapter
  This is set to ``sge``.
cluster
  The Grid Engine cluster name. *Optional*
bin
  The path to the Grid Engine client installation binaries.
sge_root
  The path to the root directory of the Grid Engine installation. *Default:* ``/var/lib/gridengine``
conf
  The path to the Grid Engine configuration file for this cluster. *Optional*
libdrmaa_path
  The full path to libdrmaa.so. Provide this to enable use of libdrmaa for more precise job status reporting.  *Optional*
bin_overrides
  Replacements/wrappers for Grid Engine's job submission and control clients. *Optional*

  Supports the following clients:

  - ``qsub``
  - ``qstat``
  - ``qhold``
  - ``qrls``
  - ``qdel``

.. tip::

   DRMAA improves OnDemand's ability to report on the precise status of jobs. To use this feature ensure that libdrmaa.so for Grid Engine is installed or built and set the config value for ``libdrmaa_path`` and ``sge_root``. If DRMAA is not installed then OnDemand is unable to get a precise job status for single jobs and will only return either queued or complete.

Common Issues
-------------

Shell environments
******************

You may run into an error similar to this where the script running is using a BASH process
substitution and there's a syntax error.

  .. code-block:: text

    /export/uge/some/file: line 156: syntax error near unexpected token <' /export/uge/some/file:
    line 156: done < <(tail -f --pid=${SCRIPT_PID} “vnc.log”) &’

What you'll need to do is add a ``script_wrapper`` element to your clusters' configuration like below.
This sets the sh shell to behave like bash and ensures you've sourced your users' bashrc file.

  .. code-block:: yaml

    # /etc/ood/config/clusters.d/my_cluster.yml
    # (other elements removed for brevity)
    ---
    v2:
      batch_connect:
        basic:
          script_wrapper: |
            set +o posix
            . ~/.bashrc
            %s
        vnc:
          script_wrapper: |
            set +o posix
            . ~/.bashrc
            %s

Invalid Job name
****************
If you encounter an issue in running batch connect applications complaining about invalid
job names like the error below.

``Unable to read script file because of error: ERROR! argument to -N option must not contain /``

You'll need to configure illegal job name characters as described
:ref:`here <set-illegal-job-name-characters>`.