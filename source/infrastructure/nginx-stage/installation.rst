.. _nginx-stage-installation:

Installation
============

#. Download the latest stable release and unpack it:

   .. code-block:: sh

      # Set latest release as of writing this
      LATEST="0.2.1"

      # Download latest release
      wget --content-disposition https://github.com/OSC/nginx_stage/archive/v${LATEST}.tar.gz

      # Unpack this archive
      tar xzvf nginx_stage-${LATEST}.tar.gz

      # Change working directory
      cd nginx_stage-${LATEST}

#. Install this package in default ``PREFIX=/opt/ood/nginx_stage`` location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install

   .. note::

      The location of the installation can be changed by altering the
      ``PREFIX`` environment variable:

      .. code-block:: sh

         sudo scl enable rh-ruby22 -- rake install PREFIX="/tmp/nginx_stage"

#. Configure the :program:`nginx_stage` installation by modifying::

     /opt/ood/nginx_stage/config/nginx_stage.yml

   You can read :ref:`nginx-stage-configuration` for details on configuration
   options.

#. Confirm that the Apache proxy is running as the user ``apache``. By default
   :program:`nginx_stage` will only give permissions to the ``apache`` user to
   access the NGINX Unix domain socket files.

#. Give the Apache proxy user ``apache`` elevated privileges when running
   :program:`nginx_stage` by adding a :program:`sudo` entry as:

   .. code-block:: sh

      # /etc/sudoers.d/ood

      Defaults:apache     !requiretty, !authenticate
      apache ALL=(ALL) NOPASSWD: /opt/ood/nginx_stage/sbin/nginx_stage
