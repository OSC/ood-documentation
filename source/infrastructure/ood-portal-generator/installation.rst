.. _ood-portal-generator-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: sh

      # Set latest release as of writing this
      LATEST="{{ ood_portal_generator_version }}"

      # Download latest release
      wget --content-disposition https://github.com/OSC/ood-portal-generator/archive/v${LATEST}.tar.gz

      # Unpack this archive
      tar xzvf ood-portal-generator-${LATEST}.tar.gz

      # Change working directory
      cd ood-portal-generator-${LATEST}

#. Install this package in the ``/opt/ood/ood-portal-generator`` location:

   .. code-block:: sh

      sudo mkdir -p /opt/ood/ood-portal-generator
      sudo cp -a ./. /opt/ood/ood-portal-generator/
