.. _resource-manager-pbspro:

Configure PBS Professional
==========================

A YAML cluster configuration file for a PBS Professional resource manager on an
HPC cluster looks like:

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
       adapter: "pbspro"
       host: "my_cluster-batch.my_center.edu"
       exec: "/opt/pbs"
      # bin_overrides:
         # qsub: "/usr/local/bin/qsub"
         # qselect: ""
         # qstat: ""
         # qhold: ""
         # qrls: ""
         # qdel: ""

with the following configuration options:

adapter
  This is set to ``pbspro``.
host
  The host of the PBS Pro batch server.
exec
  The installation path for the PBS Pro executables and libraries on the OnDemand
  host. For default installs from Github RPM releases this value should be ``/opt/pbs``.
bin_overrides
  Replacements/wrappers for PBSPro's job submission and control clients. *Optional*

  Supports the following clients:

  - `qsub`
  - `qselect`
  - `qstat`
  - `qhold`
  - `qrls`
  - `qdel`
