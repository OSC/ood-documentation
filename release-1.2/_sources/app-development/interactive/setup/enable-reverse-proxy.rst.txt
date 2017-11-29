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

  .. code-block:: console

     $ hostname
     n0001.ten.osc.edu

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

#. We will update the Apache configuration file by adding ``Location``
   directives that will be used for the reverse proxy. This requires modifying
   the configuration file for the :ref:`ood-portal-generator`.

   .. code-block:: sh

      cd ~/ood/src/ood-portal-generator

#. :ref:`ood-portal-generator-configuration` is handled by editing the
   ``config.yml`` as such:

   .. code-block:: yaml
      :emphasize-lines: 18-

      # ~/ood/src/ood-portal-generator/config.yml
      ---
      servername: webdev05.hpc.osc.edu
      ssl:
        - 'SSLCertificateFile "/etc/pki/tls/certs/webdev05.hpc.osc.edu.crt"'
        - 'SSLCertificateKeyFile "/etc/pki/tls/private/webdev05.hpc.osc.edu.key"'
        - 'SSLCertificateChainFile "/etc/pki/tls/certs/webdev05.hpc.osc.edu-interm.crt"'
      auth:
        - 'AuthType Basic'
        - 'AuthName "private"'
        - 'AuthBasicProvider ldap'
        - 'AuthLDAPURL "ldaps://openldap1.infra.osc.edu:636/ou=People,ou=hpc,o=osc?uid" SSL'
        - 'AuthLDAPGroupAttribute memberUid'
        - 'AuthLDAPGroupAttributeIsDN off'
        - 'RequestHeader unset Authorization'
        - 'Require valid-user'

      host_regex: '[\w.-]+\.osc\.edu'
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

        https://ondemand.center.edu/rnode/phishing.site.com/80/...

      And users will implicitly trust the link since it points to the trusting
      domain of ``ondemand.center.edu``.

#. Re-build the Apache config:

   .. code-block:: console

      $ scl enable rh-ruby22 -- rake
      mkdir -p build
      rendering templates/ood-portal.conf.erb => build/ood-portal.conf

#. Copy it over to the default location:

   .. code-block:: console

      $ sudo scl enable rh-ruby22 -- rake install
      cp build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

#. Restart the Apache server:

   .. code-block:: console

      $ sudo service httpd24-httpd restart

   .. warning::

      If using **RHEL 7** you will need to replace the above command with:

      .. code-block:: console

         $ sudo systemctl restart httpd24-httpd

Verify it Works
---------------

We can test that the reverse proxy is now functional by starting up a simple
server on a compute node and connecting to it through the proxy with our
browser.

#. SSH to any compute node that matches the regular expression above:

   .. code-block:: console

      $ ssh n0001.ten.osc.edu

#. Start up a very simple listening server on a high number port:

   .. code-block:: console

      $ nc -l 5432

#. In your browser navigate to this server using the Apache reverse proxy with
   the following URL format::

     http://ondemand.my_center.edu/node/<host>/<port>/...

   So for our simplified case lets use::

     http://ondemand.my_center.edu/node/n0001.ten.osc.edu/5432/

#. Go back to your SSH session and verify that it received the browser
   request:

   .. code-block:: console

      $ nc -l 5432
      GET /node/n0691.ten.osc.edu/5432/ HTTP/1.1
      Host: n0691.ten.osc.edu:5432
      Upgrade-Insecure-Requests: 1
      ...

   .. note::

      As we don't have the simple server return anything to the browser, you
      can ignore any errors or warnings you see in your browser.

.. _reverse proxy: https://en.wikipedia.org/wiki/Reverse_proxy
