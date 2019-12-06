.. _app-development-tutorials-interactive-apps-add-matlab-edit-form-yml:

Customize Attributes
====================

Now we will customize the app to work on your cluster. Be sure that you walk through :ref:`app-development-tutorials-interactive-apps-add-matlab-software-requirements` for the given cluster ahead of time.

The main responsibility of the ``form.yml`` file (:ref:`app-development-interactive-form`) located in the root of the app is defining the attributes (their values or HTML form elements) used when generating the batch script.

0. Open ``~/ondemand/dev/bc_my_center_matlab/form.yml`` you should see something that looks like this:

  .. code-block:: yaml

    ---
    cluster: "owens"
    form:
      - version
      - bc_account
      - bc_num_hours
      - bc_num_slots
      - num_cores
      - node_type
      - bc_vnc_resolution
      - bc_email_on_started
    attributes:
      num_cores:
        widget: "number_field"
        label: "Number of cores"
        value: 1
        help: |
          Number of cores on node type (4 GB per core unless requesting whole
          node). Leave blank if requesting full node.
        min: 0
        max: 48
        step: 1
        id: 'num_cores'
      bc_num_slots: "1"
      bc_vnc_resolution:
        required: true
      bc_account:
        label: "Project"
        help: "You can leave this blank if **not** in multiple projects."
      node_type:
        widget: select
        label: "Node type"
        help: |
          - **any** - (*1-28 cores*) Use any available Owens node. This reduces the
            wait time as there are no node requirements.
          - **hugemem** - (*48 cores*) Use an Owens node that has 1.5TB of
            available RAM as well as 48 cores. There are 16 of these nodes on
            Owens. Requesting hugemem nodes allocates entire nodes.
          - **vis** - (*1-28 cores*) Use an Owens node that has an [NVIDIA Tesla P100
            GPU](http://www.nvidia.com/object/tesla-p100.html) with an X server
            running in the background. This utilizes the GPU for hardware
            accelerated 3D visualization. There are 160 of these nodes on Owens.
        options:
          - [ "any",     ""            ]
          - [ "hugemem", ":hugemem"    ]
          - [ "vis",     ":vis:gpus=1" ]
      version:
        widget: select
        label: "MATLAB version"
        help: "This defines the version of MATLAB you want to load."
        options:
          - [ "R2018b", "matlab/r2018b" ]
          - [ "R2018a", "matlab/r2018a" ]
          - [ "R2017a", "matlab/r2017a" ]
          - [ "R2016b", "matlab/r2016b" ]
          - [ "R2015b", "matlab/r2015b" ]

.. note::

    Multiple form elements / attributes are specific to OSC. We will focus on
    the ones that are required, and some that may be universally useful.

1. We will begin by adding a cluster for the Matlab app to use. You do this by editing ``~/ondemand/dev/bc_my_center_matlab/form.yml`` in your favorite editor as such:

  .. code-block:: yaml
    :emphasize-lines: 3

    # ~/ondemand/dev/bc_my_center_matlab/form.yml
    ---
    cluster: "owens"  # <---- Change this
    form:
      - version  # At OSC we provide
      - bc_account
      - bc_num_hours
      - bc_num_slots
      - num_cores
      - node_type
      - bc_vnc_resolution
      - bc_email_on_started
    # ...


  where we replace ``owens`` with a valid cluster that corresponds to a cluster configuration file located under ``/etc/ood/config/clusters.d/owens.yml``.

  .. note::

    The ``cluster`` attribute is not available to the form and cannot be changed at runtime.

2. Set common options:

    .. code-block:: yaml

      ---
      cluster: "owens"
      form:
        - version               # <-- OSC supports multiple versions of Matlab via LMod 
        - bc_account            # <-- the charge account
        - bc_num_hours          # <-- the number of user requested hours that the job run
        - bc_num_slots          # <-- the number of nodes
        - num_cores             # <-- the number of processors per node
        - node_type             # <-- OSC offers different hardware types (any, huge memory, GPU, ...)
        - bc_vnc_resolution     # <-- the resolution settings for the VNC connection
        - bc_email_on_started   # <-- should the system email the user when the job starts

3. Set attribute values for each form element

    ``num_cores`` has a max and min set that are specific to OSC's Owens cluster; set these values to whatever makes sense for your site.

      .. code-block:: yaml

        ---
        attributes:
          num_cores:
            widget: "number_field"
            label: "Number of cores"
            value: 1
            help: |
              Number of cores on node type (4 GB per core unless requesting whole
              node). Leave blank if requesting full node.
            min: 0
            max: 48
            step: 1
            id: 'num_cores'

   ``bc_num_slots`` is hardcoded to 1 and is not user editable because OSC does not support MPI work from the Batch Connect app. The value for ``bc_vnc_resolution`` should be copied verbatim. ``bc_account`` is the charge account for the batch work.

      .. code-block:: yaml

        ---
        attributes:
          bc_num_slots: "1"
          bc_vnc_resolution:
            required: true
          bc_account:
            label: "Project"
            help: "You can leave this blank if **not** in multiple projects."


    ``node_type`` allows users to select which hardware they want to run their work on. In the ``options`` mapping the first value is displayed to the user, the second value is made available to any `ERB`_ files in ``~/ondemand/dev/bc_my_center_matlab/template/*`` and ``~/ondemand/dev/bc_my_center_matlab/submit.yml.erb``. ``version`` allows the user to select what version of Matlab they want to run, and the second value corresponds to OSC's module names.

      .. code-block:: yaml

        ---
        attributes:
          node_type:
              widget: select
              label: "Node type"
              help: |
                - **any** - (*1-28 cores*) Use any available Owens node. This reduces the
                  wait time as there are no node requirements.
                - **hugemem** - (*48 cores*) Use an Owens node that has 1.5TB of
                  available RAM as well as 48 cores. There are 16 of these nodes on
                  Owens. Requesting hugemem nodes allocates entire nodes.
                - **vis** - (*1-28 cores*) Use an Owens node that has an [NVIDIA Tesla P100
                  GPU](http://www.nvidia.com/object/tesla-p100.html) with an X server
                  running in the background. This utilizes the GPU for hardware
                  accelerated 3D visualization. There are 160 of these nodes on Owens.
              options:
                - [ "any",     ""            ]
                - [ "hugemem", ":hugemem"    ]
                - [ "vis",     ":vis:gpus=1" ]
          version:
            widget: select
            label: "MATLAB version"
            help: "This defines the version of MATLAB you want to load."
            options:
              - [ "R2018b", "matlab/r2018b" ]
              - [ "R2018a", "matlab/r2018a" ]
              - [ "R2017a", "matlab/r2017a" ]
              - [ "R2016b", "matlab/r2016b" ]
              - [ "R2015b", "matlab/r2015b" ]

  .. note::

    ``submit.yml.erb`` may also be ``submit.yml`` if there is no requirement to pass form values to the adapter, or perform another server-side task.

.. _erb: https://en.wikipedia.org/wiki/ERuby