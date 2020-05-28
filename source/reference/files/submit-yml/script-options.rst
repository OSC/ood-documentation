.. _script-options:

Script Options
==============

.. code-block:: yaml

    script:
      content: nil
      args: nil
      submit_as_hold: nil
      rerunnable: nil
      job_environment: nil
      workdir: nil
      email: nil
      email_on_started: nil
      email_on_terminated: nil
      job_name: nil
      shell_path: nil
      error_path: nil
      input_path: nil
      output_path: nil
      reservation_id: nil
      queue_name: nil
      priority: nil
      start_time: nil
      wall_time: nil
      accounting_id: nil
      native: nil
      copy_environment: nil


Descriptions of Script Options
..............................

Note the use of ERB templates throughout these examples.

.. describe:: content (String, nil)

    the content of the script being submitted

    Default
      an empty string, specified by the batch connect application

      .. code-block:: yaml

        content: ""
    
    Example
      None given because users should not specify this

.. describe:: args (Array<String>, nil)

    extra arguments to pass to the schedulers' submit command

    Default
      empty, no extra arguments

      .. code-block:: yaml

        args: nil

    Example
      pass arguments ``--foo`` and ``--bar`` into the submit command

      .. code-block:: yaml

        args:
          - "--foo"
          - "--bar"

.. describe:: submit_as_hold (Boolean, nil)

    hold the job after submitting

    Default
      empty, do not hold the job

      .. code-block:: yaml

        submit_as_hold: nil

    Example
      always hold the job

      .. code-block:: yaml

        submit_as_hold: true

.. describe:: rerunnable (Boolean, nil)

    indicate whether the job is rerunnable

    Default
      empty, it is not rerunnable

      .. code-block:: yaml

        rerunnable: nil

    Example
      the job is rerunnable

      .. code-block:: yaml

        rerunnable: true

.. describe:: job_environment (Hash<String, String>, nil)

    extra environment variables to pass into the schedulers' submit command

    Default
      empty, no extra environment variables

      .. code-block:: yaml

        job_environment: nil

    Example
      set the ``SINGULARTITY_BIND_PATH`` environment variable to ``/etc,/tmp,/home`` and
      ``MY_APP_IMAGE`` to ``/opt/app.img``

      .. code-block:: yaml

        job_environment:
          SINGULARTITY_BIND_PATH: "/etc,/tmp/home"
          MY_APP_IMG: "/opt/app.img"

.. describe:: workdir (String, nil)

    the working directory of the job

    Default
      not set, specified by the batch connect application

      .. code-block:: yaml

        workdir: nil

    Example
      set to ~/work

      .. code-block:: yaml

        workdir: "<%= ENV['HOME'] %>/work"

.. describe:: email (Array<String>, nil)

    addresses to send emails to when the job starts or stops.

    Default
      empty, uses the schedulers' default

      .. code-block:: yaml

        email: nil

    Example
      use a specific domain in the email address

      .. code-block:: yaml

        email: 
        - "<%= ENV['USER'] %>@the-real-domain-I-want.edu"

.. describe:: email_on_started (Boolean, nil)

    have the scheduler send an email when the job has started

    Default
      not set, users should use the ``bc_email_on_started`` form attribute
      instead of setting it directly

      .. code-block:: yaml

        email_on_started: nil

    Example
      always email when the job starts

      .. code-block:: yaml

        email_on_started: true

.. describe:: email_on_terminated (Boolean, nil)

    have the scheduler send an email when the job has finished

    Default
      not set, uses the schedulers' default

      .. code-block:: yaml

        email_on_terminated: nil

    Example
      given the form checkbox option ``email_on_terminated``, set this attribute

      .. code-block:: yaml

        email_on_terminated: "<%= email_on_terminated %>"

.. describe:: job_name (String, nil)

    the name of the job. 

    Default
      not set, specified by the batch connect application

      .. code-block:: yaml

        job_name: nil

    Example
      set the job name to ``jupyter``

      .. code-block:: yaml

        job_name: "jupyter"

.. describe:: shell_path (String, nil)

    the login shell path of the script 

    Default
      not specified

      .. code-block:: yaml

        shell_path: nil

    Example
      use bash as the login shell

      .. code-block:: yaml

        shell_path: "/usr/bin/bash"

.. describe:: error_path (String, nil)

    the path for the standard error of the job

    Default
      not set, uses scheduler default

      .. code-block:: yaml

        error_path: nil

    Example
      send standard error to ~/job.err

      .. code-block:: yaml

        error_path: "<%= ENV['HOME'] %>/job.err"

.. describe:: input_path (String, nil)

    use this file for standard input for the job's script.
    batch connect scripts do not expect to read anything 
    from standard in.

    Default
      not set, uses scheduler default (like /dev/null)

      .. code-block:: yaml

        output_path: nil

    Example
      use the file ~/input_file as standard input to the job's script

      .. code-block:: yaml

        output_path: "<%= ENV['HOME'] %>/input_file"

.. describe:: output_path (String, nil)

    the path for the standard output of the job

    Default
      not set, specified by the batch connect application

      .. code-block:: yaml

        output_path: nil

    Example
      send standard error to ~/job.out

      .. code-block:: yaml

        output_path: "<%= ENV['HOME'] %>/job.out"

.. describe:: reservation_id (String, nil)

    the reservation id the job will submit to

    Default
      not specified

      .. code-block:: yaml

        reservation_id: nil

    Example
      submit jobs to the ``next.may.2020`` reservation

      .. code-block:: yaml

        reservation_id: "next.may.2020"

.. describe:: queue_name (String, nil)

    the queue the job will submit to

    Default
      not specified

      .. code-block:: yaml

        queue_name: nil

    Example
      submit jobs to the ``debug`` queue

      .. code-block:: yaml

        queue_name: "debug"

.. describe:: priority (String, nil)

    the priority the job has

    Default
      not specified

      .. code-block:: yaml

        priority: nil

    Example
      submit jobs with ``TOP`` priority

      .. code-block:: yaml

        priority: "TOP"

.. describe:: start_time (String, nil)

    the start time of the job

    Default
      not set, which schedulers generally interpret as now

      .. code-block:: yaml

        start_time: nil

    Example
      start at midnight

      .. code-block:: yaml

        start_time: "00:00:00"

.. describe:: wall_time (Integer, nil)

    the wall time of the job in seconds

    Default
      not set, users should use the ``bc_num_hours`` form attribute to
      set this

      .. code-block:: yaml

        wall_time: nil

    Example
      always limit this job to one hour

      .. code-block:: yaml

        wall_time: 3600

.. describe:: accounting_id (String, nil)

    the accounting id the job should be charged to

    Default
      not specified, uses the schedulers' default. users should use 
      the ``bc_account`` form attribute to set this for convenience.

      .. code-block:: yaml

        priority: nil

    Example
      all jobs to use the ``rstudio-class-account`` accounting id

      .. code-block:: yaml

          accounting_id: 'rstudio-class-account' 

.. describe:: native (Object, nil)

    native arguments to pass to the schedulers' submit command

    .. warning::
      All schedulers use Array<String> for native attributes except for Torque.
      Torque schedulers use Hash<String, String>.

    Default
      not specified

      .. code-block:: yaml

        native: nil

    Example
      submit the job with SLURM requests for one node, ``num_cores`` (a form variable) 
      cores and ``memory`` (another form variable) amount of memory

      .. code-block:: yaml

          native:
            - "-N"
            - "1"
            - "-n"
            - "<%= num_cores %>"
            - "--mem"
            - "<%= memory %>"

.. describe:: copy_environment (Boolean, nil)

    have the scheduler to copy the environment. SLURM uses 
    ``--export=ALL`` (default is NONE). PBS/Torque and LSF 
    set the ``-V`` flag.

    Default
      not specified

      .. code-block:: yaml

        native: nil

    Example
      Copy the environment 

      .. code-block:: yaml

          copy_environment: true








