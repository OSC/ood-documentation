.. _nginx-stage-app-reset:

nginx_stage app_reset
=====================

This command will update all the deployed application NGINX
configuration files using the current template.

.. code-block:: console

   $ sudo nginx_stage app_reset [OPTIONS]

.. program:: nginx_stage app_reset

General Options
---------------

.. option:: -i <sub_uri>, --sub-uri <sub_uri>

   The sub-URI path in the request.

.. note::

   The sub-URI corresponds to any reverse proxy namespace that denotes the
   request should be proxied to the per-user NGINX server (e.g., ``/pun``)

Examples
--------

To update all the deployed app configs using the currently available
template:

.. code-block:: console

   $ sudo nginx_stage app_reset --sub-uri '/pun'

This will return the paths to the newly generated app configs.
