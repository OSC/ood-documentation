.. _app-development-tutorials-rstudio-setup-singularity:

Setup Singularity
=================

Download The Singularity Image
------------------------------

The Singularity image may be downloaded from Singularity Hub by users without sudoer rights by running the following:

  .. code-block:: sh

    singularity pull --name rserver-launcher-centos7.simg shub://OSC/centos7-launcher

This will download the pre-built image to the current working directory.

Alternatively, Build The Singularity Image
------------------------------------------

Running a build is trivial but does require sudoer access to the build host.

Where ``Singularity`` is the file that defines the image. The image is just the base CentOS 7 packages plus a run script. This simplicity is because the actual executables and libraries must be bound and mounted into the container/guest at runtime from the host. By bind-mounting executables and libaries from the host system we are able to swap RStudio versions at launch time without having to update the Singuarlity image.

Likewise the runscript defined in the image uses the host ``$PATH`` which is propagated into the guest's environment as ``$USER_PATH``.

An example Singularity file for running RStudio:

   .. code-block:: sh

      Bootstrap: yum
      OSVersion: 7
      MirrorURL: http://mirror.centos.org/centos-%{OSVERSION}/%{OSVERSION}/os/$basearch/
      Include: yum

      %labels
        Maintainer OSC Gateways

      %help
      This will run RStudio Server which must be mounted with dependencies into the container

      %apprun rserver
        if ! [[ "$USER_PATH" = "" ]]; then
          export PATH="$USER_PATH"
        fi

        exec rserver "${@}"

      %runscript
        if ! [[ "$USER_PATH" = "" ]]; then
          export PATH="$USER_PATH"
        fi

        exec rserver "${@}"
