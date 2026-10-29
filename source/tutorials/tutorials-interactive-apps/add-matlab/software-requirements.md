(app-development-tutorials-interactive-apps-add-matlab-software-requirements)=

# Software Requirements

The MATLAB app requires the following software to be installed on the
**compute** nodes that batch job is meant to run on, **NOT** the OnDemand
node:

- [MATLAB]
- [Xfce Desktop] 4+ or [Mate Desktop] 1+ (provides window manager, terminal, file manager)
- [OpenJDK runtime]
- [VirtualGL] 2.5+ only necessary to enable GPU acceleration; if you do not
  have GPU nodes available you do not need this

**Optional** (but recommended) software:

- [Lmod] 6.0.1+ or any other CLI tool used to load appropriate environments
  within the batch job before launching the Jupyter Notebook Server, e.g.,

  ```sh
  module purge
  module load python
  ```

:::{warning}
Do **NOT** install the above software on the **OnDemand node**. The above
software requirements are **ONLY** for the **compute nodes** you intend on
launching the Jupyter Notebook Server on within batch jobs.
:::

:::{note}
We believe that the desktop based approach is superior, but are aware that
other sites may prefer an implementation that does not require a full desktop
be installed. [Fluxbox] is a window manager that has been used in place of
XFCE/Mate. An example of OSC's deprecated [Fluxbox based implementation] is
available on Github.
:::

[fluxbox]: http://fluxbox.org/
[fluxbox based implementation]: https://github.com/OSC/bc_osc_matlab/tree/bcff07264b318688c3f4272a9662b13477833373/template
[lmod]: https://www.tacc.utexas.edu/research-development/tacc-projects/lmod
[mate desktop]: https://mate-desktop.org/
[matlab]: https://www.mathworks.com/products/matlab.html
[openjdk runtime]: https://openjdk.java.net/
[virtualgl]: https://www.virtualgl.org/
[xfce desktop]: https://xfce.org/
