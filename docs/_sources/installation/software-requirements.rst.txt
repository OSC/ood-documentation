.. _software-requirements:

Software Requirements
=====================

We will use RedHat Software Collections to satisfy these requirements:

- `Apache HTTP Server 2.4
  <https://www.softwarecollections.org/en/scls/rhscl/httpd24/>`__
- `NGINX 1.6 <https://www.softwarecollections.org/en/scls/rhscl/nginx16/>`__
- `Phusion Passenger 4.0
  <https://www.softwarecollections.org/en/scls/rhscl/rh-passenger40/>`__
- `Ruby 2.2 <https://www.softwarecollections.org/en/scls/rhscl/rh-ruby22/>`__
  with :command:`rake`, :command:`bundler`, and development files
- `Node.js 0.10
  <https://www.softwarecollections.org/en/scls/rhscl/nodejs010/>`__
- `Git 1.9 <https://www.softwarecollections.org/en/scls/rhscl/git19/>`__

In this tutorial RHSCL (RedHat Software Collections) packages are installed
under ``/opt/rh``. This tutorial is also done from an account that has
:command:`sudo` access but is not root.

Enable the RHSCL repository. Note that you may also need to enable the Optional
channel and attach a subscription providing access to RHSCL to be able to use
the repository.

.. code-block:: sh

   sudo subscription-manager repos --enable=rhel-server-rhscl-6-rpms
   # => Repository 'rhel-server-rhscl-6-rpms' is enabled for this system.

.. warning::

   If using **RHEL 7** you will need to replace the above command with:

   .. code-block:: sh

      sudo subscription-manager repos --enable=rhel-server-rhscl-7-rpms

Install dependencies:

.. code-block:: sh

   sudo yum install -y \
     sqlite-devel \
     httpd24 \
     nginx16 \
     rh-passenger40 \
     rh-ruby22 \
     rh-ruby22-rubygem-rake \
     rh-ruby22-rubygem-bundler \
     rh-ruby22-ruby-devel \
     nodejs010 \
     git19

Update the Apache Environment to include Ruby 2.2. This is necessary for the
user mapping script written in Ruby. Do this by editing
``/opt/rh/httpd24/service-environment`` as such:

.. code-block:: diff

   -HTTPD24_HTTPD_SCLS_ENABLED="httpd24"
   +HTTPD24_HTTPD_SCLS_ENABLED="httpd24 rh-ruby22"

.. warning::

   If using **RHEL 7** you will also need to override the :program:`systemd`
   configuration for Apache:

   .. code-block:: sh

      sudo systemctl edit httpd24-httpd

   and then add the following to ovverride the default settings:

   .. code-block:: sh

      [Service]
      KillSignal=SIGTERM
      KillMode=process
      PrivateTmp=false

   Finally, save your changes and run:

   .. code-block:: sh

      sudo systemctl daemon-reload

Finally, make a source directory that will contain the checked out and built
OOD infrastructure components and apps:

.. code-block:: sh

   mkdir -p ~/ood/src
