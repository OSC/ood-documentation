.. _enable-desktops-software-requirements:

Software Requirements
=====================

The interactive Desktop app requires a Desktop Environment be installed on the
nodes that the batch job is meant to run on, **NOT** the OnDemand node.

The following desktops are currently supported:

- `Xfce Desktop`_ 4+
- `Mate Desktop`_ 1+ (**default**)
- `Gnome Desktop`_ 2 (currently we do not support Gnome 3)

.. warning::

   Do **NOT** install the Desktop Environment on the **OnDemand node**. The
   above Desktop Environments are **ONLY** for the **compute nodes** you intend
   on launching Desktops on within batch jobs.

.. _gnome desktop: https://www.gnome.org/
.. _mate desktop: https://mate-desktop.org/
.. _xfce desktop: https://xfce.org/
