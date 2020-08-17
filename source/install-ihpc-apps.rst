.. _install-ihpc-apps:

Install Other Interactive Apps
==============================

For Jupyter, we provide a tutorial for copying a generic Jupyter batch connect
template and modifying it to work at your center. See
:ref:`app-development-tutorials-interactive-apps-add-jupyter` to install
Jupyter.

If you have developed an app and would like to contribute it to the community, please post a description and link to the app to https://discourse.osc.edu/c/open-ondemand.
In order to submit the code of an interactive app that you developed to the GitHub repository, it should be available on the developer’s GitHub and well commented. The comments need to include, but not limited to, mentioning if there are parts of the app that are site-specific. Also, the following files must be included:

- LICENSE file - the license should be open source. If you are not sure what to choose, OnDemand uses MIT License.

- README.md file - which specifies all the dependencies as well as cluster specific instructions



.. list-table:: Generic Interactive App Templates
   :header-rows: 1

   * - Name
     - GitHub URL
   * - Jupyter
     - https://github.com/OSC/bc_example_jupyter

While we don't yet provide this for other interactive apps, here is a list of
interactive apps that are currently deployed at OSC and other contributing institutions. 

.. list-table:: Interactive App
   :header-rows: 1

   * - Name
     - Institution
     - GitHub URL
     - Container
     - GUI
     - Notes/Features
   * - Abaqus/CAE
     - OSC
     - https://github.com/OSC/bc_osc_abaqus
     - no
     - 
     -
   * - 
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_abaqus
     -  no
     - 
     -
   * - ANSYS Workbench
     - OSC
     - https://github.com/OSC/bc_osc_ansys_workbench
     -  no
     - 
     -
   * - COMSOL Multiphysics
     - OSC
     - https://github.com/OSC/bc_osc_comsol
     - no
     - noVNC
     -
   * - 
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_comsol
     - no
     - noVNC
     -
   * - MATLAB
     - OSC
     - https://github.com/OSC/bc_osc_matlab
     - no
     - noVNC
     -
   * - 
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_matlab
     -  no
     - noVNC
     -
   * - Jupyter
     - OSC
     - https://github.com/OSC/bc_osc_jupyter
     - no
     - node
     -
   * - 
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_jupyter
     - no
     - node
     -
   * -  
     - University of Utah
     - https://github.com/CHPC-UofU/bc_jupyter_dynpart
     - no
     - node
     - Dynamic SLURM Partition
   * - Jupyter
     - Standford
     - https://github.com/stanford-rc/sh_ood-apps#sh_jupyter
     - no
     - node
     -
   * - 
     - TechSquareInc
     - https://gitlab.com/mjbludwig/jupyter_experimental
     - no
     - node
     -
   * - Jupyter + Spark
     - OSC
     - https://github.com/OSC/bc_osc_jupyter_spark
     - no
     - node
     -
   * - Paraview
     - OSC
     - https://github.com/OSC/bc_osc_paraview
     - no
     - 
     -
   * - RStudio Server
     - OSC
     - https://github.com/OSC/bc_osc_rstudio_server
     - hybrid
     - rnode
     -
   * - 
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_rstudio_server
     - yes
     - rnode
     -
   * - 
     - Standord
     - https://github.com/stanford-rc/sh_ood-apps#sh_rstudio
     - yes
     - rnode
     -
   * - VMD
     - OSC
     - https://github.com/OSC/bc_osc_vmd
     - no
     - 
     -
   * - QGIS
     - OSC
     - https://github.com/OSC/bc_osc_qgis
     - yes
     - noVNC
     -
   * - Stata 
     - OSC
     - https://github.com/OSC/bc_osc_stata
     - no
     - 
     -
   * - Shiny App
     - University of Utah
     - https://github.com/CHPC-UofU/bc_osc_example_shiny
     - yes
     - 
     -
   * - Tensorboard
     - Standford
     - https://github.com/stanford-rc/sh_ood-apps#sh_tensorboard 
     - no
     - 
     -
  
