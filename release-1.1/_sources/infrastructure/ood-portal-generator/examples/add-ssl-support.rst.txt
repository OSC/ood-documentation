.. _add-ssl-support:

Add SSL Support
---------------

Highly recommended for a production OnDemand Server. The SSL protocol provides
for a secure channel of communication between the user’s browser and the Open
OnDemand portal.

The following prerequisites need to be satisfied:

- The OnDemand Server will need a public facing host name, e.g., ``ondemand.my-center.edu``
- An SSL certificate associated with this host name

Then you can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   servername: ondemand.my-center.edu
   ssl:
     - "SSLCertificateFile \"/path/to/public.crt\""
     - "SSLCertificateKeyFile \"/path/to/private.key\""

Each array item is treated as a line in the Apache configuration file. You can
add more Apache `SSL directives`_ as separate array items.

Build the Apache configuration file and install it.

.. _ssl directives: https://httpd.apache.org/docs/2.4/mod/mod_ssl.html
