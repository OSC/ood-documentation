PUN
===

This command will generate a per-user NGINX (PUN) configuration file for the
given user and subsequently launch the NGINX process as the user.

.. code-block:: sh

   sudo nginx_stage pun [OPTIONS]

.. program:: nginx_stage pun

Required Options
----------------

.. option:: -u <user>, --user <user>

   The user of the per-user NGINX process.

General Options
---------------

.. option:: -a <app_init_url>, --app-init-url <app_init_url>

   The URL the user is redirected to if app doesn't exist.

.. option:: -N, --skip-nginx

   Skip execution of the per-user NGINX process.

.. warning::

   If :option:`nginx_stage pun --app-init-url` is not specified, then the
   server will return a 503 status code when a user requests an app that
   doesn't have a corresponding NGINX configuration file.

Examples
--------

To generate a per-user NGINX environment and subsequently launch the NGINX
process:

.. code-block:: sh

   sudo nginx_stage pun --user 'bob' --app-init-url 'https://ondemand.center.edu/nginx/init?redir=$http_x_forwarded_escaped_uri'

This will add a redirect URL if the user accesses an app that doesn't have a
respective NGINX configuration file.

To generate **only** the per-user NGINX environment:

.. code-block:: sh

   sudo nginx_stage pun --user 'bob' --skip-nginx

This will return the path to the generated PUN configuration file and will not
run the NGINX process. In addition it won't add a redirect URL.
