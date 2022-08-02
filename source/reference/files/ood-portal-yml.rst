.. _ood-portal-generator-configuration:

ood_portal.yml
==============

Relying on the default build is fine for a demo deployment, but it is not
recommended for a production environment. Options can be configured by default
under the file :file:`/etc/ood/config/ood_portal.yml`.

The RPMs copy this file from ``/opt/ood/ood-portal-generator/ood_portal_example.yml``
during the installation.

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

.. _ood-portal-generator-servername:
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

.. describe:: proxy_server (String, null)

  The proxy server, if one exists. Used when you have a proxy
  in front of the Open OnDemand server(s).

  Default
    No proxy server

    .. code-block:: yaml

      proxy_server: null

  Example
    Access website through the proxy name ``www.example-proxy.com``

    .. code-block:: yaml

      proxy_server: "www.example-proxy.com"

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
       
       .. code-block:: yaml

         ssl:
            - SSLCertificateFile /etc/letsencrypt/live/change-me/cert.pem
            - SSLCertificateKeyFile /etc/letsencrypt/live/change-me/privkey.pem
            - SSLCertificateChainFile /etc/letsencrypt/live/change-me/chain.pem


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

.. describe:: errorlog (String, 'error.log')

  The Error log filename

  Default
    "error.log"

    .. code-block:: yaml

      errorlog: "error.log"

  Example
    "my.site.error.log"

    .. code-block:: yaml

      errorlog: "my.site.error.log"

.. describe:: accesslog (String, 'access.log')

  The Access log filename

  Default
    "access.log"

    .. code-block:: yaml

      accesslog: "access.log"

  Example
    "my.site.access.log"

    .. code-block:: yaml

      accesslog: "my.site.access.log"

.. describe:: logformat (String, apache conbined format)

  The log format.

  Default
    apache combined format

    .. code-block:: yaml

      logformat: null

  Example
    Change the error and access log format.

    .. code-block:: yaml

      logformat: '"%v %h \"%r\" %>s %O \"%{Referer}i\" \"%{User-Agent}i\" %{SSL_PROTOCOL}x %T"'

.. describe:: use_rewrites (Boolean)

     Should RewriteEngine be used

     Default
       Use RewriteEngine

       .. code-block:: yaml

          use_rewrites: true

     Example
       Disable RewriteEngine usage

       .. code-block:: yaml

          use_rewrites: false

.. describe:: use_maintenance (Boolean)

     Enable Rewrite rules for supporting maintenance mode of OnDemand
     Requires `use_rewrites` to be `true`

     Default
       Support maintenance mode support

       .. code-block:: yaml

          use_maintenance: true

     Example
       Disable maintenance mode support

       .. code-block:: yaml

          use_maintenance: false

.. describe:: maintenance_ip_whitelist (Array<String>)

     List of IP regular expressions to be allowed to access OnDemand
     when maintenance is enabled

     Default
       No IPs are whitelisted

       .. code-block:: yaml

          maintenance_ip_whitelist: []

     Example
       Allow 192.168.1.0/24 and 10.0.0.1 to access OnDemand during maintenance

       .. code-block:: yaml

          maintenance_ip_whitelist:
            - '192.168.1..*'
            - '10.0.0.1'

.. describe:: security_csp_frame_ancestors (Boolean)

     Set Header Content-Security-Policy frame-ancestors.

     Default
       Set Content-Security-Policy frame-ancestors to servername

       .. code-block:: yaml

           security_csp_frame_ancestors: https://ondemand.example.com

     Example
       Disable Content-Security-Policy header

       .. code-block:: yaml

          security_csp_frame_ancestors: false

.. describe:: security_strict_transport (Boolean)

     Set Header Strict-Transport-Security to help enforce SSL

     Default
       Set Strict-Transport-Security if SSL is defined for OnDemand

       .. code-block:: yaml

           security_strict_transport: true

     Example
       Disable Strict-Transport-Security header

       .. code-block:: yaml

          security_strict_transport: false

.. describe:: lua_root (String)

     the root directory where the Lua handler code resides

     Default
       Point to the install location of the ood_mod_proxy lua library

       .. code-block:: yaml

          lua_root: "/opt/ood/mod_ood_proxy/lib"

     Example
       Point to a different directory

       .. code-block:: yaml

          lua_root: "/path/to/lua/handlers"

.. _ood-portal-generator-lua-log-level:
.. describe:: lua_log_level (String, null)

     the verbosity of the Lua module in the logs

     Default
       Use default log level of ``info``

       .. code-block:: yaml

          lua_log_level: null

     Example
       Decrease verbosity

       .. code-block:: yaml

          lua_log_level: "warn"

.. _ood-portal-generator-user-map-cmd:
.. describe:: user_map_cmd (String)

     the system command used to map authenticated user name to a system user
     name

     Default
       Since 2.0 there is no provided user map command.

       .. code-block:: yaml

          user_map_cmd: null

     Example
       Capture system user name from regular expression

       .. code-block:: yaml

          user_map_cmd: "/opt/site/site_mapper.sh"

.. _ood-portal-generator-user-map-match:
.. describe:: user_map_match (String)

   The lua pattern to map authenticated user name to a system user
   name.

   ``user_map_match`` was added in 2.0 to be a simpler replacement
   for ``user_map_cmd`` above. match has precedence over cmd if they're both
   configured.

   Note that lua patterns are not regular expressions. So boolean OR matches
   like ``|`` for example are not supported. See the `documentation on lua patterns`_
   for details more.

   You can test your configuration out in a lua shell like so:

   .. code-block:: lua

      > string.match('ktrout@example.edu', '^([^@]+)@example.edu$')
      ktrout

   Default
      Match any characters 0 or more times.

   .. code-block:: yaml

      user_map_match: '.*'

   Example
      Capture system user name from email pattern.

   .. code-block:: yaml

      user_map_match: '^([^@]+)@example.edu$'

.. _ood-portal-generator-user-env:
.. describe:: user_env (String, null)

     the CGI environment variable that holds the authenticated user name used
     as the argument for the user mapping command

     Default
       Use ``REMOTE_USER`` if not defined

       .. code-block:: yaml

          user_env: null

     Example
       Use a custom environment variable instead

       .. code-block:: yaml

          user_env: "OIDC_CLAIM_preferred_username"

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

     the system command used to launch the :ref:`nginx stage <nginx-stage-usage>` command with
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

    The list of Apache directives defining how authentication is handled for
    various protected resources on the website. See :ref:`authentication` for
    more details.

    Default
      Empty. No authentication. Open OnDemand will not work at all without authentication
      of some kind.

      .. code-block:: yaml

          auth: []

    Example
      Open ID Connect authentication.

      .. code-block:: yaml

          auth:
            - "AuthType openid-connect"
            - "Require valid-user"

.. describe:: root_uri (String)

     the URI a user is redirected to when they access the root of the website
     (e.g., ``https://www.example.com/``)

     Default
       Redirect the user to the dashboard

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
       See :ref:`google-analytics`

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

The dashboard will send the user to this URI when they click the Logout
button. This URI will then redirect the user to the logout mechanism for your
corresponding authentication mechanism. If either of these properties are
``null`` then users will get an error when they try to logout from the
dashboard.

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
       Fallback to the dashboard's log out page

       .. code-block:: yaml

          logout_redirect: "/pun/sys/dashboard/logout"

     Example
       See:

       - :ref:`authentication-shibboleth`
       - :ref:`authentication-tutorial-oidc-keycloak-rhel7-configure-cilogon`

.. _ood-portal-generator-configuration-configure-reverse-proxy:

Configure Reverse Proxy
-----------------------

The reverse proxy will proxy a request to any specified host and port through
IP sockets. This is different than what is used for proxying to per-user NGINX
processes through Unix domain sockets. This can be used to connect to Jupyter
notebook servers, RStudio servers, VNC servers, and more... This is disabled by
default as it can be security risk if not properly setup using a good
``host_regex``.

A URL request to the ``node_uri`` will reverse proxy to the given ``host`` and
``port`` using the **full** URI path. So a request to the frontend Apache
proxy that looks like:

.. code-block:: http

   GET /<node_uri>/<host>/<port>/... HTTP/1.1
   Host: ondemand.example.edu

will be reverse proxied to the backend server with the following request
format:

.. code-block:: http

   GET /<node_uri>/<host>/<port>/... HTTP/1.1
   Host: <host>:<port>

A URL request to the ``rnode_uri`` will reverse proxy to the given ``host`` and
``port`` using the **relative** URI path. So a request to the frontend Apache
proxy that looks like:

.. code-block:: http

   GET /<rnode_uri>/<host>/<port>/... HTTP/1.1
   Host: ondemand.example.edu

will be reverse proxied to the backend server with the following request
format:

.. code-block:: http

   GET /... HTTP/1.1
   Host: <host>:<port>

Notice that we strip off the portion of the URI request path that is used to
determine the backend web server.

Both formats are provided to better support the varying capabilities for the
multitude of web application servers. For the case of using ``node_uri`` the
developer will need to modify the web server to accommodate requests with a
sub-URI that follows the dynamic formatting of ``/<node_uri>/<host>/<port>``.
For the case of using ``rnode_uri`` the developer needs to confirm that all
assets and links supplied by the web server are relative and not absolute.

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

          pun_socket_root: "/var/run/ondemand-nginx"

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

.. _ood-portal-generator-pun-pre-hook:

PUN Pre Hook command is functionality to initialize things as root before
the PUN starts up.

Authentication information like OIDC tokens are not passed to OnDemand apps like
the dashboard.  This feature is useful when you need to use things like OIDC tokens
in some initialization process before the PUN starts.  For example, you can
configure your ~/.kube/config with OIDC information with this feature.

There is currently only one thing passed into this command and that is the
username. It's passed as a named argument like so: ``--user USERNAME``.

You may pass in environment variables from apache to this command, though they are
prefixed with ``OOD_``. For example if you configure this to pass ``OIDC_ACCESS_TOKEN``
to the pre hook command, you can read the variable as ``OOD_OIDC_ACCESS_TOKEN``.

Additionally you may add entries to ``/etc/ood/config/hook.env`` and source this
file for additional environment variables. For example environment specific information
for your test and production environments.

.. describe:: pun_pre_hook_root_cmd (String, null)

  Run a hook command as root before the the PUN starts up.

  Default
    No pun pre hook.

    .. code-block:: yaml

      pun_pre_hook_root_cmd: null

  Example
    Run a pre hook called "my_site_hook.sh".

    .. code-block:: yaml

      pun_pre_hook_root_cmd: "/path/to/my_site_hook.sh"

.. describe:: pun_pre_hook_exports (String, null)

  A comma seperated list of environment variables to export to the
  pun_pre_hook_root_cmd.

  Default
    Don't pass any environment variables.

    .. code-block:: yaml

      pun_pre_hook_exports: null

  Example
    Export OIDC_ACCESS_TOKEN and OIDC_CLAIM_EMAIL environment variables
    to the pun_pre_hook_root_cmd.

    .. code-block:: yaml

      pun_pre_hook_exports: "OIDC_ACCESS_TOKEN,OIDC_CLAIM_EMAIL"

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

.. _mod_auth_openidc: https://github.com/zmartzone/mod_auth_openidc

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

.. describe:: oidc_provider_metadata_url (String, null)

     Refer to OIDCProviderMetadataURL in `auth_openidc.conf`_.

     Default
       This is disabled by default, and no OIDC configurations will be added.

       .. code-block:: yaml

          oidc_provider_metadata_url: null

     Example
       Set OIDCProviderMetadataURL

       .. code-block:: yaml

          oidc_provider_metadata_url: "https://example.com:5554/.well-known/openid-configuration"

.. describe:: oidc_client_id (String, null)

     Refer to OIDCClientID in `auth_openidc.conf`_.

     Default
       This is disabled by default, and no OIDC configurations will be added.

       .. code-block:: yaml

          oidc_client_id: null

     Example
       Set OIDCClientID

       .. code-block:: yaml

          oidc_client_id: "ondemand.example.com"

.. describe:: oidc_client_secret (String, null)

     Refer to OIDCClientSecret in `auth_openidc.conf`_.

     Default
       This is disabled by default.

       .. code-block:: yaml

          oidc_client_secret: null

     Example
       Set OIDCClientSecret

       .. code-block:: yaml

          oidc_client_secret: "ondemand.example.com"

.. _ood-portal-generator-oidc-remote-user-claim:
.. describe:: oidc_remote_user_claim (String)

     Refer to OIDCRemoteUserClaim in `auth_openidc.conf`_.

     Default
       The default value is ``email`` if no Dex connectors are defined.
       If connectors are defined the default is ``preferred_username``

       .. code-block:: yaml

          oidc_remote_user_claim: "email"

     Example
       Set OIDCRemoteUserClaim

       .. code-block:: yaml

          oidc_remote_user_claim: "preferred_username"

.. describe:: oidc_scope (String)

     Refer to OIDCScope in `auth_openidc.conf`_.

     Default
       The default value is ``openid profile email``.

       .. code-block:: yaml

          oidc_scope: "openid profile email"

     Example
       Set OIDCScope

       .. code-block:: yaml

          oidc_scope: "openid profile email groups"

.. describe:: oidc_session_inactivity_timeout (Integer)

     Refer to OIDCSessionInactivityTimeout in `auth_openidc.conf`_.

     Default
       The default value is ``28800``.

       .. code-block:: yaml

          oidc_session_inactivity_timeout: 28800

     Example
       Set OIDCSessionInactivityTimeout

       .. code-block:: yaml

          oidc_session_inactivity_timeout: 57600

.. describe:: oidc_session_max_duration (Integer)

     Refer to OIDCSessionMaxDuration in `auth_openidc.conf`_.

     Default
       The default value is ``28800``.

       .. code-block:: yaml

          oidc_session_max_duration: 28800

     Example
       Set OIDCSessionMaxDuration

       .. code-block:: yaml

          oidc_session_max_duration: 57600

.. describe:: oidc_state_max_number_of_cookies (String)

     Refer to OIDCStateMaxNumberOfCookies in `auth_openidc.conf`_.

     Default
       The default value is ``10 true``.

       .. code-block:: yaml

          oidc_state_max_number_of_cookies: "10 true"

     Example
       Set OIDCStateMaxNumberOfCookies

       .. code-block:: yaml

          oidc_state_max_number_of_cookies: "20 true"

.. describe:: oidc_cookie_same_site (String)

     Refer to OIDCCookieSameSite in `auth_openidc.conf`_.

     Default
       The default value is ``On`` when SSL is disabled or ``Off`` when SSL is enabled.

       .. code-block:: yaml

          oidc_cookie_same_site: "On"

     Example
       Set OIDCCookieSameSite

       .. code-block:: yaml

          oidc_cookie_same_site: "Off"

.. describe:: oidc_settings (Hash, {})

     A Hash to supply additional OIDC settings.

     Default
       The default value is an empty Hash.

       .. code-block:: yaml

          oidc_settings: {}

     Example
       Set OIDCStateMaxNumberOfCookies

       .. code-block:: yaml

          oidc_settings:
            OIDCPassIDTokenAs: serialized
            OIDCPassRefreshToken: On

.. describe:: dex (Hash, null, false)

     The Hash to define Dex configurations.
     A value of ``false`` or ``null`` will disable Dex configuration generation.
     Refer to :ref:`OnDemand Dex configuration reference <dex-configuration>` for details.

     Default
       The default value is an empty Hash.

       .. code-block:: yaml

          dex: {}

     Example
       Disable Dex configuration management

       .. code-block:: yaml

          dex: false

.. _auth_openidc.conf: https://github.com/zmartzone/mod_auth_openidc/blob/master/auth_openidc.conf
.. _documentation on lua patterns: https://www.lua.org/manual/5.1/manual.html#5.4.1