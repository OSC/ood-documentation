.. _start-apache:

Start Apache
============

.. code-block:: sh

   sudo service httpd24-httpd start
   # => Starting httpd:                                            [  OK  ]

If you access the host now through a web browser you should see this error:

::

   Error -- invalid app root: /var/www/ood/apps/sys/dashboard
   Run 'nginx_stage --help' to see a full list of available command line options.

Success! The infrastructure components are installed and now we need to install
the OOD "System Apps".
