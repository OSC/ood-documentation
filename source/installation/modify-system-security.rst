.. _modify-system-security:

Modify System Security
======================

#. Check `SELinux`_ status, by default SELinux is enabled on CentOS and most other RHEL-based systems.
   
   RHEL/CentOS 6/7
      .. code-block:: sh

         $ sestatus

      .. code-block:: sh

         #Output displays the starting status of SELinux
         **SELinux status**:             **enabled**
         SELinuxfs mount:                /sys/fs/selinux
         SELinux root directory:         /etc/selinux
         Loaded policy name:             targeted
         Current mode:                   enforcing
         Mode from config file:          enforcing
         Policy MLS status:              enabled
         Policy deny_unknown status:     allowed
         Max kernel policy version:      31

#. Disable `SELinux`_ on the Open OnDemand host you intend on running the web
   server on. 

   .. note::

      If SELinux is not disabled on the web server host machine this can lead
      to permission errors when running the web applications. SELinux may also
      need to be disabled on the web server if you want to take advantage of
      certain software in your web applications such as being able to access a
      Lustre file system.


   **Option 1: Disable SELinux Temporarily**
      
      #. To temporarily disable SELinux, use the following command:

         RHEL/CentOS 6/7
            .. code-block:: sh
               
               $ setenforce 0  
      

   **Option 2: Disable SELinux Permanently**
      
      #. Using your favorite text editor open the /etc/selinux/config file and change the **SELINUX=enforcing** directive to **SELINUX=disabled**.

         RHEL/CentOS 6/7
            .. code-block:: sh

               This file controls the state of SELinux on the system.
               # SELINUX= can take one of these three values:
               #       enforcing - SELinux security policy is enforced.
               #       permissive - SELinux prints warnings instead of enforcing.
               #       disabled - No SELinux policy is loaded.
               SELINUX=disabled
               # SELINUXTYPE= can take one of these two values:
               #       targeted - Targeted processes are protected,
               #       mls - Multi Level Security protection.
               SELINUXTYPE=targeted

      #. Reboot the OS to save the changes 

         RHEL/CentOS 6/7
            .. code-block:: sh

               $ shutdown -r now

#. Open ports 80 (http) and 443 (https) in the firewall, typically done with
   `iptables`_.

   .. warning::

      If using **RHEL 7** you will need to either use the newer `firewalld`_
      daemon and modify the firewall settings or disable it and install
      `iptables`_.

   RHEL/CentOS 7
      .. code-block:: sh

         $ systemctl restart firewalld
         $ sudo firewall-cmd --zone=public --add-port=80/tcp --permanent
         $ sudo firewall-cmd --zone=public --add-port=443/tcp --permanent
         $ sudo firewall-cmd --reload

   RHEL/CentOS 6
      .. code-block:: sh

         $ sudo iptables -I INPUT -p tcp -m tcp --dport 80 -j ACCEPT
         $ sudo iptables -I INPUT -p tcp -m tcp --dport 443 -j ACCEPT
         $ sudo service iptables save    

.. _selinux: https://wiki.centos.org/HowTos/SELinux
.. _iptables: https://wiki.centos.org/HowTos/Network/IPTables
.. _firewalld: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/security_guide/sec-using_firewalls
