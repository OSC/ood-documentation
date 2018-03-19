.. _installation:

Installation
============

The OnDemand host machine needs to be setup *similarly* to a login node. This
means that it will need:

- RedHat/CentOS 6+
- a common user/group database, e.g., LDAP + NSS
- a common host file list
- the resource manager (e.g., Torque, Slurm, or LSF) client binaries and
  libraries installed used by the batch servers
- configuration on both OnDemand node and batch servers to be able to submit,
  status, and delete jobs from command line
- signed SSL certificate with corresponding intermediate certificate for your
  advertised OnDemand host name (e.g., `ondemand.my_center.edu`)

.. toctree::
   :maxdepth: 2
   :numbered: 1
   :caption: Quick Start Guide

   installation/install-software
   installation/modify-system-security
   installation/add-cluster-config
   installation/start-apache
   installation/add-ssl
   installation/add-ldap
