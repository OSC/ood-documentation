.. _architecture:

Architecture
============

Architecture diagrams below follow the `C4 <https://c4model.com/>`_ model for
software diagrams.

System context
-----------------------

Users use OnDemand to interact with their HPC resources through a web browser.
At the highest level, this is the OnDemand system does.  Ondemand is the
system that enables that interaction.


.. figure:: /architecture/ood_system_view.png

All the gray components are specific to a given site and outside the OnDemand
system.

Container context
-----------------------

In the C4 nomenclature, 'containers' are one level below the system. This is
to be confused with the `OCI containers <https://www.opencontainers.org/>`_ or
Docker containers or similar.

It's important to note in this diagram that the frontend proxy is the only
component that is shared for all clients. The system will create Per User
Nginxs (referred to as PUNs throughout the documentation). So what's diagrammed
here in the outer light blue box is replicated for every client accessing the
system.

.. figure:: /architecture/ood_container_view.png

Everything contained in the dotted line is a part of the On Demand system.
Everything outside of it in gray is site specific components.

Request Flow
-----------------------

This is the request flow through the OnDemand system. A user initiates a
request through a browser and this illustrates how that request propogates
through the system to a particular application (including the dashboard).

.. uml:: architecture/request-flow.uml


