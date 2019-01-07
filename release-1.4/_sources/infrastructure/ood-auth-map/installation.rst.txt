.. _ood-auth-map-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: sh

      LATEST="{{ ood_auth_map_version }}"
      wget --content-disposition https://github.com/OSC/ood_auth_map/archive/v${LATEST}.tar.gz

   Unpack this archive

   .. code-block:: sh

      tar xzvf ood_auth_map-${LATEST}.tar.gz

   Change working directory:

   .. code-block:: sh

      cd ood_auth_map-${LATEST}

#. Install this package in default ``PREFIX=/opt/ood/ood_auth_map`` location:

   .. code-block:: sh

      sudo scl enable rh-ruby24 -- rake install

   .. note::

      The location of the installation can be changed by altering the
      ``PREFIX`` environment variable:

      .. code-block:: sh

         sudo scl enable rh-ruby24 -- rake install PREFIX="/tmp/ood_auth_map"
