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
