.. _install-mapping-script:

Install User Mapping Script
===========================

You will need to map the Apache authenticated user to the local system user.
This is done with the :ref:`ood-auth-map` tool.

#. Clone and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src
      scl enable git19 -- git clone https://github.com/OSC/ood_auth_map.git
      cd ood_auth_map/
      scl enable git19 -- git checkout v0.0.3

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/ood_auth_map/bin
      # => cp ...

The principle behind this script is that you call it with a URL encoded
``REMOTE_USER`` user name as the only argument, and it will return the mapping
to the local system user name if it exists.
