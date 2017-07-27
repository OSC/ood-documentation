.. _add-cluster-config:

Add Cluster Configuration Files
===============================

**(Optional, but recommended)**

The following apps do not require a cluster configuration file:

- :ref:`dashboard`
- :ref:`files`
- :ref:`shell` (but only launched from within the Files App)

The following apps require a cluster configuration file:

- :ref:`shell` (connect to a cluster login node from the Dashboard App)
- :ref:`active-jobs` (view a list of active jobs for the various clusters)
- :ref:`my-jobs` (submit jobs to various clusters)

#. Create default directory for config files:

   .. code-block:: sh

      sudo mkdir -p /etc/ood/config/clusters.d

#. Add a cluster configuration file for each HPC cluster you want to provide
   access to. These are YAML files and must have the ``.yml`` file extension
   (e.g., ``cluster1.yml``, ``cluster2.yml``, ...)

Example Configs
---------------

Minimal Configuration
.....................

A YAML cluster configuration file for an HPC cluster with only a login node but
no resource manager looks like:

.. code-block:: yaml

   # /etc/ood/config/clusters.d/cluster1.yml
   ---
   v2:
     metadata:
       title: "Cluster 1"
     login:
       host: "cluster1.my_center.edu"

Where ``host`` is the SSH server host for the given cluster.

.. note::

   The :ref:`active-jobs` and the :ref:`my-jobs` won't be able to list or
   submit jobs without a resource manager.

Torque/PBS
..........

A YAML cluster configuration file for a Torque/PBS resource manager on an HPC
cluster looks like:

.. code-block:: yaml

   # /etc/ood/config/clusters.d/cluster1.yml
   ---
   v2:
     metadata:
       title: "Cluster 1"
     login:
       host: "cluster1.my_center.edu"
     job:
       adapter: "torque"
       host: "cluster1-batch.my_center.edu"
       lib: "/path/to/torque/lib"
       bin: "/path/to/torque/bin"

Where the ``adapter`` is set to ``torque`` for the job feature in the cluster
configuration file.

.. warning::

   The corresponding cluster's batch server will need to be configured with the
   Open OnDemand server as a valid ``submit_host`` to allow the :ref:`my-jobs`
   to submit jobs to it.

Slurm
.....

A YAML cluster configuration file for a Slurm resource manager on an HPC
cluster looks like:

.. code-block:: yaml

   # /etc/ood/config/clusters.d/cluster1.yml
   ---
   v2:
     metadata:
       title: "Cluster 1"
     login:
       host: "cluster1.my_center.edu"
     job:
       adapter: "slurm"
       cluster: "cluster1"
       bin: "/path/to/slurm/bin"

Where the ``adapter`` is set to ``slurm`` for the job feature in the cluster
configuration file.

.. note::

   If you do not have a multi-cluster Slurm setup you can remove the ``cluster:
   "cluster1"`` line from the above configuration file.

.. warning::

   The Open OnDemand server will need the appropriate MUNGE keys (see `Slurm
   Quick Start Administrator Guide`_) for the various clusters to be able to
   status and submit batch jobs.

.. _slurm quick start administrator guide: https://slurm.schedmd.com/quickstart_admin.html

LSF
...

A YAML cluster configuration file for an LSF resource manager on an HPC cluster
looks like:

.. code-block:: yaml

   # /etc/ood/config/clusters.d/cluster1.yml
   ---
   v2:
     metadata:
       title: "Cluster 1"
     login:
       host: "cluster1.my_center.edu"
     job:
       adapter: "lsf"
       bindir: "/path/to/lsf/bin"
       libdir: "/path/to/lsf/lib"
       envdir: "/path/to/lsf/conf"
       serverdir: "/path/to/lsf/etc"

Where the ``adapter`` is set to ``lsf`` for the job feature in the cluster
configuration file.

.. warning::

   Verified for only LSF 8.3 and support for LSF MultiCluster is not yet
   implemented.
