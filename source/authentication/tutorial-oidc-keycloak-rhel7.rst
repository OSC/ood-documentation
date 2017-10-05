.. _authentication-tutorial-oidc-keycloak-rhel7:

Tutorial: OpenID Connect via KeyCloak on RHEL7
==============================================


Install configure, and launch Keycloak IDP server behind Apache
---------------------------------------------------------------

Login to the host where you will install Keycloak. In this tutorial, we are
installing Keycloak on the same host as OnDemand, which is webdev07.hpc.osc.edu.

#. Download and unpack Keycloak 3.1.0 (from http://www.keycloak.org/archive/downloads-3.1.0.html)

   .. code-block:: sh

      cd /opt
      sudo wget https://downloads.jboss.org/keycloak/3.1.0.Final/keycloak-3.1.0.Final.tar.gz
      sudo tar xzf keycloak-3.1.0.Final.tar.gz

   .. warning::

      This tutorial has only been verified to work with Keycloak 3.0.0 and 3.1.0.
      We experienced code token errors when using Keycloak 3.2.0 and 3.2.1. However,
      Keycloak 3.3.0RC2 appeared to work. Once Keycloak 3.3.0 is released, we will
      update this tutorial to use 3.3.0.

#. Add keycloak user, chown and chmod Keycloak files

   .. code-block:: sh

      sudo groupadd -r keycloak
      sudo useradd -m -d /var/lib/keycloak -s /sbin/nologin -r -g keycloak keycloak
      # if -m doesn't work, do this:
      # sudo install -d -o keycloak -g keycloak /var/lib/keycloak
      # this makes a home directory, which is needed when running API calls as
      # keycloak user
      sudo chown keycloak: -R keycloak-3.1.0.Final
      sudo chmod 700 keycloak-3.1.0.Final


#. Install JDK 1.8.0

   .. code-block:: sh

      yum install java-1.8.0-openjdk-devel


#. Added 'admin' to '/opt/keycloak-3.1.0.Final/standalone/configuration/keycloak-add-user.json', (re)start server to load user

   .. code-block:: sh

      sudo -u keycloak ./bin/add-user-keycloak.sh --user admin --password keycloakpass --realm master

   **Be sure to use a good password - using mkpasswd or pwgen or similar.**

#. Modify ``standalone/configuration/standalone.xml``:

   Simplest is to run these three commands:

   .. code-block:: sh

      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=proxy-address-forwarding,value=true)'
      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/socket-binding-group=standard-sockets/socket-binding=proxy-https:add(port=443)'
      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=redirect-socket,value=proxy-https)'

   You can also manually edit the XML file: **TODO**

   Or you can use a config.cli file that contains these commands. We have
   provided an example file to make use of in this gist, with blocks commented
   out so you can wget the file, edit as appropriate, and run via:

   .. code-block:: sh

      sudo -u keycloak ./bin/jboss-cli.sh --file=config.cli

   **TODO: add gist with file**

   .. warning::

      This step you would change certain things if using MySQL or another
      database instead of the built in H2 database for Keycloak. If you
      need to add a truststore, uncomment this block.

#. Create keycloak.service to start and stop the server:

   .. code-block:: sh

      sudo vim /etc/systemd/system/keycloak.service

   The contents of this file look like:

   .. code-block:: text

      [Unit]
      Description=Jboss Application Server
      After=network.target

      [Service]
      Type=idle
      User=keycloak
      Group=keycloak
      ExecStart=/opt/keycloak-3.1.0.Final/bin/standalone.sh -b 0.0.0.0
      TimeoutStartSec=600
      TimeoutStopSec=600

      [Install]
      WantedBy=multi-user.target


   Then start keycloak:

   .. code-block:: sh

      sudo systemctl daemon-reload
      sudo systemctl start keycloak

      # it may take a little time to load; verify it has loaded:
      $ sudo systemctl status keycloak
      keycloak.service - Jboss Application Server
      Loaded: loaded (/etc/systemd/system/keycloak.service; disabled; vendor preset: disabled)
      Active: active (running) since Mon 2017-09-25 16:19:47 EDT; 2s ago
      ...
      Sep 25 16:19:49 webdev07.hpc.osc.edu standalone.sh[111998]: 16:19:49,644 INFO  [org.wildfly.extension.undertow] (MSC service thread ...0:8080)
      Hint: Some lines were ellipsized, use -l to show in full.


#. Define apache config to proxy keycloak requests

   We will stick Apache in front of Keycloak. In this tutorial Keycloak is
   installed on the same node as OnDemand, and we use the same Apache instance
   to serve both OnDemand and Keycloak with the same host, so we can reuse the
   same SSL certificates. You may want to run Keycloak on a separate host, however.

   Add ``/opt/rh/httpd24/root/etc/httpd/conf.d/ood-keycloak.conf``, making changes
   for the appropriate SSL certificate locations. Notice we are proxying
   https://webdev07.hpc.osc.edu:8443 to http://localhost:8080 which is the default
   port the Keycloak webserver runs as.

   .. literalinclude:: example-keycloak-apache.conf

   You may need to modify iptables to open up access to Keycloak the same way
   that you did so with port 80 and 443 for OnDemand:

   .. code-block:: sh

      sudo iptables -I INPUT -p tcp -m multiport --dports 8443 -m comment --comment "08443 *:8443" -j ACCEPT

   .. note::

      We can use the same host because Keycloak properly scopes all cookies it sets to the
      realm. For example, if I have a realm called "ondemand", then the Keycloak login
      page will be at https://idp.osc.edu/auth/realms/ondemand/protocol/openid-connect/auth
      and cookies set during authentication will be set with the path ``/auth/realms/ondemand``,
      including ``KEYCLOAK_SESSION``, ``KEYCLOAK_STATE_CHECKER``,
      ``KEYCLOAK_IDENTITY``, and ``KC_RESTART``.

#. Now you should be able to access Keycloak: https://webdev07.hpc.osc.edu:8443


Use Keycloak Admin Web UI to configure LDAP and add OnDemand OIDC Client
------------------------------------------------------------------------

#. Using the Web Admin UI, add a new realm

   #. Log into https://webdev07.hpc.osc.edu:8443 as the admin user
   #. Hover over "Master" on left and click "Add Realm"
   #. Type in name "ondemand" and click "Save". The new realm is loaded.
   #. Click Login tab, then adjust parameters:

      #. Remember Me: ON
      #. Login with email: OFF

   #. Click Save.


#. Using the Web Admin UI, configure LDAP

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

#. Using the Web Admin UI, add OIDC client template

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

#. Using the Web Admin UI, add OnDemand as a client

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
      #. The "secret" string will be in the credentials section. Copy that for future use (and keep it secure).

Configure OnDemand Apache as OIDC Client for Keycloak
-----------------------------------------------------

Install mod_auth_openidc in OnDemand's Apache
.............................................

These directions are for installing from source.

#. Install dependencies for building mod_auth_openidc

   .. code-block:: sh

      yum install httpd24-httpd-devel openssl-devel curl-devel jansson-devel pcre-devel autoconf automake

#. Install cjose

   .. code-block:: sh

      wget https://github.com/pingidentity/mod_auth_openidc/releases/download/v2.3.0/cjose-0.5.1.tar.gz
      tar xzf cjose-0.5.1.tar.gz
      cd cjose-0.5.1
      ./configure
      make
      sudo make install

#. Install mod_auth_openidc

   .. code-block:: sh

      wget https://github.com/pingidentity/mod_auth_openidc/releases/download/v2.3.2/mod_auth_openidc-2.3.2.tar.gz
      tar xzf mod_auth_openidc-2.3.2.tar.gz
      cd mod_auth_openidc-2.3.2.tar.gz

      export MODULES_DIR=/opt/rh/httpd24/root/usr/lib64/httpd/modules
      export APXS2_OPTS="-S LIBEXECDIR=${MODULES_DIR}"
      export APXS2=/opt/rh/httpd24/root/usr/bin/apxs
      export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
      ./autogen.sh
      ./configure --prefix=/opt/rh/httpd24/root/usr --exec-prefix=/opt/rh/httpd24/root/usr --bindir=/opt/rh/httpd24/root/usr/bin --sbindir=/opt/rh/httpd24/root/usr/sbin --sysconfdir=/opt/rh/httpd24/root/etc --datadir=/opt/rh/httpd24/root/usr/share --includedir=/opt/rh/httpd24/root/usr/include --libdir=/opt/rh/httpd24/root/usr/lib64 --libexecdir=/opt/rh/httpd24/root/usr/libexec --localstatedir=/opt/rh/httpd24/root/var --sharedstatedir=/opt/rh/httpd24/root/var/lib --mandir=/opt/rh/httpd24/root/usr/share/man --infodir=/opt/rh/httpd24/root/usr/share/info --without-hiredis
      make
      sudo make install

#. Add file ``/opt/rh/httpd24/root/etc/httpd/conf.modules.d/auth_openidc.conf`` with contents:

   .. code-block:: none

      LoadModule auth_openidc_module modules/mod_auth_openidc.so



.. note::

   https://github.com/pingidentity/mod_auth_openidc does provide rpms for
   both cjose and mod_auth_openidc. However, we have yet to verify this works with
   the SCL Apache package we use.

   `Release v2.3.2 Downloads <https://github.com/pingidentity/mod_auth_openidc/releases/tag/v2.3.2>`_
   at bottom of the page includes an rpm for RHEL7, that is presumably built
   against httpd24, so that might work. The RHEL6 rpm will not, however, as it is built against httpd22.
   You will need the dependent module cjose-0.5.1-1.el7.centos.x86_64.rpm
   (see `Downloads for v2.3.0 <https://github.com/pingidentity/mod_auth_openidc/releases/tag/v2.3.0>`_).


Re-generate main config using ood-portal-generator
..................................................

#. In the ood-portal-generator's config.yml file, add these lines:

   .. code-block:: yaml

      # List of Apache authentication directives
      # NB: Be sure the appropriate Apache module is installed for this
      # Default: (see below, uses basic auth with an htpasswd file)
      auth:
        - 'AuthType openid-connect'
        - 'Require valid-user'

      # Redirect user to the following URI when accessing logout URI
      # Example:
      #     logout_redirect: '/oidc?logout=https%3A%2F%2Fwww.example.com'
      # Default: '/pun/sys/dashboard/logout' (the Dashboard app provides a simple
      # HTML page explaining logout to the user)
      logout_redirect: '/oidc?logout=https%3A%2F%2Fwebdev07.hpc.osc.edu'

      # Sub-uri used by mod_auth_openidc for authentication
      # Example:
      #     oidc_uri: '/oidc'
      # Default: null (disable OpenID Connect support)
      oidc_uri: '/oidc'

   Notice that we are

    * changing the Authentication directives for openid-connect
    * specifying /oidc to be the sub-uri used by mod_auth_openidc
    * specifying that /logout should redirect to this /oidc sub-uri to handle logout
      and specifying after logout, the user should be redirected back to OnDemand
      (which in this tutorial's case is ``https%3A%2F%2Fwebdev07.hpc.osc.edu``,
      the query param escaped format of https://webdev07.hpc.osc.edu)

#. Using this modified config, regenerate the Apache config, and then install it:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake
      scl enable rh-ruby22 -- rake install


   The effect of this change in the Apache config (in case you want to apply the changes manually) are:

   #. Change the authentication directives for all of the Locations that require authentication i.e.:

      .. code-block:: diff

           <Location "/nginx">
         -    AuthType basic
         -    AuthName "Private"
         -    AuthBasicProvider ldap
         -    AuthLDAPURL "ldaps://openldap1.infra.osc.edu:636 openldap2.infra.osc.edu:636 openldap3.infra.osc.edu:636 openldap4.infra.osc.edu
         -    AuthLDAPGroupAttribute memberUid
         -    AuthLDAPGroupAttributeIsDN off
         +    AuthType openid-connect
               Require valid-user
         -    RequestHeader unset Authorization

             LuaHookFixups nginx.lua nginx_handler
           </Location>

   #. Update the ``Redirect "logout"`` directive

      .. code-block:: diff

         -  Redirect "/logout" "/pun/sys/dashboard/logout"
         -
         +  Redirect "/logout" "/oidc?logout=https%3A%2F%2Fwebdev07.hpc.osc.edu"

   #. Add the ``<Location "/oidc">`` directive

      .. code-block:: none

         # OpenID Connect redirect URI:
         #
         #     http://localhost:80/oidc
         #     #=> handled by mod_auth_openidc
         #
         <Location "/oidc">
           AuthType openid-connect
           Require valid-user
         </Location>



Add Keycloak config to OnDemand Apache for mod_auth_openidc
...........................................................

Add the file /opt/rh/httpd24/root/etc/httpd/conf.d/auth_openidc.conf with the contents:

  .. code-block:: none

     OIDCProviderMetadataURL https://webdev07.hpc.osc.edu:8443/auth/realms/ondemand/.well-known/openid-configuration
     OIDCClientID        "webdev07.hpc.osc.edu"
     OIDCClientSecret    "1111111-1111-1111-1111-111111111111"
     OIDCRedirectURI      https://webdev07.hpc.osc.edu/oidc
     OIDCCryptoPassphrase "3897531ad98e4d56ed3b795ebc486d93365fda663fcc3b37e75791b8e950f5296369bc104c74609c611538dd4ab0cc000593f160e6a144b8e9e58bf2adf97018"

     # Keep sessions alive for 8 hours
     OIDCSessionInactivityTimeout 28800
     OIDCSessionMaxDuration 28800

     # Set REMOTE_USER
     OIDCRemoteUserClaim preferred_username

     # Don't pass claims to backend servers
     OIDCPassClaimsAs environment

     # Strip out session cookies before passing to backend
     OIDCStripCookies mod_auth_openidc_session mod_auth_openidc_session_chunks mod_auth_openidc_session_0 mod_auth_openidc_session_1

  #. OIDCClientID is set to the client id specified when installing the client in Keycloak admin interface
  #. OIDCClientSecret is set to the client secret specified from the Install tab of the client in Keycloak admin interface
  #. Generate a random password for OIDCCryptoPassphrase. I used ``openssl rand -hex 64``
  #. Verify the OIDCProviderMetadataURL uses the correct realm and the port Apache exposes to the world for Keycloak

Then restart OnDemand's Apache. OnDemand should now be authenticating using KeyCloak.

.. note::

   We prevent OIDC_CLAIM headers from being passed through to the PUN
   by specifying in this file to pass claims as environment, instead of
   as HTTP headers, since Apache won't pass any environment off to the
   PUN when proxying requests, but would pass HTTP headers.
