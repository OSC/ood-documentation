.. _authentication-tutorial-oidc-keycloak-rhel7-configure-keycloak-webui:

Configure Keycloak
==================

We will now use Keycloak's admin Web UI to setup LDAP and add OnDemand as an
OIDC client that will authenticate with Keycloak.

Add a new realm
------------------------------------------

#. Log into https://webdev07.hpc.osc.edu:8443 as the admin user
#. Hover over "Master" on left and click "Add Realm"
#. Type in name "ondemand" and click "Save". The new realm is loaded.
#. Click Login tab, then adjust parameters:

   #. Remember Me: ON
   #. Login with email: OFF

#. Click Save.


Configure LDAP
------------------------------------------

#. Choose User Federation on the left (verify ondemand realm is current realm)
#. Select "ldap" for provider

   #. Import Users set to OFF
   #. Edit Mode set to READ_ONLY
   #. Vendor set to other – for OpenLDAP
   #. User Object Classes set to posixAccount – OSC specific and odd
   #. Connection URL: ldaps://openldap1.infra.osc.edu:636 ldaps://openldap2.infra.osc.edu:636 – using multiple to demonstrate more than 1
   #. User DN: ou=People,ou=hpc,o=osc
   #. Auth Type: simple – OSC specific as we allow anonymous binds
   #. Use Truststore SPI: never – OSC specific since our LDAP certificates are already trusted since from InCommon, leaving default is probably acceptable if no truststoreSpi defined in XML configs

#. Save

.. warning::

   These LDAP settings are what we set for OSC. Your configuration may vary from
   this. If you run into any problems, please let us know so that once a
   solution is reached we can document those problem areas here. Contact us on
   the OOD Mailing List at https://lists.osu.edu/mailman/listinfo/ood-users.

Add OIDC client template
--------------------------------------------------

#. Choose Client Templates
#. Click Create (upper right corner)

   #. Name: ondemand-clients
   #. Protocol: openid-connect

   #. Click Save
   #. Mappers tab
   #. Click Add Builtin
   #. Check box the following: username, email, given name, family name, full name
   #. Click Add Selected
   #. Click Scope tab
   #. Set Full Scope Allowed to ON

#. Verify Mappers >> username has "Token Claim Name" with value ``preferred_username``.
   This means that when the user logs to OnDemand, the ``preferred_username`` claim will
   contain the username of the user. We will use this when deciding what system user to map
   a request to.

Add OnDemand as a client
--------------------------------------------------

#. Choose Clients, then click Create in top right corner

   #. Client ID: webdev07.hpc.osc.edu
   #. Client Protocol: openid-connect
   #. Client Template: ondemand-clients
   #. Save (leave Root URL blank)

#. Then edit Settings for the newly created client:

   #. Access Type: confidential
   #. Direct Access Grants Enabled: off
   #. Valid Redirect URIs: Press the ``+`` button to the right of the URI field so you can insert two URLs:

      #. ``https://webdev07.hpc.osc.edu/oidc``
      #. ``https://webdev07.hpc.osc.edu``

   #. Web Origins: ``https://webdev07.hpc.osc.edu``
   #. Scroll to bottom and click "Save"

#. Finally, get the client secret to use with OnDemand installation:

   #. Select the "Installation" tab of the "Client" you are viewing i.e. "Clients >> webdev07.hpc.osc.edu"
   #. Select Format Option: Keycloak OIDC JSON
   #. The "secret" string will be in the credentials section. Copy that for future use in this tutorial (and keep it secure).

