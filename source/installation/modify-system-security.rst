Modify System Security
======================

#. Disable SELinux (not documented here)

#. Open port 80 and 443 through IP Tables i.e.

   .. code-block:: sh

      sudo iptables -I INPUT -p tcp -m multiport --dports 80 -m comment --comment "00080 *:80" -j ACCEPT
      sudo iptables -I INPUT -p tcp -m multiport --dports 443 -m comment --comment "00443 *:443" -j ACCEPT
      sudo /etc/init.d/iptables save
