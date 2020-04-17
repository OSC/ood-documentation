.. _node-proxy-handler:

node_proxy_handler
==================

This handler proxies an authenticated user's traffic to a backend node running
a web server through an IP socket. A typical request follows the following
format:

.. http:get:: (base_uri)/(host)/(port)/...

   Proxies traffic to the web server running on ``host`` and ``port``.

The actual URI request path can be altered depending on how you define this
handler in the Apache configuration file. There are two possibilities:

#. To proxy the full URI request path to the web server you would define a
   ``LocationMatch`` container in the Apache configuration file as such:

   ::

      <LocationMatch ^/node/(?<host>[^]+)/(?<port>\d+)>
        ...

        LuaHookFixups node_proxy.lua node_proxy_handler
      </LocationMatch>

   This will take the following request:

   .. code-block:: http

      GET /node/host001.hpc.edu/5000/index.html HTTP/1.1
      Host: ondemand.hpc.edu

   and generate a request to the backend web server as:

   .. code-block:: http

      GET /node/host001.hpc.edu/5000/index.html HTTP/1.1
      Host: host001.hpc.edu

   .. warning::

      The backend web server must be dynamically configured to handle requests
      with the host and port in the URI request path. It will never receive
      requests at the root URI (e.g., ``/index.html``)

#. To proxy **only** the relevant portion of the URI request path to the web
   server you would define a ``LocationMatch`` container in the Apache
   configuration file as such:

   ::

      <LocationMatch "^/rnode/(?<host>[^]+)/(?<port>\d+)(?<uri>/.*|)">
        ...

        LuaHookFixups node_proxy.lua node_proxy_handler
      </LocationMatch>

   Note the inclusion of the regular expression named group ``uri``. This is
   what is sent in the URI request path to the backend web server. So a request
   to:

   .. code-block:: http

      GET /rnode/host001.hpc.edu/5000/index.html HTTP/1.1
      Host: ondemand.hpc.edu

   will generate a request to the backend web server as:

   .. code-block:: http

      GET /index.html HTTP/1.1
      Host: host001.hpc.edu

   .. warning::

      The backend web server must be configured so that all assets and links
      must be relative links. An absolute link to ``/assets/stylesheet.css``
      will break because the frontend proxy cannot handle this request.

.. warning::

   For added security it is **recommended** that you replace the above ``host``
   regular expression named group with a more secure regular expression. For
   example:

   ::

      <LocationMatch "^/node/(?<host>[\w.-]+\.hpc\.edu)/(?<port>\d+)">
        ...

        LuaHookFixups node_proxy.lua node_proxy_handler
      </LocationMatch>

   This will only allow proxying to backend web servers within your internal
   network.

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

.. envvar:: MATCH_HOST

   This is typically set within an Apache ``LocationMatch`` container using the
   regular express named group ``host``. This corresponds to the host address
   that the user's traffic is proxied to.

.. envvar:: MATCH_PORT

   This is typically set within an Apache ``LocationMatch`` container using the
   regular express named group ``port``. This corresponds to the port number
   that the user's traffic is proxied to.

.. envvar:: MATCH_URI

   *Optional*

   This is typically set within an Apache ``LocationMatch`` container using the
   regular express named group ``uri``. This is the URI request path passed to
   the backend web server. If this is not specified then the full original URI
   request path is passed instead.
