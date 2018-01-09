.. _app-development-tutorials-interactive-apps-add-jupyter-customize-attributes:

Customize Attributes
====================

Now we will customize the app to work on a given cluster. Be sure that you walk
through :ref:`app-development-tutorials-interactive-apps-add-jupyter-software-requirements`
for the given cluster ahead of time.

The main responsibility of the ``form.yml`` file located in the root of the app
is for defining the attributes (their values or HTML form elements) used when
generating the batch script.

#. We will begin by adding a cluster for the Jupyter app to use. You do this by
   editing the ``form.yml`` in your favorite editor as such:

   .. code-block:: yaml
      :emphasize-lines: 3

      # ~/ondemand/dev/jupyter/form.yml
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        conda_extensions: "1"
        extra_jupyter_args: ""
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - bc_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   where we replace ``my_cluster`` with a valid cluster that corresponds to a
   cluster configuration file located under
   :file:`/etc/ood/config/clusters.d/{my_cluster}.yml`.

#. We will also edit the module(s) that is(are) required to be loaded within
   our batch job to get a Jupyter Notebook Server running:

   .. code-block:: yaml
      :emphasize-lines: 5

      # ~/ondemand/dev/jupyter/form.yml
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        conda_extensions: "1"
        extra_jupyter_args: ""
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - bc_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   where we replace ``python`` with a list of required modules for our given
   cluster.

   This will be called within the batch script as:

   .. code-block:: sh

      module load <modules>

#. If you do **NOT** have the Conda extensions installed for the above Python
   modules then we must disable it:

   .. code-block:: yaml
      :emphasize-lines: 6

      # ~/ondemand/dev/jupyter/form.yml
      ---
      cluster: "my_cluster"
      attributes:
        modules: "python"
        conda_extensions: "0"
        extra_jupyter_args: ""
      form:
        - modules
        - conda_extensions
        - extra_jupyter_args
        - bc_account
        - bc_queue
        - bc_num_hours
        - bc_num_slots
        - bc_email_on_started

   They are enabled by default in this file.

#. We test our changes by again clicking the *Launch Jupyter Notebook* button
   back in our details view of our sandbox app.

#. You should see a web form for the Jupyter app. Fill in the form now and try
   to *Launch* a Jupyter batch job.

   .. note::

      While you are waiting for the job to start it is **recommended** that you
      click the link under the "Session ID:". This will open the File Explorer
      in the working directory of the currently launched Jupyter batch job.

      Useful debugging files (before job runs):

      ``user_defined_context.json``
        attributes submitted by the user in the web form
      ``job_script_content.sh``
        the batch script content
      ``job_script_options.json``
        the job submission parameters (this will be used in the next section if
        you have trouble submitting the job)
      ``/var/log/nginx/<user>/error.log``
        the per-user NGINX (PUN) log file (this will contain the command line
        called when submitting the batch job, look for ``execve=...``)

      Useful debugging files (after job runs):

      ``output.log``
        this is the log file of the batch job (useful if batch job runs but
        then dies abruptly)

Continue to the next section to learn about job submission parameters.

.. note::

   It is recommended you commit any changes you made to ``form.yml`` to `git`_:

   .. code-block:: sh

      # Stage the modified file and commit your changes
      git commit form.yml -m 'updated form with cluster attributes'

.. _git: https://git-scm.com/
