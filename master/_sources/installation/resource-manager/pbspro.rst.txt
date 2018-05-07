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
       exec: "/path/to/pbspro"

with the following configuration options:

adapter
  This is set to ``pbspro``.
host
  The host of the PBS Pro batch server.
exec
  The installation path for the PBS Pro binaries and libraries on the OnDemand
  host.
