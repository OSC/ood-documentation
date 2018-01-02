.. _app-development-tutorials-interactive-apps-add-custom-queue-global-static-list:

Use a Global Static List
========================

.. warning::

   Requires permissions to modify the global cluster configurations located
   under::

     /etc/ood/config/clusters.d/

You can take advantage of the Cluster Configuration files for defining a
**common** static queue/partition list that can be used across all properly
configured Interactive Apps. This is accomplished by:

#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-modify-cluster-configuration`
#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-add-custom-attribute`
#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-handle-custom-attribute`

.. _app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-modify-cluster-configuration:

Modify Cluster Configuration
----------------------------

.. danger::

   This assumes you have walked through :ref:`add-cluster-config` for the
   cluster you intend on submitting the Interactive App to.

We will add a ``custom:`` field to our cluster configuration file if it doesn't
already exist and then introduce a custom field (named anything your heart
desires) with a list of available queues/partitions:

.. code-block:: yaml
   :emphasize-lines: 10-

   # /etc/ood/config/clusters.d/my_cluster.yml
   ---
   v2:
     metadata:
       title: "My Cluster"
     login:
       host: "my_cluster.my_center.edu"
     job:
       # ... resource manager specific options here ...
     custom:
       queues: # this can be named anything your heart desires
         - "queue1"
         - "queue2"

.. warning::

   Be sure to click "Restart Web Server" on the Dashboard everytime you edit
   the Cluster Configuration file for changes to take effect within the app.

.. _app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-add-custom-attribute:

Add Custom Attribute to Form
----------------------------

We want to **replace** the ``bc_queue`` form attribute with a custom HTML
``<select>`` element (a drop-down list of options) built up of queue/partition
options read from the corresponding cluster configuration file.

.. note::

   You can read more about customizing attributes in the ``form.yml`` file for
   Interactive Apps under the
   :ref:`interactive-development-form-customizing-attributes` section.

#. First we rename the ``form.yml`` for the Jupyter Interactive App to
   ``form.yml.erb``:

   .. code-block:: shell

      mv ~/ondemand/dev/jupyter/form.yml ~/ondemand/dev/jupyter/form.yml.erb

   This will cause the YAML file to be processed using the `eRuby (embedded
   Ruby)`_ templating system, which allows us to embed Ruby_ code into the YAML
   configuration file for flow control, variable substitution, and more.

#. Next we start with the default ``form.yml`` for the Jupyter Interactive App:

   .. code-block:: yaml

      # ~/ondemand/dev/jupyter/form.yml.erb
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        conda_extensions: "1"
        extra_jupyter_args: ""
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - bc_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

#. We remove the following line from this file:

   .. code-block:: yaml
      :emphasize-lines: 2

      - bc_account
      - bc_queue
      - bc_num_hours

   Now when we refresh the web page for our sandbox Jupyter App we won't see
   the "Queue" form element anymore.

#. We now add in code that reads in the list of available queues/partitions
   from the cluster configuration file and generates a custom drop-down
   attribute with this list of queues/partitions:

   .. code-block:: yaml
      :emphasize-lines: 2-4,11-18,24

      # ~/ondemand/dev/jupyter/form.yml.erb
      <%-
        queues = OodAppkit.clusters[:my_cluster].custom_config[:queues]
      -%>
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        conda_extensions: "1"
        extra_jupyter_args: ""
        custom_queue:
          label: Queue
          help: Please select a queue from the drop-down.
          widget: select
          options:
          <%- queues.each do |q| -%>
            - [ "<%= q %>", "<%= q %>" ]
          <%- end -%>
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - custom_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   At the top we have an *execution tag* that sets a local variable ``queues``
   from a line of Ruby code that should read in the list of queues you defined
   under ``custom:`` and ``queues:`` for the corresponding cluster
   configuration file.

   .. warning::

      The cluster defined in ``OodAppkit.clusters[:my_cluster]`` **must**
      correspond to a cluster with a cluster configuration file. Also it should
      match the cluster defined on the line:

      .. code-block:: yaml

         cluster: "my_cluster"

      in the ``form.yml.erb`` file above.

   Later in the YAML file we have another *expression tag* that loops through
   this list of queues/partitions in the local variable ``queues``. It will
   output a YAML list of pairs (see the note below).

   Now when we refresh the web page for our sandbox Jupyter App we will see a
   "Queue" form element with a drop-down that lists "queue1" and "queue2".
   Underneath this will be our custom help message defined above.

   .. note::

      An attribute with the field ``widget: select`` expects an ``options:``
      field with an array of pairs. The first string in the pair is the option
      text and the second string in the pair is the option value.

      For example:

      .. code-block:: yaml

         widget: select
         options:
           - [ "Volvo", "volvo" ]
           - [ "Ford", "ford" ]
           - [ "Toyota", "toyota" ]

      The user will see a list of options: "Volvo", "Ford", and "Toyota" to
      choose from in the HTML form, but the backend will process a value of
      either "volvo", "ford", or "toyota" depending on what the user chose.

.. _app-development-tutorials-interactive-apps-add-custom-queue-global-static-list-handle-custom-attribute:

Handle Custom Attribute in Job Submission
-----------------------------------------

Now that we have our custom form attribute called ``custom_queue``, we need to
tell our app how to handle it when submitting the job. As of right now our app
has no idea what to do with this value when the user clicks "Launch" after
filling out the form.

.. note::

   You can read more about customizing submission arguments in the
   ``submit.yml.erb`` file for Interactive Apps under the
   :ref:`app-development-interactive-submit` section.

#. We first start with the default ``submit.yml.erb`` for the Jupyter
   Interactive App:

   .. code-block:: yaml

      # ~/ondemand/dev/jupyter/submit.yml.erb
      ---
      batch_connect:
        template: "basic"

#. We now create a ``script:`` section if it doesn't already exist and handle
   the value of the ``custom_queue`` attribute submitted by the user:

   .. code-block:: yaml
      :emphasize-lines: 5-

      # ~/ondemand/dev/jupyter/submit.yml.erb
      ---
      batch_connect:
        template: "basic"
      script:
        queue_name: <%= custom_queue %>

   Where we take advantage of the generic `OodCore::Job::Script#queue_name <queue_name>`_
   method to supply a queue/partition that is resource manager (e.g., Slurm,
   Torque, ...) agnostic.

   .. note::

      For the queue/partition we do not need to use the ``native:`` field which
      **must be** customized for the specific resource manager you are
      leveraging.

      You can find a list of generic fields that are resource manager agnostic
      under the `OodCore::Job::Script <script>`_ documentation.

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
.. _ruby: https://www.ruby-lang.org/en/
.. _queue_name: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script#queue_name-instance_method
.. _script: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
