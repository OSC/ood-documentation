.. _app-development-add-jupyter-deploy:

Deploy Jupyter App
==================

After you've confirmed you are happy with all of your app changes you can
deploy it as a System App.

.. warning::

   The following steps **MUST** be done from the OnDemand host and not another
   machine.

#. Go to your OnDemand sandbox directory:

   .. code-block:: sh

      cd ~/ondemand/dev

#. Copy the app to the system deployment location as **root**:

   .. code-block:: sh

      sudo cp -r jupyter /var/www/ood/apps/sys/.

#. In your browser navigate to the OnDemand URL and confirm you see the new app
   in the *Interactive Apps* dropdown on the :ref:`dashboard`::

     https://ondemand.my_center.edu/
