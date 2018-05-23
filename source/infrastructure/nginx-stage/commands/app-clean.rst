.. _nginx-stage-app-clean:

nginx_stage app_clean
=====================

This command will remove any deployed web application NGINX
configuration files for applications that don't exist anymore on the
file system.

.. code-block:: sh

   sudo nginx_stage app_clean [OPTIONS]

.. program:: nginx_stage app_clean

Examples
--------

To clean up all the stale app configs:

.. code-block:: sh

   sudo nginx_stage app_clean

This displays the paths to all the app configs that were deleted.
