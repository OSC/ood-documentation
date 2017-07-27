.. _install-desktops-customize-desktop-app:

Customize Desktop App
=====================

In some cases the defaults used to submit a batch job may not work on your
given cluster or you may just want to remove some form options presented to the
user and fill in hard-coded values. All of these cases and more can easily be
customized in the following files:

:file:`bc_desktop/local/{cluster_desktop}.yml`
  Form configuration file that describes a given Desktop app along with form
  attributes presented to the user. Replace ``cluster_desktop`` with a
  representable name, in the previous section we used ``cluster1.yml`` and
  ``cluster2.yml`` to describe the desktops for the various clusters. For each
  form configuration file underneath ``bc_desktop/local/``, a separate desktop
  app will be presented as an option to the user.

:file:`bc_desktop/local/submit/{custom_submit}.yml.erb`
  Describes how the batch job should be submitted to your cluster. Replace
  ``custom_submit`` with a descriptive name. Be sure that the name of this file
  is specified in the :file:`bc_desktop/local/{cluster_desktop}.yml` form
  configuration file, so that when a user submits the form, the specified
  submission configuration is used when submitting the batch job.

.. note::

   The ``.erb`` file extension will cause the YAML configuration file to be
   processed using the `eRuby (Embedded Ruby)`_ templating system. This allows
   you to embed Ruby code into the YAML configuration file for flow control,
   variable subsitution, and more.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   customize-desktop-app/modify-form-attributes
   customize-desktop-app/custom-job-submission

.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
