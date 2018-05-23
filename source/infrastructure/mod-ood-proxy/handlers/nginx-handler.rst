.. _nginx-handler:

nginx_handler
=============

This handler provides the following HTTP request options:

.. http:get:: (OOD_NGINX_URI)/init

   :query redir: the URL path of the Passenger app

   Stages a Passenger application's NGINX configuration file, followed by
   restarting the user's per-user NGINX (PUN) process, and finally
   redirecting the user to the specified application.

   **Example request for Dashboard App**

   Assuming we have the following defined in the Apache configuration file:

   .. code-block:: apache

      SetEnv OOD_NGINX_URI "/nginx"
      SetEnv OOD_PUN_URI   "/pun"

   and we want to initialize the Dashboard App at ``/pun/sys/dashboard``,
   we'd make the following request:

   .. code-block:: http

      GET /nginx/init?redir=%2Fpun%2Fsys%2Fdashboard HTTP/1.1

.. http:get:: (OOD_NGINX_URI)/stop

   :query redir: the URL to redirect user to after stopping PUN

   Stops a user's PUN process and redirects the user to the URL if specified.

   **Example request**

   Assuming we have the following defined in the Apache configuration file:

   .. code-block:: apache

      SetEnv OOD_NGINX_URI "/nginx"

   and we want to stop the user's PUN followed by a redirect to the root URL,
   we'd make the following request:

   .. code-block:: http

      GET /nginx/stop?redir=%2F HTTP/1.1

.. note::

   This handler requires the :ref:`pun-proxy-handler` for redirecting the user
   to after the app's NGINX configuration file is generated.

Configuration
-------------

Configuration is handled by setting CGI environment variables within the Apache
configuration file with the following format:

.. code-block:: apache

   SetEnv ARG_FOR_LUA "value of argument"

.. envvar:: OOD_USER_MAP_CMD

   Absolute path to the script that maps the authenticated user name to the
   local user name. See :ref:`ood-auth-map`.

.. envvar:: OOD_USER_ENV

   *Optional*

   Points to the CGI environment variable that stores the authenticated user
   name if different than ``REMOTE_USER``.

.. envvar:: OOD_MAP_FAIL_URI

   *Optional*

   URL the user redirected to if we fail to map the authenticated user name to
   a local user name. If not specified then return an error message to the
   user.

.. envvar:: OOD_PUN_STAGE_CMD

   Absolute path to the script that stages the PUN processes. See
   :ref:`nginx-stage`.

.. envvar:: OOD_NGINX_URI

   The base URI that namespaces this handler from the other handlers.
   Recommended value is ``/nginx``.

.. envvar:: OOD_PUN_URI

   The base URI that namespaces the :ref:`pun-proxy-handler` from the other
   handlers. Recommended value is ``/pun``.
