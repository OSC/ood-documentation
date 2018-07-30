.. _authentication-overview-configure-authentication:

Configure Apache Authentication
===============================

Compile Authentication Module
-----------------------------

Open OnDemand uses `Apache HTTP Server 2.4`_ provided by Software Collections.
This means that any Apache authentication module (``mod_auth_*``) used will
need to be compiled against the ``apxs`` and ``apr`` tools that reside under:

.. code-block:: text

   /opt/rh/httpd24/root/usr/bin

and **not** the versions that come with the default system version of Apache
HTTP Server.

Configure Authentication Module
-------------------------------

Any Apache authentication module specific configuration directives (e.g.,
``OIDCCLientID``, ``CASLoginURL``, ...) should reside outside of the
:file:`/opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf` configuration
file. The Apache configuration files are loaded in lexical order, so placing
these module specific configuration directives in the file:

.. code-block:: text

   /opt/rh/httpd24/root/etc/httpd/conf.d/auth-config.conf

will cause your authentication configuration directives to be loaded before
:file:`/opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf`. If there are any
secrets inside this file you can ensure privacy by adding restrictive file
permissions:

.. code-block:: sh

   sudo chmod 640 /opt/rh/httpd/root/etc/httpd/conf.d/auth-config.conf

Add to OnDemand Portal
----------------------

.. danger::

   **Never** directly edit the
   :file:`/opr/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf` to include
   this authentication module within your Open OnDemand portal. This could
   cause future upgrades of OnDemand to break.

Edit the YAML configuration file for the :ref:`ood-portal-generator` located
under :file:`/etc/ood/config/ood_portal.yml`. For example, to add support for
an authentication module with ``AuthType`` of ``my-auth``, you would modify the
:file:`/etc/ood/config/ood_portal.yml` file as such:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---
   # ...
   # Your other custom configuration options...
   # ...

   auth:
     - 'AuthType my-auth'
     - 'Require valid-user'

You would then build and install the new Apache configuration file with:

.. code-block:: sh

   sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

Finally you will need to restart your Apache HTTP Server for the changes to
take effect.

.. note::

   You can find more :ref:`ood-portal-generator` configuration examples under
   :ref:`ood-portal-generator-examples`.

Sanitize Session Information
----------------------------

You will need to sanitize any session-specific request headers that may be
passed to the backend web servers that a user is proxied to. For most Apache
authentication modules there are module-specific directives that can be enabled
to wipe session information from being passed as headers (e.g.,
``OIDCStripCookies ...``). In other cases you may have to use regular
expressions to search for the session cookies and remove them manually.

For example, Shibboleth does not have a directive to strip session information
from the cookies, so we accomplish this with the following options in our
:ref:`ood-portal-generator` configuration file:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---
   # ...
   # Your other custom configuration options...
   # ...

   auth:
     - 'AuthType shibboleth'
     - 'ShibRequestSetting requireSession 1'
     - 'RequestHeader edit* Cookie "(^_shibsession_[^;]*(;\s*)?|;\s*_shibsession_[^;]*)" ""'
     - 'RequestHeader unset Cookie "expr=-z %{req:Cookie}"'
     - 'Require valid-user'

where we use a regular expression to replace any ``shibsession`` cookies with
empty strings and delete the cookie header if it becomes empty.

.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
