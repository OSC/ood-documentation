.. _app-development-interactive-view:

Connection View
===============

The HTML template file ``view.html.erb`` is responsible for providing the user
with a small web interface that makes connecting to the backend web server
running on the compute node for a given interactive session as simple as
possible. It is located in the root of the application directory.

Assuming we already have a sandbox Interactive App deployed under::

  ${HOME}/ondemand/dev/my_app

The ``view.html.erb`` configuration file can be found at::

  ${HOME}/ondemand/dev/my_app/view.html.erb

The ``.erb`` file extension will cause the HTML file to be processed using the
`eRuby (Embedded Ruby)`_ templating system. This allows you to embed Ruby code
into the HTML file for flow control, variable substitution, and more.

.. danger::

   If developing a VNC Interactive App, **DO NOT** include the
   ``view.html.erb`` file. The Dashboard has internal logic in place for
   displaying connection information of VNC sessions to the user.

Session Information
-------------------

A **running** interactive session will generate a connection information file
in the working directory of the corresponding batch job. This information is
then made available to the HTML template ``view.html.erb`` when it is rendered.
The possible connection information attributes are:

host
  the hostname of the compute node that the interactive session is running on
port
  the port number that the running web server is listening on
password
  the password that the web server expects when authenticating the user

Typically these attributes are used to construct links or forms within the
``view.html.erb`` file. See the various
:ref:`app-development-interactive-view-examples` below.

Reverse Proxy
-------------

A detailed introduction to the reverse proxy can be found in
:ref:`ood-portal-generator-configuration-configure-reverse-proxy`. Under a
default installation the following URL paths will be enabled:

.. http:get:: /node/(host)/(port)(path)

   reverse proxies the request to the given ``host`` and ``port`` using the
   **full and untouched** URL request path

   Example
     By visiting the hypothetical link below::

       https://ondemand.my_center.edu/node/node01.my_center.edu/8080/index.html

     the following URL request::

       /node/node01.my_center.edu/8080/index.html

     is sent to the web server running on host ``node01.my_center.edu`` and
     port ``8080``.

.. http:get:: /rnode/(host)/(port)(path)

   reverse proxies the request to the given ``host`` and ``port`` using
   **ONLY** the ``path`` portion of the URL request path

   Example
     By visiting the hypothetical link below::

       https://ondemand.my_center.edu/rnode/node02.my_center.edu/5000/index.html

     the following URL request::

       /index.html

     is sent to the web server running on host ``node02.my_center.edu`` and
     port ``5000``.

.. note::

   In order to leverage the reverse proxy that comes with Open OnDemand the
   system administrator must have it enabled as outlined under
   :ref:`app-development-interactive-setup-enable-reverse-proxy`. It only needs
   to be enabled once and then all developers can take advantage of it within
   their applications.

Typically generating links with ``/node`` is preferred if the web server can be
configured with a sub-URI. For instance, the `Jupyter Notebook server`_ can be
`configured`_ with a sub-URI using the ``NotebookApp.base_url`` option:

.. code-block:: python

   c.NotebookApp.base_url = '/node/node01.my_center.edu/8080/'

Some web servers that are known to work with ``/node``:

- `Jupyter Notebook server`_

Links can be generated with ``/rnode`` if the web server relies **ONLY** on
relative links and does not use any absolute links. Some web servers that are
known to work with ``/rnode`` are:

- `COMSOL Server`_
- `RStudio Server`_

Stylizing
---------

The ``view.html.erb`` HTML template has access to `Bootstrap 3`_ and `Font
Awesome`_ allowing any stylistic pizzazz to be added to it.

For example, to make a link that appears as a button with an icon in it, you
can do:

.. code-block:: html

   <a href="#" class="btn btn-primary">
     <i class="fa fa-eye"></i> Connect to My App
   </a>

All stylization is handled through the HTML `class global attribute`_ using
predefined Bootstrap and Font Awesome classes.

.. _app-development-interactive-view-examples:

Examples
--------

The simplest example of a ``view.html.erb`` consists of just a plain link to
the backend running web server using the Open OnDemand reverse proxy:

.. code-block:: html+erb

   <a href="/node/<%= host %>/<%= port %>/">Click me!</a>

where ``host`` and ``port`` are rendered using the interactive session's
connection information.

.. danger::

   It is not safe to submit ``password`` in a ``GET`` request as this can
   appear in logs. It is recommended to use a ``POST`` request if available,
   see below.

POST Password
`````````````

For some Interactive Apps you may want a single click solution that not only
connects the user to the backend web server but also logs them in with the
generated session password. This may be possible depending on the web server
you use.

For the case of a `Jupyter Notebook server`_ we can create a button that
submits a form with the ``password`` included in it to the Jupyter server's
login page.

.. code-block:: html+erb

   <form action="/node/<%= host %>/<%= port %>/login" method="post">
     <input type="hidden" name="password" value="<%= password %>">
     <button class="btn btn-primary" type="submit">
       <i class="fa fa-eye"></i> Connect to Jupyter
     </button>
   </form>

In this example, the password is stored in a hidden input field that the user
doesn't see and it gets communicated to the Jupyter server in the ``POST``
request.

.. _bc_info_html_md_erb:

Adding Additional Information to the panel
------------------------------------------

It's possible for you to add additional information to this connection view.

You can do so by creating a Markdown file ``info.md.erb`` or an html file
``info.html.erb`` in the applications folder.  Markdown files get generated
into html with # turning into a h1 and ## turning into an h2 and so on.

Again, they're `eRuby (Embedded Ruby)`_ files so you can add some dynamic behavior
to them. Along with any library you may choose to use you can also access these
variables directly.

id
  The UUID of the job
cluster_id
  The cluster the job was submitted to
job_id
  The job id from the scheduler
created_at
  The time the session was created

.. _bc_native_vnc_view:

Adding Native VNC instructions to the panel
-------------------------------------------

Your site may wish to provide users with instructions on how to connect to
interactive jobs with native VNC tools instead of connecting through the browser.
To enable this feature configure the dashboard with ``ENABLE_NATIVE_VNC=true`` in
the dashboard's environment file ``/etc/ood/config/apps/dashboard/env``.

Enabling this will provide generic instructions for the user to create an ssh tunnel
*a host*. If you wish to specify the host users should tunnel to (a well known login
host for example) use the ``OOD_NATIVE_VNC_LOGIN_HOST`` configuration in the same
environment file.

You can also create your own instructions for major OS platforms. You can create
``_native_vnc_{windows,mac,linux}.html.erb`` files and place them in
``/etc/ood/config/apps/dashboard/views/batch_connect/sessions/connections/``
directory to override the default instructions for a given platform.

These file are `eRuby (Embedded Ruby)`_ extensions and so here are some useful
variables and objects you may need to create helpful instructions. You can also
`refer to the original files for help in creating new panels
<https://github.com/OSC/ondemand/tree/master/apps/dashboard/app/views/batch_connect/sessions/connections>`_.

Configuration.native_vnc_login_host
  The OOD_NATIVE_VNC_LOGIN_HOST configuration if given.
connect.host
  The compute node host the interactive job is on
connect.port
  The compute node port the interactive job has opened
connect.password
  The VNC password for the interactive job
ENV["USER"]
  The USER environment variable

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
.. _jupyter notebook server: http://jupyter.readthedocs.io/en/latest/
.. _configured: http://jupyter-notebook.readthedocs.io/en/stable/config.html
.. _comsol server: https://www.comsol.com/comsol-server
.. _rstudio server: https://www.rstudio.com/products/rstudio-server/
.. _bootstrap 3: https://getbootstrap.com/docs/3.3/
.. _font awesome: https://fontawesome.com/
.. _class global attribute: https://developer.mozilla.org/en-US/docs/Web/HTML/Global_attributes/class
