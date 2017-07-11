.. _install-desktops-install-desktop-app:

Install Desktop App
===================

No we will go through installing the provided `bc_desktop`_ app as well as
configuring it work at your center.

#. We will build this app in our previous working directory:

   .. code-block:: sh

      cd ~/ood/src

#. We start by cloning and checking out the latest tag for the `bc_desktop`_
   app:

   .. code-block:: sh

      scl enable git19 -- git clone https://github.com/OSC/bc_desktop.git
      cd bc_desktop/
      scl enable git19 -- git checkout v0.1.0

#. We now must configure desktop apps for each cluster you want this to run
   under in the following directory ``local/``

   .. code-block:: sh

      # Make the `local/` directory if it doesn't already exist
      mkdir local

      # Change our working directory to `local/`
      cd local

#. For each cluster we want to allow desktops to run we will need a
   corresponding YAML configuration file (e.g., ``cluster1.yml``,
   ``cluster2.yml``, ...) that looks like:

   .. code-block:: yaml

      # bc_desktop/local/cluster1.yml
      ---
      title: "Cluster1 Desktop"
      cluster: "cluster1"        # must correspond to a cluster config
      attributes:
        desktop: "mate"          # is the desktop "gnome" or "mate"
        node_type: null          # this is an advanced option typically not needed
      submit: submit/torque.yml.erb

   Most of the above configuration should be self-explanatory, but the
   ``submit`` option is special. It points to a file under the ``local/``
   directory that describes any resource manager specific settings your cluster
   needs for batch job submission (typically this will describe how to request
   a job for a given number of nodes/procs).

   In the above case I named it ``submit/torque.yml.erb``, but if you use Slurm
   you can name it ``submit/slurm.yml.erb``.

   .. danger::

      Please do not modify any of the code below the ``local/`` path as it may
      put the Git repo in a bad state.

      We recommend you version all the changes you make in the ``local/``
      directory you use for the `bc_desktop`_ app so that you don't lose any of
      it.

#. Now we will modify the resource manager specific settings in our given
   ``submit/<resource_mgr>.yml.erb`` file using an ERB template to dynamically
   fill in the YAML configuration file based on what the user submitted in the
   form. The attribute of interest is ``bc_num_slots``, which holds the number
   of nodes or processors the user requested in the form.

   Some examples are included below.

   **Torque**:

   .. code-block:: yaml

      # bc_desktop/local/submit/torque.erb.yml
      ---
      script:
        native:
          resources:
            nodes: "<%= bc_num_slots %>:ppn=12"  # assumes a 12 procs per node

   For more information on the available options for the ``native`` attribute
   when using Torque please see the `pbs-ruby documentation`_.

   **Slurm**:

   .. code-block:: yaml

      # bc_desktop/local/submit/slurm.erb.yml
      ---
      script:
        native: [ "-N", "<%= bc_num_slots %>" ]

   The ``native`` attribute underneath ``script`` accepts an array of command
   line arguments that are fed to ``sbatch``.

   **LSF**:

   TODO

   **PBSPro**:

   .. code-block:: yaml

      # bc_desktop/local/submit/slurm.erb.yml
      ---
      script:
        native: [ "-l", "select=<%= bc_num_slots %>:ncpus=20:mem=16gb" ] # assumes ncpus & mem

   The ``native`` attribute underneath ``script`` accepts an array of command
   line arguments that are fed to ``qsub``.

   .. note::

      You do not need to add command line arguments to ``native`` for the other
      form options because those should be handled correctly. Only
      ``bc_num_slots`` is not properly handled because of the complexity across
      the various resource managers.

#. Navigate to your OnDemand site, in particular the Dashboard App, and you
   should see in the top dropdown menu "Interactive Apps" => "Desktops".

   After choosing Desktops from the menu, you should be presented with a form
   to submit a Desktop to the given cluster.

   Submit a desktop and wait for it to run. If you see a Desktop start Running
   but then quickly disappear you can debug it by viewing the logs in::

     ~/ondemand/data/sys/dashboard/batch_connect/sys/bc_desktop/<cluster>/output/<uuid>/

   where ``uuid`` is a randomly generated id for a single desktop session. You
   might want to find the latest one by looking at the timestamps.

.. _bc_desktop: https://github.com/OSC/bc_desktop/
.. _pbs-ruby documentation: http://www.rubydoc.info/gems/pbs/PBS/Batch#submit_script-instance_method
