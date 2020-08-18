.. _basic-bc-yml-detailed:


Details on Basic Batch Connect Options
======================================

.. describe:: min_port (Integer, 2000)

    the smallest value to use when trying to open a port

    Default
      2000 is the lowest value to use when trying to open a port

      .. code-block:: yaml

        min_port: 2000

    Example
      set the lowest possible port number to 3005

      .. code-block:: yaml

        min_port: 3005
      
.. describe:: max_port (Integer, 65535)

    the largest value to use when trying to open a port

    Default
      65535 is the highest possible value a port could have

      .. code-block:: yaml

        max_port: 65535

    Example
      set the highest possible port number to 40000

      .. code-block:: yaml

        max_port: 40000

.. describe:: password_size (Integer, 8)

    the number of characters in the passwords

    Default
      passwords will be generated with 8 characters

      .. code-block:: yaml

        password_size: 8

    Example
      passwords will be generated with 32 characters

      .. code-block:: yaml

        password_size: 32

.. describe:: header (String, "")

    the script header

    Default
      the script has no header

      .. code-block:: yaml

        header: ""

    Example
      set the header to a bash shebang

      .. code-block:: yaml

        header: "#!/bin/bash"

.. describe:: footer (String, "")

    commands at the bottom of the script

    Default
      the script has no footer

      .. code-block:: yaml

        header: ""

    Example
      print the end time of the job

      .. code-block:: yaml

        header: 'echo "all done at $(date)"'

.. describe:: script_wrapper (String, "%s")

    wrap the script ('%s' being the script content) with commands before
    and after

    Default
      the script has no wrapper

      .. code-block:: yaml

        script_wrapper: "%s"

    Example
      load a module before the script and echo a statement after it

      .. code-block:: yaml

        script_wrapper: |
          module load vnc
          %s
          echo "all done now!"


.. describe:: set_host (String, "host=$(hostname)")

    set the host variable with this command

    Default
      the host variable is set by the hostname command

      .. code-block:: yaml

        set_host: "host=$(hostname)"

    Example
      the host variable the first item in the ``hostname -A`` output

      .. code-block:: yaml

        set_host: "host=$(hostname -A | awk '{print $1}')"

.. describe:: before_script (String, "...")

    commands to execute the before file

    Default
      sources the configurable ``before_file`` if it exists

      .. code-block:: ruby

        def before_script
          context.fetch(:before_script) do
            before_file = context.fetch(:before_file, "before.sh").to_s

            "[[ -e \"#{before_file}\" ]] && source \"#{before_file}\""
          end.to_s
        end

    Example
      temporarily override the PATH variable when executing the before script

      .. code-block:: yaml

        before_script: |
          # careful now, we can't override before_file or we have to
          # change it here too!
          PATH=$PATH:/opt/ood-before/bin source before.sh

.. describe:: before_file (String, "before.sh")

    the script file to run before the main script

    Default
      execute the file before.sh before the main script

      .. code-block:: yaml

        before_file: "before.sh"

    Example
      execute the file prepare.sh before the main script

      .. code-block:: yaml

        before_file: "prepare.sh"

.. describe:: run_script (String, "...")

    commands to execute the main file

    Default
      execute the configurable ``script_file`` or optionally run with 
      the timeout command if there is a timeout given.

      .. code-block:: ruby

        def run_script
          context.fetch(:run_script) do
            script_file = context.fetch(:script_file,  "./script.sh").to_s
            timeout     = context.fetch(:timeout, "").to_s

            timeout.empty? ? "\"#{script_file}\"" : "timeout #{timeout} \"#{script_file}\""
          end.to_s
        end

    Example
      execute the main script in a singularity container

      .. code-block:: yaml

        run_script: |
          # careful now, we can't override run_file or we have to
          # change it here too!  This also doesn't account for timeout,
          # if it's provided.
          IMAGE=/opt/images/centos7.sif
          singularity exec -p $IMAGE /bin/bash script.sh

.. describe:: script_file (String, "./script.sh")

    the main script file

    Default
      execute the file script.sh in the current working directory

      .. code-block:: yaml

        script_file: "./script.sh"

    Example
      execute the file other_main.sh in the current working directory

      .. code-block:: yaml

        script_file: "./other_main.sh"

.. describe:: timeout (String, "")

    timeout (in seconds) of the main script

    Default
      no timeout applied to the main script file

      .. code-block:: yaml

        script_file: ""

    Example
      all scripts timeout after 3600 seconds (1 hour)

      .. code-block:: yaml

        script_file: "3600"

.. describe:: clean_script (String, "...")

    commands to execute the clean script file

    Default
      sources the configurable ``clean_file`` if it exists

      .. code-block:: ruby

        def clean_script
          context.fetch(:clean_script) do
            clean_file = context.fetch(:clean_file, "clean.sh").to_s

            "[[ -e \"#{clean_file}\" ]] && source \"#{clean_file}\""
          end.to_s
        end

    Example
      temporarily override the PATH variable when executing the clean script

      .. code-block:: yaml

        clean_script: |
          # careful now, we can't override clean_file or we have to
          # change it here too!
          PATH=$PATH:/opt/ood-clean/bin source clean.sh

.. describe:: clean_file (String, "clean.sh")

    the cleanup script file

    Default
      execute the file clean.sh

      .. code-block:: yaml

        clean_file: "clean.sh"

    Example
      execute the file scrub.sh

      .. code-block:: yaml

        clean_file: "scrub.sh"


.. warning::
    These items below should not be set by users.  They are
    given for completeness only.  It's likely they'll cause
    errors if overridden.


.. describe:: work_dir (String, null)

    the working directory of the job.  This is set by the dashboard
    for batch connect apps and users shouldn't need to set it.

    Default
      set by the dashboard to a directory under ~/ondemand/data

    Example
      no example given because users shouldn't set this value

.. describe:: conn_file (String, "connection.yml")

    the file all the connection data will be written to

    Default
      a file named 'connection.yml'

      .. code-block:: yaml

        conn_file: "connection.yml"

    Example
      no example given because users shouldn't set this value

.. describe:: conn_params (Array<String>, ['host','port','password'])

    the connection parameters that will be written to the ``conn_file``

    Default
      'host', 'port' and 'password'

      .. code-block:: yaml

        conn_params: [ 'host', 'port', 'password' ]

    Example
      no example given because users shouldn't set this value

.. describe:: bash_helpers (String, "...")

    a library of bash utility functions called in all the other scripts

    Default
      a very large set of functions. See source code for complete library

    Example
      no example given because users shouldn't set this value