.. _add-ldap:

Add LDAP Support
================

**(Optional, but recommended)**

.. warning::

   This page explains how to add LDAP support to Dex in Open OnDemand.
   For a more robust authentication solution, see :ref:`authentication`.


#. Add LDAP configurations to to Dex, refer to :ref:`Configuring OnDemand Dex for LDAP <dex-ldap>`.

#. Build/install the updated Apache configuration file as well as updated Dex configuration:

   .. code-block:: sh

      sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

#. Restart the Apache server to have the changes take effect:

   .. code-block:: sh

      sudo systemctl restart httpd24-httpd.service httpd24-htcacheclean.service
      sudo systemctl restart ondemand-dex.service

Open your browser and access the portal. You should now be able to authenticate with your
LDAP username and password.

The theme for Dex can be customized to be site-specific, see :ref:`customize_dex_theme`.

