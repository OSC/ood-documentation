.. _ood-portal-generator-usage:

Usage
=====

This software uses Rake_ which is a Make-like program implemented in Ruby_. So
to build a working Apache configuration file from the template, you would run:

.. code-block:: sh

   rake

This will build the following Apache configuration file::

   build/ood-portal.conf

After viewing and confirming that this Apache configuration file will meet your
OnDemand portal needs, you will run:

.. code-block:: sh

   sudo rake install

This will copy the build file to::

   /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

.. _ruby: https://www.ruby-lang.org/en/
.. _rake: https://ruby.github.io/rake/
