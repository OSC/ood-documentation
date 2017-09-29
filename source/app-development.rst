.. _app-development:

App Development
===============

OnDemand is made up of the platform (Apache and NGINX), Passenger apps and
plugins. Passenger apps are rack based Ruby apps, wsgi based Python web apps, or
Node.js apps that follow a convention for the app's startup file.

The Dashboard app, Shell app, and all other core apps in OnDemand are Passenger
apps that can be replaced by custom Passenger apps. Or you can create your own.


.. toctree::
   :maxdepth: 2
   :caption: App Development Guide

   app-development/enabling-development-mode
   app-development/tutorial-ps-to-quota
