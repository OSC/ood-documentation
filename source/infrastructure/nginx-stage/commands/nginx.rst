.. _nginx-stage-nginx:

NGINX
=====

This command will start an NGINX process as the user as well as
control this process.

.. code-block:: sh

   sudo nginx_stage nginx [OPTIONS]

.. program:: nginx_stage nginx

Required Options
----------------

.. option:: -u <user>, --user <user>

   The user of the per-user NGINX process.

General Options
---------------

.. option:: -s <signal>, --signal <signal>

   Send the given signal to the per-user NGINX process.

.. option:: -N, --skip-nginx

   Skip the execution of the per-user NGINX process.

.. note::

   Under a default installation, the possible signals are
   ``stop/quit/reopen/reload``.

.. note::

   If no signal is specified, then it will attempt to start the user's per-user
   NGINX process.

Examples
--------

To stop Bob's NGINX process:

.. code-block:: sh

   sudo nginx_stage nginx --user 'bob' --signal 'stop'

This sends a ``stop`` signal to Bob's per-user NGINX process.

If you run :option:`nginx_stage nginx --skip-nginx`, it will
**only** display the system command that would have been called.
