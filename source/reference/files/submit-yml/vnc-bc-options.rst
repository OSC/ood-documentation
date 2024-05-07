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


.. describe:: websockfiy_cmd (String, "/opt/websockify/run")

    the command to start websockify

    Default
      the '/opt/websockify/run' command

      .. code-block:: yaml

        websockfiy_cmd: "/opt/websockify/run"

    Example
      the '/usr/bin/websockify' command

      .. code-block:: yaml

        websockify_cmd: "/usr/bin/websockify"

.. describe:: vnc_passwd (String, "vnc.passwd")

    the file vncserver will read for a password

    Default
      a file named 'vnc.passwd'

      .. code-block:: yaml

        vnc_passwd: "vnc.passwd"

    Example
      a file named 'my-other-vnc.passwd'

      .. code-block:: yaml

        vnc_passwd: "my-other-vnc.passwd"

.. describe:: vnc_args (String, "")

    vnc arguments to use instead of the specific options
    ``name``, ``geometry``, ``dpi``, ``fonts``, ``idle`` and
    ``extra_args``.

    Default
      no arguments

      .. code-block:: yaml

        vnc_args: ""

    Example
      only specify the xstartup option

      .. code-block:: yaml

        vnc_args: "-xstartup /opt/vnc/startup.sh"

.. describe:: name (String, "")

    the desktop name

    Default
      do not specify name, vncserver defaults to ``host:display# (username)``

      .. code-block:: yaml

        name: ""

    Example
      boot vncserver with ``-name ood-$USER-$DISPLAY`` argument

      .. code-block:: yaml

        name: "ood-ood-$USER-$DISPLAY"

.. describe:: geometry (String, "")

    the geometry size of the VNC desktop

    Default
      do not specify geometry, turbovnc defaults to ``1240x900``

      .. code-block:: yaml

        geometry: ""

    Example
      boot vncserver with ``-geometry 1920x1080`` argument

      .. code-block:: yaml

        geometry: "1920x1080"

.. describe:: dpi (String, "")

    the dots per inch setting of the VNC desktop

    Default
      do not specify dpi

      .. code-block:: yaml

        dpi: ""

    Example
      boot vncserver with ``-dpi 96`` argument

      .. code-block:: yaml

        dpi: "96"

.. describe:: fonts (String, "")

    the font path for X11 fonts

    Default
      do not specify -fp option

      .. code-block:: yaml

        fonts: ""

    Example
      boot vncserver with ``-fp unix/:7100`` argument

      .. code-block:: yaml

        fonts: "unix/:7100"

.. describe:: idle (String, "")

    the idle timeout setting for the vncserver

    Default
      do not specify -idletimeout option

      .. code-block:: yaml

        idle: ""

    Example
      boot vncserver with ``-idletimeout 3600`` argument

      .. code-block:: yaml

        idle: "3600"

.. describe:: extra_args (String, "")

    any extra arguments to pass into vncserver

    Default
      do not specify extra arguments

      .. code-block:: yaml

        idle: ""

    Example
      set the color depth of the vncserver to 32, in addition to any
      other specific argument given above

      .. code-block:: yaml

        extra_args: "-depth 32"

.. warning::
    These items below should not be set by users.  They are
    given for completeness only.  It's likely they'll cause
    errors if overridden.

.. describe:: conn_params (Array<String>, 
      ['host','port','password','spassword','display','websocket'])

    the connection parameters that will be written to the ``conn_file``

    Default
      'host', 'port', 'password', 'spassword', 'display' and 'websocket'

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

  The duration in seconds websockify will wait to send heartbeats
  to the client.

  Default
    Websockify will send heartbeats every 30 seconds.

    .. code-block:: yaml

      websockify_heartbeat_seconds: 30

  Example
    Have websockfiy send heartbeats every 10 seconds.

    .. code-block:: yaml

      websockify_heartbeat_seconds: 10
