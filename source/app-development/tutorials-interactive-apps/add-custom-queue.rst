.. _app-development-tutorials-interactive-apps-add-custom-queue:

Add Custom Qeueus/Partitions
============================

This tutorial will walk you through **replacing** the ``bc_queue`` form
attribute in your Interactive App with a custom HTML ``<select>`` element (a
drop-down list of options) that allows the user to choose from a list of
queues/partitions to submit their batch job to.

.. warning::

   This tutorial will assume that you have walked through and setup a working
   instance of the Jupyter Interactive App following the directions outlined
   under :ref:`app-development-tutorials-interactive-apps-add-jupyter`.

As there are multiple solutions to add custom queues/partitions to your
Interactive Apps, we document a few such solutions that range in complexity as
well as possible access restrictions that a developer may have.

.. toctree::
   :maxdepth: 1
   :caption: Possible Solutions

   add-custom-queue/local-static-list
   add-custom-queue/global-static-list
   add-custom-queue/local-dynamic-list
