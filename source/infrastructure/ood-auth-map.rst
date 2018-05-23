.. _ood-auth-map:

ood_auth_map
============

`View on GitHub <https://github.com/OSC/ood_auth_map>`__

This library provides a few useful scripts that can map a supplied
authenticated username to a local system username. This is typically used to
map the Apache proxy's ``REMOTE_USER`` to a local system user when proxying the
client to the correct backend per-user NGINX process listening on a Unix domain
socket.

To get started you will need at a minimum the following prerequisites:

- The Ruby_ language version 2.2 or newer

Please see :ref:`install-software` on how to install the above requirements.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   ood-auth-map/installation
   ood-auth-map/usage

.. _ruby: https://www.ruby-lang.org/en/
