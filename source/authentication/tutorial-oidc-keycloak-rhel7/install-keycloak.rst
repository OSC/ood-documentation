.. _authentication-tutorial-oidc-keycloak-rhel7-install-keycloak:

Install Keycloak
================

We will install, configure, and launch Keycloak IDP server behind Apache.

Login to the host where you will install Keycloak. In this tutorial, we are
installing Keycloak on the same host as OnDemand, which is webdev07.hpc.osc.edu.

#. Download and unpack Keycloak 3.1.0 (from http://www.keycloak.org/archive/downloads-3.1.0.html)

   .. code-block:: sh

      cd /opt
      sudo wget https://downloads.jboss.org/keycloak/3.1.0.Final/keycloak-3.1.0.Final.tar.gz
      sudo tar xzf keycloak-3.1.0.Final.tar.gz


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

      cd keycloak-3.1.0.Final
      sudo -u keycloak ./bin/add-user-keycloak.sh --user admin --password keycloakpass --realm master

   **Be sure to use a good password - using mkpasswd or pwgen or similar.**

#. Modify ``standalone/configuration/standalone.xml`` to enable proxying to Keycloak:

   Simplest is to run these three commands:

   .. code-block:: sh

      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=proxy-address-forwarding,value=true)'
      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/socket-binding-group=standard-sockets/socket-binding=proxy-https:add(port=443)'
      sudo -u keycloak ./bin/jboss-cli.sh 'embed-server,/subsystem=undertow/server=default-server/http-listener=default:write-attribute(name=redirect-socket,value=proxy-https)'

   Or you can use a config.cli file that contains these commands. We have
   provided an example file to make use of in this gist, with blocks commented
   out so you can wget the file, edit as appropriate, and run via:

   .. code-block:: sh

      sudo -u keycloak ./bin/jboss-cli.sh --file=config.cli

   Where the config.cli looks like:

   .. literalinclude:: example-keycloak-jboss-config.cli

#. Create keycloak.service to start and stop the server:

   .. code-block:: sh

      sudo cat > /etc/systemd/system/keycloak.service <<EOF

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
      EOF


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
