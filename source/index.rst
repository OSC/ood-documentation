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

- Bowdoin College. For help with the SGE adapter.
- Oregon State University. For help with the SGE adapter.
- Pittsburgh Supercomputer Center. This work used the Bridges system, which is
  supported by NSF award number ACI-1445606, at the Pittsburgh Supercomputing
  Center (PSC). For early adoption and help with the Slurm adapter, platform
  feedback, and webinar participation.
- Texas A&M High Performance Research Computing. Portions of this research were
  conducted with the advanced computing resources provided by Texas A&M High
  Performance Research Computing. For early adoption and help with the LSF
  adapter, platform feedback.
- Tufts Technology Services HPC Research Computing for early adoption and help
  with Slurm adapter development, platform feedback, and webinar participation.
- University of Arizona HPC. An allocation of computer time from the UA
  Research Computing High Performance Computing (HPC) at the University of
  Arizona is gratefully acknowledged. For early adoption and help with the
  PBSPro adapter, platform feedback.
- University at Buffalo Center for Computational Research. For early adoption,
  platform feedback, and collaboration on the next major version of Open
  OnDemand, 2.0.
- UCLA Institute for Digital Research and Education. This work used
  computational and storage services associated with the Hoffman2 Shared
  Cluster provided by UCLA Institute for Digital Research and Education’s
  Research Technology Group. For help with the SGE adapter.

.. toctree::
   :maxdepth: 2
   :caption: Install

   installation
   authentication
   installation/add-cluster-config
   installation/resource-manager
   customization_overview
   customization


.. toctree::
   :maxdepth: 2
   :caption: Extend

   app-development/interactive/setup
   enable-desktops
   install-ihpc-apps
   app-development
   app-sharing
   app-development/tutorials-interactive-apps
   app-development/tutorials-passenger-apps

.. toctree::
   :maxdepth: 2
   :caption: Release Notes

   release-notes/v1.5-release-notes
   release-notes/v1.4-release-notes
   release-notes/v1.3-release-notes
   release-notes/v1.2-release-notes
   release-notes/v1.1-release-notes
   release-notes/v1.0-release-notes

.. toctree::
   :maxdepth: 2
   :caption: Legacy Docs

   infrastructure
   applications
   user-documentation


.. _website: https://osc.github.io/Open-OnDemand/
