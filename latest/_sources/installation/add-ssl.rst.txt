.. _add-ssl:

Add SSL Support
===============

**(Optional, but recommended)**

The SSL protocol provides for a secure channel of communication between the
user's browser and the Open OnDemand portal.

Requirements:

- a server name that points to the Open OnDemand server
  (``ondemand.my_center.edu``)
- signed SSL certificates with possible intermediate certificates

.. note::

   You may use `Let's Encrypt`_ to obtain a free SSL certificate. You can read
   more about it in their `Getting Started`_ documentation.

.. _let's encrypt: https://letsencrypt.org/
.. _getting started: https://letsencrypt.org/getting-started/

In this example we assume the following certificates are provided:

Public certificate
  :file:`/etc/pki/tls/certs/ondemand.my_center.edu.crt`
Private key
  :file:`/etc/pki/tls/private/ondemand.my_center.edu.key`
Intermediate certificate
  :file:`/etc/pki/tls/certs/ondemand.my_center.edu-interm.crt`

#. Edit the Open OnDemand Portal :ref:`ood-portal-generator-configuration` file
   :file:`/etc/ood/config/ood_portal.yml` as such:

   .. code-block:: yaml
      :emphasize-lines: 6-

      # /etc/ood/config/ood_portal.yml
      ---

      # ...

      servername: ondemand.my_center.edu
      ssl:
        - 'SSLCertificateFile "/etc/pki/tls/certs/ondemand.my_center.edu.crt"'
        - 'SSLCertificateKeyFile "/etc/pki/tls/private/ondemand.my_center.edu.key"'
        - 'SSLCertificateChainFile "/etc/pki/tls/certs/ondemand.my_center.edu-interm.crt"'

   .. note::

      For documentation on SSL directives please see:
      https://httpd.apache.org/docs/2.4/mod/mod_ssl.html

#. Build/install the updated Apache configuration file:

   .. code-block:: sh

      sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

#. Restart the Apache server to have the changes take effect:

   CentOS/RHEL 7:
     .. code-block:: sh

        sudo systemctl try-restart httpd24-httpd.service httpd24-htcacheclean.service

Now when you browse to your OnDemand portal at::

  http://ondemand.my_center.edu

it should redirect you to the HTTP over SSL protocol deployment::

  https://ondemand.my_center.edu

where depending on your browser, should display a green lock of some kind to
indicate that the site is secure.
