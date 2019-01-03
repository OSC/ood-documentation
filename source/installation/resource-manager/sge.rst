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
       adapter: "slurm"
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
  The full path to libdrmaa.so *Optional*
bin_overrides
  Replacements/wrappers for Grid Engine's job submission and control clients. *Optional*

  Supports the following clients:

  - ``qsub``
  - ``qstat``
  - ``qhold``
  - ``qrls``
  - ``qdel``

.. tip::

   DRMAA improves OOD's ability to report on the precise status of jobs. To use this feature ensure that libdrmaa.so for Grid Engine is installed or built and set the config value for ``sge_root``. It may also be necessary to set the full path for ``libdrmaa_path``. If DRMAA is not installed then OOD is unable to get a precise job status for single jobs and will only return either queued or complete.
   