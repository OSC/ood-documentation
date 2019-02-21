.. _app_sharing:

App Sharing
=============

Overview
--------

1. System installed by admin for everyone to launch (access control via file
   permissions)
2. Source Code Sharing (share code, launch your own copy of an app). This is
   like how the Job Composer works, or how many groups collaborate when using
   HPC: they share their job scripts and code, and use their own copies to
   submit jobs.
3. Executable Sharing (peer to peer) is where a user deploys an app in their
   home directory that other users can launch. This is similar to adding to your
   PATH the bin directory of another user.

The rest of this document addresses OnDemand's support for Executable Sharing.

.. warning:: Executable sharing means the app and all its code runs as the user
             executing it, like everything else in OnDemand. User's might not
             realize this. We currently do not provide an opt in screen warning
             users that this app "will have permission to do everything on their
             behalf and act as them". As a result, you should fully trust whoever
             you enable to do share apps using executable sharing.


Demo
----

This is with two users Eric (efranz) and Bob (an0047).

Eric has a dev app "Matlab", and interactive plugin app. Eric can

1. Launch Matlab
2. View and Edit the code

.. figure:: /images/app-sharing-1.png
   :align: center



Bob (an0047) cannot see this app because it is isolated in Eric's "Sandbox"
i.e. ``~efranz/ondemand/dev/matlab``:

.. figure:: /images/app-sharing-2.png
   :align: center

If Eric shares the git repo path or URL with Bob, Bob can clone this into his
home directory if he is enabled as a developer. This is called "Source Code Sharing".

Eric can share this app with Bob by selecting "My Shared Apps" and cloning the Matlab
repo to deploy ``~efranz/ondemand/share/matlab``

.. figure:: /images/app-sharing-3.png
   :align: center

.. figure:: /images/app-sharing-4.png
   :align: center

.. figure:: /images/app-sharing-5.png
   :align: center

Now when Bob accesses the OnDemand home page he sees Eric's MATLAB app and can
launch it:

.. figure:: /images/app-sharing-6.png
   :align: center


Enabling App Sharing Dashboard
------------------------------

#. To enable App Sharing in the Dashboard, set ``OOD_APP_SHARING=1`` in
   ``/etc/ood/config/apps/dashboard/env``.
#. Set ``OOD_DASHBOARD_SUPPORT_EMAIL=your@email.edu`` to add a link to support
   for finding an app.
#. Set ``OOD_APP_CATALOG_URL=https://link.to.online/app/catalog`` to link
   externally to an advertised listing of apps available.

Enabling App Sharing in the dashboard serves two primary purposes:

1. For shared app users, provide an interface to launch those apps
2. For app developers, provide an interface to help manage shared apps

Currently this significantly changes the interface of the Dashboard. The MOTD
moves to the right of the screen and shared apps appear below the welcom logo
and text.

Before:

.. figure:: /images/app-sharing-mode-before.png
   :align: center


After:

.. figure:: /images/app-sharing-mode-after.png
   :align: center



Controlling Who Can Share and Access Apps
-----------------------------------------

Shared apps are deployed to
``/var/www/ood/apps/usr/$USERNAME/gateway/$APPNAME``. We recommend ``gateway``
be a symlink to the user's home directory at ``~username/ondemand/share`` and
by default set ``750`` permissions on ``/var/www/ood/apps/usr/$USERNAME``. This
approach has these benefits:

#. The admin as root controls who can share apps by creating root owned
   directories like ``/var/www/ood/apps/usr/efranz`` and
   ``/var/www/ood/apps/usr/an0047``.
#. The admin controls who can access that user's shared apps by setting
   permissions on this directory. Thus by setting ``750`` on
   ``/var/www/ood/apps/usr/an0047`` this ensures that an0047 can only share
   apps with users in his primary group. At times we have created a \
   supplemental group (shinyusr) and chgrp the share directory to this group so
   that the develepr can share apps with every user in this group.
#. The developer who can share apps can modify permissions on the app
   directories themselves i.e.
   ``/var/www/ood/apps/usr/an0047/gateway/customapp``
   so that only a subset of the users he could share with have access. This can
   be done through FACLs or using the same chgrp + 755 approach

In summary, to enable a new user to create shared apps, run these commands:

.. code:: sh

   # given a user efranz
   sudo mkdir -p /var/www/ood/apps/usr/efranz
   cd /var/www/ood/apps/usr/efranz
   chmod 750 .
   ln -s ~efranz/ondemand/share gateway


Known Issues
------------

This is being documented as is. There parts of this feature that work well at
OSC but may need fixed before working at another center.
