.. _ood-portal-generator-usage:

Usage
=====

The :program:`ood-portal-generator` tool takes a user-defined YAML
configuration file and generates an `Apache configuration`_ file from the
provided template file. This Apache configuration file can then be used in an
Apache HTTP server to host an Open OnDemand portal.

The command that generates the Apache configuration file is given as:

.. code-block:: console

   $ bin/generate [OPTIONS]

At any point you can display a quick reference of the capabilities offered by
:program:`bin/generate` with:

.. code-block:: console

   $ bin/generate --help
   Usage: generate [options]
       -c, --config CONFIG              YAML config file used to render template
       -t, --template TEMPLATE          ERB template that is rendered
       -o, --output OUTPUT              File that rendered template is output to
       -v, --version                    Print current version
       -h, --help                       Show this help message

   Default:
     generate \
       -c /etc/ood/config/ood_portal.yml \
       -t /opt/ood/ood-portal-generator/templates/ood-portal.conf.erb

.. program:: ood-portal-generator

Options
-------

.. option:: -c <config>, --config <config>

   the :program:`ood-portal-generator` YAML configuration file

   Default
     :file:`/etc/ood/config/ood_portal.yml`

   Example
     Use a local configuration file

     .. code-block:: console

        $ bin/generate -c my_conf.yml

.. option:: -o <output>, --output <output>

   the Apache configuration file that is rendered

   Default
     piped to standard output

   Example
     Output Apache configuration file to local file

     .. code-block:: console

        $ bin/generate -o my_portal.conf

.. option:: -t <template>, --template <template>

   the ERB template that is used to render the Apache configuration file

   Default
     use built-in template

   Example
     Use a custom ERB template for the Apache config (not recommended)

     .. code-block:: console

        $ bin/generate -t my_portal.conf.erb

.. _apache configuration: https://httpd.apache.org/docs/2.4/configuring.html
