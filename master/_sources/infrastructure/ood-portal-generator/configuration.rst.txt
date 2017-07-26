.. _ood-portal-generator-configuration:

Configuration
=============

Relying on the default build is fine for a demo deployment, but it is not
recommended for a production environment. Options can be configured by
including a file called ``config.yml`` with your configuration settings in the
root directory before running :program:`rake`.

This project includes a good starting configuration file that you can use:

.. code-block:: sh

   cp config.default.yml config.yml

All the default options are listed in this configuration file. Feel free to
read it through before continuing on.

Configure General Options
-------------------------

.. describe:: listen_addr_port (String, Array<String>, null)

     the address and port server listens on for connections

     Default
       Don't add a ``Listen`` directive in this Apache config (typically it
       exists in another config)

       .. code-block:: yaml

          listen_addr_port: null

     Example
       Explicitly listen on port 443

       .. code-block:: yaml

          listen_addr_port: "443"

.. describe:: servername (String, null)

     the host name used to access the Open OnDemand portal

     Default
       Access website through IP address only

       .. code-block:: yaml

          servername: null

     Example
       Access website through the host name ``www.example.com``

       .. code-block:: yaml

          servername: "www.example.com"

.. describe:: port (Integer, null)

     the port used to access the Open OnDemand portal (if different than ``80``
     or ``443``)

     Default
       Use port ``80`` or port ``443`` if SSL is enabled

       .. code-block:: yaml

          port: null

     Example
       Use a higher numbered port to access the website

       .. code-block:: yaml

          port: 8080

.. describe:: ssl (Array<String>, null)

     a list of Apache directives that enable SSL support


     Default
       Disable SSL support

       .. code-block:: yaml

          ssl: null

     Example
       See :ref:`add-ssl-support`

.. describe:: logroot (String)

     the root directory where log files are stored (can be relative to
     ``ServerRoot``)

     Default
       Store logs in ``$ServerRoot/logs`` directory

       .. code-block:: yaml

          logroot: "logs"

     Example
       Store logs in a different directory

       .. code-block:: yaml

          logroot: "/path/to/my/logs"

.. describe:: lua_root (String)

     the root directory where the Lua handler code resides

     Default
       Point to the install location of :ref:`mod-ood-proxy`

       .. code-block:: yaml

          lua_root: "/opt/ood/mod_ood_proxy/lib"

     Example
       Point to a different directory

       .. code-block:: yaml

          lua_root: "/path/to/lua/handlers"

.. describe:: lua_log_level (String, null)

     the verbosity of the Lua module in the logs

     Default
       Use default log level of ``warn``

       .. code-block:: yaml

          lua_log_level: null

     Example
       Increase verbosity

       .. code-block:: yaml

          lua_log_level: "info"

.. describe:: user_map_cmd (String)

     the system command used to map authenticated user name to a system user
     name

     Default
       Use :ref:`ood-auth-map` and echo back the authenticated user name as
       the system user name

       .. code-block:: yaml

          user_map_cmd: "/opt/ood/ood_auth_map/bin/ood_auth_map.regex"

     Example
       Capture system user name from regular expression

       .. code-block:: yaml

          user_map_cmd: "/opt/ood/ood_auth_map/bin/ood_auth_map.regex --regex='^(\\w+)@example.com'"

.. describe:: map_fail_uri (String, null)

     the URI a user is redirected to if we fail to map the authenticated user
     name to a system user name

     Default
       Don't redirect the user and just display an error message

       .. code-block:: yaml

          map_fail_uri: null

     Example
       Redirect the user to a registration page you set up beforehand

       .. code-block:: yaml

          map_fail_uri: "/register"

.. describe:: pun_stage_cmd (String)

     the system command used to launch the :ref:`nginx-stage` command with
     :program:`sudo` privileges

     Default
       Use default install location

       .. code-block:: yaml

          pun_stage_cmd: "sudo /opt/ood/nginx_stage/sbin/nginx_stage"

     Example
       Use a different install location

       .. code-block:: yaml

          pun_stage_cmd: "sudo /path/to/nginx_stage"

.. describe:: auth (Array<String>)

     the list of Apache directives defining how authentication is handled for
     various protected resources on the website

     Default
       Use basic authentication with a plain-text password file (see
       :ref:`default-authentication`)

       .. code-block:: yaml

          auth:
            - "AuthType Basic"
            - "AuthName \"private\""
            - "AuthUserFile \"/opt/rh/httpd24/root/etc/httpd/.htpasswd\""
            - "RequestHeader unset Authorization"
            - "Require valid-user"

     Example
       See:

       - :ref:`add-ldap-authentication`
       - :ref:`add-shibboleth-authentication`
       - :ref:`add-cilogon-authentication`

.. describe:: root_uri (String)

     the URI a user is redirected to when they access the root of the website
     (e.g., ``https://www.example.com/``)

     Default
       Redirect the user to the :ref:`dashboard`

       .. code-block:: yaml

          root_uri: "/pun/sys/dashboard"

     Example
       Redirect to a different URI

       .. code-block:: yaml

          root_uri: "/my_uri"

.. describe:: analytics (Hash, null)

     the object describing how to track server-side analytics with a Google
     Analytics account and property

     Default
       Do not track analytics

       .. code-block:: yaml

          analytics: null

     Example
       See :ref:`add-google-analytics`

Configure Public Assets
-----------------------

This is a location where files can be served without a user being
authenticated. Useful to serve favicon, images, or user documentation. If
either of these properties are ``null`` then users won't be able to access
public assets through the website.

.. describe:: public_uri (String, null)

     the URI used to access public assets (no authentication needed)

     Default
       Access as ``http://www.example.com/public``

       .. code-block:: yaml

          public_uri: "/public"

     Example
       Access under a different URI

       .. code-block:: yaml

          public_uri: "/assets"

.. describe:: public_root (String, null)

     the root directory where the public assets are served from

     Default
       Using a default installation

       .. code-block:: yaml

          public_root: "/var/www/ood/public"

     Example
       Serve files under a different directory

       .. code-block:: yaml

          public_root: "/path/to/public/files"

Configure Logout Redirect
-------------------------

The :ref:`dashboard` will send the user to this URI when they click the Logout
button. This URI will then redirect the user to the logout mechanism for your
corresponding authentication mechanism. If either of these properties are
``null`` then users will get an error when they try to logout from the
:ref:`dashboard`.

.. describe:: logout_uri (String, null)

     the URI used to logout from an Apache session

     Default
       Access as ``http://www.example.com/logout``

       .. code-block:: yaml

          logout_uri: "/logout"

     Example
       Access under a different URI

       .. code-block:: yaml

          logout_uri: "/log_me_out"

.. describe:: logout_redirect (String, null)

     the URI the user is redirected to when accessing the logout URI above

     Default
       Fallback to the :ref:`dashboard` log out page

       .. code-block:: yaml

          logout_redirect: "/pun/sys/dashboard/logout"

     Example
       See:

       - :ref:`add-shibboleth-authentication`
       - :ref:`add-cilogon-authentication`

Configure Reverse Proxy
-----------------------

The reverse proxy will proxy a request to any specified host and port through
IP sockets. This is different than what is used for proxying to per-user NGINX
processes through Unix domain sockets. This can be used to connect to Jupyter
notebook servers, RStudio servers, VNC servers, and more... This is disabled by
default as it can be security risk if not properly setup using a good
``host_regex``.

A URL request to the ``node_uri`` will reverse proxy to the given ``host`` and
``port`` using the **full** URI path:

.. code-block:: sh

   http://www.example.com/<node_uri>/<host>/<port>/...
   #=> http://<host>:<port>/<node_uri>/<host>/<port>/...

A URL request to the ``rnode_uri`` will reverse proxy to the given ``host`` and
``port`` using the **relative** URI path:

.. code-block:: sh

   http://www.example.com/<rnode_uri>/<host>/<port>/...
   #=> http://<host>:<port>/...

Web server apps will have a preference for the format of the URI request they
receive, and this provides two such options. In the case of ``node_uri`` the
developer may have to program the web server to accept requests with a sub-URI
that matches ``/<node_uri>/<host>/<port>``.

.. describe:: host_regex (String)

     the regular expression used as a whitelist for allowing a user to reverse
     proxy to a given host

     Default
       Allow proxying to all hosts in the world (please change this if you
       enable this feature)

       .. code-block:: yaml

          host_regex: "[^/]+"

     Example
       Restrict access to only within internal network

       .. code-block:: yaml

          host_regex: "[\\w.-]+\\.example\\.com"

.. describe:: node_uri (String, null)

     the URI used to reverse proxy a user to a server running on a given host
     and port that knows the **full** URI path

     Default
       This feature is disabled by default

       .. code-block:: yaml

          node_uri: null

     Example
       Use the recommended URI by our team

       .. code-block:: yaml

          node_uri: "/node"

.. describe:: rnode_uri (String, null)

     the URI used to reverse proxy a user to a server running on a given host
     and port that knows the **relative** URI path

     Default
       This feature is disabled by default

       .. code-block:: yaml

          rnode_uri: null

     Example
       Use the recommended URI by our team

       .. code-block:: yaml

          rnode_uri: "/rnode"

Configure per-user NGINX
------------------------

The reverse proxy will proxy a request under the ``pun_uri`` URI to the user's
per-user NGINX (PUN) process through Unix domain sockets. It will send process
signals to the user's PUN through the ``nginx_uri`` URI. If either of these
properties are ``null`` then PUN access will be disabled.

.. describe:: nginx_uri (String, null)

     the URI used to control the PUN process

     Default
       User's can send signals to PUN through ``http://www.example.com/nginx``

       .. code-block:: yaml

          nginx_uri: "/nginx"

     Example
       Use a different URI

       .. code-block:: yaml

          node_uri: "/my_pun_controller"

.. describe:: pun_uri (String, null)

     the URI used to access the PUN process

     Default
       User's access their PUN through ``http://www.example.com/pun``

       .. code-block:: yaml

          pun_uri: "/pun"

     Example
       Use a different URI

       .. code-block:: yaml

          pun_uri: "/my_pun_apps"

.. describe:: pun_socket_root (String)

     the root directory that contains the socket files for the running PUNs

     Default
       Using a default installation

       .. code-block:: yaml

          pun_socket_root: "/var/run/nginx"

     Example
       Socket files are located in a different directory

       .. code-block:: yaml

          pun_socket_root: "/path/to/pun/sockets"

.. describe:: pun_max_retries (Integer)

     the number of times the proxy attempt to connect to the PUN before giving
     up and displaying an error to the user

     Default
       Only try 5 times

       .. code-block:: yaml

          pun_max_retries: 5

     Example
       Try 25 times

       .. code-block:: yaml

          pun_max_retries: 25

Configure OpenID Connect
------------------------

If using OpenID Connect for authentication, these are a few properties you will
need to tweak. For a better understanding of these options you should read more
on mod_auth_openidc_.

.. describe:: oidc_uri (String, null)

     the redirect URI used by mod_auth_openidc_ for authentication

     Default
       This is disabled by default

       .. code-block:: yaml

          oidc_uri: null

     Example
       Enable it on a recommended URI

       .. code-block:: yaml

          oidc_uri: "/oidc"

.. describe:: oidc_discover_uri (String, null)

     the URI a user is redirected to if they are not authenticated by
     mod_auth_openidc_ and is used to discover the ID provider the user will
     use to login through

     Default
       This is disabled by default

       .. code-block:: yaml

          oidc_discover_uri: null

     Example
       Enable it to a recommended URI

       .. code-block:: yaml

          oidc_discover_uri: "/discover"

.. describe:: oidc_discover_root (String, null)

     the root directory on the file system that serves the HTML code used for
     the discovery page

     Default
       This is disabled by default

       .. code-block:: yaml

          oidc_discover_root: null

     Example
       Enable it to the recommended path

       .. code-block:: yaml

          oidc_discover_root: "/var/www/ood/discover"

.. _mod_auth_openidc: https://github.com/pingidentity/mod_auth_openidc

Configure User Registration
---------------------------

If you are using a :program:`grid-mapfile` to map the authenticated user name
to a system user name, then this will be used to generate mappings in the file
for a user's first time accessing your website. Setting either property below
to ``null`` will disable this feature.

.. note::

   This is unnecessary if you use regular expressions for mapping the
   authenticated user name to a system user name.

.. describe:: register_uri (String, null)

     the URI a user is redirected to if no mapping exists between an
     authenticated user name and a system user name

     Default
       This is disabled by default. An error is displayed the user if mapping fails.

       .. code-block:: yaml

          register_uri: null

     Example
       Enable it to a recommended URI

       .. code-block:: yaml

          register_uri: "/register"

.. describe:: register_root (String, null)

     the root directory on the file system that serves the HTML code used for
     the registration page

     Default
       This is disabled by default. An error is displayed the user if mapping fails.

       .. code-block:: yaml

          register_root: null

     Example
       Enable it to the recommended path

       .. code-block:: yaml

          register_root: "/var/www/ood/register"
