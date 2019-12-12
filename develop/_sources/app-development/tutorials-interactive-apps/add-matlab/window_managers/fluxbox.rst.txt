.. _app-development-tutorials-interactive-apps-add-matlab-wm-fluxbox:

Fluxbox
=======

.. warning::

  Fluxbox has been replaced by XFCE as OSC's prefered window manager / desktop environment.

The code for starting Fluxbox in the background looks like this:

    .. code-block:: shell

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
