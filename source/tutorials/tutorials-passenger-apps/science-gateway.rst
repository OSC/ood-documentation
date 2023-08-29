.. _app-development-tutorials-passenger-apps-science-gateway:

Creating a Science Gateway App
==============================

Overview of App
---------------

We will make a science gateway that displays information retrieved, 
processed, and rendered in the browser using phusion passenger and 
the python programming language.

The app we will be copying is: https://github.com/OSC/ood-example-science-gateway. Running
this app at the start you should only see:

.. figure:: /images/passenger-python-flask-app.png
   :align: center

   Initial state of app after launch.

And by the end of this tutorial the app will look like the following:

.. figure:: /images/app-sharing-2.png
   :align: center

   Final state of app after tutorial.

This **assumes** you have followed the directions to :ref:`enabling-development-mode` in the
Dashboard.

Our app will use and have the following:

#. Bootstrap 5 for nice views.
#. The navbar in the app will contain a link back to the ood dashboard.
#. The app will make requests for us which are then processed and returned for our view.
#. It is built using `Python's Flask <https://github.com/pallets/flask>`__ which 
   is similar to the `Sinatra framework <https://github.com/sinatra/sinatra>`__, 
   or `Node.js's Express <https://github.com/expressjs/express>`__ .

Benefits
........

This will provide users with an example of how to build their own 
science gateway in OnDemand and hosted through OnDemand. 

By doing so, we will se that OnDemand provides great flexibility in 
allowing you to work in either ``ruby``, ``node.js``, or 
``python`` which all integrate easily with Passenger Phusion.

But *any* language can now be supported as of **Passenger Phusion 6**, as long 
as your app:

#. Speaks ``http``.
#. Binds to a ``port``.
#. Runs in the foreground.
#. **And The language of your choice and its build tools are available on your system.**

The App's Packages and Code
...........................

For any app we develop, the key thing here will be that we can use our *own packages* and code 
to build what we are trying to do, **assuming your cluster has the language and tooling in place.**

We will be using ``python3`` in this example with a combination of ``venv`` and ``pip`` to build our project.

This will enable us to login to OnDemand and then work within our development sandbox to use 
code from *our own* python modules. This could just as easily be our own ``gems`` if we used 
``ruby`` or packages if we used ``node``.

This means we will have to do some setup to ensure our app uses our own designated packages and 
not OnDemand's or the system packages. This gives users a great deal of flexibility in how they develop.

Phusion Passenger Project Structure
...................................

The project structure is simply following a common pattern used when developing a phusion passenger app.

This mainly consists of an entrypoint file for passenger phusion, and then various files to be used by our 
webserver to be served or executed by the app.

You can see this explanation and the various forms of the files and their names in 
the `Passenger project structure documentation <https://www.phusionpassenger.com/docs/tutorials/fundamental_concepts/python/>`__

Files and Their Purpose
.......................

.. list-table:: Initial Skeleton Files
   :header-rows: 1

   * - File
     - Description
   * - ``passenger_wsgi.py``
     - Entry point of the Phusion Passenger app which expects the file to be named ``passenger_wsgi.py``. The contents and file name will depend on the application and the web framework used.
   * - ``app.rb``
     - Flask app config and routes.
   * - ``templates/index.html``
     - the main section of the html page template using ``render_template()`` commands from ``app.py``.
       which auto-escapes output of ERB tags by default (for security)
   * - ``teamplates/layout.html``
     - the rendered HTML from ``views/index.html`` is inserted into this layout,
       where css and javascript files are included.
   * - ``tmp/always_restart.txt``
     - A Phusion Passenger convention to restart our server each request to see our code changes. The file should be empty.

Build From Scratch
..................

#. ``cd`` into you dev directory, which should have already been setup as per prereqs above.
#. ``mkdir science_gateway_app`` and ``cd`` into it.
#. Initialize our environment with ``python3 -m venv .venv``.
#. ``touch passenger_wsgi.py``. Thise creates a WSGI file in the app's root directory. 
#. ``touch app.py``
#. ``mkdir -p tmp/always_restart.txt``. No content needed as this is a passenger convention to reload our changes each request.
#. ``mkdir -p templates/index.html``

Build From GitHub
-----------------
There are going to be 2 branches for this repo. The ``completed`` branch has all the code we are going to write and the 
completed app.

The ``master`` branch is what will have the initial project skeleton files we need to begin in order to follow the steps below.

Development
-----------

Brand App
---------

Publish App
-----------