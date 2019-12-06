.. _app-development-tutorials-interactive-apps-add-matlab-edit-script-sh:

Edit Launch Script
==================

Here we will look at the script that actually launches Matlab.

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

If you get Java errors
**********************

Matlab may throw Java errors when the window is resized, moved, or displayed on a seconadary monitor. There does not appear to be an official Matlab fix for this problem, but an interim solution mitigates the bug enough to let work continue. In order to solve the problem: create or edit a file named ``$MATLAB_ROOT/bin/glnxa64/java.opts`` and add a line: ``-Dsun.java2d.xrender=false``. Alternatively the following may be added to the job script prior to Matlab being started:

    .. code-block:: shell

        # Fix the Java errors relating to resizing the window
        cat << JAVA_OPT > java.opts
        -Dsun.java2d.xrender=false
        JAVA_OPT

Confirm that the option has been set by running the following command within Matlab:

    .. code-block:: none

        java.lang.management.ManagementFactory.getRuntimeMXBean.getInputArguments

    .. warning::

        ``xrender`` is a performance optimization, disabling it may adversely impact the user experience.

        https://docs.oracle.com/javase/8/docs/technotes/guides/2d/flags.html#xrender

References:

- https://www.mathworks.com/matlabcentral/answers/373897-external-monitor-throws-java-exception
- https://www.mathworks.com/matlabcentral/answers/381324-why-do-i-get-java-exception-on-display-change
- https://www.mathworks.com/matlabcentral/answers/424725-disable-xrender-at-startup


What if the matlab command did not block?
*****************************************

Matlab is convenient in that the command ``matlab`` blocks instead of backgrounding itself, this prevents our script from ending immediately, which would prevent the user from accomplishing anything useful. Some GUI applications like Stata put themselves into the background. For apps like Stata it is necessary to perform the blocking ourselves:

  .. code-block:: shell

    # Launch Stata GUI
    xstata-mp

    # Get the PID of the last xstata-mp process started that $USER owns
    stata_pid=$( pgrep -u "$USER" 'xstata-mp' | tail )
    # As long as the PID directory exists we wait
    while [[ -d "/proc/$stata_pid" ]]; do
      sleep 1
    done