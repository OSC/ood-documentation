.. _authentication-tutorial-pam-authnz:

PAM Authentication using mod Authnz
=======================================

These are the steps you'll need to take to enable PAM authentication in
OnDemand using the ``mod_authnz_external`` httpd plugin.  These steps are
community provided, so if you have issues with them, let us know!


#. Enable epel if required

    .. code-block:: sh

       yum install epel-release

#. Install pwauth

    .. code-block:: sh

       yum install pwauth


#. Download the mod_authnz_external rpm

    .. code-block:: sh

       wget http://download.fedoraproject.org/pub/epel/7/x86_64/Packages/m/mod_authnz_external-3.3.1-7.el7.x86_64.rpm


#. Unpack the files from the rpm.

    .. code-block:: sh

       rpm2cpio mod_authnz_external-3.3.1-7.el7.x86_64.rpm | cpio -idmv


#. Copy the unpacked files to the appropriate httpd24 locations.

    .. code-block:: sh

       cp usr/lib64/httpd/modules/mod_authnz_external.so /opt/rh/httpd24/root/usr/lib64/httpd/modules
       cp etc/httpd/conf.d/authnz_external.conf /opt/rh/httpd24/root/etc/httpd/conf.d

#. Modify /etc/ood/config/ood_portal.yml to have these yaml elements.

    .. warning::
       Be careful of copy/paste errors with indentation and ' and " characters.

    .. code-block:: yaml

       - 'DefineExternalAuth pwauth pipe /usr/bin/pwauth'

       auth:
       - 'SSLRequireSSL'
       - 'AuthType Basic'
       - 'AuthName "private"'
       - 'AuthBasicProvider external'
       - 'AuthExternal pwauth'
       - 'RequestHeader unset Authorization'
       - 'require valid-user'


#. Generate config files with the ood_portal command.

    .. code-block:: sh

      /opt/ood/ood-portal-generator/sbin/update_ood_portal

#. Restart apache httpd

    .. code-block:: sh

      sudo service httpd24-httpd condrestart

#. Cleanup the files extracted in step 4 and disable epel if you wish.
