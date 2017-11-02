.. _app-development-add-jupyter-copy-app:

Copy Jupyter App
================

We will begin by first copying over a pre-built example Jupyter app.

.. warning::

   This example Jupyter app will not work out of the box and requires each
   center to develop and maintain it themselves. The goal of this tutorial is
   to:

   - get a working Jupyter app running at your center
   - introduce you to app development and make you an Interactive App developer

Steps to Copy
-------------

#. We do all of our app development in our Open OnDemand sandbox directory:

   .. code-block:: sh

      # Create the sandbox directory if it doesn't already exist
      mkdir -p ~/ondemand/dev

      # Change our working directory
      cd ~/ondemand/dev

   .. note::

      Open OnDemand looks for apps in *special* directories on the file system.
      Two types of apps in particular are **system** apps and **sandbox** apps.

      system apps
        These are apps that all users have access to and appear in the
        Dashboard dropdown menus. They are installed on the local disk with
        very permissive file permissions.

        Located on the file system under::

          /var/www/ood/apps/sys/<app_directory>

        This system app can be accessed by navigating in your browser to::

          https://ondemand.my_center.edu/pun/sys/<app_directory>

        If this is a system Interactive App (Dashboard plugin), then it can be
        accessed by navigating to::

          https://ondemand.my_center.edu/pun/sys/dashboard/batch_connect/sys/<app_directory>/session_contexts/new

      sandbox apps
        These are apps that **only** the owner of the app can access
        irrespective of file permissions. Typically you develop apps in your
        sandbox before moving them to the production system location.

        Located on the file system under::

          ${HOME}/ondemand/dev/<app_directory>

        Can be accessed by navigating in your browser to::

          https://ondemand.my_center.edu/pun/dev/<app_directory>

        Note that we just replaced ``sys`` with ``dev`` in the URL when going
        from system app to sandbox app.

        If this is a sandbox Interactive App (Dashboard plugin), then it can be
        accessed by navigating to::

          https://ondemand.my_center.edu/pun/sys/dashboard/batch_connect/dev/<app_directory>/session_contexts/new

#. Download our example Jupyter app using `git`_:

   .. code-block:: sh

      git clone https://github.com/OSC/bc_example_jupyter.git jupyter_app

#. Change our working directory:

   .. code-block:: sh

      cd jupyter_app

#. Wipe the previous `git`_ history so we have a fresh app:

   .. code-block:: sh

      rm -fr .git

#. Unlike system apps you do **not** need to install this app to another
   directory. As it is already in the *special* sandbox directory the app is
   already accessible from your browser.

.. note::

   It is recommended you version your new app using `git`_.

   .. code-block:: sh

      # Create a local repository
      git init

      # Stage all the files under app
      git add --all

      # Make your first commit
      git commit -m 'my first commit'

Verify it Works
---------------

You can now test that this app is *functional* by visiting your local OnDemand
server in your browser:

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/jupyter_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

.. note::

   By default all browsers send ``GET`` requests when navigating to a URL. The
   above block can be accessed simply by navigating to the following URL in
   your browser::

     https://ondemand.my_center.edu/pun/sys/dashboard/batch_connect/dev/jupyter_app/session_contexts/new

   Where you replace ``ondemand.my_center.edu`` with your domain.

   *Keep this link handy as you will want to access it everytime you make
   changes to the app code to test your changes.*

Notice that we have ``dev/jupyter_app`` in the above URL. This tells the
Dashboard app (which is responsible for launching these Batch Connect plugins)
to search for the app in a directory called ``jupyter_app`` in your OnDemand
sandbox directory.

.. warning::

   The app will probably display a warning about requiring a cluster. This is
   perfectly fine. Continue on to the next section to learn about customizing
   the app.

.. _git: https://git-scm.com/
