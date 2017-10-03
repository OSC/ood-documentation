.. _authentication-tutorial-oidc-keycloak-rhel7:

Tutorial: OpenID Connect via KeyCloak on RHEL7
==============================================

**TODO: rethink Installation: 11. Add LDAP Support section** - if you are adding
another authentication mechanism like OIDC with Keycloak or OIDC with CAS or
etc. it doesn't make sense to add all the changes to the Apache config now.

**TODO: alter for generic (remove ref to webdev07)**

**login to webdev07 and do these steps**

#. Download and unpack new version of keycloak

   .. code-block:: sh

      cd /opt
      sudo wget https://downloads.jboss.org/keycloak/3.2.1.Final/keycloak-3.2.1.Final.tar.gz
      sudo tar xzf keycloak-3.2.1.Final.tar.gz

#. Add keycloak user, chown and chmod Keycloak files

   .. code-block:: sh

      sudo groupadd -r keycloak
      sudo useradd -m -d /var/lib/keycloak -s /sbin/nologin -r -g keycloak keycloak
      # if -m doesn't work, do this:
      # sudo install -d -o keycloak -g keycloak /var/lib/keycloak
      # this makes a home directory, which is needed when running API calls as
      # keycloak user
      sudo chown keycloak: -R keycloak-3.2.1.Final
      sudo -u chmod 700 keycloak-3.2.1.Final


#. Install JDK 1.8.0

   .. code-block:: sh

      yum install java-1.8.0-openjdk-devel


#. Added 'admin' to '/opt/keycloak-3.2.1.Final/standalone/configuration/keycloak-add-user.json', (re)start server to load user

   .. code-block:: sh

      sudo -u keycloak ./bin/add-user-keycloak.sh --user admin --password keycloakpass --realm master

   **Be sure to use a good password - using mkpasswd or pwgen or similar.**

#. Modify ``standalone/configuration/standalone.xml``:

   Simplest is to run these three commands:

   .. code-block:: sh

      ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=proxy-address-forwarding,value=true)'
      ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=redirect-socket,value=proxy-https)'
      ./bin/jboss-cli.sh 'embed-server,/socket-binding-group=standard-sockets/socket-binding=proxy-https:add(port=443)'

   You can also manually edit the XML file: **TODO**

   Or you can use a config.cli file that contains these commands. We have
   provided an example file to make use of in this gist, with blocks commented
   out so you can wget the file, edit as appropriate, and run via:

   .. code-block:: sh

      ./bin/jboss-cli.sh --file=config.cli

   **TODO: add gist with file**

   **This step you would change certain things if using MySQL or another
   database instead of the built in H2 database for Keycloak. If you need to add a truststore, uncomment this block.**

#. Create keycloak.service to start and stop the server:

   .. code-block:: sh

      sudo vim /etc/systemd/system/keycloak.service

   The contents of this file look like:

   .. code-block:: text

      TODO: ADD THIS FILE CONTENT

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
   installed on the same node as OnDemand, and we use the same Apache conf
   files, and thus reuse the same SSL certificates.

   **TODO**: show proxying 8080 to 8443

   **TODO**: show open up iptables

   We can use the same host because Keycloak properly scopes all cookies it sets to the
   realm. For example, if I have a realm called osc, then the Keycloak login
   page will be at https://idp.osc.edu/auth/realms/osc/protocol/openid-connect/auth
   and cookies set during authentication will be set with the path ``/auth/realms/osc``,
   including ``KEYCLOAK_SESSION``, ``KEYCLOAK_STATE_CHECKER``,
   ``KEYCLOAK_IDENTITY``, and ``KC_RESTART``.

#. Now you should be able to access https://your.ondemand.install.edu:8080/. In
   my case it was https://webdev07.hpc.osc.edu:8080/auth/

   The rest of the setup can now go two ways. You can either login as the admin
   user and use the Web UI, or you can use the command line API. In both cases
   we will be:

   #. addding a new realm
   #. client template for OIDC (do we need this?)
   #. add ldap config
   #. add ldap mapper config (delete some too via web ui)
   #. add client(s) i.e. ondemand install

   Then after those steps are complete we will finish with updating OnDemand to
   use KeyCloak for authentication:

   #. install mod_auth_openidc
   #. regenerate ondemand apache config using oidc + add oidc apache conf file
   #. update mapping script to use the right OIDC claim

   **TODO**: after completing directions, lets create a diagram of the end
   result (Apache is doing what? etc.)

#. Using the Web Admin UI, configure LDAP

   #. Log into https://webdev07.hpc.osc.edu:8443
   #. Ensure appropriate non-master realm selected in upper left corner
   #. Choose User Federation
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

      #. Name: osc-clients
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
      #. Client Template: osc-clients
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

#. Update OnDemand Apache to authenticate with KeyCloak

   #. Install mod_auth_openidc in OnDemand Apache

      #. **TODO**

   #. Re-generate main config using ood-portal-generator

      #. **TODO**

   #. Add Keycloak config to OnDemand Apache for mod_auth_openidc

      #. **TODO**

