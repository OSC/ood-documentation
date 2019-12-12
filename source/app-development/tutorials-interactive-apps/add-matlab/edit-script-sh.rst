.. _app-development-tutorials-interactive-apps-add-matlab-edit-script-sh:

Edit Launch Script
==================

Here we will look at the script that actually launches Matlab ``~/ondemand/dev/bc_my_center_matlab/template/script.sh.erb``.

By now you should have selected your prefered window manager. Examples of using XFCE, Mate, and Fluxbox:

.. toctree::
   :maxdepth: 1
   :caption: Window Manager Options

   window_managers/xfce
   window_managers/mate
   window_managers/fluxbox

Invoking Matlab itself
**********************

    .. code-block:: shell

        $WINDOW_MANAGER_CODE_GOES_HERE

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
        vglrun matlab -desktop -nosoftwareopengl  # Launch Matlab using VirtualGL
        <%- else -%>
        # When not using a GPU node
        module list  # List loaded modules for debugging purposes
        set -x
        matlab -desktop  # Launch Matlab
        <%- end -%>

Generalizing our approach: What if the matlab command did not block?
********************************************************************

Matlab is convenient in that the command ``matlab`` blocks instead of backgrounding itself, this prevents our script from ending immediately, which would prevent the user from accomplishing anything useful. Some other GUI applications like Stata put themselves into the background. For apps like Stata it is necessary to perform the blocking ourselves:

  .. code-block:: shell

    # Launch Stata GUI
    xstata-mp

    # Get the PID of the last xstata-mp process started that $USER owns
    stata_pid=$( pgrep -u "$USER" 'xstata-mp' | tail )
    # As long as the PID directory exists we wait
    while [[ -d "/proc/$stata_pid" ]]; do
      sleep 1
    done