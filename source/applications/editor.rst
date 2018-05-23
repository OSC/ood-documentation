.. _editor:

File Editor App
===============

`View on GitHub <https://github.com/OSC/ood-fileeditor>`__

.. figure:: /images/editor-app.png
   :align: center

   Example of the File Editor App viewing the contents of a file.

This Open OnDemand application provides a web-based file editor that allows the
user to remotely edit files on the HPC center's local file system. This
application is built with the `Ruby on Rails`_ web application framework.

The File Editor App uses the `Ace Editor`_ (an embeddable code editor written
in JavaScript) as the client-side editor. This client provides syntax
highlighting, automatic indenting, key bindings, code folding, and many more
features.

Usage
-----

This app is deployed on the OnDemand Server under the following path on the
local file system::

  /var/www/ood/apps/sys/file-editor

and can be accessed with the following browser request:

.. http:get:: /pun/sys/file-editor/edit/(path)

   Launches the File Editor App with the file corresponding to the ``path``
   in the editor.

   **Example request**:

   .. code-block:: http

      GET /pun/sys/file-editor/edit/home/user/my_file HTTP/1.1
      Host: ondemand.hpc.edu

   Launches the File Editor App with the contents of the file
   ``/home/user/my_file`` in the editor.

How it Works
------------

Requirements needed for the File Editor App to work on your local HPC network:

- OnDemand Server
- Shared File System

.. _editor-diagram:
.. figure:: /images/editor-diagram.png
   :align: center

   Diagram detailing how the File Editor App interacts with the HPC
   infrastructure.

:numref:`editor-diagram` details how the File Editor App works on a local HPC
system. The user's PUN running on the OnDemand Server launches the Ruby on
Rails File Editor app through Passenger_ as the user. The File Editor app then
interacts with the local and shared file systems for reading and writing the
file contents.

.. _ruby on rails: http://rubyonrails.org/
.. _ace editor: https://ace.c9.io/
.. _passenger: https://www.phusionpassenger.com/
