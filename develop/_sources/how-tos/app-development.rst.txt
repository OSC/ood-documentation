.. _app-development:

App Development
===============

OnDemand is made up of the platform (Apache and NGINX), Passenger apps and
plugins. Passenger apps are rack based Ruby apps, wsgi based Python web apps, or
Node.js apps that follow a convention for the app's startup file.

The Dashboard app, Shell app, and all other core apps in OnDemand are Passenger
apps that can be replaced by custom Passenger apps. Or you can create your own.

OnDemand's Interactive Apps are plugins that contain configuration files and a job
template for running a VNC Server or Web Server application (such as Jupyter or MATLAB)
on a compute node.


.. toctree::
   :maxdepth: 2
   :caption: App Development Guide

   app-development/enabling-development-mode
   app-development/interactive
   app-development/app-sharing
