.. _interactive-usage:

Usage
=====

A **production** Interactive App (denoted by ``sys``) is deployed on the
OnDemand Server under the following path on the local file system::

  /var/www/ood/apps/sys/my_app

A personal **sandbox** Interactive App (denoted by ``dev``) that you are
developing is deployed in your home directory under the following path::

  ${HOME}/ondemand/dev/my_app

Interactive Apps are :ref:`dashboard` plugins. They can be directly accessed
through the following URLs:

.. http:get:: /pun/sys/dashboard/batch_connect/(app_type)/(app_name)/session_contexts/new

   this view displays the HTML form for launching the corresponding Interactive
   App session

   **Example request**:

   Display the HTML form for the production ``my_app`` Interactive App

   .. code-block:: http

      GET /pun/sys/dashboard/batch_connect/sys/my_app/session_contexts/new HTTP/1.1
      Host: ondemand.my_center.edu

   :param app_type: Type of Interactive App (``sys`` or ``dev``)
   :param app_name: Directory name of the deployed Interactive App

.. http:get:: /pun/sys/dashboard/batch_connect/sessions

   this view lists **all active** Interactive App sessions and provides an
   interface for the user to connect to or delete a running session
