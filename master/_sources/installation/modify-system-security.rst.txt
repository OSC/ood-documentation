.. _modify-system-security:

Modify System Security
======================

#. Disable SELinux on the Open OnDemand host you intend on running the web
   server on.

   .. note::

      You can read more about modifying SELinux at
      `https://wiki.centos.org/HowTos/SELinux
      <https://wiki.centos.org/HowTos/SELinux>`__

   .. warning::

      If SELinux is not disabled on the web server host machine this can lead
      to permission errors when running the web applications. In some cases
      disabling SELinux is required to mount a Lustre file system as well.

#. Open ports 80 and 443 in the firewall.

   .. note::

      You can read more about modifying the firewall rules with
      :command:`iptables` at `https://wiki.centos.org/HowTos/Network/IPTables
      <https://wiki.centos.org/HowTos/Network/IPTables>`__
