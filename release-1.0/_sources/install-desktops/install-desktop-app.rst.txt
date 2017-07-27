.. _install-desktops-install-desktop-app:

Install Desktop App
===================

Now we will install the provided `bc_desktop`_ app as well as configure it work at your center.

#. We will build this app in our previous web applications setup directory
   (discussed in :ref:`install-apps`):

   .. code-block:: sh

      cd ~/ood/src/apps/

#. By default this app is not built and installed with all the other required
   OOD apps. You will need to build this app explicitly with:

   .. code-block:: sh

      scl enable rh-ruby22 nodejs010 git19 -- rake build:bc_desktop

   .. note::

      The Desktop App is an **optional** app and will not be built and
      installed when you call:

      .. code-block:: sh

         scl enable rh-ruby22 nodejs010 git19 -- rake
         sudo scl enable rh-ruby22 -- rake install

      Instead you need to explicitly build and install it to prevent you from
      installing an app that is not properly configured for your users:

      .. code-block:: sh

         scl enable rh-ruby22 nodejs010 git19 -- rake build:bc_desktop
         sudo scl enable rh-ruby22 -- rake install:bc_desktop

#. We now must configure Desktop apps for each cluster you want this to run
   under in the following directory ``local/``

   .. code-block:: sh

      # Make the `local/` directory if it doesn't already exist
      mkdir local

      # Change our working directory to `local/`
      cd local

#. For each cluster we want to launch a Desktop session on we will need a corresponding
   form configuration file in YAML format (e.g., ``cluster1.yml``, ``cluster2.yml``, ...) that
   looks like:

   .. code-block:: yaml

      # bc_desktop/local/cluster1.yml
      ---
      title: "Cluster1 Desktop"
      cluster: "cluster1"        # must correspond to a cluster config

   where the ``cluster`` attribute must match a valid cluster configuration
   file.

   .. danger::

      Please do not modify any of the code above the ``local/`` path as it may
      put the Git repo in a bad state.

      We recommend you version all the changes you make in the ``local/``
      directory you use for the `bc_desktop`_ app so that you don't lose any of
      it.

#. Install the Desktop App to its system location at ``/var/www/ood/apps/sys``
   with:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install:bc_desktop

#. Navigate to your OnDemand site, in particular the Dashboard App, and you
   should see in the top dropdown menu "Interactive Apps" => "Cluster1
   Desktop".

   After choosing "Cluster1 Desktop" from the menu, you should be presented
   with a form to submit a Desktop session to the given cluster.

   Submit a Desktop session and wait for it to run. If you see a Desktop session start Running
   but then quickly disappear you can debug it by viewing the logs in::

     ~/ondemand/data/sys/dashboard/batch_connect/sys/bc_desktop/<cluster>/output/<uuid>/

   where ``uuid`` is a randomly generated id for a single Desktop session. You
   might want to find the latest one by looking at the timestamps.

   .. warning::

      The form may fail to submit due to the defaults we chose for a given
      resource manager: Torque, Slurm, LSF, PBS Pro... Please continue to the
      next section to learn how to customize batch job submission.

.. _bc_desktop: https://github.com/OSC/bc_desktop/
