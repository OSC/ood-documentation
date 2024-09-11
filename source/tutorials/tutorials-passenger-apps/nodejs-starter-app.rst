.. _app-development-tutorials-node-js:

Starter NodeJS Application
==========================

This document describes how to start a Passenger application
in `NodeJs`_ language.


Initialize the application
--------------------------

In this example we're going to initialize an application called ``nodejs-hello-world``.
You may want to rename this directory to something more appropriate.

.. code:: shell

  cd ~/ondemand/dev
  mkdir nodejs-hello-world
  cd nodejs-hello-world
  npm init

.. warning::
  ``npm init`` will initialize the ``main`` script as ``index.js``.  For OnDemand to recognzie
  this application, the ``main`` attribute in ``package.json`` should be ``app.js`` not
  ``index.js``.

Add Web Framework
-----------------

First we need to add `Express`_ web framework.  Like all web frameworks, this
library will route requests to the appropriate pages.

Issue these commands to add and install the package.

.. code:: shell

  npm add express
  npm install

.. tip::

  While this example uses `Express`_, you can choose any `NodeJs`_ web framework
  available.

Add and edit app.js
-------------------

Now we need the ``app.js`` file that's the entrypoint for this application.
After creating this file, we've provided this starter content for you add
to the file.

This ``app.js`` imports the `Express`_ framework and sets up the ``router``
to route requests to the functions that can serve that request. This starter
file only has one route to the root url ``/`` and returns a simple ``Hello World``
string.

.. code:: javascript

  // app.js

  const express = require('express');
  const app = express();
  const port = 3000;

  // have to use a Router to mount the `PASSENGER_BASE_URI`
  // base uri that's /pun/dev/appname or /pun/sys/appname depending
  // on the environment.
  const router = express.Router();
  app.use(process.env.PASSENGER_BASE_URI || '/', router);

  router.get('/', (req, res) => {
    res.send('Hello World!');
  })

  app.listen(port, () => {
    console.log(`Example app listening on port ${port}`);
  })


Boot the application
--------------------


Now that the app's all setup and implemented, you should be able to
boot it up.  To do so, simply navigate to ``My Sandbox Apps (Development)``
in the ``Develop`` menu of your OnDemand installation.

There you should see this application at the top of the list.  Clicking
``Launch Nodejs Hello World`` will launch this application in a new tab.

When the new tab opens you should see a blank page with the text ``Hello World``.
This is your new `NodeJs`_ application!

.. _NodeJs: https://nodejs.org/en
.. _Express: https://expressjs.com/
