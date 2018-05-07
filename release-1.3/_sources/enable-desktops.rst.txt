.. _enable-desktops:

Enable Interactive Desktop
==========================

This installation guide will walk you through setting up an Interactive Desktop
app that your users will be able to use to launch a Gnome 2, Mate, or Xfce
desktop on a compute node within your HPC cluster. The user should then be able
to connect to a running session through their browser using the `noVNC`_
client.

.. danger::

   Confirm that you have walked through the
   :ref:`app-development-interactive-setup` instructions for :ref:`interactive`
   before continuing on.

.. toctree::
   :maxdepth: 2
   :numbered: 1
   :caption: Quick Start Guide

   enable-desktops/software-requirements
   enable-desktops/add-cluster
   enable-desktops/modify-form-attributes
   enable-desktops/custom-job-submission

.. _novnc: http://novnc.com/info.html
