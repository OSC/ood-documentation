.. _add-cluster-config:

Cluster Configuration
=====================

Cluster configuration files describe each cluster a user may submit jobs to and login hosts the user can ssh to.
These files detail how the system can interact with your scheduler. Without them, many of the features in 
Open OnDemand won't work - including interactive apps.

Indeed, one of the main reasons to use Open OnDemand is use your clusters interactively.

Apps that require proper cluster configuration include:

- shell (connect to a cluster login node from the Dashboard App)
- active-jobs (view a list of active jobs for the various clusters)
- job-composer (submit jobs to various clusters)
- All interactive apps such as Jupyter and RStudio


.. tip::

   We provide a `puppet module`_ and an `ansible role`_ for automating all of this configuration.


#. Create the default directory that the cluster configuration files reside
   under:

   .. code-block:: sh

      sudo mkdir -p /etc/ood/config/clusters.d

#. Create a cluster YAML configuration file for each HPC cluster you want to
   provide access to. They must have the ``.yml`` or ``.yaml`` extensions.

   .. note::

      It is best to name the file after the HPC cluster it is defining. For
      example, we added the cluster configuration file
      :file:`/etc/ood/config/clusters.d/oakley.yml` for the Oakley cluster here
      at OSC.

   The *simplest* cluster configuration file for an HPC cluster with only a login
   node and **no resource manager** looks like:

   .. code-block:: yaml

      # /etc/ood/config/clusters.d/my_cluster.yml
      ---
      v2:
        metadata:
          title: "My Cluster"
        login:
          host: "my_cluster.my_center.edu"

   Where ``host`` is the SSH server host for the given cluster.

   In production you will also want to add a resource manager. That is because the
   active-jobs and job-composer pages won't be able to list or submit
   jobs without a defined resource manager.


The :ref:`resource-manager-test` page provides directions on using a Rake task
to verify the resource manager configuration.

The :ref:`bin-overrides` provides directions on how to
provide a replacement or wrapper script for one or more of the resource manager
client binaries.

.. toctree::
   :maxdepth: 1
   :caption: Cluster Config

   cluster-config-schema
   resource-manager/torque
   resource-manager/slurm
   resource-manager/lsf
   resource-manager/pbspro
   resource-manager/sge
   resource-manager/linuxhost
   resource-manager/ccq
   resource-manager/kubernetes
   resource-manager/systemd
   resource-manager/bin-override-example
   resource-manager/test

.. _puppet module: https://forge.puppet.com/modules/osc/openondemand
.. _ansible role: https://galaxy.ansible.com/osc/open_ondemand
