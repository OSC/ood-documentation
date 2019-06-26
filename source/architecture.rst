.. _architecture:

Architecture
============

Architecture diagrams below follow the `C4 <https://c4model.com/>`_ model for
software diagrams.

System context
-----------------------

Users use OnDemand to interact with their HPC resources through a web browser.
At the highest level, this is the OnDemand system does.

.. uml:: architecture/system-context.uml


Container context
-----------------------

Only a few Apps are shown here because Apps may or may not exist in any given
installation. What is shown here is typical of an OnDemand installation
with "Interactive Apps" being generic.

.. uml:: architecture/container-context.uml


Request Flow
-----------------------

This is the request flow through the OnDemand system. A user initiates a
request through a browser and this illustrates how that request propogates
through the system to a particular application (including the dashboard).

.. uml:: architecture/request-flow.uml


