.. _app-development-tutorials-python:

Starter Python Application
==========================


This document describes how to start a Passenger application
in `Python`_ language.

Basic application
-----------------

``passenger_wsgi.py`` is the entrypoint for any python application.

.. code:: shell

  cd ~/ondemand/dev
  mkdir python-hello-world
  cd python-hello-world
  touch passenger_wsgi.py

Now with the ``passenger_wsgi.py`` file created, we can add this content to
serve a response to a request.

.. code:: python

  # passenger_wsgi.py 
  import sys

  def application(environ, start_response):
      start_response('200 OK', [('Content-type', 'text/plain')])
      return ["Hello World from Open OnDemand (Python WSGI)!\n\n" + sys.version]

Boot the application
--------------------

Now that the app's all setup and implemented, you should be able to
boot it up.  To do so, simply navigate to ``My Sandbox Apps (Development)``
in the ``Develop`` menu of your OnDemand installation.

There you should see this application at the top of the list.  Clicking
``Launch Python Hello World`` will launch this application in a new tab.

When the new tab opens you should see a mostly blank page with the something
like the following:

.. code:: shell

  Hello World from Open OnDemand (Python WSGI)!

  3.9.21 (main, Dec  5 2024, 00:00:00) 
  [GCC 11.5.0 20240719 (Red Hat 11.5.0-2)]

This is your new `Python`_ application!


Application using Flask and a virtual environment
-------------------------------------------------

The basic application above is fine, but you'll likely need to add
more dependencies and load those dependencies at runtime.

So this section goes over adding the `Flask`_ web framework and having
the application load the virtual environment that has your dependencies in
it.

Create the virtual environment
``````````````````````````````

First, we need to create the virtual environment. Issue this command below
to create one. This will create a subdirectory ``python-hello-world`` with a
``bin/activate`` file you can use to activate the environment.

.. code:: shell

  python3 -m venv python-hello-world

You can also use other Python virtual environment managers such as ``uv``. If you
have ``uv`` installed, the following command will create a virtual environment 
subdirectory ``.venv``.

.. code:: shell

  uv venv

Install required packages
``````````````````````````````

Now, let's create the ``requriements.txt`` file where we'll add the application's
required libraries. Here, we're only adding ``flask`` of any version.

.. code:: text

  # requirements.txt
  flask

Activate and install requirements.txt

.. code:: shell

  source python-hello-world/bin/activate
  python3 -m pip install -r requirements.txt

Create application files
```````````````````````

In the basic example above, the entire implementation is held within a ``passenger_wsgi.py``.
This project is more advanced, so it will include three files. ``passenger_wsgi.py``,
``app.py``, and ``bin/python``.  ``app.py`` will hold the logic for the application.

``passenger_wsgi.py`` simply imports the app from the ``app.py`` file. 

.. code:: python

  # passenger_wsgi.py
  from app import MyApp as application

``app.py`` on the other hand, has logic associated with the web application in it.
It imports the `Flask`_ libraries, configures the routes and starts the flask server.

.. code:: python

  # app.py
  from flask import Flask
  import sys

  MyApp = Flask('python_hello_world')

  @MyApp.route("/")
  def index():
    return 'Hello World!<br>' + sys.version

  if __name__ == "__main__":
    MyApp.run()

``bin/python`` is a wrapper file to load the appropriate virtual environment.

.. code:: shell

  #!/usr/bin/env bash

  SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
  source $SCRIPT_DIR/../python-hello-world/bin/activate

  exec /bin/env python3 "$@"

.. warning::
  Ensure that this ``bin/python`` file has executable permissions on it.
  Issue the command ``chmod +x bin/python`` to give it executable permissions.

.. warning::
  The command in``bin/python`` will need to be updated if you gave your python environment 
  a different name than the example.

Now, with the python wrapper script to load the environment for your application,
it should boot up correctly and you should see something similar to the following:

.. code:: shell

  Hello World!
  3.13.0 (main, Oct 8 2024, 01:04:00) [Clang 18.1.8 ]

.. include:: deploy-to-production.inc

.. _Python: https://www.python.org/
.. _Flask: https://flask.palletsprojects.com/en/3.0.x/
