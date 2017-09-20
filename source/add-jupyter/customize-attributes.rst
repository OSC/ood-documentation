.. _add-jupyter-customize-attributes:

Customize Attributes
====================

Now we will customize the app to work on a given cluster. Be sure that you walk
through :ref:`add-jupyter-software-requirements` for the given cluster ahead of
time.

Modify Form File
----------------

The main responsibility of the ``form.yml`` file is for defining the attributes
(their values or HTML form elements) used when generating the batch script.

#. We will begin by adding a cluster for the Jupyter app to use. You do this by
   editing the ``form.yml`` in your favorite editor as such:

   .. code-block:: yaml

      # form.yml
      ---

      ...

      cluster: "my_cluster"

      ...

   where we replace ``my_cluster`` with a valid cluster that corresponds to a
   cluster configuration file located under
   :file:`/etc/ood/config/clusters.d/{my_cluster}.yml`.

#. We will also edit the module(s) that is(are) required to be loaded within
   our batch job to get a Jupyter Notebook Server running:

   .. code-block:: yaml

      # form.yml
      ---

      ...

      attributes:

        ...

        modules: "python/3.5"

      ...

   where we replace ``python/3.5`` with a list of required modules for our
   given cluster.

#. **Optional** If we do NOT have the Conda extensions installed for the above
   Python modules then we must disable it:

   .. code-block:: yaml

      # form.yml
      ---

      ...

      attributes:

        ...

        conda_extensions: "0"

      ...

   They are enabled by default in this file.

.. note::

   It is recommended you commit the changes you made to ``form.yml`` to `git`_:

   .. code-block:: sh

      # Stage the modified file and commit your changes
      git commit form.yml -m 'updated form with cluster attributes'

Verify it Works
---------------

You can now test the app again by visiting your local OnDemand server in your
browser:

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/jupyter_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

You should see a web form for the Jupyter app. Fill in the form now and try to
"Launch" a Jupyter batch job.

.. note::

   While you are waiting for the job to start it is **recommended** that you
   click the link under the "Session ID:". This will open the File Explorer in
   the working directory of the currently launched Jupyter batch job.

   Useful debugging files (before job runs):

   - ``user_defined_context.json`` - Attributes submitted by the user in the
     web form.
   - ``job_script_content.sh`` - The batch script content.
   - ``job_script_options.json`` - The job submission parameters (this will be
     used in the next section if you have trouble submitting the job).

   Useful debugging files (after job runs):

   - ``output.log`` - This is the log file of the batch job. This is helpful to
     look at if your batch job dies abruptly due to an invalid ``module`` or
     missing Jupyter libraries.

Continue to the next section to learn about job submission parameters.

.. warning::

   The app will probably display a warning about requiring a cluster. This is
   perfectly fine. Continue on to the next section to learn about customizing
   the app.

.. _git: https://git-scm.com/
