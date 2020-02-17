.. _shell:

Shell App
=========

`View on Github <https://github.com/OSC/ondemand/tree/master/apps/shell>`__

.. figure:: /images/shell-app.png
   :align: center

   Example of the Shell App connected to a compute node with ``htop`` running.

This Open OnDemand application provides a web-based terminal that connects the
user through an SSH session to either the local machine or any other machine
allowed within the internal network. Typically this will connect the user to a
login node. This application uses Node.js_ for its exceptional support of
websockets providing a responsive user-experience as well as its event-driven
framework allowing for multiple sessions simultaneously.

The terminal client is an xterm-compatible terminal emulator written entirely
in JavaScript. The Shell App uses the Google client hterm_ for this. It
performs reasonably well across most modern browsers on various operating
systems. It is currently used by the developers of Open OnDemand quite a bit.

Usage
-----

This app is deployed on the OnDemand Server under the following path on the
local file system::

  /var/www/ood/apps/sys/shell

and can be accessed with the following browser request:

.. http:get:: /pun/sys/shell/ssh/(host)/(path)

   Starts SSH session on ``host`` machine with current working directory
   ``path``.

   **Example request**:

   .. code-block:: http

      GET /pun/sys/shell/ssh/default HTTP/1.1
      Host: ondemand.hpc.edu

   Starts SSH session on the default host (specified by system administrator
   when app was first installed) in the user's home directory.

   **Example request**:

   .. code-block:: http

      GET /pun/sys/shell/ssh/node01.hpc.edu/home/user/path/to/work HTTP/1.1
      Host: ondemand.hpc.edu

   Starts SSH session on host ``node01.hpc.edu`` and changes working directory
   to ``/home/user/path/to/work``.

How it Works
------------

Requirements needed for the Shell App to work on your local HPC network:

- OnDemand Server
- An SSH Server running on the host machine that the Shell App connects to

.. _shell-diagram:
.. figure:: /images/shell-diagram.png
   :align: center

   Diagram detailing how the Shell App interacts with HPC infrastructure.

:numref:`shell-diagram` details how the Shell App works on a local HPC system.
The user's PUN running on the OnDemand Server launches the Node.js Shell App
through Passenger_ as the user. The Shell App then forks off an ``ssh`` process
that then connects to a server specified by the administrator (typically a
login node). The ``stdin``, ``stdout``, and ``stderr`` streams are all piped
through the websocket connection. When the user drops the websocket connection
(e.g., leaves the page, refreshes browser, drops connection) the ``ssh``
process is terminated.

.. _node.js: https://nodejs.org/en/
.. _hterm: https://chromium.googlesource.com/apps/libapps/+/master/hterm
.. _passenger: https://www.phusionpassenger.com/
