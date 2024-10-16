.. _app-development-interactive-conn-params:

Connection Parameters ``conn_params``
=====================================

App developers can use ``conn_params`` in the ``submit.yml.erb`` to pass runtime data generated
in the ``before.sh.erb`` back to the ``view.html.erb``. 

This is helpful for:

* Data that is only known **after** the job submits and starts running.
* Data that needs to be used to connect to the application.

This technique will generate a file in the jobs working directory called ``connection.yml``
when the app launches which will contain the defined variables and their associated values.


Jupyter Notebook Example
------------------------

Here's an example using a Jupyter application which needs
needs to know the exact API to connect to. We can either connect to
JuypterLab at ``/lab`` or Juypter Notebook at ``/tree``, but this
information is not known until the job has been submitted.

So once the job is submitted, we need to export the ``jupyter_api``
environment variable that can then be written to ``connection.yml``
which OnDemand will consume and use in the ``view.html.erb``.

.. warning::

  The environment variables in ``before.sh.erb`` *must* be lowercase and
  exported through the *export* function.

.. code:: shell
  
  # within template/before.sh.erb

  JUPYTER_API="<%= context.jupyterlab_switch == "1" ? "lab" : "tree" %>"
    
  export jupyter_api="$JUPYTER_API"


Now with that variable exported, you need to add it to ``conn_params`` in
``submit.html.erb`` to ensure that OnDemand makes use of it.

.. code::yaml

  batch_connect:
    template: "basic"
    conn_params:
      - jupyter_api

In the ``view.html.erb``, which renders after the submission in the interactive apps page, 
you can access the value of this variable with::

    <%-
      ...
      next_url  = "#{base_url}/#{jupyter_api}"

      full_url="#{login_url}?next=#{CGI.escape(next_url)}"
      ...
    %>

    ...

    <form id="<%= form_id %>" action="<%= full_url %>" method="post" target="_blank" onsubmit="changeTarget()" >

This configuration uses the value from ``jupyter_api`` to populate 
the ``action`` attribute in the rendered page in the interactive sessions.
