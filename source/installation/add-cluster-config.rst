.. _add-cluster-config:

Add Cluster Configuration Files
===============================

Cluster configuration files describe each cluster a user may submit jobs to and login hosts the user can ssh to. Without cluster config files, the only
apps that work are the :ref:`dashboard` and :ref:`files` apps, and :ref:`shell` if you only want to support ssh to localhost on the web host.

Apps that require proper cluster configuration include:

- :ref:`shell` (connect to a cluster login node from the Dashboard App)
- :ref:`active-jobs` (view a list of active jobs for the various clusters)
- :ref:`job-composer` (submit jobs to various clusters)
- All interactive apps such as Jupyter and RStudio

The cluster config files are where the :ref:`resource-manager` configuration goes, which is necessary for enabling apps to submit batch jobs.

#. Create the default directory that the cluster configuration files reside
   under:

   .. code-block:: sh

      sudo mkdir -p /etc/ood/config/clusters.d

#. Create a cluster YAML configuration file for each HPC cluster you want to
   provide access to. They must have the ``*.yml`` extension.

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
   :ref:`active-jobs` and the :ref:`job-composer` won't be able to list or submit
   jobs without a defined resource manager.

   See :ref:`resource-manager` for how to modify the cluster config so OnDemand works with your particular resource manager.

.. toctree::
   :maxdepth: 1
   :caption: Cluster Config

   cluster-config-schema

