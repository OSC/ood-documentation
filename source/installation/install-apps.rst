.. _install-apps:

Install Applications
====================

Now we will go through installing all of the Open OnDemand system web
applications:

- :ref:`dashboard`
- :ref:`shell`
- :ref:`files`
- :ref:`editor`
- :ref:`active-jobs`
- :ref:`my-jobs`

This is greatly simplified by the ood-apps-installer_ utility.

#. Clone and check out the latest tag for the ood-apps-installer_ utility:

   .. code-block:: sh

      cd ~/ood/src
      scl enable git19 -- git clone https://github.com/OSC/ood-apps-installer.git apps
      cd apps/
      scl enable git19 -- git checkout v0.1.1

#. Begin building the apps (may take ~15 min):

   .. code-block:: sh

      scl enable rh-ruby22 nodejs010 git19 -- rake

#. After a **successful** build, you will want to add a default SSH host that
   the :ref:`shell` will log into. It is recommended to choose one of your
   publicly accessible login nodes.

   .. code-block:: sh

      echo "DEFAULT_SSHHOST=login.my_center.edu" > build/shell/.env

   where you replace ``login.my_center.edu`` with your public login host.

#. Finally, we install the apps to their system location at
   ``/var/www/ood/apps/sys`` with:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

.. _ood-apps-installer: https://github.com/OSC/ood-apps-installer
