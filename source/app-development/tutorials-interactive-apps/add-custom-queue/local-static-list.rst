.. _app-development-tutorials-interactive-apps-add-custom-queue-local-static-list:

Use a Local Static List
=======================

The *simplest* customization can be done by defining a static list of
queues/partitions within the Interactive App that a user can submit the batch
job to. This is accomplished by:

#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-local-static-list-add-custom-attribute`
#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-local-static-list-handle-custom-attribute`

.. _app-development-tutorials-interactive-apps-add-custom-queue-local-static-list-add-custom-attribute:

Add Custom Attribute to Form
----------------------------

We want to **replace** the ``bc_queue`` form attribute with a custom HTML
``<select>`` element (a drop-down list of options).

.. note::

   You can read more about customizing attributes in the ``form.yml`` file for
   Interactive Apps under the
   :ref:`interactive-development-form-customizing-attributes` section.

#. Starting with the the default ``form.yml`` for the Jupyter Interactive
   App, replace the bc_queue field with a custom queue field that is configured
   as a drop-down of queues/partitions. The code diff is:

   .. code-block:: diff

        # ~/ondemand/dev/jupyter/form.yml
        ---
        cluster: "my_cluster"
        attributes:
          modules: "python"
          conda_extensions: "1"
          extra_jupyter_args: ""
      +   custom_queue:
      +     label: Queue
      +     help: Please select a queue from the drop-down.
      +     widget: select
      +     options:
      +       - [ "Queue 1", "queue1" ]
      +       - [ "Queue 2", "queue2" ]
        form:
          - modules
          - conda_extensions
          - extra_jupyter_args
          - bc_account
      -   - bc_queue
      +   - custom_queue
          - bc_num_hours
          - bc_num_slots
          - bc_email_on_started

  And the resulting yaml is:

   .. code-block:: yaml
      :emphasize-lines: 8-14,20

      # ~/ondemand/dev/jupyter/form.yml
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
            - [ "Queue 1", "queue1" ]
            - [ "Queue 2", "queue2" ]
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - custom_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   Now when we refresh the web page for our sandbox Jupyter App we will see a
   "Queue" form element with a drop-down that lists "Queue 1" and "Queue 2".
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

.. _app-development-tutorials-interactive-apps-add-custom-queue-local-static-list-handle-custom-attribute:

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

.. _queue_name: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script#queue_name-instance_method
.. _script: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
