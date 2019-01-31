.. _app-development-tutorials-rstudio:

Add A RStudio App
=================

In a previous example we showed how an interactive Jupyter application could be set up. In this example we will explore the different requirements of an RStudio installation.

.. note::

   Confirm that you have worked through the :ref:`app-development-tutorials-interactive-apps-add-jupyter` and previous examples before continuing on.

Software Requirements
---------------------

- `R`_
- `RStudio`_
- `Singularity`_ (3.x)

**Optional** (but recommended) software:

- `Lmod`_ 6.0.1+ or any other CLI tool used to load appropriate environments
  within the batch job before launching the RStudio server, e.g.,

  .. code-block:: sh

     module purge
     module load R/3.5.2

Why Is Singularity Required?
----------------------------

RStudio is not intended to run multiple instances on the same machine. Due to several hardcoded paths in RStudio there are conflicts which necessitate running each instance of RStudio in its own filesystem context. There are two ways OSC has accomplished this: using `Proot`_ and Singularity. OSC has decided to chose Singularity as our solution moving forward because it is both a common tool in HPC, and better maintained than Proot.

Build The Singularity Image
---------------------------

The Singularity image must be built before it can be used. Running a build is trivial but does require sudoer access to the build host.

   .. code-block:: sh

      singularity build -f rstudio_launcher_centos7.simg Singularity

Where `Singularity` is the file that defines the image. The image is basic, installing only the command `which` over the base CentOS 7 packages. This simplicity is because most of the actual executables and libraries must be bound and mounted into the container/guest at runtime from the host.

Likewise the runscript defined in the image uses the host `$PATH` which is propagated into the guest's environment as `$USER_PATH`.

   .. code-block:: sh

      export PATH="$USER_PATH"
      exec rserver "${@}"

Offering Users A Choice Of Software Versions
--------------------------------------------

It is possible to offer users a choice of which versions of R they may run. By offering the choice you enable early adopters a chance to use newer versions of R, without causing potentially breaking changes in existing code.

To begin add a select control in `form.yml` for the versions of R that are available on your system.

  .. code-block:: yaml

    version:  
      widget: select
      label: "R version"
      help: "This defines the version of R you want to load."
      options:
        # Each value in the options represents a valid set of modules to load
        - [ "3.4.2", "intel/16.0.3 R/3.4.2 rstudio/1.1.380_server"]
        - [ "3.3.2", "intel/16.0.3 R/3.3.2 rstudio/1.0.136_server"]

After users have submitted the form, its values are used as context when expanding the template files; in particular we will have set the modules to load. Next, to set the version of R and RStudio next edit `template/script.sh.erb`.

  .. code-block:: sh

    # Load the version of R and RStudio that the user has selected
    module load <%= context.version %>

Running RStudio
---------------

Authentication
..............

In `template/before.sh.erb` the variable `password` is set and its value is exported as `RSTUDIO_PASSWORD`.

  .. code-block:: sh

    # Define a password and export it for RStudio authentication
    password="$(create_passwd 16)"
    export RSTUDIO_PASSWORD="${password}"

In `template/script.sh.erb` export the path to PAM helper executable `RSTUDIO_AUTH`.

  .. code-block:: sh

    # PAM auth helper used by RStudio
    export RSTUDIO_AUTH="${PWD}/bin/auth"

    # Generate an `rsession` wrapper script
    export RSESSION_WRAPPER_FILE="${PWD}/rsession.sh"
    (
    umask 077
    sed 's/^ \{2\}//' > "${RSESSION_WRAPPER_FILE}" << EOL
      #!/usr/bin/env bash

      # Log all output from this script
      export RSESSION_LOG_FILE="${RSTUDIO_SINGULARITY_HOST_MNT}${PWD}/rsession.log"

      exec &>>"\${RSESSION_LOG_FILE}"

      # Launch the original command
      echo "Launching rsession..."
      set -x
      exec rsession --r-libs-user "${R_LIBS_USER}" "\${@}"
    EOL
    )
    chmod 700 "${RSESSION_WRAPPER_FILE}"

Use A Custom RSession Wrapper
.............................

Using a custom RSession wrapper enables us to get diagnostic logging and ensure that user space libraries are available. We write this file from inside `template/script.sh.erb`.

  .. code-block:: sh

    # Generate an `rsession` wrapper script
    export RSESSION_WRAPPER_FILE="${PWD}/rsession.sh"
    (
    umask 077
    sed 's/^ \{2\}//' > "${RSESSION_WRAPPER_FILE}" << EOL
      #!/usr/bin/env bash

      # Log all output from this script
      export RSESSION_LOG_FILE="${RSTUDIO_SINGULARITY_HOST_MNT}${PWD}/rsession.log"

      exec &>>"\${RSESSION_LOG_FILE}"

      # Launch the original command
      echo "Launching rsession..."
      set -x
      exec rsession --r-libs-user "${R_LIBS_USER}" "\${@}"
    EOL
    )
    chmod 700 "${RSESSION_WRAPPER_FILE}"

Launching RStudio Using Singularity 
...................................

Ensure that R, RStudio and their dependencies are available inside the guest by binding their paths on the host into the container. Likewise ensure that each instance of RStudio gets its own private `/tmp` by binding `$TMPDIR` on the host to `/tmp` in the guest.

  .. code-block:: sh

    export SINGULARITY_BINDPATH="/usr/local,/etc/profile.d/lmod.sh,/usr/share/lmod,/opt/intel,/opt/mvapich2,/usr/lib64,$TMPDIR:/tmp"

    singularity run /users/PZS0002/mrodgers/singularity/centos7.simg \
     --www-port "${port}" \
     --auth-none 0 \
     --auth-pam-helper-path "${RSTUDIO_AUTH}" \
     --auth-encrypt-password 0 \
     --rsession-path "${RSESSION_WRAPPER_FILE}"

  .. warning::

      If `$TMPDIR` is not guaranteed to be unique then consider appending the results of a `mktemp -d` to it.

Complete OSC-Specific Example
-----------------------------

The OSC offers its OnDemand users an RStudio interactive application. For reference this is the complete OSC-specific implementation available on `Github`_.

.. _github: https://github.com/OSC/bc_osc_rstudio_server
.. _lmod: https://www.tacc.utexas.edu/research-development/tacc-projects/lmod
.. _proot: https://proot-me.github.io/
.. _r: https://www.r-project.org/
.. _rstudio: https://www.rstudio.com/
.. _singularity: https://www.sylabs.io/