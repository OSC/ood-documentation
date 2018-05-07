.. _app-development-interactive:

Interactive Apps (Plugins)
==========================

:ref:`interactive` can be developed and deployed using the same tools that are
currently provided for all Open OnDemand applications but requires further
:ref:`app-development-interactive-setup`.

An Interactive App is a :ref:`dashboard` plugin that follows a custom
file/directory structure and API that can be described by the four stages:
:ref:`app-development-interactive-form`,
:ref:`app-development-interactive-template`,
:ref:`app-development-interactive-submit`, and
:ref:`app-development-interactive-view`.

A typical file/directory structure for an Interactive App can look like::

  my_app/
  ├── form.yml
  ├── manifest.yml
  ├── submit.yml.erb
  ├── template
  │   ├── before.sh.erb
  │   └── script.sh.erb
  └── view.html.erb

Each of these files/directories are described below in their respective stage.

.. toctree::
   :maxdepth: 3
   :caption: Stages of an Interactive App

   interactive/setup
   interactive/form
   interactive/template
   interactive/submit
   interactive/view
