.. _app-development-tutorials-interactive-apps-add-matlab:

Add a Matlab App
================

This tutorial will walk you through creating an interactive Matlab app that
your users will use to launch a `Matlab`_ within a batch job on a compute node.
Matlab will be launched within the context of an XFCE desktop to provide a 
window manager and terminal. The user will then be able to connect to the
application through their browser and take advantage of the resources provided
within the batch job.

.. danger::

   Confirm that you have walked through the
   :ref:`app-development-interactive-setup` instructions for :ref:`interactive`
   as well as :ref:`enable-desktops` before continuing on.

.. toctree::
   :maxdepth: 2
   :numbered: 1
   :caption: Quick Start Guide

   add-matlab/software-requirements
   add-matlab/copy-app
   add-matlab/edit-form-yml
   add-matlab/edit-script-sh
   add-matlab/edit-submit-yml
   add-matlab/edit-form-js
   add-matlab/deploy
   add-matlab/known-issues

.. _Matlab: https://www.mathworks.com/products/matlab.html
