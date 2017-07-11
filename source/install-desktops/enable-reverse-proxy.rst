.. _install-desktops-enable-reverse-proxy:

Enable Reverse Proxy
====================

The reverse proxy will proxy a request to any specified host and port through
IP sockets. This is different than what is used for proxying to per-user NGINX
processes through Unix domain sockets. This can be used to connect to Jupyter
notebook servers, RStudio servers, VNC servers, and more... This is disabled by
default as it can be a security risk if not properly setup using a good
``host_regex``.

Requirements:

- a regular expression that best describes all the hosts that you would want a
  user to connect to through the proxy (e.g., ``[\w.-]+\.osc\.edu``)
- confirm that if you run the command ``hostname`` from a compute node it will
  return a string that matches the above regular expression

  .. code-block:: sh

     $ hostname
     n0001.ten.osc.edu

#. We will update the Apache configuration file by adding ``Location``
   directives that will be used for the reverse proxy. This requires modifying
   the configuration file for the :ref:`ood-portal-generator`.

   .. code-block:: sh

      cd ~/ood/src/ood-portal-generator

#. :ref:`ood-portal-generator-configuration` is handled by editing the
   ``config.yml`` as such:

   .. code-block:: yaml

      ---
      # ...
      # ... any other configuration options you had from before ...
      # ...

      host_regex: "[\\w.-]+\\.osc\\.edu"
      node_uri: "/node"
      rnode_uri: "/rnode"

   You can read more about these options under
   :ref:`ood-portal-generator-configuration-configure-reverse-proxy`.

   .. warning::

      Since we use double quotes in the YAML file to wrap the regular
      expression, we will need to escape the blackslashes, so ``\w`` becomes
      ``\\w``. If you use single quotes, you will not need to escape them.

#. Re-build the Apache config:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake

#. Copy it over to the default location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

#. Restart the Apache server:

   .. code-block:: sh

      sudo service httpd24-httpd restart

   .. warning::

      If using **RHEL 7** you will need to replace the above command with:

      .. code-block:: sh

         sudo systemctl restart httpd24-httpd

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

     http://ondemand.domain.edu/node/<host>/<port>/...

   So for our simplified case lets use::

     http://ondemand.domain.edu/node/n0001.ten.osc.edu/5432/

#. Go back to your SSH session and verify that it received the browser
   request::

     GET /node/n0691.ten.osc.edu/5432/ HTTP/1.1
     Host: n0691.ten.osc.edu:5432
     Upgrade-Insecure-Requests: 1
     ...

   .. note::

      As we don't have the simple server return anything to the browser, you
      can ignore any errors or warnings you see in your browser.

      You can get fancier using a Python ``SimpleHTTPServer``, but we leave
      that as an exercise to the reader.
