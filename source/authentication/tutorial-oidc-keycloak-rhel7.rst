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

#. Add keycloak user

   .. code-block:: sh

      sudo groupadd -r keycloak
      sudo useradd -m -d /var/lib/keycloak -s /sbin/nologin -r -g keycloak keycloak
      # if -m doesn't work, do this:
      # sudo install -d -o keycloak -g keycloak /var/lib/keycloak
      # this makes a home directory, which is needed when running API calls as
      # keycloak user
      sudo chown keycloak: -R keycloak-3.2.1.Final


#. Install JDK 1.8.0

   .. code-block:: sh

      yum install java-1.8.0-openjdk-devel


#. Added 'admin' to '/opt/keycloak-3.2.1.Final/standalone/configuration/keycloak-add-user.json', (re)start server to load user

   .. code-block:: sh

      sudo -u keycloak ./bin/add-user-keycloak.sh --user admin --password keycloakpass --realm master

   **Be sure to use a good password - using mkpasswd or pwgen or similar.**

#. **TODO**

   Use config.cli file [2] to modify standalone.xml configuration -
   /opt/keycloak-3.0.0.Final/bin/jboss-cli.sh --file=config.cli

   I need to get a copy of the file I used. Mention this just modifies
   standalone.xml, which can be hand-modified as well.


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
   installed on the same node as OnDemand, so we can use the same Apache conf
   files, and thus reuse the same SSL certificates.

   **TODO**: show proxying 8080 to 8443

   **TODO**: show open up iptables

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

   **TODO**: one problem with this approach is that cookies are shared across
   all ports of a given host. That means that any cookies Keycloak sets is going
   to be sent in requests to OnDemand, and we might not be filtering these
   cookies out. In that case, we would need to expand our tutorial to use a
   separate host for KeyCloak completely.

   **TODO**: how do we automate these steps?


#. Create a new Keycloak API session

   .. code-block:: sh

      yum install java-1.8.0-openjdk-devel

      sudo -u keycloak ./bin/kcadm.sh config credentials --server http://localhost:8080/auth --realm master --user admin --password keycloakpass

   Use the same user and password you setup earlier. This stores a session file
   in the keycloak user's home directory and on repeated execution of
   ./bin/kcadm.sh commands uses this session info. The kcadm.sh script is a
   wrapper around the Keycloak API which is why you can only use it when the
   server is running.

   Verify that your session was completed by fetching information about the
   realms:

   .. code-block:: sh

      sudo -u keycloak ./bin/kcadm.sh get realms

   **Be sure to use a good password - using mkpasswd or pwgen or similar.**
