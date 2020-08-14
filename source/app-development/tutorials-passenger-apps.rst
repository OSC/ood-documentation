.. _app-development-tutorials-passenger-apps:

Tutorials: Passenger Apps
=========================

A Passenger App is any Rack-based Ruby app, WSGI-based Python app, or Node.js app that has a “startup file” following `the convention <https://www.phusionpassenger.com/library/config/nginx/reference/#passenger_startup_file>`__ that Phusion Passenger Web Application Server instances use to start the process. OnDemand uses the `NGINX Integration mode <https://www.phusionpassenger.com/library/walkthroughs/basics/ruby/fundamental_concepts.html#multiple-integration-modes>`__ for Passenger, where NGINX and Passenger and individual web app processes all communicate using UNIX domain sockets.

At the bottom of the page is a list of tutorials for developing Passenger apps for OnDemand.

In addition, all pre-installed Ruby gems used by OnDemand are available, which makes it easy for users to develop. These include:

- sinatra
- sinatra-contrib
- erubi

On the OnDemand web host, you can execute the command `source scl_source enable ondmeand` and then `gem list` to see all available gems. These gems are provided by a separate ``ondemand-gems`` rpm that is installed when you do ``yum install ondemand``. The name of the RPM includes the OnDemand release version, such as ``ondemand-gems-1.7.12-1.7.12-1.el7.x86_64.rpm``. This ensures that if you do yum update this gem will not be removed - so apps can depend on the presence of these gems.

.. toctree::
   :maxdepth: 2
   :caption: Tutorials

   tutorials-passenger-apps/ps-to-quota
