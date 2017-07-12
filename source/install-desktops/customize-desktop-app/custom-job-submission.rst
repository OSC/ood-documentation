.. _install-desktops-customize-desktop-app-custom-job-submission:

Custom Job Submission
=====================

To customize job submission we will need to first edit our custom desktop app
YAML file as such:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that points to our custom job submission
   # configuration file
   submit: "submit/my_submit.yml.erb"

Notice we included the configuration option ``submit`` that points to our
custom job submission YAML configuration file. This can be an absolute file
path or a relative file path with respect to the ``local/`` directory.

We can now create and modify a job submission configuration file at::

  bc_desktop/local/submit/my_submit.yml.erb

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

   # bc_desktop/local/submit/my_submit.yml.erb
   ---
   script:
     native: [ "-N", "<%= bc_num_slots %>" ]

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

   # bc_desktop/local/submit/my_submit.yml.erb
   ---
   script:
     native:
       resources:
         nodes: "<%= bc_num_slots %>:ppn=28"  # assumes cluster has 28 procs per node

All `batch script options`_ are underneath the ``script`` configuration option.
In particular since there is no option to modify number of nodes, we need to
directly interact with the ``native`` command line arguments.

For more information on the available options for the ``native`` attribute
when using Torque please see the `pbs-ruby documentation`_.

.. note::

   It is recommended you use the corresponding `batch script options`_ before
   using the ``native`` fallback.

LSF
---

TODO

PBS Professional
----------------

For most cases of Slurm you will want to modify how the ``bc_num_slots``
(number of CPUs on a single node) is submitted to the batch server.

This can be handled in your custom job submission configuration file as such:

.. code-block:: yaml

   # bc_desktop/local/submit/my_submit.yml.erb
   ---
   script:
     native: [ "-l", "select=1:ncpus=<%= bc_num_slots %>" ]

All `batch script options`_ are underneath the ``script`` configuration option.
In particular since there is no option to modify number of nodes/cpus, we need
to directly interact with the ``native`` command line arguments. This is
specified as an array of :command:`qsub` arguments.

If you would like to mimic how Torque handles ``bc_num_slots`` (number of
**nodes**), then we will first need to change the form label of
``bc_num_slots`` that the user sees in the form. This can be done by modifying
our Desktop app local YAML configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"
   submit: "submit/my_submit.yml.erb"

   # Add the below option that allows us to modify attributes
   attributes:
     bc_num_slots:
       label: "Number of nodes"

Now when we go to the Desktop app form in our browser it will have the new
label "Number of nodes" instead of "Number of CPUs on a single node".

Next we will need to handle how we submit the ``bc_num_slots`` since it means
something different now. So now modify the job submission configuration file as
such:

.. code-block:: yaml

   # bc_desktop/local/submit/my_submit.yml.erb
   ---
   script:
     native: [ "-l", "select=<%= bc_num_slots %>:ncpus=28" ] # assumes 28 procs per node

You can also append ``mem=...gb`` to the ``select=...`` statement if you'd
like.

.. note::

   It is recommended you use the corresponding `batch script options`_ before
   using the ``native`` fallback.

.. _batch script options: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
.. _pbs-ruby documentation: http://www.rubydoc.info/gems/pbs/PBS/Batch#submit_script-instance_method
