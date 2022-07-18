.. _resource-manager-torque:

Torque
======

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
     # bin_overrides:
         # qsub: "/usr/local/bin/qsub"

with the following configuration options:

adapter
  This is set to ``torque``.
host
  The host of the Torque batch server.
lib
  The path to the Torque client libraries.
bin
  The path to the Torque client binaries.
submit_host
  A different, optional host to ssh to and *then* issue commands. *Optional*
bin_overrides
  Replacements/wrappers for Torque's job submission and control clients. *Optional*

  The Torque adapter uses the foreign function interface interact with `libtorque.so` and so it is only possible to override `qsub`.

.. warning::

   The corresponding cluster's batch server will need to be configured with the
   Open OnDemand server as a valid ``submit_host`` to allow the jobs to be submitted.
