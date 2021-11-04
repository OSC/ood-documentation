.. _start-services:

Start Services
==============

By default the Apache HTTP Server is disabled. In this section we will enable
the Apache service.
Please see section :ref:`add-ldap` for a more advanced and recommended authentication method after this.

#. Start the Apache HTTP Server:

   RHEL/CentOS 7
     .. code-block:: sh

        sudo systemctl start httpd24-httpd
        sudo systemctl enable httpd24-httpd

   RHEL/Rocky 8
     .. code-block:: sh

        sudo systemctl start httpd
        sudo systemctl enable httpd

   Ubuntu
     .. code-block:: sh

        sudo systemctl start apache2
        sudo systemctl enable apache2

   .. warning::

      If you access the OnDemand server that you just started, you will be
      presented with a username/password dialog box.
      The default user must exist on the system before login is possible.

#. (Optional) Start the Dex server

   If using the default OnDemand authentication mechanism, you must start the ``ondemand-dex`` service.

   .. code-block:: sh

      sudo systemctl start ondemand-dex
      sudo systemctl enable ondemand-dex

#. (Optional) Configure default user

   If you wish to use the default ``ood`` you must create that user on the OnDemand system.

   .. warning::

      Using the default ``ood`` user is not recommended for production and is intended only for
      evaluation and testing of OnDemand. The recommended approach is to configure LDAP, see :ref:`add-ldap`,
      or some othe authentication mechanism in Apache such as OIDC or Shibboleth.

   .. code-block:: sh

      sudo groupadd ood
      sudo useradd -d /home/ood -g ood -k /etc/skel -m ood

#. Browse to your OnDemand server and login the username ``ood@localhost`` and the password ``password``.
   If everything worked you should be presented with the OnDemand :ref:`dashboard`.
