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
:ref:`install-desktops` at least once for your Open OnDemand portal. This will
ensure your Open OnDemand portal is properly configured to host Interactive
Apps.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   interactive/usage
   interactive/development

.. _ohio supercomputer center: https://www.osc.edu/
.. _vnc server: https://en.wikipedia.org/wiki/Virtual_Network_Computing
.. _jupyter notebook server: http://jupyter.org/
.. _rstudio server: https://www.rstudio.com/
.. _comsol server: https://www.comsol.com/comsol-server/
.. _passenger: https://www.phusionpassenger.com/
