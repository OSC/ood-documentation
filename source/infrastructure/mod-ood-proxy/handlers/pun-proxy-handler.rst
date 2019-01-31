.. _pun-proxy-handler:

pun_proxy_handler
=================

This handler proxies a user's traffic to his/her backend PUN listening on a
protected Unix domain socket. If the user's PUN is down, then this handler will
attempt to start up their PUN process.

.. note::

   This handler requires the :ref:`nginx-handler` to initialize an app's NGINX
   configuration file if the app does not exist in the backend PUN.

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

.. envvar:: OOD_PUN_SOCKET_ROOT

   Absolute path to the directory that contains the user directories with the
   corresponding Unix domain socket files. Under a default installation this
   should be ``/var/run/ondemand-nginx``.

.. envvar:: OOD_PUN_MAX_RETRIES

   Maximum number of attempts to start up a user's PUN before giving up and
   displaying an error to the user. Recommended value is ``5``.

.. envvar:: OOD_NGINX_URI

   The base URI that namespaces the :ref:`nginx-handler` from the other
   handlers. Recommended value is ``/nginx``.
