.. _authentication-overview-map-user:


Configure Apache to map authenticated user to system user
================================================================

Default mapping works for most use cases
----------------------------------------

In OnDemand, Apache is configured to use a mapping :ref:`ood-auth-map` that is
executed on each request to determine which system user the authenticated user
is associated with, so that the request will be proxied to the correct system
user's processes.

The way this typically works:

1. Apache is configured to specify command to execute the mapping script by
   setting this to the environment variable ``OOD_USER_MAP_CMD``
2. The mod_ood_proxy Apache module executes this command on each request, passing the env var
   ``REMOTE_USER`` as an argument. The executed command outputs the mapped system user.
3. The request is then proxied to the system user's per user NGINX process.

Since most Apache authentication modules set ``REMOTE_USER`` with the
authenticated user, and often this user is the system user, the default mapping
functionality between authenticated user and system user should be sufficient.

Customizing mapping
-------------------

See :ref:`ood-auth-map` for an overview on how these mapping scripts work. The
default mapping script just echo's back the ``REMOTE_USER`` so that is used
as the system user.

If you need to configure the mapping script to use a regex on the ``REMOTE_USER``,
or have the mapping script inspect a different env var
besides ``REMOTE_USER``, or need to use a custom mapping script, look at
configuration options for the :ref:`ood-portal-generator`, including customizing
the ``user_map_cmd`` and ``user_env`` configuration options, which result in the
generated Apache config setting ``OOD_USER_MAP_CMD`` and ``OOD_USER_ENV`` vars
that the mod_ood_proxy module uses.
