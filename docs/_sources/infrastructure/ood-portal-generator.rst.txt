.. _ood-portal-generator:

ood-portal-generator
====================

`View on GitHub <https://github.com/OSC/ood-portal-generator>`__

Generates an Apache configuration file that can be used for hosting an Open
OnDemand portal on the OnDemand Server.

To get started generating an Apache configuration file you will need the
following prerequisites:

- The Ruby_ language version 1.9 or newer
- The Ruby Rake_ software

Please see :ref:`software-requirements` on how to install the above
requirements.

Usage
-----

This software uses Rake_ which is a Make-like program implemented in Ruby_. So
to build a working Apache configuration file from the template, you would run:

.. code-block:: sh

   rake

This will build the following Apache configuration file::

   build/ood-portal.conf

After viewing and confirming that this Apache configuration file will meet your
OnDemand portal needs, you will run:

.. code-block:: sh

   sudo rake install

This will copy the build file to::

   /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

.. _ruby: https://www.ruby-lang.org/en/
.. _rake: https://ruby.github.io/rake/

Configuration
-------------

Relying on the default build is fine for a demo deployment, but it is not
recommended for a production environment. Options can be configured by
including a file called ``config.yml`` with your configuration settings in the
root directory before running :program:`rake`.

This project includes a good starting configuration file that you can use:

.. code-block:: sh

   cp config.default.yml config.yml

All the default options are listed in this configuration file. Feel free to
read it through before continuing on.

Add Google Analytics
~~~~~~~~~~~~~~~~~~~~

To support this project we recommend enabling Google Analytics with the
following options:

.. code-block:: yaml

   # config.yml

   analytics:
     id: UA-79331310-4
     url: "http://www.google-analytics.com/collect"

This will collect various metrics and submit them to OSC's Google Analytics
account.

Build the Apache configuration file and install it.

.. note::

   Please contact us if you'd like access to your center's Google Analytics
   data. This will require us to generate a new ``id`` for the configuration
   above.

Add SSL Support
~~~~~~~~~~~~~~~

Highly recommended for a production OnDemand Server. The SSL protocol provides
for a secure channel of communication between the user’s browser and the Open
OnDemand portal.

The following prerequisites need to be satisfied:

- The OnDemand Server will need a public facing host name, e.g., ``ondemand.my-center.edu``
- An SSL certificate associated with this host name

Then you can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   servername: ondemand.my-center.edu
   ssl:
     - "SSLCertificateFile \"/path/to/public.crt\""
     - "SSLCertificateKeyFile \"/path/to/private.key\""

Each array item is treated as a line in the Apache configuration file. You can
add more Apache `SSL directives`_ as separate array items.

Build the Apache configuration file and install it.

.. _ssl directives: https://httpd.apache.org/docs/2.4/mod/mod_ssl.html

Authentication
~~~~~~~~~~~~~~

The default :program:`ood-portal-generator` configuration sets up the Apache
configuration file to use HTTP Basic authentication to restrict access by
looking up users in plain text password files.

.. code-block:: yaml

   auth:
     - "AuthType Basic"
     - "AuthName \"private\""
     - "AuthUserFile \"/opt/rh/httpd24/root/etc/httpd/.htpasswd\""
     - "RequestHeader unset Authorization"
     - "Require valid-user"

Where the ``RequestHeader`` setting is used to strip private session
information from being sent to the backend web servers.

By default it will look up users in the following password file::

   /opt/rh/httpd24/root/etc/httpd/.htpasswd

You can read about the `basics of password files`_ for more information on
setting up this file.

.. warning::

   The user name specified in the password file must correspond to a system
   user, but the passwords need not match.

.. _basics of password files: https://httpd.apache.org/docs/2.4/howto/auth.html#gettingitworking

Add LDAP Authentication
.......................

The following prerequisites need to be satisfied:

- An LDAP server, e.g., ``ldap.my-center.edu``
- NSS configured on the OnDemand Server to look up users via LDAP
- The mod_authnz_ldap_ Apache module installed

Then you can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   auth:
     - "AuthType Basic"
     - "AuthName \"private\""
     - "AuthBasicProvider ldap"
     - "AuthLDAPURL \"ldaps://ldap.my-center.edu:636/ou=People,ou=hpc\""
     - "RequestHeader unset Authorization"
     - "Require valid-user"

Where the ``RequestHeader`` setting is used to strip private session
information from being sent to the backend web servers.

Each array item is treated as a line in the Apache configuration file. You can
add more Apache `LDAP directives`_ as separate array items.

Build the Apache configuration file and install it.

.. _mod_authnz_ldap: https://httpd.apache.org/docs/2.4/mod/mod_authnz_ldap.html
.. _ldap directives: mod_authnz_ldap_

Add Shibboleth Authentication
.............................

The following prerequisites need to be satisfied:

- A Shibboleth IdP server deployed, e.g., ``idp.my-center.edu`` (outside of
  scope of this document)
- The `Apache module for Shibboleth`_ installed on the OnDemand Server and
  properly configured with its own Apache config (outside of scope of this
  document)

.. warning::

   It is required you turn on ``ShibCompatValidUser`` in your Apache config
   when setting up the Shibboleth module for Apache above.

   .. code-block:: apache

      # /path/to/httpd/conf.d/auth_shib.conf

      #
      # Turn this on to support "require valid-user" rules from other
      # mod_authn_* modules, and use "require shib-session" for anonymous
      # session-based authorization in mod_shib.
      #
      ShibCompatValidUser On

Then you can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   # Use Shibboleth authentication
   auth:
     - "AuthType shibboleth"
     - "ShibRequestSetting requireSession 1"
     - "RequestHeader edit* Cookie \"(^_shibsession_[^;]*(;\\s*)?|;\\s*_shibsession_[^;]*)\" \"\""
     - "RequestHeader unset Cookie \"expr=-z %{req:Cookie}\""
     - "Require valid-user"

   # Use Shibboleth logou
   logout_redirect: /Shibboleth.sso/Logout?return=https%3A%2F%2Fidp.my-center.edu%2Fidp%2Fprofile%2FLogout

   # Capture system user name from authenticated user name
   user_map_cmd: "/opt/ood/ood_auth_map/bin/ood_auth_map.regex --regex='^(\\w+)@my-center.edu'"


Where:

- The ``user_map_cmd`` uses regular expressions to map the authenticated user
  ``bob@my-center.edu`` to their system user name ``bob``.
- The ``RequestHeader`` settings are used to strip private session information
  from being sent to the backend web servers.
- The ``logout_redirect`` will first redirect the user to log out of the Open
  OnDemand portal followed by redirecting the user to log out of the Shibboleth
  IdP server.

Build the Apache configuration file and install it.

.. _apache module for shibboleth: https://wiki.shibboleth.net/confluence/display/SHIB2/NativeSPApacheConfig

Add CILogon Authentication
..........................

.. danger::

   This process is fraught with problems and requires more hand holding than I
   am willing to document. If you'd like to add CILogon authentication we
   recommend you contact us.

The following prerequisites need to be satisfied:

- Registered with CILogon_ and was given a client id and secret
- The mod_auth_openidc_ Apache module version 2.0.0 or newer installed on the
  OnDemand Server
- The ood_auth_discovery_ PHP project deployed on the local file system (be
  sure to properly brand it for your center)
- The ood_auth_registration_ PHP project deployed on the local file system (be
  sure to set up LDAP connection settings as well as brand it for your center)
- The ood_auth_mapdn_ Python project deployed on the local file system (outside
  of the scope of this documentation)

The Apache configuration file for mod_auth_openidc_ will need to be set up
along the lines of:

.. code-block:: apache

   # /path/to/httpd/conf.d/auth_openidc.conf

   OIDCMetadataDir      /path/to/oidc/metadata
   OIDCDiscoverURL      https://ondemand.my-center.edu/discover
   OIDCRedirectURI      https://ondemand.my-center.edu/oidc
   OIDCCryptoPassphrase "<Chosen Passphrase>"

   # Keep sessions alive for 8 hours
   OIDCSessionInactivityTimeout 28800
   OIDCSessionMaxDuration 28800

   # Don't pass claims to backend servers
   OIDCPassClaimsAs environment

   # Strip out session cookies before passing to backend
   OIDCStripCookies mod_auth_openidc_session mod_auth_openidc_session_chunks mod_auth_openidc_session_0 mod_auth_openidc_session_1

Then you will need to add the CILogon_ IdP configuration settings in the
metadata directory you specified in the above config to the following three
files:

#. ``/path/to/oidc/metadata/cilogon.org.provider``

   .. code-block:: json

      {
        "issuer": "https://cilogon.org",
        "authorization_endpoint": "https://cilogon.org/authorize",
        "token_endpoint": "https://cilogon.org/oauth2/token",
        "userinfo_endpoint": "https://cilogon.org/oauth2/userinfo",
        "response_types_supported": [
          "code"
        ],
        "token_endpoint_auth_methods_supported": [
          "client_secret_post"
        ]
      }

#. ``/path/to/oidc/metadata/cilogon.org.client``

   .. code-block:: json

      {
        "client_id": "<CLIENT ID>",
        "client_secret": "<CLIENT SECRET>"
      }

#. ``/path/to/oidc/metadata/cilogon.org.conf``

   .. code-block:: json

      {
        "scope": "openid email profile org.cilogon.userinfo",
        "response_type": "code",
        "auth_request_params": "skin=default"
      }

After you've accomplished all the above **successfully** give yourself a pat on
the back and lets continue.

Now we can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   # Use OpenID Connect for authentication
   auth:
     - "AuthType openid-connect"
     - "Require valid-user"

   # OpenID Connect options
   oidc_uri: /oidc
   oidc_discover_uri: /discover
   oidc_discover_root: /var/www/ood/discover

   # Allow user to register their authenticated user name to a local system
   # user name
   register_uri: /register
   register_root: /var/www/ood/register

   # If a user can't be mapped to a system user name, then redirect them to the
   # registration page
   map_fail_uri: /register

   # Use OpenID Connect logout
   logout_redirect: /oidc?logout=https%3A%2F%2Fondemand.my-center.edu

   # Use a grid-mapfile for mapping authenticated user name to the system user
   # name
   user_map_cmd: /opt/ood/ood_auth_map/bin/ood_auth_map.mapfile

Where the ``logout_redirect`` contains the URL that the user is redirected to
after they are logged out of their session.

Build the Apache configuration file and install it. Fingers crossed it all
works.

.. _cilogon: http://www.cilogon.org/
.. _mod_auth_openidc: https://github.com/pingidentity/mod_auth_openidc
.. _ood_auth_discovery: https://github.com/OSC/ood_auth_discovery/
.. _ood_auth_registration: https://github.com/OSC/ood_auth_registration/
.. _ood_auth_mapdn: https://github.com/OSC/ood_auth_mapdn/
