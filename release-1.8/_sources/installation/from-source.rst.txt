.. _from_source:

Install From Source
===================

  .. note::

    Skip to the :ref:`modify-system-security` section when installing from RPMs

..

The alternative to installing the core of OnDemand using RPMs is to install from source. This tutorial will assume installation on a CentOS/RHEL 7 base. We will look at how to install the core of OnDemand, while still using some OSC-provided RPMs to ensure a functioning build without having to go into too much detail. Installation on non-RPM-based systems is possible, but installing compatible versions of certain dependencies is left as an exercise for the interested.

  .. tip::
    If you prefer an automated build and installation procedure, we provide an `Ansible role`_ for that purpose.

.. _Ansible role: https://github.com/osc/ood-ansible

.. note::

  For those familiar with developing RPM distributed software the following is going to be drawn from the OnDemand RPM specfile which can be found on Github: https://github.com/OSC/ondemand/blob/5e6623de7e72c17d858dd7f533eb817f6193e7da/packaging/ondemand.spec

.. toctree::
   :maxdepth: 2
   :caption: Steps

   from-source/system-dependencies
   from-source/ood-infrastructure
   from-source/core-apps
   from-source/finalizing
