.. _app-development-tutorials-passenger-apps:

Tutorials: Passenger Apps
=========================

A Passenger App is any Rack-based Ruby app, WSGI-based Python app, or Node.js app that has a “startup file” following `the convention <https://www.phusionpassenger.com/library/config/nginx/reference/#passenger_startup_file>`__ that Phusion Passenger Web Application Server instances use to start the process. OnDemand uses the `NGINX Integration mode <https://www.phusionpassenger.com/library/walkthroughs/basics/ruby/fundamental_concepts.html#multiple-integration-modes>`__ for Passenger, where NGINX and Passenger and individual web app processes all communicate using UNIX domain sockets.

At the bottom of the page is a list of tutorials for developing Passenger apps for OnDemand. In addition, all pre-installed gems used by OnDemand are available, which makes it easy for users to develop and support simple apps such as:

- sinatra
- sinatra-contrib
- erubi

The full ondemand gem rpms can be found at https://yum.osc.edu/ondemand/latest/web/el7/x86_64/, containing separate rpms for each version - no loss of dependencies due to yum update. On the webhost, users can also use the commands `source scl_source enable ondmeand` and then `gem list` to see all available gems.

.. toctree::
   :maxdepth: 2
   :caption: Tutorials

   tutorials-passenger-apps/ps-to-quota
