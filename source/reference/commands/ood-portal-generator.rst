.. _ood-portal-generator:

ood-portal-generator
====================

The :program:`ood-portal-generator` tool takes a user-defined YAML
configuration file and generates an `Apache configuration`_ file from the
provided template file. This Apache configuration file can then be used in an
Apache HTTP server to host an Open OnDemand portal.

The command that generates and updates the Apache configuration file is given as:

.. code-block:: sh

   /opt/ood/ood-portal-generator/sbin/update_ood_portal [OPTIONS]

At any point you can display a quick reference of the capabilities offered by
:program:`bin/generate` with:

.. code-block:: sh

   $ /opt/ood/ood-portal-generator/sbin/update_ood_portal -h
   Usage: update_ood_portal [options]
      -r, --rpm                        Execution performed during RPM install
      -f, --force                      Force replacement of configs even if checksums differ
         --detailed-exitcodes          Exit with 3 when changes are made and 4 when changes skipped
      -c, --config CONFIG              YAML config file used to render template
      -t, --template TEMPLATE          ERB template that is rendered
      -v, --version                    Print current version
      -h, --help                       Show this help message

   Default:
   update_ood_portal -c /etc/ood/config/ood_portal.yml -t /opt/ood/ood-portal-generator/templates/ood-portal.conf.erb


.. program:: ood-portal-generator

Options
-------

.. option:: -r, --rpm

   Execution performed during RPM install

   Default
      not used

   Example
      Run the script as if it were during the RPM installation

     .. code-block:: sh

        /opt/ood/ood-portal-generator/sbin/update_ood_portal -r

.. option:: -f, --force

   Force the update to occur even if the checksums don't match

   Default
      not used

   Example
      Force the update to occur even if the checksums don't match

     .. code-block:: sh

        /opt/ood/ood-portal-generator/sbin/update_ood_portal -f

.. option:: --detailed-exitcodes

   Exit with different codes

   Default
      exits 0 if the update is successful, 1 if not

   Example
      Exit with 3 when changes are made and 4 when changes skipped

     .. code-block:: sh

        /opt/ood/ood-portal-generator/sbin/update_ood_portal --detailed-exitcodes

.. option:: -c <config>, --config <config>

   the :program:`ood-portal-generator` YAML configuration file

   Default
     :file:`/etc/ood/config/ood_portal.yml`

   Example
     Use a local configuration file

     .. code-block:: sh

        /opt/ood/ood-portal-generator/sbin/update_ood_portal -c my_conf.yml

   .. warning::
      The systemd file for Apache will run the update_ood_portal script with defaults
      and will not use a different file, rendering this option obsolete.

.. option:: -t <template>, --template <template>

   the ERB template to use as the input

   Default
     :file:`/opt/ood/ood-portal-generator/templates/ood-portal.conf.erb`

   Example
     Use a different ERB template (not recommended)

     .. code-block:: sh

        /opt/ood/ood-portal-generator/sbin/update_ood_portal -t /opt/myfiles/different-ood-portal.conf.erb
      
   .. warning::
      The systemd file for Apache will run the update_ood_portal script with defaults
      and will not use a different file, rendering this option obsolete.

.. _apache configuration: https://httpd.apache.org/docs/2.4/configuring.html
