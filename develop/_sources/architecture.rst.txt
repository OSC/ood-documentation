.. _architecture:

Architecture
============

Below are some diagrams of OnDemand's architecture:

#. Overview is a high level visual generated from Powerpoint.
#. System context and Container context diagrams below follow the `C4 <https://c4model.com/>`_.
   model for software diagrams, are more technically detailed and are built using draw.io
#. Request flow diagram is a sequence diagram built using plantuml.

Overview
--------


.. figure:: /architecture/ood_overview.png

#. Apache is the server front end, running as the Apache user, and accepting all requests from users and serves four primary functions:

   #. Authenticates user.
   #. Starts Per-User NGINX processes (PUNs).
   #. Reverse proxies each user to her PUN via Unix domain sockets.
   #. Reverse proxies to interactive apps running on compute nodes (RStudio, Jupyter, VNC desktop) via TCP sockets.

#. The Per-User NGINX serves web apps in Ruby and NodeJS and is how users submit jobs and start interactive apps.


System context
-----------------------

Users use OnDemand to interact with their HPC resources through a web browser.

.. figure:: /architecture/ood_system_view.png

All the gray components are specific to a given site and outside the OnDemand
system.

Container context
-----------------------

.. tip::

   In the C4 nomenclature, 'containers' are one level below the system context. This is
   not to be confused with Linux containers via cgroups and namespaces (i.e. Docker or
   Singularity or `OCI containers <https://www.opencontainers.org/>`_).

The Front-end proxy is the only component that is shared with all clients.
The Front-end proxy will create Per User Nginx (PUN) processes (light blue boxes labeled "Per User Instance").

.. figure:: /architecture/ood_container_view.png

* Everything contained in the dotted line is a part of the OnDemand system (see blue box in System context diagram).
* Everything outside of it in gray is site specific components.
* The "Per User Instance" light blue boxes are replicated for every user accessing the system.

Request Flow
-----------------------

This is the request flow through the OnDemand system. A user initiates a
request through a browser and this illustrates how that request propagates
through the system to a particular application (including the dashboard).

.. uml:: architecture/request-flow.uml


