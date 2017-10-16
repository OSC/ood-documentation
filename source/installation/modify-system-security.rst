.. _modify-system-security:

Modify System Security
======================

#. Disable `SELinux`_ on the Open OnDemand host you intend on running the web
   server on.

   .. note::

      If SELinux is not disabled on the web server host machine this can lead
      to permission errors when running the web applications. SELinux may also
      need to be disabled on the web server if you want to take advantage of
      certain software in your web applications such as being able to access a
      Lustre file system.

#. Open ports 80 (http) and 443 (https) in the firewall, typically done with
   `iptables`_.

   .. warning::

      If using **RHEL 7** you will need to either use the newer `firewalld`_
      daemon and modify the firewall settings or disable it and install
      `iptables`_.

.. _selinux: https://wiki.centos.org/HowTos/SELinux
.. _iptables: https://wiki.centos.org/HowTos/Network/IPTables
.. _firewalld: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/security_guide/sec-using_firewalls
