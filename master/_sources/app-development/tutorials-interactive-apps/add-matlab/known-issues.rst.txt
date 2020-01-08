.. _app-development-tutorials-interactive-apps-add-matlab-known-issues:

Known Issues
============

If you get Java errors
**********************

    MATLAB may throw Java errors when its window is resized, moved, or displayed on a secondary monitor. There does not appear to be an official MATLAB fix for this problem, but an interim solution mitigates the bug enough to let work continue. In order to solve the problem: create or edit a file named ``$MATLAB_ROOT/bin/glnxa64/java.opts`` and add a line: ``-Dsun.java2d.xrender=false``. Alternatively the following may be added to the job script (``~/ondemand/dev/bc_my_center_matlab/template/script.sh.erb``) prior to MATLAB being started:

        .. code-block:: shell

            # Fix the Java errors relating to resizing the window
            cat << JAVA_OPT > java.opts
            -Dsun.java2d.xrender=false
            JAVA_OPT

    Confirm that the option has been set by running the following command within MATLAB:

        .. code-block:: none

            java.lang.management.ManagementFactory.getRuntimeMXBean.getInputArguments

        .. warning::

            ``xrender`` is a performance optimization, disabling it may adversely impact the user experience.

            https://docs.oracle.com/javase/8/docs/technotes/guides/2d/flags.html#xrender

    References:


    Describing the problem:
        - https://www.mathworks.com/matlabcentral/answers/373897-external-monitor-throws-java-exception
        - https://www.mathworks.com/matlabcentral/answers/381324-why-do-i-get-java-exception-on-display-change
        - https://www.mathworks.com/matlabcentral/answers/424725-disable-xrender-at-startup

    Describing parts of the solution:

        - Setting Java options: https://www.mathworks.com/help/matlab/matlab_env/java-opts-file.html
        - The startup folder: https://www.mathworks.com/help/matlab/matlab_env/matlab-startup-folder.html
