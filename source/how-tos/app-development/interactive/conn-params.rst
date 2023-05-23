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


And the ``submit.yml.erb`` will use ``conn_params`` to set the custom variable::

    ---
    batch_connect:
      template: "basic"
      conn_params:
        - custom_variable
    ...

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

Rstudio Example
---------------

Suppose we need some authentication piece in the rendered card in interactive apps to allow 
a user to connect to an Rstudio session with a password.

First, open the ``template/before.sh.erb`` file and add the following::

    password="$PASSWORD"
    host="$HOST_CFG"
    port="$PORT_CFG"
    ...
    # rstudio 1.4+ needs a csrf token
    csrf_token=<%= SecureRandom.uuid %>
    ...
    # Define a password and export it for RStudio authentication
    password="$(create_passwd 16)"
    ...
    export RSTUDIO_PASSWORD="${password}"

Then, in the ``submit.sh.erb``::

    ---
    batch_connect:
      template: "basic"
      conn_params:
        - csrf_token
    ...

And finally to use the variables in the ``view.html.erb`` set::

    <form action="/rnode/<%= host %>/<%= port %>/auth-do-sign-in" method="post" target="_blank">
      <input type="hidden" name="csrf-token" value="<%= csrf_token %>"/>
      <input type="hidden" name="username" value="<%= ENV["USER"] %>">
      <input type="hidden" name="password" value="<%= password %>">
      ...
    </form>
