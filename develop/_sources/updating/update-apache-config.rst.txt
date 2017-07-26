.. _update-apache-config:

Update Apache Config
====================

The tool used to update an Apache configuration file that describes an OOD
Portal is maintained by the :ref:`ood-portal-generator` project. Assuming you
previously installed it with :ref:`generate-apache-config` you can update it
with the following directions.

Do I need to update?
--------------------

Latest version: ``v0.4.0``

You can compare this to the OOD Portal Apache configuration file you have
installed locally with the following command:

.. code-block:: sh

   grep 'Generated using template' /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf
   #=> # Generated using template v0.4.0

where the version number should be given at the end of the line. If the version
numbers match then you can skip this update.

Instructions to update
----------------------

#. Fetch the latest changes and check out the latest tag of
   :ref:`ood-portal-generator`:

   .. code-block:: sh

      cd ~/ood/src/ood-portal-generator
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v0.4.0

#. Confirm your original configuration file is in this root directory and you
   are happy with the configuration:

   .. code-block:: sh

      cat config.yml

#. Rebuild the Apache configuration file under the `build/` directory:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake
      # => mkdir -p build
      # => rendering templates/ood-portal.conf.erb => build/ood-portal.conf

  .. danger::

     **Confirm** the changes between the built Apache config and your locally
     installed Apache config:

     .. code-block:: sh

        diff build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

     In fact you should **save** the locally installed Apache config in case
     anything goes wrong.

#. Copy this built Apache confif to the default installation location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => cp build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

#. Restart the Apache server:

   .. code-block:: sh

      sudo service httpd24-httpd restart

   .. warning::

      If using **RHEL 7** you will need to replace the above command with:

      .. code-block:: sh

         sudo systemctl restart httpd24-httpd
