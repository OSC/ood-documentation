.. _app-development-interactive-setup-enable-reverse-proxy:

Enable Reverse Proxy
====================

The `reverse proxy`_ will proxy a request to any specified host and port through
IP sockets. This can be used to connect to Jupyter notebook servers, RStudio
servers, VNC servers, and more... This is disabled by default as it can be a
security risk if not properly setup using a good ``host_regex``.

You can read more about how this works in Open OnDemand under
:ref:`ood-portal-generator-configuration-configure-reverse-proxy`.

Requirements
------------

- a regular expression that best describes all the hosts that you would want a
  user to connect to through the proxy (e.g., ``[\w.-]+\.osc\.edu``)
- confirm that if you run the command ``hostname`` from a compute node it will
  return a string that matches the above regular expression

  .. code-block:: sh

     hostname
     # n0001.ten.osc.edu

  .. note::

     If the :command:`hostname` command gives you a value that cannot be used
     to connect to the compute node from the OnDemand host, then you can
     override it in the cluster config with a :command:`bash` command that will
     work, e.g.:

     .. code-block:: yaml
        :emphasize-lines: 16,23

        # /etc/ood/config/clusters.d/cluster1.yml
        ---
        v2:
          metadata:
            title: "Cluster 1"
          login:
            host: "cluster1.my_center.edu"
          job:
            adapter: "..."
            ...
          batch_connect:
            basic:
              script_wrapper: |
                module purge
                %s
              set_host: "host=$(hostname -A | awk '{print $1}')"
            vnc:
              script_wrapper: |
                module purge
                export PATH="/usr/local/turbovnc/bin:$PATH"
                export WEBSOCKIFY_CMD="/usr/local/websockify/run"
                %s
              set_host: "host=$(hostname -A | awk '{print $1}')"

Steps to Enable in Apache
-------------------------

#. This requires modifying the YAML configuration file for
   :ref:`ood-portal-generator` located at
   :file:`/etc/ood/config/ood_portal.yml` as such:

   .. code-block:: yaml
      :emphasize-lines: 17-

      # /etc/ood/config/ood_portal.yml
      ---
      servername: ondemand.my_center.edu
      ssl:
        - 'SSLCertificateFile "/etc/pki/tls/certs/ondemand.my_center.edu.crt"'
        - 'SSLCertificateKeyFile "/etc/pki/tls/private/ondemand.my_center.edu.key"'
        - 'SSLCertificateChainFile "/etc/pki/tls/certs/ondemand.my_center.edu-interm.crt"'
      dex:
        connectors:
          - type: ldap
            id: ldap
            name: LDAP
            config:
              host: openldap.my_center.edu:636
              insecureSkipVerify: false
              bindDN: cn=admin,dc=example,dc=org
              bindPW: admin
              userSearch:
                baseDN: ou=People,dc=example,dc=org
                filter: "(objectClass=posixAccount)"
                username: uid
                idAttr: uid
                emailAttr: mail
                nameAttr: gecos
                preferredUsernameAttr: uid
              groupSearch:
                baseDN: ou=Groups,dc=example,dc=org
                filter: "(objectClass=posixGroup)"
                userMatchers:
                  - userAttr: DN
                    groupAttr: member
                nameAttr: cn
      host_regex: '[\w.-]+\.my_center\.edu'
      node_uri: '/node'
      rnode_uri: '/rnode'

   You can read more about these options under
   :ref:`ood-portal-generator-configuration-configure-reverse-proxy`.

   .. tip::

      What if my site foregos the FQDN in the host names for compute nodes, and
      we have compute names that give their hosts as:

      - ``ab001`` ... ``ab100`` (for the AB cluster)
      - ``pn001`` ... ``pn500`` (for the PN cluster)
      - ``xy001`` ... ``xy125`` (for the XY cluster)

      You could then use the following regular expression in your configuration
      file:

      .. code-block:: yaml

         host_regex: '(ab|pn|xy)\d+'
         node_uri: '/node'
         rnode_uri: '/rnode'

   .. warning::

      Do not add start (``^``, ``A``) or end (``$``, ``Z``) of string/line
      anchors as this regular expression will be inserted into another regular
      expression.

   .. danger::

      Failing to add an appropriate regular expression to the Reverse Proxy
      opens you up to possible phishing attacks. As a malicious party could
      send links to unsuspecting users as::

        https://ondemand.my_center.edu/rnode/phishing.site.com/80/...

      And users will implicitly trust the link since it points to the trusting
      domain of ``ondemand.my_center.edu``.

#. Build/install the updated Apache configuration file:

   .. code-block:: sh

      sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

#. Restart the Apache server to have the changes take effect:

   CentOS/RHEL 7:
     .. code-block:: sh

        sudo systemctl try-restart httpd24-httpd.service httpd24-htcacheclean.service

Verify it Works
---------------

We can test that the reverse proxy is now functional by starting up a simple
server on a compute node and connecting to it through the proxy with our
browser.

#. SSH to any compute node that matches the regular expression above:

   .. code-block:: sh

      ssh n0001.ten.osc.edu

#. Start up a very simple listening server on a high number port:

   .. code-block:: sh

      nc -l 5432

#. In your browser navigate to this server using the Apache reverse proxy with
   the following URL format::

     http://ondemand.my_center.edu/node/<host>/<port>/...

   So for our simplified case lets use::

     http://ondemand.my_center.edu/node/n0001.ten.osc.edu/5432/

#. Go back to your SSH session and verify that it received the browser
   request:

   .. code-block:: sh

      nc -l 5432
      # GET /node/n0691.ten.osc.edu/5432/ HTTP/1.1
      # Host: n0691.ten.osc.edu:5432
      # Upgrade-Insecure-Requests: 1
      ...

   .. note::

      As we don't have the simple server return anything to the browser, you
      can ignore any errors or warnings you see in your browser.

.. _reverse proxy: https://en.wikipedia.org/wiki/Reverse_proxy
