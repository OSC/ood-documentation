Modify System Security
======================

#. Disable SELinux (not documented here)

#. Open ports 80 and 443 in :command:`iptables`:

   .. code-block:: sh

      # Open port 80
      sudo iptables -I INPUT -p tcp -m multiport --dports 80 -j ACCEPT

      # Open port 443
      sudo iptables -I INPUT -p tcp -m multiport --dports 443 -j ACCEPT

      # Save changes
      sudo /etc/init.d/iptables save
