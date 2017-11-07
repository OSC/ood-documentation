.. _update-mapping-script:

Update Mapping Script
=====================

The custom mapping script is maintained by the :ref:`ood-auth-map` project.
Assuming you previously installed it with :ref:`install-mapping-script` you can
update it with the following directions.

Do I need to update?
--------------------

Latest version: ``v{{ ood_auth_map_version }}``

You can compare this to the locally installed :ref:`ood-auth-map` with the
following command:

.. code-block:: console

   $ scl enable rh-ruby22 -- /opt/ood/ood_auth_map/bin/ood_auth_map.regex -v
   ood_auth_map, version {{ ood_auth_map_version }}

where the version number should be given at the end of the line. If the version
numbers match then you can skip this update.

Instructions to update
----------------------

#. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/ood_auth_map
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v{{ ood_auth_map_version }}

#. Install it to its global location:

   .. code-block:: console

      $ sudo scl enable rh-ruby22 -- rake install
      mkdir -p /opt/ood/ood_auth_map/bin
      ...

.. note::

   You will not need to restart the Apache process after an update of the
   mapping script. All changes happen in real time.
