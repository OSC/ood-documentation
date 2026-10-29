(authentication-tutorial-oidc-keycloak-rhel7-configure-keycloak-webui)=

# Configure Keycloak

We will now use Keycloak's admin Web UI to setup LDAP and add OnDemand as an
OIDC client that will authenticate with Keycloak.

## Add a new realm

1. Log into `https://ondemand-idpdev.hpc.osc.edu` as the admin user

2. Hover over "Master" on left and click "Add Realm"

3. Type in name "ondemand" and click "Create". The new realm is loaded.

4. Click Login tab, then adjust parameters:

   1. Remember Me: ON
   2. Login with email: OFF

5. Click Save.

## Configure LDAP

1. Choose User Federation on the left (verify ondemand realm is current realm)

2. Select `ldap` for provider

   1. Import Users set to OFF
   2. Edit Mode set to READ_ONLY
   3. Vendor set to other – for OpenLDAP
   4. User Object Classes set to `posixAccount` – OSC specific and odd
   5. Connection URL: `ldaps://ldap1.infra.osc.edu:636 ldaps://ldap2.infra.osc.edu:636` – using multiple to demonstrate more than 1
   6. User DN: `ou=People,dc=osc,dc=edu`
   7. Auth Type: none – OSC specific as we allow anonymous binds
   8. Use Truststore SPI: never – OSC specific since our LDAP certificates are already trusted since from InCommon, leaving default is probably acceptable if no `truststoreSpi` defined in XML configurations.

3. Save

:::{warning}
These LDAP settings are what we set for OSC. Your configuration may vary from
this. If you run into any problems, please let us know so that once a
solution is reached we can document those problem areas here. Contact us on
the OnDemand Discourse at <https://discourse.osc.edu/c/open-ondemand>.
:::

## Add OnDemand as a client

1. Choose Clients, then click Create in top right corner

   1. Client ID: `ondemand-dev.hpc.osc.edu`
   2. Client Protocol: `openid-connect`
   3. Save (leave Root URL blank)

2. Then edit Settings for the newly created client:

   1. Access Type: confidential

   2. Direct Access Grants Enabled: off

   3. Valid Redirect URIs: Press the `+` button to the right of the URI field so you can insert two URLs:

      1. `https://ondemand-dev.hpc.osc.edu/oidc`
      2. `https://ondemand-dev.hpc.osc.edu`

   4. Scroll to bottom and click "Save"

3. Finally, get the client secret to use with OnDemand installation:

   1. Select the "Credentials" tab of the "Client" you are viewing i.e. `Clients >> ondemand-dev.hpc.osc.edu`
   2. Copy the value for "secret" for future use in this tutorial (and keep it secure).
