.. _install-desktops-customize-desktop-app-modify-form-attributes:

Modify Form Attributes
======================

In some cases you may want to modify a form attribute. Some examples:

- Use a Gnome desktop instead of Mate desktop.
- Remove the "Queue" form field as your cluster will handle the queue
  dynamically.
- Hard-code the "Number of nodes" to just 1, so that users can't launch
  desktops with multiple nodes.
- Change the label for the form field "Account" to "Project".
- Add help text to a given form field.
- Change default value for a form field.

All modifications can be done in your custom desktop app YAML file as such:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     # ...
     # modifications go here
     # ...

Before we begin modifying form attributes. Let us first take a look at the
default form definition located at :file:`bc_desktop/form.yml`:

.. code-block:: yaml

   # bc_desktop/form.yml
   ---
   description: |
     This app will launch an interactive desktop on one or more compute nodes. You
     will have full access to the resources these nodes provide. This is analogous
     to an interctive batch job.
   attributes:
     desktop: "mate"
     bc_vnc_idle: 0
     bc_vnc_resolution:
       required: true
     node_type: null
   form:
     - bc_vnc_idle
     - desktop
     - bc_num_hours
     - bc_num_slots
     - node_type
     - bc_account
     - bc_queue
     - bc_vnc_resolution
     - bc_email_on_started

The ``description``, ``attributes``, and ``form`` configuration options can be
all overridden in our local YAML configuration file. But typically you will
only modify ``description`` and/or the ``attributes`` options.

In the following sections you will find common examples on how to override the
above options.

.. note::

   The ``form`` configuration option defines all the available attributes as
   well as the order they appear in the form.

.. warning::

   Caution must be taken if you decide to ovverride the ``form`` configuration
   option. As this is an array, you can't simply prepend or append, you will
   need to completely redefine it with your included modifications.

Change to Gnome Desktop
-----------------------

The default installation has the ``desktop`` attribute hard-coded to the value
``"mate"``. If you would like to change this to use ``"gnome"`` you can make
the following edits to your custom YAML configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     desktop: "gnome"

And all Desktops will attempt to launch the Gnome desktop.

.. note::

   Whenever you hard-code a form attribute to a value like ``"gnome"`` in the
   above case, no input field will appear in the form for the user to fill in.
   So in the above case, the user cannot specify the ``desktop`` attribute in
   the form because we hard-coded it.

Remove Form Field
-----------------

To remove a form field such as "Queue" defined under the attribute ``bc_queue``
from the Desktop form you can make the following edits to your custom YAML
configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     bc_queue: null

After refreshing the form in your browser you should not see the "Queue" field
anymore.

Basically we are hard-coding the value of ``bc_queue`` to be the YAML type
``null``. And as we discussed in the previous example whenever you hard-code an
attribute, it will not show up in the form.

.. warning::

   If you have any
   :ref:`install-desktops-customize-desktop-app-custom-job-submission`
   configuration files that use this attribute, they will receive empty strings
   ``""``, so you will need to test if they are blank before handling them.

Hard-code a Form Field
----------------------

If we want to remove a form field but define its value to something other than
a blank string, we can set the attribute's value directly.

For example, if you don't want users to submit Desktops with more than 1 node
under the attribute ``bc_num_slots``, you can make the following edits to your
custom YAML configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     bc_num_slots: 1

As in the previous two examples, since we are hard-coding the value of the
attribute, the form field will not show up and the user is unable to change
this value. For the above case, the attribute ``bc_num_slots`` will always
return ``"1"``.

.. warning::

   If you have any
   :ref:`install-desktops-customize-desktop-app-custom-job-submission`
   configuration files that use this attribute, care must be taken when
   handling the attribute as it will always come back as a Ruby string.

   So if you hard-coded an attribute to the integer ``1`` it will come back as
   the string ``"1"`` and if you perform any arithmetic operations on this
   attribute it will require you convert this back to an integer with the
   method ``String#to_i``.

Change a Label
--------------

You are able to modify the label for a corresponding attribute that appears
above the input field in the form.

For example, if you want to change the label for the "Account" form field given
by the ``bc_account`` attribute to instead display "Project". This can be
modified with the following edits to your custom YAML configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     bc_account:
       label: "Project"

The key here is that we are defining a hash for the ``bc_account`` attribute
instead of hard-coding it to a specific value. This means we will only override
the equivalent option for this attribute (for the above example we are
ovverriding the ``label`` option for the ``bc_account`` attribute).

Now when you refresh the form in your browser, you should now see an input
field with the label "Project".

.. warning::

   If you have any
   :ref:`install-desktops-customize-desktop-app-custom-job-submission`
   configuration files that use this attribute, changing the label of the
   attribute will not affect the value received by the user upon form
   submission.

   But care must be taken that if by changing the label of the attribute you
   also change the *meaning* of the attribute, then you may have to handle it
   differently. For example, changing a label of "Number of processors" to
   "Number of nodes" will have consequences on how you submit the job.

Add Help Message to Field
-------------------------

You are also able to add a help message to any given form field through its
corresponding attribute.

For example, if you would like to add a help message to the attribute
``bc_account`` you can make the following edits to your custom YAML
configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     bc_account:
       help: "You can leave this blank if **not** in multiple projects."

The key here is that we are defining a hash for the ``bc_account`` attribute
instead of hard-coding it to a specific value. This means we will only override
the equivalent option for this attribute (for the above example we are
ovverriding the ``help`` option for the ``bc_account`` attribute).

Now when you refresh the form in your browser, you should see the help message
below the "Account" form input field.

.. note::

   Help messages can be written in Markdown_ format, but it is best not to get
   carried away in the size of the help message.

.. _markdown: https://en.wikipedia.org/wiki/Markdown

Change Field Default Value
--------------------------

You are able to modify the default value of a form field for a given attribute,
which should not be confused with hard-coding a value for an attribute.

For example, if you would like the form field "Number of hours" given by
``bc_num_hours`` to be ``8`` hours by default, but still allow the user to
change it then you can make the following edits in your custom YAML
configuration file:

.. code-block:: yaml

   # bc_desktop/local/cluster1.yml
   ---
   title: "Cluster1 Desktop"
   cluster: "cluster1"

   # Add the below option that allows us to modify form attributes
   attributes:
     bc_num_hours:
       value: 8

The key here is that we are defining a hash for the ``bc_num_hours`` attribute
instead of hard-coding it to a number. This means we want to override the
equivalent option for this attribute (for the above example we are ovverriding
the ``value`` option for the ``bc_num_hours`` attribute).

Now when you refresh the desktop form in your browser, you should see a default
value of ``8`` in the "Number of hours" form field.

.. note::

   There is a possibility you may see a number other than ``8`` in the above
   example. That is because the Interactive Apps tool built into the Dashboard
   **remembers** your last succesful app launch for a corresponding app. So
   when you go back to the form page for that given app, it will auto-fill in
   the form with your previous values.
