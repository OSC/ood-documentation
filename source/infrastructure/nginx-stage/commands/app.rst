.. _nginx-stage-app:

nginx_stage app
===============

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

Default Installation
....................

:numref:`app-mapping-table` details the mapping between the requested URL path
to the app root directory for in the NGINX app config under a default
installation.

.. _app-mapping-table:
.. list-table:: Mapping of apps for a default installation
   :header-rows: 1

   * - App type
     - URL path
     - File system path
   * - dev
     - :file:`/dev/{app_name}/\*`
     - :file:`~{user}/ondemand/dev/{app_name}`
   * - usr
     - :file:`/usr/{app_owner}/{app_name}/\*`
     - :file:`/var/ww/ood/apps/usr/{app_owner}/gateway/{app_name}`
   * - sys
     - :file:`/sys/{app_name}/\*`
     - :file:`/var/www/ood/apps/sys/{app_name}`
