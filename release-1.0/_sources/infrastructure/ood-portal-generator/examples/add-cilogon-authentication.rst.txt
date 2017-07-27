.. _add-cilogon-authentication:

Add CILogon Authentication
--------------------------

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
