.. _add-ssl:

Secure Apache httpd
===================

The SSL protocol provides for a secure channel of communication between the
user's browser and the Open OnDemand portal.  It is recommended that you secure
your Apache server by adding these configurations.

.. warning::

    Open OnDemand expects secure (https) traffic by default. If you do
    not add SSL to your Apache server you will have to follow FIXME-LINK-NEEDED
    to enable some (if not most) functionality.

    This is not recommended as someone on your network could see your traffic in
    plain text, including passwords.

Requirements:

- A server name that points to the Open OnDemand server (``ondemand.my_center.edu``).
  I.e., `nslookup ondemand.my_center.edu` resolves to your instance.
- signed SSL certificates with possible intermediate certificates

.. note::

    `Let's Encrypt`_ is a great option to obtain a free SSL certificate. You can read
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

1. Edit the Open OnDemand Portal :ref:`ood-portal-generator-configuration` file
```````````````````````````````````````````````````````````````````````````````

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

2. Update CA (Dex Users only)
`````````````````````````````

Dex users may encounter issues with SSL certificates like::

  remote error: tls: unknown certificate authority

If this is the case, you need to ensure that their certificate authority (CA) is
in the system trust store and that your CA certificates are up to date.

First, try updating your CA certificates.  This could especially happen when
you have a `Let's Encrypt`_ and your machine does not know about that certificate
authority.

.. tabs::

  .. tab:: RHEL

    .. code:: sh

      sudo yum update ca-certificates

  .. tab:: Ubuntu

    .. code:: sh

      sudo apt update ca-certificates


If you're still having issues, copy your certificate authority (examples could be ``fullchain.pem``)
to your trust store. replace ``CA CERT location`` with the actual certificate
authority you're using and run these commands to copy it to the appropriate place.

.. tabs::

  .. tab:: RHEL

    .. code:: sh

      sudo cp <CA CERT location> /etc/pki/ca-trust/source/anchors/
      sudo update-ca-trust extract
      update-ca-certificates

  .. tab:: Ubuntu

    .. code:: sh

      sudo cp <CA CERT location> /usr/local/share/ca-certificates/
      sudo update-ca-certificates

3. Restart the Apache service for the changes take effect.
``````````````````````````````````````````````````````````

:ref:`Restart the Apache service <restart-apache>` for the changes take effect.

Now when you browse to your OnDemand portal at::

  http://ondemand.my_center.edu

it should redirect you to the HTTP over SSL protocol deployment::

  https://ondemand.my_center.edu

where depending on your browser, should display a green lock of some kind to
indicate that the site is secure.
