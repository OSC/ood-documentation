.. _app-development-tutorials-interactive-apps-troubleshooting:

Troubleshooting Interactive Apps
================================

The window cannot be resized/moved/maximized
********************************************

While a window manager is not strictly required to be able to set up a desktop/VNC application, one is required to be able to perform many common tasks like moving a window, resizing it, or even locating the window after it has been minimized. The Matlab example provides examples of how to set up :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-xfce`, :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-mate`, and :ref:`app-development-tutorials-interactive-apps-add-matlab-wm-fluxbox` (mentioned in order of OSC preference).

Matlab throws Java errors when the window is resized
****************************************************

A remedy for Matlab throwing Java errors when its window is resized, moved, or displayed on a secondary monitor is detailed in Matlab's :ref:`app-development-tutorials-interactive-apps-add-matlab-known-issues`.

Job finishes instantly because, desktop app backgrounds itself
**************************************************************

Many apps are convenient in that their launch command blocks instead of backgrounding itself. By blocking the process our script is prevented from ending immediately, which in turn would prevent the user from accomplishing anything useful. Some GUI applications like Stata put themselves into the background. For apps like Stata it is necessary to perform the blocking ourselves:

  .. code-block:: shell

    # Launch Stata GUI
    xstata-mp

    # Get the PID of the last xstata-mp process started that $USER owns
    stata_pid=$( pgrep -u "$USER" 'xstata-mp' | tail )
    # As long as the PID directory exists we wait
    while [[ -d "/proc/$stata_pid" ]]; do
      sleep 1
    done
