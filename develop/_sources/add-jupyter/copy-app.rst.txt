.. _add-jupyter-copy-app:

Copy Jupyter App
================

We will begin by copying a pre-built Jupyter app to hit the ground running.

Steps to Copy
-------------

#. We do all of our app development in our Open OnDemand sandbox directory:

   .. code-block:: sh

      # Create the sandbox directory if it doesn't already exist
      mkdir -p ~/ondemand/dev

      # Change our working directory
      cd ~/ondemand/dev

#. Download our example Jupyter app using `git`_:

   .. code-block:: sh

      git clone https://github.com/OSC/bc_example_jupyter.git jupyter_app

#. Change our working directory:

   .. code-block:: sh

      cd jupyter_app

#. Wipe the previous `git`_ history so we have a fresh app:

   .. code-block:: sh

      rm -fr .git

.. note::

   It is recommended you version your new app using `git`_.

   .. code-block:: sh

      # Create a local repository
      git init

      # Stage all the files under app
      git add --all

      # Make your first commit
      git commit -m 'my first commit'

Verify it Works
---------------

You can now test that this app is *functional* by visiting your local OnDemand
server in your browser:

.. code-block:: http

   GET /pun/sys/dashboard/batch_connect/dev/jupyter_app/session_contexts/new HTTP/1.1
   Host: ondemand.my_center.edu

Notice that we have ``dev/jupyter_app`` in the above URL. This tells the
Dashboard app (which is responsible for launching these Batch Connect plugins)
to search for the app in a directory called ``jupyter_app`` in your OnDemand
sandbox directory.

.. warning::

   The app will probably display a warning about requiring a cluster. This is
   perfectly fine. Continue on to the next section to learn about customizing
   the app.

.. _git: https://git-scm.com/
