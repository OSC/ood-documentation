.. _app-development-tutorials-passenger-apps-science-gateway:

Creating a Science Gateway App
==============================

Overview of App
---------------

We will make a science gateway that displays information retrieved by 
our app, processed, and handed to us rendered in a format of our 
choosing.

The app we will be copying is: https://github.com/OSC/ood-example-science-gateway. Running
this app looks like:

.. figure:: /images/app-sharing-1.png
   :align: center

   What app looks like after cloning and launching.

After this tutorial the resulting app will be:

.. figure:: /images/app-sharing-2.png
   :align: center

   What app looks like after modifying in this tutorial.

This assumes you have followed the directions to :ref:`enabling-development-mode` on the
Dashboard.

#. The app uses the custom branded Bootstrap 5 that Job Composer and Active Jobs apps
   use.
#. The navbar contains a link back to the dashboard.
#. On a request, the app will generate a request, process the result, then hand us back that result to be rendered in some way in our view.
#. It is built using `Python's Flask <https://github.com/pallets/flask>`__ which 
   is similar to the `Sinatra framework <https://github.com/sinatra/sinatra>`__, 
   or `Node.js's Express <https://github.com/expressjs/express>`__ .

Benefits
........

This will provide users with an example of how to build their own 
science gateway in OnDemand and hosted through OnDemand. 

By doing so, we will se that OnDemand provides great flexibility in 
allowing you to work in either ``ruby``, ``node.js``, or 
``python`` which all integrate easily with Passenger.

But *any* language can now be supported as of **Passenger 6**, as long 
as your app:

#. Speaks ``http``.
#. Binds to a ``port``.
#. Runs in the foreground.

The App's Packages and Code
...........................

For any app we develop, the key thing here will be that we can use our *own packages* and code 
to build what we are trying to do.

We will be using ``python`` in this example so combination of ``venv`` and ``pip`` will be used 
to work out of.

This will enable us to login to OnDemand and then work within our development sandbox to use 
code from *our own* python modules. This could just as easily be our own ``gems`` if we used 
``ruby`` or packages if we used ``node``.

This means we will have to do some setup to ensure our app uses our own designated packages and 
not OnDemand's or the system packages. This gives users a great deal of flexibility in how they develop.

Project Structure
.................

The project structure is simply following a common pattern used when developing a passenger app.

This mainly consists of an entrypoint file for passenger, and then various files to be used by our 
webserver to be served or executed by the app:

You can see this explanation and the various forms the names of the files will take in 
the `Passenger project structure documentation <https://www.phusionpassenger.com/docs/tutorials/fundamental_concepts/python/>`__

Create a WSGI file in the app's directory. Passenger expects it be 
called ``passenger_wsgi.py``. The contents depends on the application and the web framework.

Clone and Setup
---------------

Development
-----------

Brand App
---------

Publish App
-----------