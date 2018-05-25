.. _nginx-stage-nginx-show:

nginx_stage nginx_show
======================

This command will show the relevant details of a running per-user NGINX (PUN)
process for a given user.

.. code-block:: console

   $ sudo nginx_stage nginx_show [OPTIONS]

.. program:: nginx_stage nginx_show

Required Options
----------------

.. option:: -u <user>, --user <user>

   The user of the per-user NGINX process.

Examples
--------

To display the details of Bob's PUN process:

.. code-block:: console

   $ sudo nginx_stage nginx_show --user 'bob'
   User: bob
   Instance: 24214
   Socket: /var/run/nginx/bob/passenger.sock
   Sessions: 1

Where ``Sessions`` is the number of active connections to the given Unix domain
socket file.
