.. _installation:

Installation
============

The OnDemand host machine needs to be setup *similarly* to a login node. This
means that it will need:

- RedHat/CentOS 7+
- a common user/group database, e.g., LDAP + NSS
- a common host file list
- the resource manager (e.g., Torque, Slurm, or LSF) client binaries and
  libraries used by the batch servers installed
- configuration on both OnDemand node **and batch servers** to be able to
  submit, status, and delete jobs from command line
- signed SSL certificate with corresponding intermediate certificate for your
  advertised OnDemand host name (e.g., ``ondemand.my_center.edu``)
- your LDAP URL, base DN, and attribute to search for (in some rare cases a
  bind DN and corresponding bind password)

.. toctree::
   :maxdepth: 2
   :numbered: 1
   :caption: Quick Start Guide

   installation/install-software
   installation/modify-system-security
   installation/start-apache
   installation/add-ssl
   installation/add-ldap

Building From Source
--------------------

Building from source is left as an exercise to the reader. 
     
It's not particularly difficult to build the code, but installing it with all the various files is. Should you be interested, 
review the ``Dockerfile`` and packaging specs for what would be involved.

- https://github.com/OSC/ondemand/blob/master/Dockerfile
- https://github.com/OSC/ondemand/tree/master/packaging

If you'd like a package built for a system that we don't currently support, feel free to open a ticket!

- https://github.com/OSC/ondemand/issues/new
