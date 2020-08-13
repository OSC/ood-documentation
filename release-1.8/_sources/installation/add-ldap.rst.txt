.. _add-ldap:

Add LDAP Support
================

**(Optional, but recommended)**

.. warning::

   This page explains how to add LDAP support to basic auth in Open OnDemand.
   Basic auth should only be used for evaluation purposes. For a more robust
   authentication solution, see :ref:`authentication`.

LDAP support allows for your users to log in using their local username and
password. It also removes the need for the system administrator to keep
updating the ``.htpasswd`` file.

Requirements:

- an LDAP server preferably with SSL support (``openldap.my_center.edu:636``)

#. Edit the Open OnDemand Portal :ref:`ood-portal-generator-configuration` file
   :file:`/etc/ood/config/ood_portal.yml` as such:

   .. code-block:: yaml
      :emphasize-lines: 6-

      # /etc/ood/config/ood_portal.yml
      ---

      # ...

      auth:
        - 'AuthType Basic'
        - 'AuthName "private"'
        - 'AuthBasicProvider ldap'
        - 'AuthLDAPURL "ldaps://openldap.my_center.edu:636/ou=People,ou=hpc,o=my_center?uid"'
        - 'AuthLDAPGroupAttribute memberUid'
        - 'AuthLDAPGroupAttributeIsDN off'
        - 'RequestHeader unset Authorization'
        - 'Require valid-user'

   .. note::

      For documentation on LDAP directives please see:
      https://httpd.apache.org/docs/2.4/mod/mod_authnz_ldap.html

#. Build/install the updated Apache configuration file:

   .. code-block:: sh

      sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

#. Restart the Apache server to have the changes take effect:

   CentOS/RHEL 7:
     .. code-block:: sh

        sudo systemctl try-restart httpd24-httpd.service httpd24-htcacheclean.service

Close your browser so that you are properly logged out. Then open your browser
again and access the portal. You should now be able to authenticate with your
local username and password.
