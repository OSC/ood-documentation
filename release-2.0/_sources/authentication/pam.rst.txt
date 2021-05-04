.. _authentication-pam:

Add PAM Authentication
======================

PAM can be used to authenticate users to OnDemand, for example if users only exist in `/etc/passwd` and `/etc/shadow`.

#. Install the Apache PAM module

   .. code-block:: sh

      sudo yum install mod_authnz_pam

#. **RHEL/CentOS 7 only** Copy PAM module into SCL Apache's modules directory

   .. code-block:: sh

      sudo cp /usr/lib64/httpd/modules/mod_authnz_pam.so /opt/rh/httpd24/root/usr/lib64/httpd/modules/

#. Enable the PAM Apache module

   RHEL/CentOS 7:

   .. code-block:: sh

      sudo echo "LoadModule authnz_pam_module modules/mod_authnz_pam.so" > /opt/rh/httpd24/root/etc/httpd/conf.modules.d/55-authnz_pam.conf

   RHEL/CentOS 8:

   .. code-block:: sh

      sudo echo "LoadModule authnz_pam_module modules/mod_authnz_pam.so" > /etc/httpd/conf.modules.d/55-authnz_pam.conf

#. Set the necessary PAM service. For simplicity you can start by copying SSH PAM service

   .. code-block:: sh

      sudo cp /etc/pam.d/sshd /etc/pam.d/ood
       
#. Allow the Apache user to read ``/etc/shadow``.

   .. code-block:: sh

      sudo chmod 640 /etc/shadow
      sudo chgrp apache /etc/shadow

#. Update :file:`/etc/ood/config/ood_portal.yml` to use PAM authentication

   .. code-block:: yaml

      auth:
        - 'AuthType Basic'
        - 'AuthName "Open OnDemand"'
        - 'AuthBasicProvider PAM'
        - 'AuthPAMService ood'
        - 'Require valid-user'
      # Capture system user name from authenticated user name
      user_map_cmd: "/opt/ood/ood_auth_map/bin/ood_auth_map.regex"

#. Apply modifications to the :file:`/etc/ood/config/ood_portal.yml`

   .. code-block:: sh

      sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

