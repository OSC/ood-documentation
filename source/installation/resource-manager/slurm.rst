.. _resource-manager-slurm:

Configure Slurm
===============

A YAML cluster configuration file for a Slurm resource manager on an HPC
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
       bin: "/path/to/slurm/bin"
       conf: "/path/to/slurm.conf"

with the following configuration options:

adapter
  This is set to ``slurm``.
cluster
  The Slurm cluster name. *Optional*
bin
  The path to the Slurm client installation binaries.
conf
  The path to the Slurm configuration file for this cluster. *Optional*

.. note::

   If you do not have a multi-cluster Slurm setup you can remove the ``cluster:
   "cluster1"`` line from the above configuration file.

.. warning::

   The Open OnDemand server will need the appropriate MUNGE keys (see `Slurm
   Quick Start Administrator Guide`_) for the various clusters to be able to
   status and submit batch jobs.

.. _slurm quick start administrator guide: https://slurm.schedmd.com/quickstart_admin.html
