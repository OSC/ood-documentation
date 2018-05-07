.. _nginx-stage:

nginx_stage
===========

`View on GitHub <https://github.com/OSC/nginx_stage>`__

Stages and launches the per-user NGINX (PUN) processes for individual users. It
is also responsible for staging, listing, and cleaning up web application NGINX
configuration files, as well as listing and stopping running PUNs.

To get started you will need at a minimum the following prerequisites:

- The Ruby_ language version 2.2 or newer
- The NGINX_ web server version 1.6 or newer
- The `Phusion Passenger`_ web app server version 4.0.55 or newer

Please see :ref:`install-software` on how to install the above requirements.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   nginx-stage/installation
   nginx-stage/usage
   nginx-stage/configuration

.. _ruby: https://www.ruby-lang.org/en/
.. _nginx: https://www.nginx.com/
.. _phusion passenger: https://www.phusionpassenger.com/
