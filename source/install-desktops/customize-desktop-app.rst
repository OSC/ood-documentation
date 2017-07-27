.. _install-desktops-customize-desktop-app:

Customize Desktop App
=====================

In some cases the defaults used to submit a batch job may not work on your
given cluster or you may just want to remove some form options presented to the
user and fill in hard-coded values. All of these cases and more can easily be
customized in the following files:

:file:`bc_desktop/local/{cluster_desktop}.yml`
  form config file that describes a given Desktop app along with form attributes presented to the
  user. Replace ``{cluster_desktop}`` with whatever name you desire, as the
  previous section used ``cluster1.yml``, ``cluster2.yml`` etc. as examples. For
  each form config file underneath ``bc_desktop/local/``, a separate desktop app
  will be presented as an option to the user.

:file:`bc_desktop/local/submit/{custom_submit}.yml.erb`
  describes how the batch job should be submitted to your cluster. Replace ``{custom_submit}`` with whatever name you desire. The name of
  this file needs to be specified in the :file:`bc_desktop/local/{cluster_desktop}.yml` form configuration
  file, so when a user submits the the form, the specified submit config is used
  to set the arguments.

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
