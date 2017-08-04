.. _update-proxy-module:

Update Proxy Module for Apache
==============================

The custom Apache proxy module is maintained by the :ref:`mod-ood-proxy`
project. Assuming you previously installed it with :ref:`install-proxy-module`
you can update it with the following directions.

Do I need to update?
--------------------

Latest version: ``v{{ mod_ood_proxy_version }}``

You can compare this to the locally installed :ref:`mod-ood-proxy` with the
following command:

.. code-block:: sh

   grep 'VERSION' /opt/ood/mod_ood_proxy/lib/ood/version.lua
   #=>   VERSION = '{{ mod_ood_proxy_version }}'

where the version number should be given at the end of the line. If the version
numbers match then you can skip this update.

Instructions to update
----------------------

#. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/mod_ood_proxy
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v{{ mod_ood_proxy_version }}

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/mod_ood_proxy
      # => cp ...

.. note::

   You will not need to restart the Apache process after an update of the
   custom OOD proxy module.
