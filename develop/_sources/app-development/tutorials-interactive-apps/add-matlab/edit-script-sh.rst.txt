.. _app-development-tutorials-interactive-apps-add-matlab-edit-script-sh:

Edit Launch Script
==================

Here we will look at the script that actually launches MATLAB ``~/ondemand/dev/bc_my_center_matlab/template/script.sh.erb``.

By now you should have selected your prefered window manager. Examples of using XFCE, Mate, and Fluxbox:

- :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-xfce`
- :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-mate`
- :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-fluxbox`


Invoking MATLAB without a Window Manager
----------------------------------------

    .. code-block:: shell
       :linenos:

        cd "$HOME"

        #
        # Start MATLAB
        #

        # Load the required environment
        module load xalt/latest <%= context.version %>

        # Launch MATLAB
        # Switch the implementation on if the user requested a visualization GPU node
        <%- if context.node_type.include?("vis") -%>
        module load intel/16.0.3 virtualgl  # Perform whatever set up you want / need
        module list  # List loaded modules for debugging purposes
        set -x
        vglrun matlab -desktop -nosoftwareopengl  # Launch MATLAB using VirtualGL
        <%- else -%>
        # When not using a GPU node
        module list  # List loaded modules for debugging purposes
        set -x
        matlab -desktop  # Launch MATLAB
        <%- end -%>


.. _app-development-tutorials-interactive-apps-add-matlab-wm-xfce:

Use XFCE for the Window Manager
-------------------------------

XFCE is OSC's prefered desktop environment for launching VNC applications. The code for starting XFCE in the background looks like this (see highlighted lines 1-20):

    .. code-block:: shell
      :emphasize-lines: 1-20
      :linenos:

        #
        # Launch Xfce Window Manager and Panel
        #

        (
          export SEND_256_COLORS_TO_REMOTE=1
          # session.staged_root.join("config") refers to /.../bc_my_center_matlab/template/config
          # which is copied at job start time to a session specifc directory.
          # It will override without replacing any XFCE settings that the user
          # already has.
          export XDG_CONFIG_HOME="<%= session.staged_root.join("config") %>"
          export XDG_DATA_HOME="<%= session.staged_root.join("share") %>"
          export XDG_CACHE_HOME="$(mktemp -d)"
          module restore
          set -x
          xfwm4 --compositor=off --daemon --sm-client-disable
          xsetroot -solid "#D3D3D3"
          xfsettingsd --sm-client-disable
          xfce4-panel --sm-client-disable
        ) &

        cd "$HOME"

        #
        # Start MATLAB
        #

        # Load the required environment
        module load xalt/latest <%= context.version %>

        # Launch MATLAB
        # Switch the implementation on if the user requested a visualization GPU node
        <%- if context.node_type.include?("vis") -%>
        module load intel/16.0.3 virtualgl  # Perform whatever set up you want / need
        module list  # List loaded modules for debugging purposes
        set -x
        vglrun matlab -desktop -nosoftwareopengl  # Launch MATLAB using VirtualGL
        <%- else -%>
        # When not using a GPU node
        module list  # List loaded modules for debugging purposes
        set -x
        matlab -desktop  # Launch MATLAB
        <%- end -%>

.. _app-development-tutorials-interactive-apps-add-matlab-wm-mate:

Use Mate for the Window Manager
-------------------------------

The code for starting Mate in the background looks like this (see highlighted lines 1-4):

    .. code-block:: shell
      :emphasize-lines: 1-4
      :linenos:

        # Launch Mate Window Manager and Panel
        marco --no-composite --no-force-fullscreen --sm-disable &
        # mate-panel blocks, but does not work reliably when launched in the same subshell as marco
        mate-panel &

        cd "$HOME"

        #
        # Start MATLAB
        #

        # Load the required environment
        module load xalt/latest <%= context.version %>

        # Launch MATLAB
        # Switch the implementation on if the user requested a visualization GPU node
        <%- if context.node_type.include?("vis") -%>
        module load intel/16.0.3 virtualgl  # Perform whatever set up you want / need
        module list  # List loaded modules for debugging purposes
        set -x
        vglrun matlab -desktop -nosoftwareopengl  # Launch MATLAB using VirtualGL
        <%- else -%>
        # When not using a GPU node
        module list  # List loaded modules for debugging purposes
        set -x
        matlab -desktop  # Launch MATLAB
        <%- end -%>

.. note::

    `According to the developers`_ the correct pronunciation of Mate is "mah-tay" like the drink, and not matey like pirates, or mate like a friend.

.. _app-development-tutorials-interactive-apps-add-matlab-wm-fluxbox:

Use Fluxbox for the Window Manager
----------------------------------

.. warning::

  Fluxbox has been replaced by XFCE as OSC's prefered window manager / desktop environment.

The code for starting Fluxbox in the background looks like this (see highlighted lines 1-36):

    .. code-block:: shell
      :emphasize-lines: 1-36
      :linenos:

        #
        # Launch Fluxbox
        #

        FLUXBOX_RC_FILE="$(pwd)/fluxbox.rc"
        # Find an example of the Fluxbox assets at https://github.com/OSC/bc_osc_matlab/tree/bcff07264b318688c3f4272a9662b13477833373/template/fluxbox
        FLUXBOX_ASSETS_ROOT="<%= session.staged_root.join("fluxbox")%>"

        # Create Fluxbox root or it will override the below init file
        (
          umask 077
          mkdir -p "${HOME}/.fluxbox"
        )

        # Build Fluxbox init file
        cat > "${FLUXBOX_RC_FILE}" << EOT
        session.configVersion: 13
        session.screen0.toolbar.widthPercent: 60
        session.screen0.toolbar.tools: prevworkspace, workspacename, nextworkspace, iconbar, systemtray, prevwindow, nextwindow, clock
        session.menuFile: $FLUXBOX_ASSETS_ROOT/menu
        session.keyFile: $FLUXBOX_ASSETS_ROOT/keys
        session.styleOverlay: $FLUXBOX_ASSETS_ROOT/overlay
        EOT

        # Export the module function for the terminal
        [[ $(type -t module) == "function" ]] && export -f module

        # Start the Fluxbox window manager (it likes to crash on occassion, make it
        # persistent)
        (
          export FLUXBOX_ASSETS_ROOT="${FLUXBOX_ASSETS_ROOT}"
          until fluxbox -display "${DISPLAY}.0" -rc "${FLUXBOX_RC_FILE}"; do
            echo "Fluxbox crashed with exit code $?. Respawning..." >&2
            sleep 1
          done
        ) &

        cd "$HOME"

        #
        # Start MATLAB
        #

        # Load the required environment
        module load xalt/latest <%= context.version %>

        # Launch MATLAB
        # Switch the implementation on if the user requested a visualization GPU node
        <%- if context.node_type.include?("vis") -%>
        module load intel/16.0.3 virtualgl  # Perform whatever set up you want / need
        module list  # List loaded modules for debugging purposes
        set -x
        vglrun matlab -desktop -nosoftwareopengl  # Launch MATLAB using VirtualGL
        <%- else -%>
        # When not using a GPU node
        module list  # List loaded modules for debugging purposes
        set -x
        matlab -desktop  # Launch MATLAB
        <%- end -%>

.. _according to the developers: https://ubuntu-mate.org/blog/how-to-pronounce-mate/
