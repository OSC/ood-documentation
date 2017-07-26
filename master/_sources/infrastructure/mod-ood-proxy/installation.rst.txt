.. _mod-ood-proxy-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: sh

      # Set latest release as of writing this
      LATEST="0-2-stable"

      # Download latest release
      wget --content-disposition https://github.com/OSC/mod_ood_proxy/archive/${LATEST}.tar.gz

      # Unpack this archive
      tar xzvf mod_ood_proxy-${LATEST}.tar.gz

      # Change working directory
      cd mod_ood_proxy-${LATEST}

#. Install this package in default ``PREFIX=/opt/ood/mod_ood_proxy`` location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

  .. note::

     The location of the installation can be changed by altering the ``PREFIX``
     environment variable:

     .. code-block:: sh

        sudo scl enable rh-ruby22 -- rake install PREFIX="/tmp/mod_ood_proxy"
