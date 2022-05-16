.. _authentication-oidc:

OpenID Connect
--------------

This is a summary of using OpenID Connect for authentication. Two example OpenID Connect identity providers we have documented include :ref:`Dex <authentication-dex>` and :ref:`Keycloak <authentication-tutorial-oidc-keycloak-rhel7>`.

The following prerequisites need to be satisfied:

- A OIDC IdP server deployed, e.g., ``idp.example.com`` (outside of scope of this document)
- The `mod_auth_openidc`_ installed on the OnDemand Server.

.. note::

   OnDemand repos provide the ``httpd24-mod_auth_openidc`` RPM for RHEL 7 and CentOS 7 as it must be built against SCL Apache. The OnDemand repos also have the ``mod_auth_openidc`` RPM for RHEL 8 and Rocky 8 that are newer than what the OS provides to make use of some newer features.

The following is an example :program:`ood-portal-generator` configuration file:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---
   servername: ondemand.example.com

   # Use OIDC authentication
   auth:
     - "AuthType openid-connect"
     - "Require valid-user"

   # Use OIDC logout
   logout_redirect: "/oidc?logout=https%3A%2F%2Fondemand.example.com"

   # Capture system user name from authenticated user name
   user_map_cmd: "/opt/ood/ood_auth_map/bin/ood_auth_map.regex"

   oidc_uri: "/oidc"
   oidc_provider_metadata_url: "https://idp.example.com/.well-known/openid-configuration"
   oidc_client_id: "ondemand.example.com"
   oidc_client_secret: "b972c25d-88a4-41fa-87f7-a12ff167dd13"
   oidc_remote_user_claim: "preferred_username"
   oidc_scope: "openid profile email groups"
   oidc_session_inactivity_timeout: 28800
   oidc_session_max_duration: 28800
   oidc_state_max_number_of_cookies: "10 true"
   oidc_settings:
     OIDCPassIDTokenAs: "serialized"
     OIDCPassRefreshToken: "On"
     OIDCPassClaimsAs: "environment"
     OIDCStripCookies: "mod_auth_openidc_session mod_auth_openidc_session_chunks mod_auth_openidc_session_0 mod_auth_openidc_session_1"

.. note::

   It's recommended to secure :file:`/etc/ood/config/ood_portal.yml` by changing the file permissions to be ``0600`` and make the file only readable by ``root``:

     .. code-block:: sh

        sudo chmod root:root /etc/ood/config/ood_portal.yml
        sudo chmod 0600 /etc/ood/config/ood_portal.yml

Build the Apache configuration file and install it.

.. _mod_auth_openidc: https://github.com/zmartzone/mod_auth_openidc
