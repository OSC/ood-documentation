.. Open OnDemand documentation master file, created by
   sphinx-quickstart on Thu Mar  9 18:18:09 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Open OnDemand
=============

`Website`_ | `Mailing list`_ | `GitHub`_


The Open OnDemand Project [1]_ is an NSF-funded [2]_ open-source HPC portal based on
the `Ohio Supercomputer Center's <osc_>`_ original OnDemand portal. The goal of
Open OnDemand is to provide an easy way for system administrators to provide
web access to their HPC resources.

----

.. [1] David E. Hudak, Douglas Johnson, Jeremy Nicklas, Eric Franz, Brian
       McMichael, and Basil Gohar. 2016. Open OnDemand: Transforming
       Computational Science Through Omnidisciplinary Software
       Cyberinfrastructure. In *Proceedings of the XSEDE16 Conference on
       Diversity, Big Data, and Science at Scale* (XSEDE16). ACM, New York, NY,
       USA, , Article 43 , 7 pages. DOI:
       http://dx.doi.org/10.1145/2949550.2949644
.. [2] This material is based upon work supported by the `National Science
       Foundation <https://www.nsf.gov>`_ under grant number `1534949
       <grant_>`_


.. toctree::
   :maxdepth: 2
   :caption: Install

   installation
   authentication

.. toctree::
   :maxdepth: 2
   :caption: Configure

   installation/add-cluster-config

.. toctree::
   :maxdepth: 2
   :caption: Customize
   :glob:

   customization/*


.. toctree::
   :maxdepth: 2
   :caption: Extend

   enable-desktops
   install-ihpc-apps
   app-development


.. toctree::
   :maxdepth: 2
   :caption: Release Notes

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
.. _mailing list: https://lists.osu.edu/mailman/listinfo/ood-users
.. _github: https://github.com/OSC/Open-OnDemand
.. _grant: https://www.nsf.gov/awardsearch/showAward?AWD_ID=1534949
.. _osc: https://www.osc.edu
