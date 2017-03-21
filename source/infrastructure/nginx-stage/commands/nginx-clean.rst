NGINX_CLEAN
===========

This command will kill all per-user NGINX (PUN) processes that do not have
active connections.

.. code-block:: sh

   sudo nginx_stage nginx_clean [OPTIONS]

.. program:: nginx_stage nginx_clean

General Options
---------------

.. option:: -f, --force

   Force clean **all** of the per-user NGINX processes including ones with
   active connections.

.. option:: -N, --skip-nginx

   Skip the execution of the per-user NGINX process.

Examples
--------

To kill all PUN processes with no active connections:

.. code-block:: sh

   sudo nginx_stage nginx_clean

This also displays the users who had their PUN processes killed.

To kill **all** PUN processes irrespective of the number of active connections:

.. code-block:: sh

   sudo nginx_stage nginx_clean --force

To **only** display the users with PUN processes that have no active
connections:

.. code-block:: sh

   sudo nginx_stage nginx_clean --skip-nginx

This will not kill the PUN processes.
