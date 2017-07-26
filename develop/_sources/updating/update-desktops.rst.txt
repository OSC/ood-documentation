.. _update-desktops:

Update Desktops
===============

The desktop app plugin is maintained by the `bc_desktop`_ project. Assuming you
previously installed with :ref:`install-desktops` you can update it with the
following directions.

Do I need to update?
--------------------

Latest version: ``v0.1.1``

You can compare this to the locally installed `bc_desktop`_ with the following
command:

.. code-block:: sh

   grep '##' /var/www/ood/apps/sys/bc_desktop/CHANGELOG.md
   #=> ## [Unreleased]
   #=> ## [0.1.1] - 2017-07-12
   #=> ### Changed
   #=> ...

where the version number should be given in the line after ``[Unreleased]``. If
the version numbers match then you can skip this update.

Instructions to update
----------------------

#. Back up this directory. If you already performed :ref:`update-apps` then you
   should have a back up of this already. In particular, the most important
   code lies in your custom configuration directory::

     /var/www/ood/apps/sys/bc_desktop/local

#. We will be re-using the `ood-apps-installer`_ utility script that we used
   previously to install the apps to handle installation/updating of the
   Desktops app. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/apps
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v0.3.0

#. Confirm that your center's local configuration files under
   ``build/bc_desktop/local/`` exist.

#. Rebuild the app:

   .. code-block:: sh

      scl enable rh-ruby22 nodejs010 git19 -- rake build:bc_desktop

#. Finally, we install the app to its system location at
   ``/var/www/ood/apps/sys/bc_desktop`` with:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install:bc_desktop

.. _bc_desktop: https://github.com/OSC/bc_desktop
.. _ood-apps-installer: https://github.com/OSC/ood-apps-installer
