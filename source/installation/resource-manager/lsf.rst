.. _resource-manager-lsf:

Configure LSF
=============

A YAML cluster configuration file for an LSF resource manager on an HPC cluster
looks like:

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
       adapter: "lsf"
       bindir: "/path/to/lsf/bin"
       libdir: "/path/to/lsf/lib"
       envdir: "/path/to/lsf/conf"
       serverdir: "/path/to/lsf/etc"

with the following configuration options:

adapter
  This is set to ``lsf``.
bindir
  The path to the LSF client ``bin/`` directory.
libdir
  The path to the LSF client ``lib/`` directory.
envdir
  The path to the LSF client ``conf/`` directory.
serverdir
  The path to the LSF client ``etc/`` directory.

.. warning::

   Verified for only LSF 8.3 and support for LSF MultiCluster is not yet
   implemented.
