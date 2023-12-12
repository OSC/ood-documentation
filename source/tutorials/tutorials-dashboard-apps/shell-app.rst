.. _app-development-tutorials-dashboard-apps-shell-app:

Developing the Shell App
========================

The ``shell`` app is different from the other OOD apps. For starters, it is purely a ``node.js`` app. This means that 
we only need to use ``npm`` to build and work with this app.

Building You Own Shell
......................

#. pull down ondemand in ``cd ~/ondemand/misc`` then ``git clone git@github.com:OSC/ondemand.git``
#. ``cd ~/ondemand/dev/``
#. create the symlink for your shell app: ``ln -s ../misc/ondemand/apps/dashboard/shell/ dev_shell``
#. run ``git checkout -b your_branch`` 
#. now make a branch with your changes and use ``bin/setup`` to rebuild if needed
#. navigate to the Sandbox and launch your ``dev_shell`` app

Notice the ``url`` for this app. No longer do you  see ``*/sys/dashboard/shell`` but instead ``*/dev/dashboard/shell``. 

Build Old Version of Shell
..........................

#. pull down ondemand in ``~/ondemand/misc``
#. then list versions with ``git tags``
#. run ``git checkout <version>`` 
#. now make a branch with your changes and use ``bin/setup`` to rebuild if needed

Then for the **shell app** from a login terminal run:

#. ``cd dev``
#. ``ln -s ../misc/ondemand/apps/dashboard/shell/ shell-18``

And then step into that symlinked directory and run:
#. ``bin/setup`` 

If you go start this app from sandbox you'll notice a different url than before, showing you are in a dev shell: ``pun/dev/shell-1.8``

Issues and Errors
.................
**If above fails** try to purge the modules with ``module purge`` on the login node first, 
then ensure the *correct ruby version* with ``module load ruby/3.0.2`` then rebuild with ``bin/setup`` as above.

