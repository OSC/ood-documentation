.. _authentication-overview-map-user:

Setup User Mapping
==================

Every HTTP request sent to the OnDemand portal triggers a call to the
:ref:`ood-auth-map` script to map the remote authenticated user name to the
local system user name. Mapping to the local system user not only restricts
access of OnDemand to local users but it is also required by the OnDemand proxy
to traffic the HTTP data to the user's corresponding per-user NGINX (PUN)
server.

The :ref:`ood-portal-generator` and its corresponding ``config.yml`` are used
to configure both the system command that performs the mapping
(:ref:`user_map_cmd <ood-portal-generator-user-map-cmd>`) and the argument fed
to the system command (:ref:`user_env <ood-portal-generator-user-env>`). By
default these configuration options are defined as:

.. code-block:: yaml

   # /path/to/ood-portal-generator/config.yml
   ---

   user_map_cmd: '/opt/ood/ood_auth_map/bin/ood_auth_map.regex'
   user_env: 'REMOTE_USER'

which uses :ref:`ood-auth-map` for the mapping command and ``REMOTE_USER``
(this variable holds the name of the authenticated user by the web server) as
its command line argument.

This is equivalent to calling from the command line:

.. code-block:: console

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.regex "$REMOTE_USER"

which just echos back the value of ``REMOTE_USER``.

.. note::

   The default user mapping employed by an OnDemand portal **directly** maps
   the remote authenticated user name to the local user name. So the Apache
   authentication module used is expected to set the correct local user name in
   ``REMOTE_USER``.

Custom Mapping
--------------

As mentioned previously the :ref:`ood-portal-generator` configuration options
of interest are:

- :ref:`user_map_cmd <ood-portal-generator-user-map-cmd>`
- :ref:`user_env <ood-portal-generator-user-env>`

It is recommended you read the discussion on :ref:`ood-auth-map` before
modifying these values.

After modifying the ``config.yml`` with the mapping you want you would then
build the new ``ood-portal.conf`` from this configuration file with:

.. code-block:: console

   $ scl enable rh-ruby22 -- rake
   Rendering templates/ood-portal.conf.erb => build/ood-portal.conf

This will build ``ood-portal.conf`` in the ``build/`` directory. Open that file
and confirm everything is accurate, then install it in the global location:

.. code-block:: console

   $ sudo scl enable rh-ruby22 -- rake install
   cp build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

Finally you will need to restart your Apache HTTP Server for the changes to
take effect.
