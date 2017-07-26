.. _update-apps:

Update Applications
===================

If there is an OOD update it is almost guaranteed that there will be web
application updates. So it is recommended to always perform these steps when
updating your OOD installation. The apps installation is handled by a script
that is maintained by the `ood-apps-installer`_ project.

The following steps assume you previously installed the apps following the
:ref:`install-apps` procedures.

Do I need to update?
--------------------

Most likely, **yes**.

Instructions to update
----------------------

#. Make backups of your locally installed copies of the apps. This is a
   **highly recommended** since app configuration is located underneath the
   installation directory of each app (may change in the future). So if
   something goes wrong, we don't want to lose your custom setup.

   .. code-block:: sh

      cp -r /var/www/ood/apps/sys /path/to/backup/location

   This step may take awhile but it is worth it.

   .. tip::

      If this is a development or test instance of OOD and you already version
      your custom configuration files for the various apps then you can
      probably skip this step.

   .. warning::

      The various OOD apps can support custom configuration files at:

      - ``.env.local`` (Dashboard, ActiveJobs, MyJobs)
      - ``config/initializers/ood.rb`` (Dashboard)
      - ``config/initializers/filter.rb`` (ActiveJobs)
      - ``templates/`` (MyJobs)
      - ``.env`` (Shell)
      - ``local/`` (Desktops)

      If these exist for your installation please version these at your center
      and back them up.

#. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/apps
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v1.0.0

#. Confirm that the local configuration files for the various apps exist under
   the appropriate app build directory as :file:`build/{app_dir}/...`.

#. Rebuild the apps (may take ~15 min):

   .. code-block:: sh

      scl enable rh-ruby22 nodejs010 git19 -- rake

#. Finally, we install the apps to their system location at
   ``/var/www/ood/apps/sys`` with:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

.. _ood-apps-installer: https://github.com/OSC/ood-apps-installer
