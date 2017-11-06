.. _authentication-overview-configure-authentication:

Configure Apache to use desired authentication method
================================================================

Install authentication module
----------------------------------------------------------------

Open OnDemand uses `Apache HTTP Server 2.4`_ provided by Software
Collections. This means that any Apache authentication module
(``mod_auth_*``) used will need to be compiled against the ``apxs`` and
``apr`` tools that reside under:

.. code-block:: text

    /opt/rh/httpd24/root/usr/bin

and not the versions that come with the default system version of Apache HTTP
Server.


Add auth module specific configuration file
----------------------------------------------------------------

Any Apache authentication module specific configuration directives (e.g.,
``OIDCCLientID``, ``CASLoginURL``, ...) should reside outside of the
``ood-portal.conf`` configuration file. The Apache configuration files are
loaded in lexical order, so placing these module specific configuration
directives in the file:

.. code-block:: text

    /opt/rh/httpd24/root/etc/httpd/conf.d/auth-config.conf

will cause your authentication configuration directives to be loaded before
``ood-portal.conf``. If there are any secrets inside this file you can ensure
privacy by adding restrictive file permissions:

.. code-block:: console

    $ sudo chmod 640 /opt/rh/httpd/root/etc/httpd/conf.d/auth-config.conf

Update main Apache config
----------------------------------------------------------------

Do not directly edit the ``ood-portal.conf`` to include this authentication
module within your Open OnDemand portal. Anytime you need to edit the
``ood-portal.conf`` you should use the :ref:`ood-portal-generator` and its
corresponding ``config.yml``. For example, to add support for an
authentication module with ``AuthType`` of ``my-auth``, you would modify the
``config.yml`` as such:

.. code-block:: yaml

    # /path/to/ood-portal-generator/config.yml
    ---
    # ...
    # Your other custom configuration options...
    # ...

    auth:
      - 'AuthType my-auth'
      - 'Require valid-user'

You would then build the new ``ood-portal.conf`` from this configuration file
with:

.. code-block:: console

    $ scl enable rh-ruby22 -- rake
    Rendering templates/ood-portal.conf.erb => build/ood-portal.conf

This will build ``ood-portal.conf`` in the ``build/`` directory. Open that
file and confirm everything is accurate, then install it in the global
location:

.. code-block:: console

    $ sudo scl enable rh-ruby22 -- rake install
    cp build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

Finally you will restart your Apache HTTP Server for the changes to take
effect.

Sanitize session-specific request headers
----------------------------------------------------------------

You will need to sanitize any session-specific request headers that may be
passed to the backend web servers that a user is proxied to. For most Apache
authentication modules there are module-specific directives that can be
enabled to wipe session information from being passed as headers (e.g.,
``OIDCStripCookies ...``). In other cases you may have to use regular
expressions to search for the session cookies and remove them manually.

For example, Shibboleth does not have a directive to strip session
information from the cookies, so we accomplish this with the following
options in our :ref:`ood-portal-generator` configuration file:

.. code-block:: yaml

    # /path/to/ood-portal-generator/config.yml
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
