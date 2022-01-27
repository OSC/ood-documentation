.. _app-development-tutorials-interactive-apps-add-matlab-copy-app:

Copy MATLAB App
===============

We will begin by first copying over a pre-built MATLAB app in production at OSC.

.. warning::

   This example MATLAB app will not work out of the box and requires each
   center to develop and maintain it themselves. The goal of this tutorial is
   to:

   - get a working MATLAB app running at your center
   - introduce you to app development and make you an Interactive App developer

#. We do all of our app development in our Open OnDemand sandbox directory. So
   we first need to create our sandbox directory:

   .. code-block:: sh

      mkdir -p "${HOME}/ondemand/dev"

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

        Notice that we are using the **system** :ref:`dashboard` to launch the
        **sandbox** Interactive App (Dashboard plugin).

#. After creating the sandbox directory navigate in your browser to::

     https://ondemand.my_center.edu/

   You should now see a *Develop* dropdown menu option in the top right of the
   :ref:`dashboard`.

#. Open up the *Develop* menu dropdown and click the link *My Sandbox Apps
   (Development)*.

#. You will navigate to a page that lists all of your sandbox apps (all the
   apps in your sandbox directory). For now click *New App* in the top left
   of the page.

#. Currently there is only one option for building new apps and that is to
   "Clone an existing app". Click the button *Clone Existing App*.

#. Now we are presented with a form that describes how we will clone the app.

     Directory name
       this is the directory that the app will be cloned to in our sandbox
       directory (must be unique)
     Git remote
       this is the link to the git repo that is cloned
     Create a new Git Project from this?
       whether we want to create a new app from this git repo

   For now fill in the form with the following values:

     Directory name
       ``bc_my_center_matlab``
     Git remote
       ``https://github.com/OSC/bc_osc_matlab.git``
     Create a new Git Project from this?
       check this!

   Then click *Submit*.

#. You should now see a details view of the MATLAB app you just created. If
   you click *Launch MATLAB* it should open a new tab with the
   following warning:

     This app requires a cluster that does not exist.

   If you see this warning message then continue on.

.. danger::

   A bug was introduced in 1.4 where an "invalid" interactive app will hide the
   Launch button in the developer views. This `was fixed in 1.5 <https://github.com/OSC/ood-dashboard/pull/435>`_.

   A work around is to manually enter the URL to the batch connect app. In this
   MATLAB tutorial, if the directory name is "bc_my_center_matlab" then the URL will be
   ``/pun/sys/dashboard/batch_connect/dev/bc_my_center_matlab``.
