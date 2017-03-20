APP
===

This command will generate a web application NGINX configuration file
and subsequently restart the NGINX process as the user.

.. code-block:: sh

   sudo nginx_stage app [OPTIONS]

.. program:: nginx_stage app

Required Options
----------------

.. option:: -u <user>, --user <user>

   The user of the per-user NGINX process.

.. option:: -r <sub_request>, --sub-request <sub_request>

   The request URI path beneath the sub-URI path.

General Options
---------------

.. option:: -i <sub_uri>, --sub-uri <sub_uri>

  The sub-URI path in the request.

.. option:: -N, --skip-nginx

   Skip execution of the per-user NGINX process.

.. note::

   The sub-URI corresponds to any reverse proxy namespace that denotes the
   request should be proxied to the per-user NGINX server (e.g., ``/pun``)

Examples
--------

To generate an app config from the request::

  http://ondemand.center.edu/pun/usr/jim/myapp/session/1

and subsequently restart the per-user NGINX process:

.. code-block:: sh

   sudo nginx_stage app --user 'bob' --sub-uri '/pun' --sub-request '/usr/jim/myapp/session/1'

To generate **only** the app config:

.. code-block:: sh

   sudo nginx_stage app --user 'bob' --sub-uri '/pun' --sub-request '/sys/dashboard' --skip-nginx

This will return the path to the app config and will not restart the
NGINX process.
