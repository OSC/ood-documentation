.. _install-desktops-customize-desktop-app:

Customize Desktop App
=====================

In some cases the defaults used to submit a batch job may not work on your
given cluster or you may just want to remove some form options presented to the
user and fill in hard-coded values. All of these cases and more can easily be
customized in the following files:

:file:`bc_desktop/local/{cluster_desktop}.yml`
  describes a given desktop app along with form attributes presented to the
  user

:file:`bc_desktop/local/submit/{custom_submit}.yml.erb`
  describes how the batch job should be submitted to your cluster (needs to be
  specified in a :file:`bc_desktop/local/{cluster_desktop}.yml` configuration
  file)

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
