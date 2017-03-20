.. _add-shibboleth-authentication:

Add Shibboleth Authentication
-----------------------------

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
