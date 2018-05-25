.. _ood-auth-map-installation:

Installation
============

#. Download the latest stable release and unpack it:

   Download the latest release as of this writing:
   
   .. code-block:: console

      $ LATEST="{{ ood_auth_map_version }}"
      $ wget --content-disposition https://github.com/OSC/ood_auth_map/archive/v${LATEST}.tar.gz

   Unpack archive:
   
   .. code-block:: console
   
      $ tar xzvf ood_auth_map-${LATEST}.tar.gz

   Change working directory:
   
   .. code-block:: console
   
      $ cd ood_auth_map-${LATEST}

#. Install this package in default ``PREFIX=/opt/ood/ood_auth_map`` location:

   .. code-block:: console

      $ sudo scl enable rh-ruby22 -- rake install

   .. note::

      The location of the installation can be changed by altering the
      ``PREFIX`` environment variable:

      .. code-block:: console

         $ sudo scl enable rh-ruby22 -- rake install PREFIX="/tmp/ood_auth_map"
