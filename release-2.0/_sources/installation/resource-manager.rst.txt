.. _resource-manager:

Resource Manager Configuration
==============================

Below are directions on how to modify the cluster config files to work with the
resource managers for your clusters. Each cluster can be configured with a
different resource manager.

The :ref:`resource-manager-test` page provides directions on using a Rake task
to verify the resource manager configuration.

The :ref:`bin-overrides` provides directions on how to
provide a replacement or wrapper script for one or more of the resource manager
client binaries.

.. toctree::
   :maxdepth: 1
   :caption: Resource Manager Configuration

   resource-manager/torque
   resource-manager/slurm
   resource-manager/lsf
   resource-manager/pbspro
   resource-manager/sge
   resource-manager/linuxhost
   resource-manager/ccq
   resource-manager/bin-override-example
   resource-manager/test
