.. _submit-script-options:

Batch Connect Script Options
============================

The ``script`` section of the :ref:`submit-yml-erb` file defines
the arguments you're passing to the scheduler when you submit the
script.

.. warning::
  These options are documented here for completeness. Some may not
  be available to override in batch connect applications.
  
  For example, ``workdir`` is set by the OnDemand system in batch
  connect applications, and cannot be overidden.

.. tip::
  If you're using the ``ood_core`` gem (where all these are defined and used)
  you should refer to `ood_core gem Ruby docs`_.

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


Note the use of ERB templates throughout these examples.

.. describe:: content (String, nil)

    The content of the script being submitted.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        content: ""

    Example
      **None given because users cannot specify this in batch connect applications.**

.. describe:: args (Array<String>, nil)

    Extra arguments to pass to the schedulers' submit command.

    Default
      Empty, no extra arguments.

      .. code-block:: yaml

        args: nil

    Example
      Pass arguments ``--foo`` and ``--bar`` into the submit command.

      .. code-block:: yaml

        args:
          - "--foo"
          - "--bar"

.. describe:: submit_as_hold (Boolean, nil)

    Hold the job after submitting.

    Default
      Empty, do not hold the job.

      .. code-block:: yaml

        submit_as_hold: nil

    Example
      Always hold the job.

      .. code-block:: yaml

        submit_as_hold: true

.. describe:: rerunnable (Boolean, nil)

    Indicate whether the job is rerunnable.

    Default
      Empty, it is not rerunnable.

      .. code-block:: yaml

        rerunnable: nil

    Example
      The job is rerunnable.

      .. code-block:: yaml

        rerunnable: true

.. describe:: job_environment (Hash<String, String>, nil)

    Extra environment variables to pass into the schedulers' submit command.

    Default
      Empty, no extra environment variables.

      .. code-block:: yaml

        job_environment: nil

    Example
      Set the ``SINGULARTITY_BIND_PATH`` environment variable to ``/etc,/tmp,/home`` and
      ``MY_APP_IMAGE`` to ``/opt/app.img``.

      .. code-block:: yaml

        job_environment:
          SINGULARTITY_BIND_PATH: "/etc,/tmp/home"
          MY_APP_IMG: "/opt/app.img"

.. describe:: workdir (String, nil)

    The working directory of the job.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        workdir: nil

    Example
      **None given because users cannot specify this in batch connect applications.**
      

.. describe:: email (Array<String>, nil)

    Addresses to send emails to when the job starts or stops.

    Default
      Empty, uses the schedulers' default.

      .. code-block:: yaml

        email: nil

    Example
      Use a specific email address.

      .. code-block:: yaml

        email:
        - "<%= ENV['USER'] %>@the-real-domain-I-want.edu"

.. describe:: email_on_started (Boolean, nil)

    Have the scheduler send an email when the job has started.

    Default
      Not set, uses the schedulers' default.

      .. code-block:: yaml

        email_on_started: nil

    Example
      **None given because users should use :ref:`bc_email_on_started` instead
      of supplying it here**.

.. describe:: email_on_terminated (Boolean, nil)

    Have the scheduler send an email when the job has finished.

    Default
      Not set, uses the schedulers' default.

      .. code-block:: yaml

        email_on_terminated: nil

    Example
      Given the form checkbox option ``email_on_terminated``, set this attribute.

      .. code-block:: yaml

        email_on_terminated: "<%= email_on_terminated %>"

.. describe:: job_name (String, nil)

    The name of the job.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        job_name: nil

    Example
      **None given because users cannot specify this in batch connect applications.**

.. describe:: shell_path (String, nil)

    The login shell path of the script.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        shell_path: nil

    Example
      **None given because users cannot specify this in batch connect applications.**

.. describe:: error_path (String, nil)

    The path for the standard error of the job.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        error_path: nil

    Example
      **None given because users cannot specify this in batch connect applications.**

.. describe:: input_path (String, nil)

    Use this file for standard input for the job's script.
    Batch connect applications do not expect to read anything
    from standard in.

    Default
      Not set.

      .. code-block:: yaml

        input_path: nil

    Example
      **None given because this is likely to break batch connect applications.**

.. describe:: output_path (String, nil)

    The path for the standard output of the job.

    Default
      Not set initially, but specified by OnDemand system automatically.

      .. code-block:: yaml

        output_path: nil

    Example
      **None given because users cannot specify this in batch connect applications.**

.. describe:: reservation_id (String, nil)

    The reservation id the job will submit to.

    Default
      Not specified.

      .. code-block:: yaml

        reservation_id: nil

    Example
      Submit jobs to the ``next.may.2020`` reservation.

      .. code-block:: yaml

        reservation_id: "next.may.2020"

.. describe:: queue_name (String, nil)

    The queue the job will submit to.

    .. tip::
      Users can use :ref:`bc_queue <bc_queue>` for a text field and
      :ref:`auto_queues <auto_queues>` for a select widget.  Both of these
      form fields know how to submit to schedulers, removing
      the need to use this field in this file.

    Default
      Not specified.

      .. code-block:: yaml

        queue_name: nil

    Example
      Submit jobs to the ``debug`` queue.

      .. code-block:: yaml

        queue_name: "debug"

.. describe:: priority (String, nil)

    The priority the job has.

    Default
      Not specified.

      .. code-block:: yaml

        priority: nil

    Example
      Submit jobs with ``TOP`` priority.

      .. code-block:: yaml

        priority: "TOP"

.. describe:: start_time (String, nil)

    The start time of the job.

    Default
      Not set, which schedulers generally interpret as now or as soon as possible.

      .. code-block:: yaml

        start_time: nil

    Example
      Start at midnight.

      .. code-block:: yaml

        start_time: "00:00:00"

.. describe:: wall_time (Integer, nil)

    The wall time of the job in seconds.

    .. tip::
      Users can use :ref:`bc_num_hours <bc_num_hours>` for a number field
      that knows how to submit to schedulers, removing
      the need to use this field in this file.

    Default
      Not specified.

      .. code-block:: yaml

        wall_time: nil

    Example
      Always limit this job to one hour.

      .. code-block:: yaml

        wall_time: 3600

.. describe:: accounting_id (String, nil)

    The accounting id the job should be charged to.

    .. tip::
      Users can use :ref:`bc_account <bc_account>` for a text field and
      :ref:`auto_accounts <auto_accounts>` or :ref:`auto_accounts <auto_groups>`
      for a select widget.  
      
      All of these form fields know how to submit to schedulers, removing
      the need to use this field in this file.

    Default
      Not specified, uses the schedulers' default.

      .. code-block:: yaml

        priority: nil

    Example
      All jobs to use the ``rstudio-class-account`` accounting id.

      .. code-block:: yaml

          accounting_id: 'rstudio-class-account'

.. describe:: native (Object, nil)

    Native arguments to pass to the schedulers' submit command.

    .. warning::
      All schedulers use Array<String> for native attributes except for Torque.
      Torque schedulers use Hash<String, String>.

    Default
      not specified

      .. code-block:: yaml

        native: nil

    Example
      Submit the job with SLURM requests for one node, ``num_cores`` (a form variable)
      cores and ``memory`` (another form variable) amount of memory.

      .. code-block:: yaml

          native:
            - "-N"
            - "1"
            - "-n"
            - "<%= num_cores %>"
            - "--mem"
            - "<%= memory %>"

.. describe:: copy_environment (Boolean, nil)

    Have the scheduler to copy the environment. SLURM uses
    ``--export=ALL`` (OnDemand's default is NONE). PBS/Torque and LSF
    set the ``-V`` flag.

    Default
      not specified

      .. code-block:: yaml

        native: nil

    Example
      Copy the environment 

      .. code-block:: yaml

          copy_environment: true


.. _ood_core gem Ruby docs: https://osc.github.io/ood_core/OodCore/Job/Script.html