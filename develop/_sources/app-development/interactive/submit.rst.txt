.. _app-development-interactive-submit:

Job Submission
==============

The configuration file ``submit.yml.erb`` controls the content of the batch
script as well as the submission arguments used when submitting the batch job.
It is located in the root of the application directory.

Assuming we already have a sandbox Interactive App deployed under::

  ${HOME}/ondemand/dev/my_app

The ``submit.yml.erb`` configuration file can be found at::

  ${HOME}/ondemand/dev/my_app/submit.yml.erb

The ``.erb`` file extension will cause the YAML configuration file to be
processed using the `eRuby (Embedded Ruby)`_ templating system. This allows you
to embed Ruby code into the YAML configuration file for flow control, variable
substitution, and more.

Configuration
-------------

The two possible configuration options that can be used in the
``submit.yml.erb`` file are given as:

.. describe:: batch_connect (Hash)

   the configuration describing the batch script content (see
   `OodCore::BatchConnect::Template`_ for valid configuration options)

   Example
     Use the default basic web server template

     .. code-block:: yaml

        # ${HOME}/ondemand/dev/my_app/submit.yml.erb
        ---
        batch_connect:
          template: "basic"

.. describe:: script (Hash)

   the configuration describing the job submission parameters for the batch
   script (see `OodCore::Job::Script`_ for valid configuration options)

   Example
     Set the job's charged account and queue

     .. code-block:: yaml

        # ${HOME}/ondemand/dev/my_app/submit.yml.erb
        ---
        script:
          accounting_id: "PZS0001"
          queue_name: "parallel"

Each of these configuration options take a set of their own configuration
options described below.

Configure Batch Connect
```````````````````````

All batch scripts are generated from either the ``basic`` template or the
``vnc`` template specified with the following configuration option:

.. describe:: template (String)

   the template used for rendering the batch script (``"basic"`` or ``"vnc"``)

   Default
     ``"basic"``

   Example
     Render a batch script for a VNC Interactive Application

     .. code-block:: yaml

        # ${HOME}/ondemand/dev/my_app/submit.yml.erb
        ---
        batch_connect:
          template: "vnc"

Aside from the above configuration option, a list of all possible configuration
options for ``batch_connect`` can be found under the code documentation for
`OodCore::BatchConnect::Template`_.

.. note::

   The configuration ``template: "vnc"`` comes with more ``batch_connect``
   configuration options which can be found under the code documentation for
   `OodCore::BatchConnect::Templates::VNC`_.

Configure Script
````````````````

The ``script`` configuration option defines the batch job submission parameters
(e.g., number of nodes, wall time, queue, ...). The list of all possible
options can be found under the code documentation for `OodCore::Job::Script`_.

It is recommended to refrain from using the ``native`` option to best keep your
Interactive App as portable as possible. Although we understand this may not be
possible for all job submission parameters (e.g., number of nodes, memory, GPU)
it would be best to use the respective option corresponding to the submission
parameter if it is available.

For example, if I want to specify the charged account for the job, it is
recommended I use:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   script:
     accounting_id: "PZS0001"

as this is resource manager agnostic. But this can also be added for a Slurm
resource manager as:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   script:
     native: ["-A", "PZS0001"]

but now this app may not work at a center with a different resource manager.

.. warning::

   Care must be taken when using the ``native`` option as this is resource
   manager specific. For all supported resource managers (e.g., Slurm, LSF,
   PBSPro, ...) other than Torque, the ``native`` option is specified as an
   array of command line arguments that are fed to the resource manager's batch
   submission tool (e.g., :command:`sbatch`, :command:`qsub`, :command:`bsub`,
   ...)

   So for Slurm, the following configuration will submit a job to 5 nodes with
   feature ``c12``:

   .. code-block:: yaml

      # ${HOME}/ondemand/dev/my_app/submit.yml.erb
      ---
      script:
        native: ["-N", "5", "-C", "c12"]

Examples
--------

The simplest example consists of submitting a batch script built from the basic
web server template using all the default options for the cluster's batch job
submission tool (e.g., :command:`sbatch`, :command:`qsub`, :command:`bsub`,
...).

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "basic"

VNC Server
``````````

To submit a batch script built from the VNC server template:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "vnc"

Change Executable for Main Script
`````````````````````````````````

When the batch script is rendered from the template, one of the possible
configuration options is specifying the executable command called for the main
script it forks off into the background. This can be configured with:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "basic"
     script_file: "./my_custom_script.sh"

Specify Job Submission Parameters
`````````````````````````````````

Cherry-picking some possible options from `OodCore::Job::Script`_ gives a batch
job built from the basic web server template submitted with the following
parameters:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "basic"
   script:
     wall_time: 3600
     queue_name: "debug"
     email_on_started: true
     job_environment:
       LICENSE_FILE: "1234@license.center.edu"

Dynamically Set Submission Parameters
`````````````````````````````````````

Feel free to take advantage of the `eRuby (Embedded Ruby)`_ templating system
in the ``submit.yml.erb`` file. You have access to all the
:ref:`app-development-interactive-form` attributes.

For example, if you had a form attribute called ``number_of_hours`` that you
had the user fill out. You can add this to the submission parameters as such:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "basic"
   script:
     wall_time: <%= (number_of_hours.blank? ? 1 : number_of_hours.to_i) * 3600 %>

We have to be careful here, because all form attributes are returned as `Ruby
Strings`_. So we need to:

#. First determine if the user filled in the attribute (check if it is
   ``#blank?``).
#. If they did, then we need to convert the string to an integer (``#to_i``)
   before performing arithmetic operations on it.
#. Finally we convert hours to seconds.

Another scenario would be if the user specified the queue directly with a
custom form attribute called ``my_queue``. We can then add this user-supplied
queue conditionally to the submission parameters as such:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/submit.yml.erb
   ---
   batch_connect:
     template: "basic"
   script:
     wall_time: 3600
     <%- unless my_queue.blank? -%>
     queue_name: <%= my_queue %>
     <%- end -%>
     email_on_started: true

In this case, ``queue_name`` will only be added to the submission parameters if
the user supplied a non-blank value to the form attribute ``my_queue``.

.. note::

   Most of the common form attributes that manipulate the job submission
   parameters are provided for you as
   :ref:`app-development-interactive-form-predefined-attributes`. These
   special attributes fill-in the ``script`` configuration options internally,
   so you do not have to.

   For example, if you used the predefined form attribute ``bc_queue``, you do
   not need to specify ``queue_name:`` in the ``submit.yml.erb``.

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
.. _`oodcore::batchconnect::template`: http://www.rubydoc.info/gems/ood_core/OodCore/BatchConnect/Template
.. _`oodcore::batchconnect::templates::vnc`: http://www.rubydoc.info/gems/ood_core/OodCore/BatchConnect/Templates/VNC
.. _`oodcore::job::script`: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
.. _ruby strings: https://ruby-doc.org/core-2.2.3/String.html
