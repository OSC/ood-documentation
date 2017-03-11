Software Requirements
=====================

We will use RedHat Software Collections to satisfy these requirements:

- Apache HTTP Server 2.4
- NGINX 1.6
- Phusion Passenger 4.0
- Ruby 2.2 with rake, bundler, and ability to build gem native
  extensions
- Node.js 0.10
- Git 1.9

In this tutorial scl (RedHat Software Collections) packages happen to be
installed at ``/opt/rh``. This tutorial is also done from an account that has
sudo access but is not root.

Enable the RHSCL repository. Note that you may also need to enable the Optional
channel and attach a subscription providing access to RHSCL to be able to use
the repository.

.. code-block:: sh

   sudo subscription-manager repos --enable=rhel-server-rhscl-6-rpms
   # => Repository 'rhel-server-rhscl-6-rpms' is enabled for this system.

Install dependencies:

.. code-block:: sh

   sudo yum install -y httpd24 nginx16 rh-passenger40 rh-ruby22 rh-ruby22-rubygem-rake rh-ruby22-rubygem-bundler rh-ruby22-ruby-devel nodejs010 git19

Update Apache Environment to include ``rh-ruby22``. This is necessary for the
user mapping script written in Ruby. Do this by editing
``/opt/rh/httpd24/service-environment``:

.. code-block:: diff

   -HTTPD24_HTTPD_SCLS_ENABLED="httpd24"
   +HTTPD24_HTTPD_SCLS_ENABLED="httpd24 rh-ruby22"

Finally, make a source directory that will contain the checked out and built
OOD infrastructure components and apps:

.. code-block:: sh

   mkdir -p ~/ood/src
