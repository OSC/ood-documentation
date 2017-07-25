.. _install-proxy-module:

Install Proxy Module for Apache
===============================

An Apache module written in Lua is the primary component for the proxy logic.
It is given by the :ref:`mod-ood-proxy` project.

#. Clone and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src
      scl enable git19 -- git clone https://github.com/OSC/mod_ood_proxy.git
      cd mod_ood_proxy/
      scl enable git19 -- git checkout v0.3.0

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/mod_ood_proxy
      # => cp ...
