.. _app-development-interactive-conn-params:

Connection Parameters (connections.yml)
=======================================

The `connections.yml` configuration file facilitates communication between 
the backend server and an app, via the ``before.sh.erb``, ``submit.sh.erb``, 
and ``view.html.erb`` files.

This configuration can be crucial when specific data, such as a ``csrf_token``, 
is required for operations like logging into RStudio.

Configuration
-------------

The files which must be adjusted are::

  my_app/
  ├── submit.html.erb
  ├── templates/
  │   ├── before.sh.erb
  └── view.html.erb

The primary purpose of this configuration is to utilize the ``before.sh.erb`` script 
to generate a piece of data. This data is then passed to the ``submit.sh.erb`` which 
then will hand off to the ``view.html.erb`` for rendering in the interactive apps page.

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

The thing to notice in this example is the ``RSTUDIO_PASSWORD`` had ``export`` used and the other 
variables did not, such as ``port`` or ``password``. 