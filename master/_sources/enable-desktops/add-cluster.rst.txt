.. _enable-desktops-add-cluster:

Add a Cluster
=============

We now need to add this cluster as a Desktop option in the Interactive Apps
list. All customization is done underneath the root directory
:file:`/etc/ood/config/apps/bc_desktop` which requires escalated privileges to
modify.

#. Start by creating the working directory:

   .. code-block:: console

      $ mkdir -p /etc/ood/config/apps/bc_desktop

#. For *each* cluster that we want to launch a Desktop session on we will need
   a corresponding :ref:`app-development-interactive-form` configuration file
   in YAML format located in this directory.

   Assuming we want to launch a desktop on OSC's Oakley cluster we would have:

   .. code-block:: yaml

      # /etc/ood/config/apps/bc_desktop/oakley.yml
      ---
      title: "Oakley Desktop"
      cluster: "oakley"

   .. warning::

      The ``cluster`` attribute above **MUST** match a valid cluster
      configuration file located underneath
      :file:`/etc/ood/config/clusters.d/`.

#. Navigate to your OnDemand site, in particular the Dashboard App, and you
   should see in the top dropdown menu "Interactive Apps" ⇒ "Oakley Desktop"
   (or whatever you set as the ``title``).

   After choosing "Oakley Desktop" from the menu, you should be presented with
   a form to "Launch" a Desktop session to the given cluster.

   Most likely if you click "Launch" it will fail miserably. That is because we
   will need to configure the submission parameters for cluster's resource
   manager.

   .. note::

      If by some chance when you click "Launch" and it actually successfully
      submits a job to your cluster, it is **highly** recommended that you
      click the link under "Session ID:". This will open the :ref:`files`
      underneath the working directory of the batch job. This will allow you to
      read all the logs generated to help debug any issues that may crop up.
