(enable-desktops-software-requirements)=

# Software Requirements

The interactive Desktop app requires a Desktop Environment be installed on the
nodes that the batch job is meant to run on, **NOT** the OnDemand node.

The following desktops are currently supported:

- [Xfce Desktop] 4+
- [Mate Desktop] 1+ (**default**)
- [Gnome Desktop] 2 (currently we do not support Gnome 3)

:::{warning}
Do **NOT** install the Desktop Environment on the **OnDemand node**. The
above Desktop Environments are **ONLY** for the **compute or login nodes** you intend
on launching Desktops on within batch jobs.
:::

[gnome desktop]: https://www.gnome.org/
[mate desktop]: https://mate-desktop.org/
[xfce desktop]: https://xfce.org/
