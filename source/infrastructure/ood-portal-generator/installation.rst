.. _ood-portal-generator-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: console

      $ LATEST="{{ ood_portal_generator_version }}"
      $ wget --content-disposition https://github.com/OSC/ood-portal-generator/archive/v${LATEST}.tar.gz
      $ tar xzvf ood-portal-generator-${LATEST}.tar.gz
      $ cd ood-portal-generator-${LATEST}

#. Install this package in the ``/opt/ood/ood-portal-generator`` location:

   .. code-block:: console

      $ sudo mkdir -p /opt/ood/ood-portal-generator
      $ sudo cp -a ./. /opt/ood/ood-portal-generator/
