.. _dashboard:

Dashboard App
=============

`View on GitHub <https://github.com/OSC/ondemand/tree/master/apps/dashboard>`__

.. figure:: /images/dashboard-app.png
   :align: center

   Example of the Dashboard after a fresh install.

his Open OnDemand application provides a web-interface for launching the
various other Open OnDemand applications. It also provides links for managing
the session of the logged in user. This application is built with the `Ruby on
Rails`_ web application framework.

Usage
-----

This app is deployed on the OnDemand Server under the following path on the
local file system::

  /var/www/ood/apps/sys/dashboard

and can be accessed with the following browser request:

.. http:get:: /pun/sys/dashboard

   Launches the Dashboard App.

How it Works
------------

Requirements needed for the Dashboard App to work on your local HPC network:

- OnDemand Server
- Shared File System

.. _dashboard-diagram:
.. figure:: /images/dashboard-diagram.png
   :align: center

   Diagram detailing how the Dashboard App interacts with the HPC
   infrastructure.

:numref:`dashboard-diagram` details how the Dashboard App works on the local
HPC system. The user's PUN running on the OnDemand Server launches the Ruby on
Rails Dashboard app through Passenger_ as the user.

The Dashboard app scans the deployment locations on the local and shared file
systems for other Open OnDemand web applications. In particular it looks for a
`manifest.yml` under the application's root directory that describes how the
Dashboard should advertise the application. The Dashboard will then dynamically
construct its navigation menus based around these discovered applications.

.. note::

   Web applications that are protected by file system permissions will not show
   up in the Dashboard navigation menus if the current user does not have
   access to these files.


.. _ruby on rails: http://rubyonrails.org/
.. _passenger: https://www.phusionpassenger.com/
