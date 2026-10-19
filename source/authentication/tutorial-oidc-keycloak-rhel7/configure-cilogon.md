(authentication-tutorial-oidc-keycloak-rhel7-configure-cilogon)=

# Configure Keycloak with CILogon

We will now use Keycloak's admin Web UI to setup the ability to log existing users in with CILogon.

When a user logs in with CILogon for the first time they will be redirected back to Keycloak to log in with their local (i.e., LDAP)
credentials. This performs a mapping of their CILogon identity with their Keycloak identity.

:::{warning}
CILogon can only map a single external identity to a Keycloak account. This means if a user logs in with Institution A they
must remove their mapping in order to log in with Institution B.
:::

## Register your Keycloak instance with CILogon

1. Go to `https://cilogon.org/oauth2/register` and fill out the form

> 1. The Home URL will be the base URL of your Keycloak instance, e.g.: `https://ondemand-idpdev.hpc.osc.edu`.
> 2. The callback URL will be `https://ondemand-idpdev.hpc.osc.edu/auth/realms/<REALM>/broker/cilogon/endpoint`.
>    Replace `https://ondemand-idpdev.hpc.osc.edu` with your Keycloak instance
> 3. The box for "Is this a public client?" should not be checked
> 4. For "Scopes" be sure to check `profile` and `org.cilogon.userinfo`

You will be provided a Client ID and a Client Secret, be sure to save these values.
Your registered client will not be usable until you receive an email from CILogon stating your client has been approved.

## Add the CILogon Identity Provider

1. Log into `https://ondemand-idpdev.hpc.osc.edu` as the admin user

2. Select your desired realm in the upper left corner

3. Choose "Identity Providers" in the left menu

4. Select the "Add provider..." drop down and choose "OpenID Connect v1.0"

5. Fill in the fields as noted below

   01. Alias: `cilogon` (This must be `cilogon` as this alias is used in the callback URL)
   02. Display Name: CILogon
   03. Enabled: ON
   04. First Login Flow: browser
   05. Authorization URL: <https://cilogon.org/authorize>
   06. Token URL: <https://cilogon.org/oauth2/token>
   07. User Info URL: <https://cilogon.org/oauth2/userinfo>
   08. Client Authentication: Client secret sent as post
   09. Client ID: \<Client ID provided by CILogon at registration>
   10. Client Secret: \<Client Secret provided by CILogon at registration>
   11. Default Scopes: `openid profile org.cilogon.userinfo`

6. Click "Save"

## Support users removing CILogon mappings

In order for a user to remove an existing CILogon mapping in Keycloak they must navigate to `https://ondemand-idpdev.hpc.osc.edu/auth/realms/<REALM>/account/identity`.
Replace `ondemand-idpdev.hpc.osc.edu` with the web URL for your Keycloak instance.

The URL can be added to the OnDemand Help drop-down with custom text to make it easier for users to access their Keycloak identity page.

1. Add `OOD_DASHBOARD_HELP_CUSTOM_URL` to `/etc/ood/config/apps/dashboard/env` that points to the URL of the identity page for your Keycloak instance.
   Example: `https://ondemand-idpdev.hpc.osc.edu/auth/realms/osc/account/identity`

2. Update `/etc/ood/config/locales/en.yml` with the text to be used for the Identity provider Help link

   ```
   en:
     dashboard:
       nav_help_custom: Manage Federated Identity
   ```
