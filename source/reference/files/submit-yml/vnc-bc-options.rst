.. _vnc-bc-options:

Batch Connect VNC Options
=========================


All the options in :ref:`basic-bc-options` apply in addition to what's listed below.

  .. code-block:: yaml
  
    batch_connect:
      template: "vnc"
      conn_params:
        - host
        - port
        - password
        - spassword
        - display
        - websocket
      websockify_cmd: "/opt/websockify/run"
      vncserver_cmd: "${VNCSERVER_CMD:-vncserver}"
      vncpasswd_cmd: "${VNCPASSWD_CMD:-vncpasswd}"
      vnc_passwd: "vnc.passwd"
      vnc_args: nil
      name: ""
      geometry: ""
      dpi: ""
      fonts: ""
      idle: ""
      extra_args: ""
      vnc_clean: "..."
      websockify_heartbeat_seconds: 30


.. describe:: websockify_cmd (String, "/opt/websockify/run")

    the command to start ``websockify``.

    Default
      The ``/opt/websockify/run`` command.

      .. code-block:: yaml

        websockify_cmd: "/opt/websockify/run"

    Example
      The ``/usr/bin/websockify`` command.

      .. code-block:: yaml

        websockify_cmd: "/usr/bin/websockify"

.. describe:: vncserver_cmd (String, "${VNCSERVER_CMD:-vncserver}")

    the command used to start, check and stop the VNC server. Set it to a
    full path so a user's ``PATH`` (for example a conda environment loaded
    from ``~/.bashrc``) can't put a different ``vncserver`` first.

    If this option isn't set, the ``VNCSERVER_CMD`` environment variable is
    used, and if that isn't set either, ``vncserver`` from the ``PATH``.
    The variable has to be set before the template starts the VNC server,
    for example in a ``script_wrapper`` or with ``job_environment``.
    Setting it in ``before.sh`` is too late, because ``before.sh`` is
    sourced after the VNC server has started.

    This option applies to the ``vnc`` template only. The ``vnc_container``
    template runs ``vncserver`` inside the container.

    Default
      ``$VNCSERVER_CMD`` if it is set, otherwise ``vncserver`` from the ``PATH``.

      .. code-block:: yaml

        vncserver_cmd: "${VNCSERVER_CMD:-vncserver}"

    Example
      Always use TurboVNC's ``vncserver``.

      .. code-block:: yaml

        vncserver_cmd: "/opt/TurboVNC/bin/vncserver"

    Example
      Set the environment variable for every VNC app on a cluster, in the
      cluster's ``batch_connect`` configuration.

      .. code-block:: yaml

        batch_connect:
          vnc:
            script_wrapper: |
              export VNCSERVER_CMD="/opt/TurboVNC/bin/vncserver"
              %s

.. describe:: vncpasswd_cmd (String, "${VNCPASSWD_CMD:-vncpasswd}")

    the command used to write the VNC password file. It works the same way
    as ``vncserver_cmd``, with the ``VNCPASSWD_CMD`` environment variable.
    This option applies to the ``vnc`` template only.

    Default
      ``$VNCPASSWD_CMD`` if it is set, otherwise ``vncpasswd`` from the ``PATH``.

      .. code-block:: yaml

        vncpasswd_cmd: "${VNCPASSWD_CMD:-vncpasswd}"

    Example
      Always use TurboVNC's ``vncpasswd``.

      .. code-block:: yaml

        vncpasswd_cmd: "/opt/TurboVNC/bin/vncpasswd"

.. describe:: vnc_passwd (String, "vnc.passwd")

    the file ``vncserver`` will read for a password

    Default
      a file named ``vnc.passwd``.

      .. code-block:: yaml

        vnc_passwd: "vnc.passwd"

    Example
      a file named ``my-other-vnc.passwd``.

      .. code-block:: yaml

        vnc_passwd: "my-other-vnc.passwd"

.. describe:: vnc_args (String, "")

    VNC arguments to use instead of the specific options
    ``name``, ``geometry``, ``dpi``, ``fonts``, ``idle`` and
    ``extra_args``.

    Default
      no arguments

      .. code-block:: yaml

        vnc_args: ""

    Example
      Only specify the ``xstartup`` option.

      .. code-block:: yaml

        vnc_args: "-xstartup /opt/vnc/startup.sh"

.. describe:: name (String, "")

    the desktop name

    Default
      do not specify name, ``vncserver`` defaults to ``host:display# (username)``

      .. code-block:: yaml

        name: ""

    Example
      boot ``vncserver`` with ``-name ood-$USER-$DISPLAY`` argument.

      .. code-block:: yaml

        name: "ood-ood-$USER-$DISPLAY"

.. describe:: geometry (String, "")

    the geometry size of the VNC desktop

    Default
      do not specify geometry, TurboVNC defaults to ``1240x900``

      .. code-block:: yaml

        geometry: ""

    Example
      boot ``vncserver`` with ``-geometry 1920x1080`` argument.

      .. code-block:: yaml

        geometry: "1920x1080"

.. describe:: dpi (String, "")

    the dots per inch setting of the VNC desktop

    Default
      do not specify dpi

      .. code-block:: yaml

        dpi: ""

    Example
      boot ``vncserver`` with ``-dpi 96`` argument

      .. code-block:: yaml

        dpi: "96"

.. describe:: fonts (String, "")

    the font path for X11 fonts

    Default
      do not specify ``-fp`` option

      .. code-block:: yaml

        fonts: ""

    Example
      boot ``vncserver`` with the ``-fp unix/:7100`` argument.

      .. code-block:: yaml

        fonts: "unix/:7100"

.. describe:: idle (String, "")

    the idle timeout setting for the ``vncserver``.

    Default
      do not specify ``-idletimeout`` option

      .. code-block:: yaml

        idle: ""

    Example
      boot ``vncserver`` with ``-idletimeout 3600`` argument

      .. code-block:: yaml

        idle: "3600"

.. describe:: extra_args (String, "")

    any extra arguments to pass into ``vncserver``.

    Default
      do not specify extra arguments

      .. code-block:: yaml

        idle: ""

    Example
      set the color depth of the ``vncserver`` to 32, in addition to any
      other specific argument given above

      .. code-block:: yaml

        extra_args: "-depth 32"

.. describe:: vnc_clean (String, "...")

    the shell code that stops this job's VNC server. It runs in two places:
    before each attempt to start the VNC server, and in ``clean_up`` when
    the job ends.

    The default stops the server by its display number, so only the VNC
    server this job started is stopped. Other VNC sessions the user has
    on the same node, from other jobs, are left alone. The ``display``
    variable is empty until the server has started, so before that the
    default does nothing. With the ``vnc_container`` template, the default
    runs ``vncserver -kill`` inside the container instance.

    If you set this option, your code replaces the default completely and
    is the only thing that stops the VNC server when the job ends. Check
    that ``display`` is set before you use it.

    Default
      stop this job's VNC server by display.

      .. code-block:: yaml

        vnc_clean: '[[ -n ${display} ]] && ${VNCSERVER_CMD:-vncserver} -kill :${display}'

    Example
      also log which display was stopped.

      .. code-block:: yaml

        vnc_clean: '[[ -n ${display} ]] && vncserver -kill :${display} && echo "Stopped VNC display :${display}"'

.. warning::
    These items below should not be set by users.  They are
    given for completeness only.  It's likely they'll cause
    errors if overridden.

.. describe:: conn_params (Array<String>, 
      ['host','port','password','spassword','display','websocket'])

    the connection parameters that will be written to the ``conn_file``

    Default
      ``host``, ``port``, ``password``, ``spassword``, ``display`` and ``websocket``.

      .. code-block:: yaml

        conn_params:
          - 'host'
          - 'port'
          - 'password'
          - 'spassword'
          - 'display'
          - 'websocket'

    Example
      The API to connect to can change in the ``script.sh.erb`` based off of
      something that can only be determined during the job (for example an
      environment variable in a module).

      .. code-block:: yaml
        
        conn_params:
          - the_connect_api

.. describe:: websockify_heartbeat_seconds (Integer, 30)

  The duration in seconds ``websockify`` will wait to send heartbeats
  to the client.

  Default
    ``websockify`` will send heartbeats every 30 seconds.

    .. code-block:: yaml

      websockify_heartbeat_seconds: 30

  Example
    Have ``websockfiy`` send heartbeats every 10 seconds.

    .. code-block:: yaml

      websockify_heartbeat_seconds: 10
