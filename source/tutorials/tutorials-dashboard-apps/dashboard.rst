.. _app-development-tutorials-dashboard-apps-dashboard:

Developing the Dashboard App
============================

.. warning::
    You muse have followed :ref:`enabling-development-mode` for any part of this tutorial to work.

Strategy
--------

#. Ensure :ref:`enabling-development-mode` is completed
#. Make a symlink in our ``dev`` space back to the home directory's ``~/ondemand/misc/ondemand/<app>`` 
#. ``git branch`` from that symlinked directory for the app and do your work
#. Create a ``.env.local`` file in the app root to override system ``ENV`` variables
#. Rebuild the app with your changes using the ``bin/setup`` binary
#. Use the Sandbox to launch your app for testing

This will serve for the template in the following work on both the ``dashboard`` app and 
the ``shell`` app.

Create a Dev Dashboard
----------------------
#. pull down ondemand in ``~/ondemand/misc``: ``cd ~/ondemand/misc`` then ``git clone git@github.com:OSC/ondemand.git``
#. ``cd ~/ondemand/dev/``
#. create the symlink for your shell app: ``ln -s ../misc/ondemand/apps/dashboard/dashboard/ dev_dashboard``
#. run ``git checkout -b your_branch`` 
#. now make a branch with your changes and use ``bin/setup`` to rebuild if needed
#. navigate to the Sandbox and launch your ``dev_dashboard`` app

Notice the ``url`` for this app. No longer do you  see ``*/sys/dashboard/dashboard`` but instead ``*/dev/dashboard/dashboard``. 

Add ``.end.local`` File
-----------------------
Now that we have a our dev dashboard running, a good first step is to next ensure it *look different from prod.* This 
will ensure you do not end up in the wrong tab issuing commands.

Use an editor or IDE and do the following:

.. code-block:: sh
    cd ~/ondemand/dev/dashboard
    touch .env.local
    vim .env.local

Now, the idea here is to make sure the dev dashboard *looks* different so we don't have to check that ``url`` in the 
browser to know which dashboard we are in.

So, inside this ``.env.local`` we can add an environment variable to change the color of the dev dashboard like so:

.. code-block:: sh
    OOD_BRAND_BG_COLOR='grey'

Now click the Develop dropdown menu on the upper right corner and click ``Restart Web Server``. After a few moments 
you should now see the dashboard with a grey background in the banner. This will help to distinguish your dev 
environment from the production.

Set Dev Configuration Directory
-------------------------------
Our dev dashboard is still using the same configuration files as the system dashboard, but we can change this.

If we go back into our ``.env.local`` file we can set a new path for the dev dashboard to pick up its *own 
configurations* using the ``OOD_CONFIG_D_DIRECTORY`` environment variable like so: 

.. code-block:: sh
    vim .env.local
    OOD_CONFIG_D_DIRECTORY="~/ondemand/dev/dashboard/config/ondemand.d/"

As usual, we need to restart the PUN when we add or change an environment variable. 

Now, we can begin to set our own configurations in our new ``ondemand.d`` for the dev dashboard and see the changes.

Add Dev Configurations
----------------------
Let's add some configs to our dev dashboard to get an idea what can be done and play with the layout.

We will add ``pinned_apps`` to our dev dashboard to see how this works.

Create a file in the ``~/ondemand/dev/dashboard/config/ondemand.d/`` directory named ``ondemand.yml`` then 
open the file and add the following:

.. code-block:: yaml
    pinned_apps:
      - sys/*           # pin the sys apps

Now restart the PUN. You should be presented with a view of all the system apps in your home screen, pinned.

