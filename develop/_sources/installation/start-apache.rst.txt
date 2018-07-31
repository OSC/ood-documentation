.. _start-apache:

Start Apache
============

By default the Apache HTTP Server is disabled. In this section we will enable
it and add our account to the Basic Auth password file. Please see section
:ref:`add-ldap` for a more advanced and recommended authentication method after
this.

#. Start the Apache HTTP Server:

   CentOS/RHEL 6
     .. code-block:: sh

        sudo service httpd24-httpd start
        # Starting httpd:                                            [  OK  ]

   CentOS/RHEL 7
     .. code-block:: sh

        sudo systemctl start httpd24-httpd

   .. warning::

      If you access the OnDemand server that you just started, you will be
      presented with a username/password dialog box. Attempting to use your
      system credentials will fail because Apache by default will try to
      authenticate against a nonexistent password file.

#. Now we need to add our account to the password file that Apache is using.

   We start by generating an :file:`.htpasswd` file with our username, but
   whose password does not necessarily need to be the same as our system
   password:

   .. code-block:: sh

      sudo scl enable httpd24 -- htpasswd -c /opt/rh/httpd24/root/etc/httpd/.htpasswd $USER
      # New password:
      # Re-type new password:
      # Adding password for user .......

#. Browse to your OnDemand server and login with your username and the password
   you used in the previous step. If everything worked you should be presented
   with the OnDemand :ref:`dashboard`.
