.. _ood-auth-map-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: sh

      # Set latest release as of writing this
      LATEST="{{ ood_auth_map_version }}"

      # Download latest release
      wget --content-disposition https://github.com/OSC/ood_auth_map/archive/v${LATEST}.tar.gz

      # Unpack this archive
      tar xzvf ood_auth_map-${LATEST}.tar.gz

      # Change working directory
      cd ood_auth_map-${LATEST}

#. Install this package in default ``PREFIX=/opt/ood/ood_auth_map`` location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

   .. note::

      The location of the installation can be changed by altering the
      ``PREFIX`` environment variable:

      .. code-block:: sh

         sudo scl enable rh-ruby22 -- rake install PREFIX="/tmp/ood_auth_map"
