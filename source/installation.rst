.. _installation:

Installation
============

The OnDemand host machine needs to be setup *similarly* to a login node. This
means that it will need:

- RedHat/CentOS 7+ or Ubuntu 20.04
- signed SSL certificate with corresponding intermediate certificate for your
  advertised OnDemand host name (e.g., ``ondemand.my_center.edu``)

Adding :ref:`Open OnDemand SELinux policies <modify-system-security>` is optional for RHEL systems.  Open OnDemand, by default,
expects Apache to have SSL enabled.  Sites may reconfigure their deployment to allow
for plain text traffic see FIXME-LINK-NEEDED.

.. toctree::
   :maxdepth: 2
   :numbered: 1

   installation/install-software
   installation/modify-system-security
   installation/add-ssl

Building From Source
--------------------

Building from source is left as an exercise to the reader. 
     
It's not particularly difficult to build the code, but installing it with all the various files is. Should you be interested, 
review the ``Dockerfile`` and packaging specs for what would be involved.

- https://github.com/OSC/ondemand/blob/master/Dockerfile
- https://github.com/OSC/ondemand/tree/master/packaging

If you'd like a package built for a system that we don't currently support, feel free to open a ticket!

- https://github.com/OSC/ondemand/issues/new
