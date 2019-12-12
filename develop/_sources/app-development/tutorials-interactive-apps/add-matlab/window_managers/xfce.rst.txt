.. _app-development-tutorials-interactive-apps-add-matlab-wm-xfce:

XFCE
====

XFCE is OSC's prefered desktop environment for launching VNC applications. The code for starting XFCE in the background looks like this:

    .. code-block:: shell

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