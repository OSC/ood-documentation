.. Open OnDemand documentation master file, created by
   sphinx-quickstart on Thu Mar  9 18:18:09 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Open OnDemand
=============

Our `website`_ contains general information about the Open OnDemand project.

Community contributions
-----------------------

Throughout this documentation we will start highlighting community
contributions to the project, including linking to external useful projects or
extensions such as `PSC's Jupyter Notebook extension
<https://github.com/PSC-PublicHealth/pha-nbextensions>`_ for manipulating the
environment post launch.

.. note::

   If you have an app or extension that may be useful to others in the
   OnDemand community please share on our `Discourse <https://discourse.osc.edu/c/open-ondemand>`_ instance and we can then
   also add it to this documentation site.

Special Thanks
--------------

These are institutions who were early adopters or provided HPC resources for development and testing of the resource manager adapters currently available. The success of this project would not be possible without their generous support (in alphabetical order):

- `Bowdoin College <bowdoin_>`_ for help with the SGE adapter.
- `George Louthan, formerly of Tandy Supercomputer Center <louthan_>`_, for early adoption and help with LSF adapter.
- `Oregon State University <oregonstate_>`_ for help with the SGE adapter.
- `Pittsburgh Supercomputer Center <psc_>`_ for early adoption and help with the Slurm adapter, platform
  feedback, and webinar participation.
- `Texas A&M High Performance Research Computing <tamu_>`_ for early adoption and help with the LSF
  adapter, platform feedback.
- `Tufts Technology Services HPC Research Computing <tufts_>`_ for early adoption and help
  with Slurm adapter development, platform feedback, and webinar participation.
- `UCLA Institute for Digital Research and Education <ucla_>`_ for help with the SGE adapter.
- `University of Arizona HPC <arizona_>`_ for early adoption and help with the
  PBSPro adapter, platform feedback, and webinar participation.
- `University at Buffalo Center for Computational Research <buffalo_>`_ for early adoption,
  platform feedback, and collaboration on the next major version of Open
  OnDemand, 2.0.
- `University of Utah <utah_>`_ for early adoption and help with the Slurm adapter, platform feedback,
  and webinar participation.

.. toctree::
   :maxdepth: 2
   :caption: General

   architecture
   reference
   release-notes
   glossary


.. toctree::
   :maxdepth: 2
   :caption: Install

   requirements
   installation
   authentication
   installation/add-cluster-config
   installation/resource-manager
   customization_overview
   customization
   analytics
   monitoring

.. toctree::
  :maxdepth: 2
  :caption: How-Tos

  how-tos/apps.rst
  how-tos/app-development

.. toctree::
  :maxdepth: 2
  :caption: Tutorials

  tutorials/tutorials-interactive-apps
  tutorials/tutorials-passenger-apps

.. toctree::
   :maxdepth: 2
   :caption: Extend

   how-tos/app-development/interactive/setup
   enable-desktops
   install-ihpc-apps

.. toctree::
   :maxdepth: 2
   :caption: Deploy

   app-authorization
   app-sharing

.. toctree::
   :maxdepth: 2
   :caption: Known Issues

   issues/overview

.. toctree::
   :maxdepth: 2
   :caption: Legacy Docs

   applications
   user-documentation


.. _website: http://openondemand.org/
.. _bowdoin: https://www.bowdoin.edu/it/resources/high-performance-computing.html
.. _louthan: http://www.ou.edu/oscer/people
.. _oregonstate: https://oregonstate.edu/
.. _psc: https://www.psc.edu/
.. _tamu: https://hprc.tamu.edu/
.. _tufts: https://it.tufts.edu/it-computing/technology-research/high-performance-computing-tufts-research-cluster
.. _ucla: https://idre.ucla.edu/resources/hpc
.. _buffalo: http://www.buffalo.edu/ccr.html
.. _utah: https://www.chpc.utah.edu/
.. _arizona: https://it.arizona.edu/service/high-performance-computing
