.. _modify-system-security:

Modify System Security
======================

.. _ood_selinux:

SELinux
--------

.. DANGER::
   Support for SELinux on the Open OnDemand host is currently considered an alpha feature.

#. If you plan to use `SELinux`_ on the Open OnDemand host you must install the `ondemand-selinux` package.

   .. code-block:: sh

      sudo yum install ondemand-selinux

   .. note::

      OnDemand runs under the Apache `httpd_t` context.

The OnDemand SELinux package makes several changes to allow OnDemand to run with SELinux enabled.

* Set context of several ondemand-nginx directories and files.
* Enable several booleans.
* Apply a custom policy to allow some additional actions by processes in the `httpd_t` context.

If you experience denials when running SELinux with Open OnDemand please provide denial details by generating a `ood.te` file and posting that to `Discourse <https://discourse.osc.edu/c/open-ondemand>`_. It would also help to post the `audit.log` lines that correspond to the OnDemand specific denials.

   .. code-block:: sh

      cat /var/log/audit/audit.log | audit2allow -M ood

.. _firewall:

Firewall
---------
#. Open ports 80 (http) and 443 (https) in the firewall, typically done with
   `firewalld`_ or `iptables`_.

   Firewalld example:
     .. code-block:: sh

        $ sudo firewall-cmd --zone=public --add-port=80/tcp --permanent
        $ sudo firewall-cmd --zone=public --add-port=443/tcp --permanent
        $ sudo firewall-cmd --reload

  Iptables example:
     .. code-block:: sh

        $ sudo iptables -I INPUT -p tcp -m tcp --dport 80 -j ACCEPT
        $ sudo iptables -I INPUT -p tcp -m tcp --dport 443 -j ACCEPT
        $ sudo iptables-save > /etc/sysconfig/iptables

.. _selinux: https://wiki.centos.org/HowTos/SELinux
.. _iptables: https://wiki.centos.org/HowTos/Network/IPTables
.. _firewalld: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/security_guide/sec-using_firewalls
