

Debugging Interactive Apps
==========================

.. contents:: Table of Contents
  :depth: 2
  :local:

Log location
------------

:ref:`Information about interactive app log location. <interactive-app-logs>`


App completes without being able to connect to it.
--------------------------------------------------

If your application goes from ``queued`` to ``starting`` to ``completed`` without
ever allowing you to connect to it, the application failed to start correctly.

First, review the :ref:`output for that session <interactive-app-logs>`. You're likely
to see some errors there.

Empty Variables in ``submit.yml.erb``
-------------------------------------

Previous versions of Open OnDemand threw errors when attempting to use undefined
variables in the ``submit.yml.erb``.  Undefined variables are evaluated as ``nil``.
This being the case, you may be debugging an issue where a particular value that should
be there is missing or zero. Casting a ``nil`` to a string returns an empty string and
casting ``nil`` to an integer returns zero.

For example you may see an error like this if you're trying to use a variable
to supply ``--ntasks-per-node`` to Slurm's ``sbatch`` command.

.. figure:: /images/batch_connect_missing_item_error.png
   :alt: An interactive application's failure stating sbatch: error: Invalid numeric value "" for --ntasks-per-node.

In debugging a situation like this, it may be helpful to raise an error displaying
all the variables that are available.

.. code-block:: erb

  <%# submit.yml.erb %>
  <%-
    # ... ruby code ...

    raise(StandardError, to_h.inspect)
  -%>

It is most likely that the variable in question is in fact missing
or misspelled in either the ``form.yml`` or ``submit.yml`` files.
