.. _enable-desktops-custom-job-submission:

Custom Job Submission
=====================

The :ref:`app-development-interactive-submit` configuration file describes how
the batch job should be submitted to your cluster. The location of this file
**must** be specified in the respective
:file:`/etc/ood/config/apps/bc_desktop/{my_cluster}.yml` form configuration
file, so that when a user submits the form, the specified submission
configuration is used when submitting the batch job.

To customize job submission we will need to first edit our custom desktop app
:ref:`app-development-interactive-form` YAML file as such:

.. code-block:: yaml
   :emphasize-lines: 5-

   # /etc/ood/config/apps/bc_desktop/my_cluster.yml
   ---
   title: "My Cluster Desktop"
   cluster: "my_cluster"
   submit: "submit/my_submit.yml.erb"

Notice we included the configuration option ``submit`` that points to our
custom :ref:`app-development-interactive-submit` YAML configuration file. This
can be an absolute file path or a relative file path with respect to the
:file:`/etc/ood/config/apps/bc_desktop/` directory. It is important to notice  
you must use this or some other directory outside the app's root.

.. note::

   The ``*.erb`` file extension will cause the YAML configuration file to be
   processed using the `eRuby (Embedded Ruby)`_ templating system. This allows
   you to embed Ruby code into the YAML configuration file for flow control,
   variable substitution, and more.

.. danger::

   Do not put the :ref:`app-development-interactive-submit` configuration file
   directly underneath :file:`/etc/ood/config/apps/bc_desktop`. If you do, OOD will think
   this a different app's ``form.yml``. Instead we typically 
   create the directory :file:`submit/` underneath the app's root directory and put our
   :ref:`app-development-interactive-submit` configuration files underneath
   that.

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby

We can now create and modify the :ref:`app-development-interactive-submit`
configuration file at::

  /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb

Since it has the extension ``.erb`` we can take advantage of the Ruby language
to make the configuration file dynamic. In particular, you will now have access
to the user-submitted form arguments defined as:

bc_num_hours
  *Default:* ``"1"``

  A Ruby ``String`` containing the number of hours a user requested for the
  Desktop batch job to run.

bc_num_slots
  *Default:* ``"1"``

  A Ruby ``String`` containing either the number of nodes or processors
  (depending on the type of resource manager the cluster uses) a user
  requested.

bc_account
  *Default:* ``""``

  A Ruby ``String`` that holds the account the user supplied to charge the job
  against.

bc_queue
  *Default:* ``""``

  A Ruby ``String`` that holds the queue the user requested for the job to run
  on.

bc_email_on_started
  *Default:* ``"0"``

  A Ruby ``String`` that can either be ``"0"`` (do not send the user an email
  when the job starts) or ``"1"`` (send an email to the user when the job
  starts).

node_type
  *Default:* ``""``

  A Ruby ``String`` that can be used for more advanced job submission. This is
  an advanced option that is disabled by default and does nothing if you do
  enable it, unless you add it to a custom job submission configuration file.

Some examples on how to submit jobs using the above form attributes are given
in the following sections for the given resource manager.

Slurm
-----

For most cases of Slurm you will want to modify how the ``bc_num_slots``
(number of nodes) is submitted to the batch server.

This can be handled in your custom job submission configuration file as such:

.. code-block:: yaml

   # /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb
   ---
   script:
     native:
       - "-N"
       - "<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>"

All `batch script options`_ are underneath the ``script`` configuration option.
In particular since there is no option to modify number of nodes, we need to
directly interact with the ``native`` command line arguments. This is specified
as an array of :command:`sbatch` arguments.

.. note::

   It is recommended you use the corresponding `batch script options`_ before
   using the ``native`` fallback.

Torque
------

For most cases of Torque you will want to modify how the ``bc_num_slots``
(number of nodes) is submitted to the batch server.

This can be handled in your custom job submission configuration file as such:

.. code-block:: yaml

   # /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb
   ---
   script:
     native:
       resources:
         nodes: "<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>:ppn=28"

All `batch script options`_ are underneath the ``script`` configuration option.
In particular since there is no option to modify number of nodes, we need to
directly interact with the ``native`` command line arguments.

For more information on the available options for the ``native`` attribute
when using Torque please see the `pbs-ruby documentation`_.

.. note::

   It is recommended you use the corresponding `batch script options`_ before
   using the ``native`` fallback.

PBS Professional
----------------

For most cases of PBS Professional you will want to modify how the
``bc_num_slots`` (number of CPUs on a single node) is submitted to the batch
server.

This can be handled in your custom job submission configuration file as such:

.. code-block:: yaml

   # /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb
   ---
   script:
     native:
       - "-l"
       - "select=1:ncpus=<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>"

All `batch script options`_ are underneath the ``script`` configuration option.
In particular since there is no option to modify number of nodes/cpus, we need
to directly interact with the ``native`` command line arguments. This is
specified as an array of :command:`qsub` arguments.

If you would like to mimic how Torque handles ``bc_num_slots`` (number of
**nodes**), then we will first need to change the form label of
``bc_num_slots`` that the user sees in the form. This can be done by modifying
our Desktop app local YAML configuration file:

.. code-block:: yaml
   :emphasize-lines: 5-7

   # /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"
   attributes:
     bc_num_slots:
       label: "Number of nodes"
   submit: "submit/my_submit.yml.erb"

Now when we go to the Desktop app form in our browser it will have the new
label "Number of nodes" instead of "Number of CPUs on a single node".

Next we will need to handle how we submit the ``bc_num_slots`` since it means
something different now. So now modify the job submission configuration file as
such:

.. code-block:: yaml

   # /etc/ood/config/apps/bc_desktop/submit/my_submit.yml.erb
   ---
   script:
     native:
       - "-l"
       - "select=<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>:ncpus=28"

You can also append ``mem=...gb`` to the ``select=...`` statement if you'd
like.

.. note::

   It is recommended you use the corresponding `batch script options`_ before
   using the ``native`` fallback.

.. _batch script options: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
.. _pbs-ruby documentation: http://www.rubydoc.info/gems/pbs/PBS/Batch#submit_script-instance_method

LinuxHost Adapter
--------------------

If you're using the :ref:`resource-manager-linuxhost` you actually don't *need* a specialized
submit.yml.erb. There is no need to specify resources like the other adapters above.

You can however, use it to override the adapter's global fields for mount binding and specifying
which container use.

.. code-block:: yaml

  # /etc/ood/config/apps/bc_desktop/submit/linuxhost_submit.yml.erb
   ---
   batch_connect:
     native:
        singularity_bindpath: /etc,/media,/mnt,/opt,/run,/srv,/usr,/var,/fs,/home
        singularity_container: /usr/local/modules/netbeans/netbeans_2019.sif
