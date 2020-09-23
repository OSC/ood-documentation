.. _install_ondemand_from_source:

Install OnDemand From Source
============================

OnDemand is in a Github repository located at https://github.com/osc/ondemand, and it is installed to ``/opt/ood``.

  .. code-block:: sh

    cd /opt/ood
    git init
    git remote add origin https://github.com/osc/ondemand
    git pull origin master

.. warning::

    We need to perform the ``git init`` and ``pull`` instead of a ``clone`` because ``/opt/ood`` already exists because it is created by one of the other RPMs that we have installed, and ``git`` will refuse to clone into an existing directory with contents. These directories are added:

.. list-table:: OnDemand
   :header-rows: 1

   * - Directory
     - Description
   * - mod_ood_proxy
     - Apache OnDemand Lua module
   * - nginx_stage
     - scripts to manage Per User NGINX processes
   * - ood_auth_map
     - mapping script to map authenticated user to system user
   * - ood-portal-generator
     - scripts for generating OnDemand Apache config from configuration file
   * - apps
     - directory containing all the core OnDemand apps

- Other directories such as 'packaging' are not relevant.

Now copy the apps to the deployment location:

  .. code-block:: sh

    sudo mkdir -p /var/www/ood/apps/sys
    sudo cp -r /opt/ood/apps/* /var/www/ood/apps/sys

Finally install each app's npm or gem dependencies and build static assets. In each app directory:

  .. code-block:: sh

     cd /var/www/ood/apps/sys/$APP

     # We have both Node and Rails applications, let's cover both in a single command
     sudo NODE_ENV=production RAILS_ENV=production scl enable ondemand -- bin/setup

If on an operating system without Software Collections, ensure the correct versions of NodeJS and Ruby are set in the environment when executing sudo and omit ``scl enable ondemand --``:

  .. code-block:: sh

     cd /var/www/ood/apps/sys/$APP

     # We have both Node and Rails applications, let's cover both in a single command
     sudo NODE_ENV=production RAILS_ENV=production bin/setup

Or force install the Ruby dependencies in each app directory instead of centrally with the Ruby install:

  .. code-block:: sh

     cd /var/www/ood/apps/sys/$APP

     # We have both Node and Rails applications, let's cover both in a single command
     sudo NODE_ENV=production RAILS_ENV=production BUNDLE_PATH=vendor/bundle bin/setup

