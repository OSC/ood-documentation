.. _add-ssl:

Add SSL Support
===============

**(Optional, but recommended)**

The SSL protocol provides for a secure channel of communication between the
user's browser and the Open OnDemand portal.

Requirements:

- a server name that points to the Open OnDemand server
  (``webdev05.hpc.osc.edu``)
- signed SSL certificates with possible intermediate certificates

In this example the certificates are located at:

.. code-block:: sh

   # Public certificate
   /etc/pki/tls/certs/webdev05.hpc.osc.edu.crt

   # Private key
   /etc/pki/tls/private/webdev05.hpc.osc.edu.key

   # Intermediate certificate
   /etc/pki/tls/certs/webdev05.hpc.osc.edu-interm.crt

#. Install the necessary Apache module to use SSL:

   .. code-block:: sh

      sudo yum install httpd24-mod_ssl.x86_64

#. Update the Apache config with this server name and paths to the SSL
   certificates.

   .. code-block:: sh

      cd ~/ood/src/ood-portal-generator

#. Create or edit the ``config.yml`` as such:

   .. code-block:: yaml

      ---

      servername: webdev05.hpc.osc.edu
      ssl:
        - 'SSLCertificateFile "/etc/pki/tls/certs/webdev05.hpc.osc.edu.crt"'
        - 'SSLCertificateKeyFile "/etc/pki/tls/private/webdev05.hpc.osc.edu.key"'
        - 'SSLCertificateChainFile "/etc/pki/tls/certs/webdev05.hpc.osc.edu-interm.crt"'

   .. note::

      For documentation on SSL directives please see:
      https://httpd.apache.org/docs/2.4/mod/mod_ssl.html

#. Re-build the Apache config:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake

#. Copy it over to the default location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

#. Restart the Apache server:

   .. code-block:: sh

      sudo service httpd24-httpd restart

When you visit the portal in your browser now it should redirect any http
traffic to the proper https protocol.

::

   http://webdev05.hpc.osc.edu => https://webdev05.hpc.osc.edu
