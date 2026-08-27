.. _installation:

Installation
============

The OnDemand host machine needs to be setup *similarly* to a login node. This
means that it will need:

- RedHat/RockyLinux/AlmaLinux 8+ or Ubuntu 24.04 & 26.04 or Debian 12 & 13 or Amazon Linux 2023
- the resource manager (e.g., Torque, Slurm, or LSF) client binaries and
  libraries used by the batch servers installed
- configuration on both OnDemand node **and batch servers** to be able to
  submit, delete and get status for jobs from the command line
- signed SSL certificate with corresponding intermediate certificate for your
  advertised OnDemand host name (e.g., ``ondemand.my_center.edu``)

Adding :ref:`Open OnDemand SELinux policies <modify-system-security>` is optional for RHEL systems.
Open OnDemand, by default, expects Apache to have SSL enabled by :ref:`securing your Apache <add-ssl>`.

.. toctree::
   :maxdepth: 2
   :numbered: 1

   installation/install-software
   authentication
   integrated-authentication-solutions
   installation/add-ssl
   installation/modify-system-security

- https://github.com/OSC/ondemand/issues/new
