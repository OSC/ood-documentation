.. _app-development-interactive-setup-software-requirements:

Software Requirements
=====================

A class of :ref:`interactive` will need a VNC server on the compute node
(e.g., the Desktop app). This requires the following software to be installed
on the nodes that the batch job submitted by the Interactive App is meant to
run on, **NOT** the OnDemand node.

For VNC server support:

- `TurboVNC`_ 2.1+
- `websockify`_ 0.8.0+

.. warning::

   Do **NOT** install the above software on the **OnDemand node**. The above
   software requirements are **ONLY** for the **compute nodes** you intend on
   launching Desktops on within batch jobs.

.. _turbovnc: https://turbovnc.org/
.. _websockify: https://github.com/novnc/websockify
