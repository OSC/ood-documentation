.. _app-development-tutorials-interactive-apps-add-custom-queue-local-dynamic-list:

Use a Local Dynamic List
========================

This customization is not for the faint of heart as it requires a fair bit of
Ruby_ knowledge. We will be dynamically generating the queue/partition list
from the command line whenever a user visits the Interactive App's form
submission page. This is accomplished by:

#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-local-dynamic-list-add-custom-attribute`
#. :ref:`app-development-tutorials-interactive-apps-add-custom-queue-local-dynamic-list-handle-custom-attribute`

.. _app-development-tutorials-interactive-apps-add-custom-queue-local-dynamic-list-add-custom-attribute:

Add Custom Attribute to Form
----------------------------

We want to **replace** the ``bc_queue`` form attribute with a custom HTML
``<select>`` element (a drop-down list of options) built up of queue/partition
options read from a forked off command line call.

.. note::

   You can read more about customizing attributes in the ``form.yml`` file for
   Interactive Apps under the
   :ref:`interactive-development-form-customizing-attributes` section.

#. First we rename the ``form.yml`` for the Jupyter Interactive App to
   ``form.yml.erb``:

   .. code-block:: console

      $ mv ~/ondemand/dev/jupyter/form.yml ~/ondemand/dev/jupyter/form.yml.erb

   This will cause the YAML file to be processed using the `eRuby (embedded
   Ruby)`_ templating system, which allows us to embed Ruby_ code into the YAML
   configuration file for flow control, variable substitution, and more.

#. Next we remove the ``bc_queue`` field from our ``form.yml`` for the Jupyter
   Interactive App by removing the following line from this file:

   .. code-block:: yaml

      # ~/ondemand/dev/jupyter/form.yml.erb
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        extra_jupyter_args: ""
      form:
        - modules
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

#. We now add in our custom drop-down attribute with a dynamically generated
   list of queues/partitions (using Slurm as the example):

   .. code-block:: yaml
      :emphasize-lines: 2-15,21-41,46

      # ~/ondemand/dev/jupyter/form.yml.erb
      <%-
        cmd = "/path/to/sinfo -ho %R"
        begin
          output, status = Open3.capture2e(cmd)
          if status.success?
            queues = output.split("\n").map(&:strip).reject(&:blank?).sort
          else
            raise output
          end
        rescue => e
          queues = []
          error = e.message.strip
        end
      -%>
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        extra_jupyter_args: ""
        custom_queue:
          label: Queue
          help: |
            Please select a queue from the drop-down.
          <%- if error -%>

            <span class="text-danger">Error when parsing queues:</span>

            ```
            <%= error.gsub("\n", "\n      ") %>
            ```
          <%- end -%>
        <%- if queues.blank? -%>
          widget: text_field
        <%- else -%>
          widget: select
          options:
          <%- queues.each do |q| -%>
            - [ "<%= q %>", "<%= q %>" ]
          <%- end -%>
        <%- end -%>
      form:
        - modules
        - extra_jupyter_args
        - bc_account
        - custom_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   At the top we have an *execution tag* that:

   - forks off the ``cmd`` call and records the ``output`` and ``status`` (we
     run this inside the ``begin ... rescue ... end`` block in case something
     bad happens when calling the ``cmd``)
   - we split up the lines of the ``output`` into an array and throw away any
     empty lines before saving this into the local variable ``queues``
   - if calling ``cmd`` causes an error we store an empty ``queues`` list and
     record the error message

   Later in the YAML file we have a few more *execution tags* that:

   - appends to the help text an error message if one exists (we have to indent
     the error message if it has newlines to follow YAML formatting)
   - if there are no ``queues`` (maybe something bad happened) use a
     ``text_field`` so the user can manually input the queue/partition they
     want
   - otherwise loop through the list of ``queues`` and output a YAML list of
     pairs (see the note below)

   Now when we refresh the web page for our sandbox Jupyter App we will see a
   "Queue" form element with a drop-down that lists the formatted output from
   the ``cmd`` we defined. Underneath this will be our custom help message
   defined above.

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

.. _app-development-tutorials-interactive-apps-add-custom-queue-local-dynamic-list-handle-custom-attribute:

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
        queue_name: <%= custom_queue.blank? ? "null" : custom_queue.strip %>

   As we allow the user to input the value for ``custom_queue`` we need to be
   careful when handling it:

   - if it is blank we set it to the YAML value ``null``, which won't set a
     queue when submitting the job (you can replace this with a default queue
     for all users if you prefer)
   - otherwise we set the queue to the user defined string with leading and
     trailing whitespace removed

   We also take advantage of the generic `OodCore::Job::Script#queue_name
   <queue_name_>`_ method to supply a queue/partition that is resource manager
   (e.g., Slurm, Torque, ...) agnostic.

   .. note::

      For the queue/partition we do not need to use the ``native:`` field which
      **must be** customized for the specific resource manager you are
      leveraging.

      You can find a list of generic fields that are resource manager agnostic
      under the `OodCore::Job::Script <script_>`_ documentation.

.. _ruby: https://www.ruby-lang.org/en/
.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
.. _queue_name: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script#queue_name-instance_method
.. _script: http://www.rubydoc.info/gems/ood_core/OodCore/Job/Script
