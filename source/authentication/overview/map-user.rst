.. _authentication-overview-map-user:


Configure Apache to map authenticated user to system user
================================================================

In OnDemand Apache is configured to use a mapping :ref:`ood-auth-map` that is
executed on each request to determine which system user the authenticated user
is associated with, so that the request will be proxied to the correct system
user's processes.


1. See :ref:`ood-auth-map` for an overview on how this script works.
