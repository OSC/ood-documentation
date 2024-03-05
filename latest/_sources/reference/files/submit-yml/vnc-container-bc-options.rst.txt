.. _vnc-container-bc-options:

Batch Connect VNC Container Options
===================================


All the options in :ref:`vnc-bc-options` apply in addition to what's listed below.

  .. code-block:: yaml
  
    batch_connect:
      template: "vnc_container"
      # other 'vnc' or 'basic' options removed for brevity.
      container_path: "vnc_container.sif"
      container_bindpath: ""
      container_module: "singularity"
      container_command: "singularity"
      container_start_args: []


.. describe:: container_path (String, "vnc_container.sif")

    The full path to the container image you wish to boot.

    Default
      Load the vnc_container.sif image.

      .. code-block:: yaml

        container_path: "vnc_container.sif"

    Example
      Provide an absolute path to a ``vnc_container.sif`` image.

      .. code-block:: yaml

        container_path: "/absolute/path/to/my/container/vnc_container.sif"

.. describe:: container_bindpath (String, "")

    A comma seperated list of mountpoints you wish to bind into the container.

    Default
      Do not bind any paths into the container.

      .. code-block:: yaml

        container_bindpath: ""

    Example
      Bind /etc, /dev and /usr into the container.

      .. code-block:: yaml

        container_bindpath: "/etc,/dev,/usr"

.. describe:: container_module (String, "singularity")

    The module to load before starting the container.

    Default
      Load the ``singularity`` module.

      .. code-block:: yaml

        container_module: "singularity"

    Example
      Load the ``singularity/1.1.3`` module.

      .. code-block:: yaml

        container_module: "singularity/1.1.3"

.. describe:: container_command (String, "singularity")

    The command used to start the container.

    Default
      Use the ``singularity`` command.

      .. code-block:: yaml

        container_module: "singularity"

    Example
      Use the ``apptainer`` command.

      .. code-block:: yaml

        container_module: "apptainer"

.. describe:: container_start_args (String, [])

    Arguments to pass to the container start command.

    Default
      Pass no additional arguments.

      .. code-block:: yaml

        container_start_args: []

    Example
      Pass ``--fakeroot`` to the container ``start`` command.

      .. code-block:: yaml

        container_start_args:
          - "--fakeroot"

Starter def file
................

This is a ``.def`` file that we've tested this feature with.
You can use this as an example to start and update as required.


.. note::
  Note that we're installing turbovnc and websockify *inside*
  the container. This is important as all processes will run
  inside the contianer and not on the host.

  You can still install these on the host machine, but they will
  need to be mounted inside the container as the processes are
  expected to be ran *inside* the container.

.. code-block:: singularity

  Bootstrap: docker

  From: rockylinux/rockylinux:8

  %environment
    PATH=/opt/TurboVNC/bin:$PATH
    LANGUAGE="en_US.UTF-8"
    LC_ALL="en_US.UTF-8"
    LANG="en_US.UTF-8"

  %post   
      dnf install -y epel-release
      dnf groupinstall -y xfce
      dnf install -y python3-pip xorg-x11-xauth
      pip3 install ts
      dnf install -y https://yum.osc.edu/ondemand/latest/compute/el8Server/x86_64/python3-websockify-0.10.0-1.el8.noarch.rpm
      dnf install -y https://yum.osc.edu/ondemand/latest/compute/el8Server/x86_64/turbovnc-2.2.5-1.el8.x86_64.rpm
      dnf clean all
      chown root:root /opt/TurboVNC/etc/turbovncserver-security.conf
      rm -rf /var/cache/dnf/*
