.. _resource-manager-torque:

Configure Torque
================

A YAML cluster configuration file for a Torque/PBS resource manager on an HPC
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
       adapter: "torque"
       host: "my_cluster-batch.my_center.edu"
       lib: "/path/to/torque/lib"
       bin: "/path/to/torque/bin"

with the following configuration options:

adapter
  This is set to ``torque``.
host
  The host of the Torque batch server.
lib
  The path to the Torque client libraries.
bin
  The path to the Torque client binaries.

.. warning::

   The corresponding cluster's batch server will need to be configured with the
   Open OnDemand server as a valid ``submit_host`` to allow the
   :ref:`job-composer` to submit jobs to it.
