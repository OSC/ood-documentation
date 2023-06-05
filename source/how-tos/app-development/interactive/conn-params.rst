.. _app-development-interactive-conn-params:

Connection Parameters ``conn_params``
=====================================

App developers can use ``conn_params`` in the ``submit.yml.erb`` to pass runtime data generated
in the ``before.sh.erb`` back to the ``view.html.erb``. 

This is helpful for:

* Data that is only known **after** the job submits and starts running.
* Data that needs to be used to connect to the application.

This technique will generate a file in the app's root called ``connection.yml`` when the app launches 
which will contain the defined variables and their associated values.

Configuration
-------------

The files which must be adjusted are::

  my_app/
  ├── submit.html.erb
  ├── templates/
  │   ├── before.sh.erb
  └── view.html.erb

The files which can be adjusted to::

  my_app/
  ├── submit.html.erb
  ├── templates/
  │   ├── before.sh.erb
  │   └── dir
  │       └── another_script.sh.erb
  └── view.html.erb

And the ``submit.yml.erb`` will use ``conn_params`` to set the custom variables to pass back to the ``view`` to 
be rendered, but also it seems that is not true, Rstudio does not do so for ``port`` or ``host``. ....hmmmm::

    ---
    batch_connect:
      template: "basic"
      conn_params:
        - custom_variable_one
        - custom_variable_two
        ...
    ...

.. warning::

  The variables in ``before.sh.erb`` *must* be made available to the environment 
  by using ``export``. 

Jupyter Notebook Example
------------------------

Here's an example using the ``bc_osc_jupypter`` app which needs 
information from the server to then pass on to the submission before it renders 
in the browser for the app's launch card.

Within the ``template/before.sh.erb``, observe the following lines::

    JUPYTER_API="<%= context.jupyterlab_switch == "1" ? "lab" : "tree" %>"
    ...
    export jupyter_api="$JUPYTER_API"

Now take this exported variable and include it in the ``submit.html.erb``. 
Ensure that the syntax aligns with the following::

    ---
    batch_connect:
      template: "basic"
      conn_params:
        - jupyter_api
    ...

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
