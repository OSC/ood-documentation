.. _add-jupyter-modify-submit-parameters:

Modify Submit Parameters
========================

In some cases the Jupyter app batch job fails to submit to the given cluster or
you are not happy with the default chosen submission parameters. This section
explains how to modify the submission parameters.

Modify Submit File
------------------

The main responsibility of the ``submit.yml.erb`` file is for modifying the
underlying batch script that is generated from an internal template and its
submission parameters.

.. note::

   The ``.erb`` file extension will cause the YAML configuration file to be
   processed using the `eRuby (Embedded Ruby)`_ templating system. This allows
   you to embed Ruby code into the YAML configuration file for flow control,
   variable substitution, and more.

The simplest ``submit.yml.erb`` will look like:

.. code-block:: yaml

   # submit.yml.erb
   ---

   batch_connect
     template: "basic"

Which only describes which internal template to use when generating the batch
script. From here we can add more options to the batch script, such as:

.. code-block:: yaml

   # submit.yml.erb
   ---

   batch_connect
     template: "basic"
     set_host: "host=$(hostname -A | awk '{print $2}')"

where we override the Bash script used to determine the host name of the
compute node from within a running batch job.

You can learn more about possible ``batch_connect`` options here:

http://www.rubydoc.info/gems/ood_core/OodCore%2FBatchConnect%2FTemplate:initialize

.. warning::

   It is recommended any global ``batch_connect`` attributes be defined in the
   corresponding cluster configuration file under::

     /etc/ood/config/clusters.d/cluster.yml

   There is further discussion on this under
   :ref:`install-desktops-modify-cluster-configuration`.

But in most cases you will want to change the actual job submission parameters (e.g., node type). These are defined under the ``script`` option as:

.. code-block:: yaml

   # submit.yml.erb
   ---

   batch_connect
     template: "basic"

   script:
     ...

You can read more about all the available ``script`` options here:

http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script

Although in most cases you will want to modify the ``native`` attribute, which
is resource manager dependent. Some examples are given below.

.. note::

   It is recommended you commit the changes you made to ``submit.yml.erb`` to
   `git`_:

   .. code-block:: sh

      # Stage the modified file
      git add submit.yml.erb

      # Commit your changes
      git commit -m 'updated batch job options'

Slurm
`````

For Slurm, you can choose the features on a requested node with:

.. code-block:: yaml

   # submit.yml.erb
   ---

   batch_connect
     template: "basic"

   script:
     native: [ "-N", "<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>", "-C", "c12" ]

where we define the :command:`sbatch` parameters as an array under ``script`` and
``native``.

.. note::

   The ``bc_num_slots`` shown above located within the ERB syntax is the value
   returned from web form for "Number of nodes". We check if it is blank and
   return a valid number.

Torque
``````

For Torque, you can choose processors-per-node with:

.. code-block:: yaml

   # submit.yml.erb
   ---

   batch_connect
     template: "basic"

   script:
     native:
       resources:
         nodes: "<%= bc_num_slots.blank? ? 1 : bc_num_slots.to_i %>:ppn=28"

.. note::

   The ``bc_num_slots`` shown above located within the ERB syntax is the value
   returned from web form for "Number of nodes". We check if it is blank and
   return a valid number.

Other
`````

For most of our adapters (aside from Torque) the ``native`` attribute is an
array of command line arguments similar to Slurm above.

Verify it Works
---------------

You can now test the app again by visiting your local OnDemand server in your
browser:

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/jupyter_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

Fill in the form and launch the Jupyter batch job. Click the "Session ID" link
for the launched session and confirm your changes are made under:

- ``job_script_content.sh`` (if modified ``batch_connect``)
- ``job_script_options.json`` (if modified ``script``)

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
.. _git: https://git-scm.com/
