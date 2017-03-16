.. _files:

Files App
=========

`View on GitHub <https://github.com/OSC/ood-fileexplorer>`__

.. figure:: /images/files-app.png
   :align: center

   Example of the Files App viewing the contents of a directory.

This Open OnDemand application provides a web-based file explorer that allows
the user to remotely interact with the files on the HPC center's local file
system. This application uses Node.js_ as the code base and is based on the
CloudCommander_ file explorer app.

The Files App provides access to create files and folders, view files,
manipulate file locations, upload files, and download files. It also provides
integrated support for launching the Shell App in the currently browsed
directory as well as launching the File Editor App for the currently selected
file.

Usage
-----

This app is deployed on the OnDemand Server under the following path on the
local file system::

  /var/www/ood/apps/sys/files

and can be accessed with the following browser request:

.. http:get:: /pun/sys/files/fs/(path)

   Launches the Files App with a view of the directory for the specified
   ``path``.

   **Example request**:

   .. code-block:: http

      GET /pun/sys/files/fs/home/user/path/to/work HTTP/1.1
      Host: ondemand.hpc.edu

   Launches the Files App with the view of the ``/home/user/path/to/work``
   directory.

How it Works
------------

Requirements needed for the Files App to work on your local HPC network:

- OnDemand Server
- Shared File System

.. figure:: /images/files-diagram.png
   :align: center

   Diagram detailing how the Files App interacts with the HPC infrastructure.

The figure above details how the Files App works on a local HPC system. The
user's PUN running on the OnDemand Server launches the Node.js Files App
through Passenger_ as the user. The Files App then utilizes the `Node.js File
System`_ core library for interacting with the local and shared file systems.

.. warning::

   For File Uploads, NGINX_ will buffer the entire file under the following
   path::

     /var/lib/nginx/tmp/<user>/client_body

   before Passenger_ and subsequently the Files App can gain access to it. The
   space allocated for this location is one of the limiting factors on the size
   of file uploads.

.. _node.js: https://nodejs.org/en/
.. _cloudcommander: http://cloudcmd.io/
.. _passenger: https://www.phusionpassenger.com/
.. _node.js file system: https://nodejs.org/docs/latest-v0.10.x/api/fs.html
.. _nginx: https://nginx.org/en/
