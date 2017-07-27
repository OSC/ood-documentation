.. _update-mapping-script:

Update Mapping Script
=====================

The custom mapping script is maintained by the :ref:`ood-auth-map` project.
Assuming you previously installed it with :ref:`install-mapping-script` you can
update it with the following directions.

Do I need to update?
--------------------

Latest version: ``v0.0.3``

You can compare this to the locally installed :ref:`ood-auth-map` with the
following command:

.. code-block:: sh

   /opt/ood/ood_auth_map/bin/ood_auth_map -v
   #=> ood_auth_map v0.0.3

where the version number should be given at the end of the line. If the version
numbers match then you can skip this update.

Instructions to update
----------------------

#. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/ood_auth_map
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v0.0.3

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/ood_auth_map/bin
      # => cp ...

.. note::

   You will not need to restart the Apache process after an update of the
   mapping script. All changes happen in real time.
