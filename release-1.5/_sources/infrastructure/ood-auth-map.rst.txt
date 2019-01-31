.. _ood-auth-map:

ood_auth_map
============

`View on GitHub <https://github.com/OSC/ondemand/tree/master/ood_auth_map>`__

This library provides a few useful scripts that can map a supplied
authenticated username to a local system username. This is typically used to
map the Apache proxy's ``REMOTE_USER`` to a local system user when proxying the
client to the correct backend per-user NGINX process listening on a Unix domain
socket.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   ood-auth-map/usage
