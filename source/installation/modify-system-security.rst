.. _modify-system-security:

Modify System Security
======================

.. _ood_selinux:

SELinux
--------

.. DANGER::
   Support for SELinux on the Open OnDemand host is currently considered a beta feature.

#. If you plan to use `SELinux`_ on the Open OnDemand host you must install the `ondemand-selinux` package.

   .. code-block:: sh

      sudo yum install ondemand-selinux

   .. note::

      OnDemand runs under the `ood_pun_t` context.

The OnDemand SELinux package makes several changes to allow OnDemand to run with SELinux enabled.

* Set contexts of several filesystem paths specific to OnDemand.
* Enable SELinux booleans.
* Apply a custom policy to allow actions to performed by `ood_pun_t` context.

The custom SELinux booleans provided by the OnDemand SELinux policy:

* ``ondemand_manage_user_home_dir`` (**default=off**): Necessary if user home directories are local disk and not NFS. This is useful when OnDemand is hosted on the system also acting as the NFS server for home directories.
* ``ondemand_manage_vmblock`` (**default=off**): So far this has only proven necessary when running OnDemand inside of Vagrant when the home directory is a Virtualbox mount.
* ``ondemand_use_nfs`` (**default=on**): Allow OnDemand to manage NFS home directories, which is necessary if home directories are accessible via NFS on the OnDemand web node.
* ``ondemand_use_shell_app`` (**default=on**): Adds necessary rules to allow the OnDemand Shell app to function.
* ``ondemand_use_sssd`` (**default=on**): Allows OnDemand to access SSSD
* ``ondemand_use_slurm`` (**default=off**): Allows OnDemand to interact with SLURM and MUNGE.
* ``ondemand_use_torque`` (**default=off**): Allows OnDemand to interact with Torque.
* ``ondemand_use_ldap`` (**default=off**): Allows OnDemand to interact with remote LDAP servers. This does not affect Apache LDAP authentication. This is only necessary if the PUN is interacting with LDAP ports.
* ``ondemand_use_kerberos`` (**default=off**): Allow OnDemand to interact with Kerberos.

The following SELinux booleans are enabled by the ``ondemand-selinux`` package:

* httpd_setrlimit
* httpd_mod_auth_pam
* httpd_run_stickshift
* httpd_can_network_connect
* daemons_use_tty
* use_nfs_home_dirs (can be disabled if the OnDemand web node is not using NFS for home directories)

The following example disabled the Shell app SELinux boolean.

   .. code-block:: sh

      sudo setsebool -P ondemand_use_shell_app=off

If you experience denials when running SELinux with Open OnDemand please provide denial details by generating a `ood.te` file and posting that to `Discourse <https://discourse.osc.edu/c/open-ondemand>`_. It would also help to post the `audit.log` lines that correspond to the OnDemand specific denials.

   .. code-block:: sh

      cat /var/log/audit/audit.log | audit2allow -M ood

.. _firewall:

Firewall
---------
#. Open ports 80 (http) and 443 (https) in the firewall, typically done with
   `iptables`_.

   .. warning::

      If using **RHEL 7** you will need to either use the newer `firewalld`_
      daemon and modify the firewall settings or disable it and install
      `iptables`_.

.. _selinux: https://wiki.centos.org/HowTos/SELinux
.. _iptables: https://wiki.centos.org/HowTos/Network/IPTables
.. _firewalld: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/security_guide/sec-using_firewalls
