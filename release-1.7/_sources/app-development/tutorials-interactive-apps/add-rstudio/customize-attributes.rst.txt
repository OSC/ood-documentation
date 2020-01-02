.. _app-development-tutorials-interactive-apps-add-rstudio-customize-attributes:

Customize Attributes
====================

Now we will customize the app to work on a given cluster. Be sure that you walk through :ref:`app-development-tutorials-interactive-apps-add-jupyter-software-requirements` for the given cluster ahead of time.

The main responsibility of the ``form.yml`` file (:ref:`app-development-interactive-form`) located in the root of the app is for defining the attributes (their values or HTML form elements) used when generating the batch script.

1. We will begin by adding a cluster for the RStudio app to use. You do this by editing the ``form.yml`` in your favorite editor as such:

  .. code-block:: yaml
    :emphasize-lines: 3

    # ~/ondemand/dev/bc_example_rstudio/form.yml
    ---
    cluster: "my_cluster"
    form:
      - bc_account
      - bc_queue
      - bc_num_hours
      - bc_num_slots
      - bc_email_on_started


  where we replace ``my_cluster`` with a valid cluster that corresponds to a cluster configuration file located under ``/etc/ood/config/clusters.d/my_cluster.yml``.

2. Next we will modify the runtime environment to allow RStudio to launch inside a Singularity container. There are two ways to accomplish this, and both modify the file ``~/ondemand/dev/bc_example_rstudio/template/script.sh.erb``.

  If you are not using LMod, then in the function ``setup_env`` replace the value for ``RSTUDIO_SERVER_IMAGE`` with the absolute path to the Singularity image, and ``SINGULARITY_BINDPATH`` with all the directories that contain dependencies for RStudio server and R. Discovering those paths may benefit from using ``ptrace`` or ``lsof``. Finally ensure that ``R`` and ``rserver`` are in the ``PATH``. 

  If you are using LMod then create a module like the following:

  .. code-block:: lua
    :emphasize-lines: 4,5,6

    -- $path/to/lmodfiles/rstudio_container/v0.0.1.lua
    help([[ rstudio - loads rstudio with singularity environment for ondemand apps ]])
    whatis("loads rstudio with singularity environment for ondemand")
    setenv("RSTUDIO_SERVER_IMAGE","/usr/local/project/ondemand/singularity/rstudio/rstudio_launcher_centos7.simg")
    setenv("SINGULARITY_BINDPATH","/etc,/media,/mnt,/opt,/srv,/usr,/var")
    append_path("PATH", "/usr/lib/rstudio-server/bin)

  Then replace the exports in the function ``setup_env`` with the appropriate ``module use $module_path`` and ``module load rstudio_container/v0.0.1``.

  .. code-block:: sh

    setup_env () {
      # Additional environment which could be moved into a module
      # Change these to suit
      # export RSTUDIO_SERVER_IMAGE="/apps/rserver-launcher-centos7.simg"
      # The most robust SINGULARITY_BINDPATH appears to be: /etc,/media,/mnt,/opt,/srv,/usr,/var.
      # That, plus Singularity's standard auto-mounts, covers most of the Filesystem Hierarchy Standard.
      #
      # Notable exceptions include:
      #
      #     - /tmp which we are explicitly overriding
      #     - those directories which in Centos 7 are commonly symlinks to/usr
      #     - root's home directory
      #
      # export SINGULARITY_BINDPATH="/etc,/media,/mnt,/opt,/srv,/usr,/var"
      # export PATH="$PATH:/usr/lib/rstudio-server/bin"
      # export SINGULARITYENV_PATH="$PATH"
      module use "$path/to/lmodfiles"
      module load rstudio_container/v0.0.1
    }
    setup_env

.. note::

  It is possible to set the environment without using a module system, by setting the variables in ``~/ondemand/dev/bc_example_rstudio/template/script.sh.erb``.

.. warning::

  There was a breaking change between Singularity 2.x and 3.x with how a host ``PATH`` may be propagated to the guest. In version 2.x you must export ``PATH`` as ``SINGULARITYENV_PATH`` in order for the ``PATH`` inside the container to include ``rserver``. In version 3.x ``PATH`` alone is sufficient.