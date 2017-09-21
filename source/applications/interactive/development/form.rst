.. _interactive-development-form:

User Form
=========

Assuming we already have a sandbox Interactive App deployed under::

  ${HOME}/ondemand/dev/my_app

The following HTTP request

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/my_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

displays the HTML form used to gather the user-defined attributes for building
and launching the ``my_app`` Interactive App session.

This HTML form is constructed from the ``form.yml`` file located in the root of
the respective sandbox Interactive App directory. For our example::

   ${HOME}/ondemand/dev/my_app/form.yml

.. tip::

   You can include dynamically generated content in the form by renaming the
   form file to ``form.yml.erb`` and incorporating ERB syntax.

Configuration
-------------

.. describe:: cluster (String)

     the cluster id that the Interative App session is submitted to

     .. warning::

        The cluster id must correspond to a cluster configuration file located
        under::

          /etc/ood/config/clusters.d

.. describe:: attributes (Hash)

     the object defining the hard-coded value or HTML form element used for the
     various custom attributes

.. describe:: form (Array<String>)

     a list of **all** the attributes that will be used as the context for
     describing an Interactive App session

     .. note::

        The attributes that appear as HTML form elements will appear to the
        user in the order they are listed in this configuration option.

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

After modifying the ``form.yml`` you can navigate in your browser to the
following URL

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/my_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

and be presented with **ONLY** a Launch button, since we didn't define
``form:`` or ``attributes:``.

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

After modifying the ``form.yml`` you can navigate your browser to the following
URL

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/my_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

and you will see an empty text box with the label "My Module Version". The user
can input any value here and launch the Interactive App session. This value
will be made available to the batch job script and submission parameters that
are discussed in a later section.

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
     my_module_version: TODO
