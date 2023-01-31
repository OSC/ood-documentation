.. _app-development-interactive-form:

User Form (form.yml.erb)
========================

The configuration file ``form.yml`` creates the `html form`_ your customers will use
to start the interactive application.


Let's look at a simple example of how the main components ``form`` and ``attributes`` work.
``form`` is a list of form choices for the application. ``attributes`` is then specifying
*what* those items in ``form`` are, whether they're number fields or choices and so on.

.. code-block:: yaml

  # ${HOME}/ondemand/dev/my_app/form.yml
  ---

  # the cluster(s) this app can submit jobs to.
  cluster: "owens"

  # 'form' is a list of form choices for this app. Here we're allowing users to set
  # the account and the number of cores they want to request for this job.
  form:
    - account
    - cores

  # By default, everything defined in 'form' above is a text_field. Let's leave account alone
  # We do however, want cores to be a number_field and with some min & max values.
  attributes:
    cores:
      widget: 'number_field'
      min: 1
      max: 40

It is located in the root of the application directory.

Assuming we already have a sandbox Interactive App deployed under::

  ${HOME}/ondemand/dev/my_app

The ``form.yml`` configuration file can be found at::

  ${HOME}/ondemand/dev/my_app/form.yml

Then in the browser, navigate to the dashboard and choose in the top
right menu: *Develop* → *My Sandbox Apps (Development)*. Finally click *Launch
My App* from the list of sandbox apps.


You should now see the HTML form used to gather the user-defined attributes for
building and launching the ``my_app`` Interactive App session.

.. tip::

   You can include dynamically generated content in the form by renaming the
   form file to ``form.yml.erb`` and incorporating ERB syntax.

Configuration
-------------

This is the full list of items with details, you may supply to this yaml file to configure this application.

.. describe:: cluster (Array<String> or String)

     the cluster ids that the Interactive App session is submitted to.

     .. note::

        Prior to 1.8, this configuration was a single string (a single cluster).
        We now support one application submitting to multiple clusters. See the
        section below on `configuring which cluster to submit to`_ for more information.

     .. warning::

        The cluster id must correspond to a cluster configuration file located
        under::

          /etc/ood/config/clusters.d

.. describe:: form (Array<String>)

     a list of **all** the attributes that will be used as the context for
     describing an Interactive App session

     .. note::

        The attributes that appear as HTML form elements will appear to the
        user in the order they are listed in this configuration option.

.. describe:: attributes (Hash)

     the object defining the hard-coded value or HTML form element used for the
     various custom attributes

.. describe:: cacheable (Boolean)

       whether or not the application is cacheable or not. Defaults to true.

Attributes
----------

Attributes are *variables* whose values can be set either by the user from
within an HTML form or hard-coded to a specific value in the form
configuration. These attributes and their corresponding values are then made
available to the Interactive App through its intermediate steps:
:ref:`app-development-interactive-template` and
:ref:`app-development-interactive-submit`.

.. _app-development-interactive-form-predefined-attributes:

Predefined Attributes
``````````````````````

The Dashboard that supports these plugins provides the plugins with some useful
predefined attributes that can be included in the ``form:`` configuration list
with very little or no modification on the part of the developer.

So a very simple ``form.yml`` that requests the user input a queue followed by
an account to submit the batch job (interactive session) to, and then
subsequently submits the job to that queue without any customization on the
part of the app developer can look like:

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"
   form:
     - bc_queue
     - bc_account

The most commonly used predefined attributes are given as:

bc_account
  This adds a ``text_field`` to the HTML form that will be used as the charged
  account for the submitted job.

  This attribute gets directly set on `OodCore::Job::Script#accounting_id`_.

bc_queue
  This adds a ``text_field`` to the HTML form that will supply the name of the
  queue that the batch job is submitted to.

  This attribute gets directly set on `OodCore::Job::Script#queue_name`_.

bc_num_hours
  This adds a ``number_field`` to the HTML form that describes the maximum
  amount of hours the submitted batch job may run.

  This attribute gets converted to seconds and then set on
  `OodCore::Job::Script#wall_time`_.

bc_num_slots
  This adds a ``number_field`` to the HTML form that describes the number of
  processors, CPUs on a single node, or nodes that the submitted job may use
  (depends on the resource manager used, e.g., Torque, Slurm, ...).

  This attribute manipulates the brittle `OodCore::Job::Script#native`_ field
  with a value that depends on the given resource manager for the cluster.

  .. warning::

     This predefined attribute is very resource manager specific, and is the
     most brittle of all the other predefined attributes. May require
     customization (see
     :ref:`interactive-development-form-customizing-attributes`) to work at
     your center.

bc_email_on_started
  This adds a ``check_box`` to the HTML form that determines whether the user
  should be notified by email when the batch job starts.

  This attribute sets value of `OodCore::Job::Script#email_on_started`_
  depending on whether the user checked the box or not.


.. _auto-bc-form-options:

Automatic Predefined Attributes
````````````````````````````````

Automatic attributes automatically generate lists or values.  For example
``bc_queue`` above will generate a ``text_field`` where the user has to
input the queue name themselves.

``auto_queue`` on the other hand will automatically build a list of queues
for the user to choose from without intervention from the administrator
or the user.

auto_primary_group
  This will automatically set the `OodCore::Job::Script#accounting_id`_ to the
  primary group of the user.  No choice will be given to the user.

auto_modules_<MODULE>
  This will generate a list of modules in a ``select`` widget.
  For example ``auto_modules_matlab`` will automatically populate a dropdown
  list of every single ``matlab`` version available, including the default
  version.
  
  To disable the default version, use the ``attributes`` field like so:
  
  .. code-block:: yaml

     attributes:
       auto_modules_matlab:
         default: false
  
  See :ref:`the module directory configuration <module_file_dir>` on how to enable
  the cluster module files that need to be read.

  If you have dynamic form widgets enabled, the option list will be cluster aware.
  Meaning only versions appropriate to a given cluster will be shown when that
  cluster is chosen.

auto_groups
  This will automatically generate a ``select`` widget populated with a list of the Unix
  groups the user is currently in. Administrators can configure :ref:`filter for autogroups <auto_groups_filter>`
  to limit the groups shown.

auto_queue
  This will generate a ``select`` widget list of all the queues available to the user.

  By default, we return exactly what the scheduler returns. These accounts may be lowercase
  when you need uppercase accounts. To enable uppercase accounts set the environment variable
  ``OOD_UPCASE_ACCOUNTS`` to anything.  If the environment variable is set to *anything* the
  system will uppercase the accounts (set it to ``yes`` if you don't know what value to give).

  .. warning::
    We only have support for Slurm queues (partitions) at this time.

auto_accounts
  This will generate a ``select`` widget list of all the accounts available to the user.

  ``auto_accounts`` will generate cluster aware lists if you have :ref:`dynamic options <dynamic-bc-apps>`
  enabled.  This means it will only show a list of accounts available for the ``cluster`` that's
  currently selected.  If this setting is not enabled, it will generate a list of all accounts
  available on all clusters and will not hide any of them.

  If, however, your site has a simpler accounting scheme where all accounts are available on
  all clusters, you can set the :ref:`bc_simple_auto_accounts <bc_simple_auto_accounts>` setting
  for some optimizations.

  .. warning::
    We only have support for Slurm accounts at this time.

auto_qos
  Coming soon!

.. _`oodcore::job::script#accounting_id`: http://www.rubydoc.info/gems/ood_core/OodCore%2FJob%2FScript:accounting_id
.. _`oodcore::job::script#queue_name`: http://www.rubydoc.info/gems/ood_core/OodCore%2FJob%2FScript:queue_name
.. _`oodcore::job::script#wall_time`: http://www.rubydoc.info/gems/ood_core/OodCore%2FJob%2FScript:wall_time
.. _`oodcore::job::script#email_on_started`: http://www.rubydoc.info/gems/ood_core/OodCore%2FJob%2FScript:email_on_started
.. _`oodcore::job::script#native`: http://www.rubydoc.info/gems/ood_core/OodCore%2FJob%2FScript:native

.. _interactive-development-form-customizing-attributes:

Customizing Attributes
``````````````````````

For each defined attribute in the ``form:`` configuration option, you can
modify/override any component that makes up the HTML form element in the
``attributes:`` configuration option, e.g.:

.. code-block:: yaml

   attributes:
     my_custom_attribute:
       label: "My custom label"
       ...

The available configuration options that can be modified for a given attribute
are:

.. describe:: widget (String, null)

    For more detailed information with examples regarding the widget field, see :ref:`form-widgets`.

     the type of HTML form element to use for input

     - ``check_box``
     - ``hidden_field``
     - ``number_field`` - can use ``min``, ``max``, ``step``
     - ``radio_button``    
     - ``resolution_field`` (used for specifying resolution dimensions necessary for VNC)
     - ``select`` - can use ``options``
     - ``text_area``
     - ``text_field``

     Some other fields that have varying support across different browsers
     include: ``range_field``, ``date_field``, ``search_field``,
     ``email_field``, ``telephone_field``, ``url_field``, ``password_field``.

     Default
       Accepts any text

       .. code-block:: yaml

          widget: "text_field"

     Example
       Accepts only numbers

       .. code-block:: yaml

          widget: "number_field"

.. describe:: value (String, null)

     the default value used for the input field

     Default
       None

       .. code-block:: yaml

          value: ""

     Example
       Set default value of 5

       .. code-block:: yaml

          value: "5"

     .. warning::

        Values get cached so that users do not need to repeat previous session
        submissions. So this default value will only appear for the user if
        they have no cached value.

.. describe:: label (String, null)

     the label displayed above the input field

     Default
       Uses the name of the attribute

     Example
       Better describe the attribute

       .. code-block:: yaml

          label: "Number of nodes"

.. describe:: required (Boolean, null)

     whether this field must be filled out before submitting the form

     Default
       Not required by default

       .. code-block:: yaml

          required: false

     Example
       Make field required

       .. code-block:: yaml

          required: true

.. describe:: help (String, null)

     help text that appears below the field (can be written in Markdown_)

     Default
       No help text appears below input field

       .. code-block:: yaml

          help: null

     Example
       Leave a long descriptive help message using Markdown_

       .. code-block:: yaml

          help: |
            Please fill in this field with **one** of the following
            options:

            - `red`
            - `blue`
            - `green`

.. describe:: pattern (String, null)

     a regular expression that the control's value is checked against (only
     applies to widgets: ``text_field``, ``search_field``, ``telephone_field``,
     ``url_field``, ``email_field``, ``password_field``)

     Default
       No pattern

       .. code-block:: yaml

          pattern: null

     Example
       Only accept three letter country codes

       .. code-block:: yaml

          pattern: "[A-Za-z]{3}"

.. describe:: min (Integer, null)

     specifies minimum value for this item, which must not be greater than its
     maximum value (only applies to widget: ``number_field``)

     Default
       No minimum value

       .. code-block:: yaml

          min: null

     Example
       Set minimum value of 5

       .. code-block:: yaml

          min: 5

.. describe:: max (Integer, null)

     specifies maximum value for this item, which must not be less than its
     minimum value (only applies to widget: ``number_field``)

     Default
       No maximum value

       .. code-block:: yaml

          max: null

     Example
       Set maximum value of 15

       .. code-block:: yaml

          max: 15

.. describe:: step (Integer, null)

     works with ``min`` and ``max`` options to limit the increments at which a
     value can be set, it can be the string ``"any"`` or positive floating
     point number (only applies to widget: ``number_field``)

     Default
       No step size

       .. code-block:: yaml

          step: null

     Example
       Only accept integer values

       .. code-block:: yaml

          step: 1

.. describe:: options (Array<Array<String>>, null)

    A list of options for a ``select`` widget.  In the simplest form
    you can have a list of strings like ``chevy`` in example below.
    They can also be in the form ``[<label>, <value>]`` where label is the
    HTML label shown in the web page and value is the actual value
    that will be sent to the server and used.

    Lastly you can also set extra ``data`` HTML attributes like the
    example ``Toyota`` below. These extra attributes can be used by javascript
    or options for :ref:`dynamic options <dynamic-bc-apps>`.

     Default
       No options are supplied

       .. code-block:: yaml

          options: []

     Example

       .. code-block:: yaml

          options:
            - ["Volvo", "volvo"]
            - ["Ford", "ford"]
            - "chevy"
            - [
                "Toyota",
                "toyota",
                data-some-extra-attribute: 'set'
              ]

.. describe:: cacheable (Boolean, true)

     whether the form item is cacheable or not

     Default
       cacheable

       .. code-block:: yaml

          cacheable: true

     Example
       The item is not cacheable

       .. code-block:: yaml

          cacheable: false

.. describe:: display (Boolean, false)

     whether the form item should be displayed in the session card after it was created.

     Default
       False. The form item will not be displayed.

       .. code-block:: yaml

          display: false

     Example
       Display form item in the session card.

       .. code-block:: yaml

          display: true

Examples
--------

The simplest example consists of only a cluster id

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"

where we expect the Interactive App session to be submitted with the following
cluster configuration file::

  /etc/ood/config/clusters.d/owens.yml

After modifying the ``form.yml`` click *Launch My App* from the Dashboard
sandbox app list and you should be presented with **ONLY** a Launch button,
since we didn't define ``form:`` or ``attributes:``.

User-defined Attributes
```````````````````````

The following configuration file

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"
   form:
     - my_module_version

defines a session context attribute called ``my_module_version``.

.. warning::

   Do not use ``partition`` as attribute name within the form. The (Ruby)
   object created by the form is of type enumerable and ``partition`` is
   method of that particular class. This causes the value set in the form not
   being correctly passed to the submit script.

After modifying the ``form.yml`` click *Launch My App* from the Dashboard
sandbox app list and you will see an empty text box with the label "My Module
Version". The user can input any value here and launch the Interactive App
session. This value will be made available to the batch job script and
submission parameters that are discussed in a later section.

Hard-coded Attributes
`````````````````````

The following configuration file

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"
   form:
     - my_module_version
   attributes:
     my_module_version: "2.2.0"

does two things:

- it defines a context attribute called ``my_module_version`` in the ``form:``
  configuration option
- it then sets the value of ``my_module_version`` to ``"2.2.0"`` in the
  ``attributes:`` configuration option to later be used when defining the batch
  job script and/or submission parameters

The user will now **ONLY** be presented with a Launch button in the HTML form
because the attribute ``my_module_version`` is hard-coded, so there is no need
for a input text box.

Customize User-defined Attributes
`````````````````````````````````

The following configuration file

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"
   form:
     - my_module_version
   attributes:
     my_module_version:
       widget: "number_field"
       label: "Module version #"
       required: true
       help: "Please input a version number between 1-10"
       min: 1
       max: 11
       step: 1

does two things:

- it defines a context attribute called ``my_module_version`` in the ``form:``
  configuration option
- it then describes the HTML form element to use for the ``my_module_version``
  attribute

.. _caching-form-items:

Caching form items
``````````````````

Since 1.8 caching form items is configurable. By default all form items are
cacheable. As seen above you can enable or disable caching for the entire app
when using the top level ``cacheable`` configuration. You can also configure
on a per item basis through attributes.

Lastly you can also enable or disable this feature for the entire site, using
the configuration ``OOD_BATCH_CONNECT_CACHE_ATTR_VALUES=false`` in the
dashboard's environment file ``/etc/ood/config/apps/dashboard/env``.

.. tip::

   Since you can configure caching at different levels the rule of thumb is the
   closer the configuration is to the form item, the higher the precedence.

   Setting the configuration on the attribute overrides everything and setting it
   on a per app basis overrides the global setting.


Let's see an example.  Here, we've disabled caching for the app and did not
set OOD_BATCH_CONNECT_CACHE_ATTR_VALUES, so the site-wide configuration is set
to true by default.  So, ``bc_num_slots`` and ``python_version`` are not cacheable,
meaning the user will have to fill those form entries out every time they submit
the job. But since ``bc_queue``'s attribute is set to true, it is cacheable.

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   # OOD_BATCH_CONNECT_CACHE_ATTR_VALUES is not set, so defaults to true
   ---
   cluster: "owens"
   cacheable: false
   form:
     - bc_num_slots
     - python_version
     - bc_queue
   attributes:
     bc_queue:
       cacheable: true


.. _display-form-choices:

Displaying form items in the session card
`````````````````````````````````````````

Now, submitted form values can be displayed in the session card for users to see.
By default, items will not be shown. Add the display property to the form attributes that you wish to show.
Form values will be added after the default session card items. The order is driven from the ``form`` array.

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   ---
   cluster: "owens"
   form:
     - bc_num_hours
     - bc_num_slots
   attributes:
     bc_num_slots:
       display: true
     bc_num_hours:
       display: true

.. figure:: /images/form-display-attribute.png
   :align: center

.. _configuring-cluster:

Configuring which cluster to submit to
--------------------------------------

In 1.8 there are now several ways to configure what cluster to submit to.

The easiest way is to use the the top level ``cluster`` configuration. If you've
configured just one item, then the form UI does not change for the user. If
you configure an array of two or more options then a select dropdown will
automatically be added to the top of the form.

.. code-block:: yaml

   # ${HOME}/ondemand/dev/my_app/form.yml
   # which will generate a dropdown select automatically
   ---
   cluster:
     - "cluster1"
     - "cluster2"

.. tip::

   GLOBs are also supported. So in the example above one entry of ``cluster*``
   would have been equivalent to explicitly configuring both ``cluster1`` and
   ``cluster2``.

   This means you could configure ``cluster: "*"`` to be able to submit to all
   clusters.

If you would prefer to use some other widget, or you wish to change the text being
shown in the UI you can configure a cluster form item and specify it's attributes.
This gives you some flexibility in the form UI instead of the default select
widget that shows all lowercase cluster names.

Here's an example were the user will be shown a select dropdown menu item with
different text than the default.

.. code-block:: yaml

   # ${HOME}/ondemand/dev/different_select_cluster/form.yml
   ---
   form:
     - cluster
   attributes:
     cluster:
       widget: "select"
       options:
         - ["The first cluster", "cluster1"]
         - ["The second cluster", "cluster2"]

The last option is to :ref:`configure the cluster in the submit file <configuring-cluster-in-submit-yml>`.
When using this option, there's no need to add any cluster configuration to the
form.yml.

.. _markdown: https://en.wikipedia.org/wiki/Markdown
.. _html form: https://en.wikipedia.org/wiki/Form_(HTML)
