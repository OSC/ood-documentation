Install Applications
====================

Now we will go through installing each of the Open OnDemand system web
applications.

Dashboard App
-------------

The `Dashboard <https://github.com/OSC/ood-dashboard>`_ is a Ruby on Rails app
that serves as a gateway for all the other Open OnDemand apps.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-dashboard.git dashboard
      cd dashboard
      scl enable git19 -- git checkout tags/v1.10.0

#. Build the app:

   .. code-block:: sh

      scl enable rh-ruby22 -- bin/bundle install --path vendor/bundle
      scl enable rh-ruby22 nodejs010 -- bin/rake assets:precompile RAILS_ENV=production
      scl enable rh-ruby22 nodejs010 -- bin/rake tmp:clear

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/dashboard

Shell App
---------

The `Shell App <https://github.com/OSC/ood-shell>`_ is a Node.js app providing
a web-based terminal.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-shell.git shell
      cd shell
      scl enable git19 -- git checkout tags/v1.1.2

#. Build the app:

   .. code-block:: sh

      scl enable git19 nodejs010 -- npm install

   .. note::

      The Shell App will attempt to ``ssh`` to the ``localhost`` by default. This
      can be changed by creating a ``.env`` file in the build/deployment directory
      with the contents:

      .. code-block:: sh

         # ./.env
         DEFAULT_SSHHOST='oakley.osc.edu'

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/shell

Files App
---------

The `Files App <https://github.com/OSC/ood-fileexplorer>`_ is a Node.js app
that provides a web-based file explorer for file uploads, downloads, editing,
renaming and copying.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-fileexplorer.git files
      cd files
      scl enable git19 -- git checkout tags/v1.3.1

#. Build the app:

   .. code-block:: sh

      scl enable git19 nodejs010 -- npm install

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/files


File Editor App
---------------

The `File Editor App <https://github.com/OSC/ood-fileeditor>`_ is a Ruby on
Rails app that provides a web-based file editor for opening files on the remote
machine to edit and save.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-fileeditor.git file-editor
      cd file-editor
      scl enable git19 -- git checkout tags/v1.2.3

#. Build the app:

   .. code-block:: sh

      scl enable rh-ruby22 -- bin/bundle install --path vendor/bundle
      scl enable rh-ruby22 nodejs010 -- bin/rake assets:precompile RAILS_ENV=production
      scl enable rh-ruby22 nodejs010 -- bin/rake tmp:clear

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/file-editor

Active Jobs App
---------------

The `Active Jobs App <https://github.com/OSC/ood-activejobs>`_ is a Ruby on
Rails app that displays the current status of jobs running, queued, and held on
the clusters.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-activejobs.git activejobs
      cd activejobs
      scl enable git19 -- git checkout tags/v1.3.1

#. Build the app:

   .. code-block:: sh

      scl enable rh-ruby22 -- bin/bundle install --path vendor/bundle
      scl enable rh-ruby22 nodejs010 -- bin/rake assets:precompile RAILS_ENV=production
      scl enable rh-ruby22 nodejs010 -- bin/rake tmp:clear

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/activejobs

My Jobs App
-----------

The `My Jobs App <https://github.com/OSC/ood-myjobs>`_ is a Ruby on Rails app
for creating and managing batch job jobs from templates.

#. Start in the build directory for system web applications:

   .. code-block:: sh

      cd ~/ood/src/sys

#. Clone and checkout the latest version of the app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/ood-myjobs.git myjobs
      cd myjobs
      scl enable git19 -- git checkout tags/v2.1.2

#. Build the app:

   .. code-block:: sh

      scl enable rh-ruby22 -- bin/bundle install --path vendor/bundle
      scl enable rh-ruby22 nodejs010 -- bin/rake assets:precompile RAILS_ENV=production
      scl enable rh-ruby22 nodejs010 -- bin/rake tmp:clear

#. Copy the built app to the deployment directory:

   .. code-block:: sh

      sudo mkdir -p /var/www/ood/apps/sys
      sudo cp -r . /var/www/ood/apps/sys/myjobs
