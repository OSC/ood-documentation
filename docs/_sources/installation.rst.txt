Installation
============

This installation tutorial starts with a web host ``webdev05.hpc.osc.edu``
which has

- the users are mirrored with the other machines (LDAP+NSS)
- the home directory shared file system is mounted and accessible by users
- TORQUE client libraries installed and the :command:`trqauthd` process started
- signed SSL certificates with corresponding intermediate certificate
- Software Collections package/repo, :command:`lsof`, and :command:`sudo` are
  installed
- the host has been added as a submit host to the respective batch servers

.. toctree::
   :maxdepth: 2
   :numbered:
   :caption: Quick Start Guide

   installation/software-requirements
   installation/modify-system-security
   installation/generate-apache-config
   installation/install-proxy-module
   installation/install-pun-utility
   installation/install-mapping-script
   installation/add-cluster-config
   installation/start-apache
   installation/install-apps
   installation/add-ssl
   installation/add-ldap
