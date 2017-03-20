.. _default-authentication:

Default Authentication
----------------------

The default :program:`ood-portal-generator` configuration sets up the Apache
configuration file to use HTTP Basic authentication to restrict access by
looking up users in plain text password files.

.. code-block:: yaml

   auth:
     - "AuthType Basic"
     - "AuthName \"private\""
     - "AuthUserFile \"/opt/rh/httpd24/root/etc/httpd/.htpasswd\""
     - "RequestHeader unset Authorization"
     - "Require valid-user"

Where the ``RequestHeader`` setting is used to strip private session
information from being sent to the backend web servers.

By default it will look up users in the following password file::

   /opt/rh/httpd24/root/etc/httpd/.htpasswd

You can read about the `basics of password files`_ for more information on
setting up this file.

.. warning::

   The user name specified in the password file must correspond to a system
   user, but the passwords need not match.

.. _basics of password files: https://httpd.apache.org/docs/2.4/howto/auth.html#gettingitworking
