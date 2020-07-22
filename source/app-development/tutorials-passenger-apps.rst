.. _app-development-tutorials-passenger-apps:

Tutorials: Passenger Apps
=========================

A Passenger App is any Rack-based Ruby app, WSGI-based Python app, or Node.js app that has a “startup file” following `the convention <https://www.phusionpassenger.com/library/config/nginx/reference/#passenger_startup_file>`__ that Phusion Passenger Web Application Server instances use to start the process. OnDemand uses the `NGINX Integration mode <https://www.phusionpassenger.com/library/walkthroughs/basics/ruby/fundamental_concepts.html#multiple-integration-modes>`__ for Passenger, where NGINX and Passenger and individual web app processes all communicate using UNIX domain sockets.

Below is a list of tutorials for developing Passenger apps for OnDemand. In addition, pre-installed gems make it easy for users to develop simple apps.

.. toctree::
   :maxdepth: 2
   :caption: Tutorials

   tutorials-passenger-apps/ps-to-quota
