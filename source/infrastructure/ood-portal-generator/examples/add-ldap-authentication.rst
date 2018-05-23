.. _add-ldap-authentication:

Add LDAP Authentication
-----------------------

The following prerequisites need to be satisfied:

- An LDAP server, e.g., ``ldap.my-center.edu``
- NSS configured on the OnDemand Server to look up users via LDAP
- The mod_authnz_ldap_ Apache module installed

Then you can modify your :program:`ood-portal-generator` configuration file as
such:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---

   auth:
     - "AuthType Basic"
     - "AuthName \"private\""
     - "AuthBasicProvider ldap"
     - "AuthLDAPURL \"ldaps://ldap.my-center.edu:636/ou=People,ou=hpc\""
     - "RequestHeader unset Authorization"
     - "Require valid-user"

Where the ``RequestHeader`` setting is used to strip private session
information from being sent to the backend web servers.

Each array item is treated as a line in the Apache configuration file. You can
add more Apache `LDAP directives`_ as separate array items.

Build the Apache configuration file and install it.

.. _mod_authnz_ldap: https://httpd.apache.org/docs/2.4/mod/mod_authnz_ldap.html
.. _ldap directives: mod_authnz_ldap_
