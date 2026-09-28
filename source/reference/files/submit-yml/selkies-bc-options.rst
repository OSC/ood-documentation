.. _selkies-bc-options:

Batch Connect Selkies Options
=============================

The ``selkies`` template streams a desktop to the browser with `Selkies`_, through
the portal's reverse proxy like any web app, with audio, gamepads, and the node's
GPU encoding the stream where it has one. The job runs Selkies' session launcher,
``selkies-session``, which starts what the node lacks (a sound server, and an Xvfb
on the X11 backend) and serves the desktop on the port the job chose.

As on the ``vnc`` template, the app's ``script.sh`` is the desktop, and the session
ends when it returns, so a desktop app changes templates without other changes.
Selkies runs in its secure mode: once it answers, the job provisions a session
token, stored as the connection's ``password``, and only then reports the session
running. The launch button carries the token; the node's port refuses anyone
without it.

All the options in :ref:`basic-bc-options` apply in addition to what's listed below.

  .. code-block:: yaml

     batch_connect:
       template: "selkies"
       selkies_cmd: "selkies-session"
       selkies_session: null
       selkies_args: ""
       selkies_timeout_seconds: 120
       password_size: 32

.. describe:: selkies_cmd (String, "selkies-session")

    The command that starts Selkies' session launcher on the compute node, with
    arguments. The job adds the port, the desktop, and the options that leave the
    login and TLS to the portal.

    Default
      ``selkies-session`` from a native package or a module on ``PATH``.

      .. code-block:: yaml

         selkies_cmd: "selkies-session"

    Example
      Selkies' AppImage, on a node where nothing can be installed. Where users
      cannot mount FUSE, extract it once with ``--appimage-extract`` and use
      ``squashfs-root/AppRun`` in its place.

      .. code-block:: yaml

         selkies_cmd: "/apps/selkies/selkies-x86_64.AppImage selkies-session"

    Example
      A container image with Selkies and a desktop in it, on the node's GPU.

      .. code-block:: yaml

         selkies_cmd: "apptainer exec --nv /apps/selkies/desktop.sif selkies-session"

.. describe:: selkies_session (String, null)

    A desktop installed on the node or in the container, started in the user's
    home in place of the app's ``script.sh``: a session name (``xfce``, ``kde``,
    ``lxqt``, ``gnome``) or a command. Empty starts the default desktop. Use it
    where the launcher cannot see the job's directory, as in a container with a
    home of its own. The session then runs until it is deleted or its walltime
    ends, rather than ending with the desktop.

    Default
      Unset: the app's ``script.sh`` is the desktop.

    Example
      The desktop the user picked in the form.

      .. code-block:: yaml

         selkies_session: "<%= desktop %>"

.. describe:: selkies_args (String, "")

    Extra arguments passed to Selkies. See the `Selkies settings`_ for all of them.

    Default
      No extra arguments.

      .. code-block:: yaml

         selkies_args: ""

    Example
      Stream through Selkies' Wayland backend, where ``script.sh`` starts a Wayland
      compositor or a desktop that starts one.

      .. code-block:: yaml

         selkies_args: "--wayland"

.. describe:: selkies_timeout_seconds (Integer, 120)

    How long the job waits for Selkies to answer before it fails. The
    ``SELKIES_TIMEOUT_SECONDS`` environment variable sets it as well.

    Default
      Two minutes.

      .. code-block:: yaml

         selkies_timeout_seconds: 120

.. describe:: password_size (Integer, 32)

    The length of the session token and of the master token that provisions it.

    Default
      32 characters.

      .. code-block:: yaml

         password_size: 32

Requirements
------------

The compute node needs a Selkies release newer than 2.0.0, ``curl``, a desktop,
and Xvfb for the X11 backend. The portal's ``host_regex`` has to admit the node,
as for every interactive app.

The master token reaches Selkies through the job's environment, never a command
line. A container started with a clean environment still receives it through
``APPTAINERENV_SELKIES_MASTER_TOKEN``; a launcher that never does ends the job
before it is reported running.

The session token rides in the fragment of the URL the launch button opens,
which the browser never sends, so no access log records it. It is valid only
while the session runs.

Configuring the Cluster
-----------------------

A site configures the launcher once for every Selkies app on a cluster, as it
does for the other templates:

  .. code-block:: yaml

     # /etc/ood/config/clusters.d/my_cluster.yml
     v2:
       batch_connect:
         selkies:
           script_wrapper: |
             module load selkies
             %s

Dashboards before Selkies support show no launch button of their own; an app's
``view.html.erb`` adds one:

  .. code-block:: erb

     <a class="btn btn-primary" href="/rnode/<%= host %>/<%= port %>/#token=<%= password %>" target="_blank">
       Launch Desktop
     </a>

.. _Selkies: https://github.com/selkies-project/selkies
.. _Selkies settings: https://github.com/selkies-project/selkies/blob/main/docs/settings.md
