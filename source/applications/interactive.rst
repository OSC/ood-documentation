.. _interactive:

Interactive Apps (Plugins)
==========================

.. figure:: /images/interactive-app.png
   :align: center

   An example Interactive App that launches a desktop on the Owens cluster at
   the `Ohio Supercomputer Center`_.

Interactive Apps provide a means for a user to launch and connect to an
interactive batch job running a local web server (called Interactive App
sessions) through the OnDemand portal (e.g., `VNC server`_, `Jupyter Notebook
server`_, `RStudio server`_, `COMSOL server`_). They are considered **Dashboard
App Plugins** and not Passenger_ apps such as the :ref:`dashboard`,
:ref:`shell`, :ref:`files`, and etc.

This means that the Dashboard is responsible for building the Interactive App's
web form, submitting the batch job, and displaying connection information to
the user for a running Interactive App session.

To get started it is **recommended** that an administrator walks through
:ref:`enable-desktops` at least once for your Open OnDemand portal. This will
ensure your Open OnDemand portal is properly configured to host Interactive
Apps.

Usage
-----

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

   **Example**:

   Display the HTML form for the **production** Interactive App in the
   ``my_app`` directory

   .. code-block:: http

      GET /pun/sys/dashboard/batch_connect/sys/my_app/session_contexts/new HTTP/1.1
      Host: ondemand.my_center.edu

   **Example**:

   Display the HTML form for my development **sandbox** Interactive App in the
   ``my_app`` directory

   .. code-block:: http

      GET /pun/sys/dashboard/batch_connect/dev/my_app/session_contexts/new HTTP/1.1
      Host: ondemand.my_center.edu

   :param app_type: Type of Interactive App (``sys`` or ``dev``)
   :param app_name: Directory name of the deployed Interactive App

.. http:get:: /pun/sys/dashboard/batch_connect/sessions

   this view lists **all active** Interactive App sessions and provides an
   interface for the user to connect to or delete a running session

.. _ohio supercomputer center: https://www.osc.edu/
.. _vnc server: https://en.wikipedia.org/wiki/Virtual_Network_Computing
.. _jupyter notebook server: http://jupyter.org/
.. _rstudio server: https://www.rstudio.com/
.. _comsol server: https://www.comsol.com/comsol-server/
.. _passenger: https://www.phusionpassenger.com/
