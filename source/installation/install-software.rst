.. _install-software:

Install Software
================

Open OnDemand uses these packages, among many others.

- `Apache HTTP Server 2.4`_
- Ruby 2.7 with :command:`rake`, :command:`bundler`, and development
  libraries
- Node.js 14

Some operating systems use `Software Collections`_ to satisfy these.

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

1. Enable Dependencies
----------------------

.. tabs::

   .. tab:: CentOS 7

      .. code-block:: sh

         sudo yum install centos-release-scl epel-release


   .. tab:: RockyLinux 8

      .. code-block:: sh

         sudo dnf config-manager --set-enabled powertools
         sudo dnf install epel-release
         sudo dnf module enable ruby:2.7 nodejs:14

   .. tab:: RHEL 7

      .. warning::

         You may also need to enable the *Optional* channel and
         attach a subscription providing access to RHSCL to be able to use this
         repository.

      .. code-block:: sh

         sudo yum install epel-release
         sudo subscription-manager repos --enable=rhel-server-rhscl-7-rpms


   .. tab:: RHEL 8

      .. warning::

         You may also need to enable the *Optional* channel and
         attach a subscription providing access to RHSCL to be able to use this
         repository.

      .. code-block:: sh

         sudo dnf config-manager --set-enabled powertools
         sudo dnf install epel-release
         sudo dnf module enable ruby:2.7 nodejs:14
         sudo subscription-manager repos --enable codeready-builder-for-rhel-8-x86_64-rpms


2. Add repository and install
-----------------------------

   .. tabs::

      .. tab:: yum/dnf

         .. code-block:: sh

            sudo yum install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.noarch.rpm

            sudo yum install ondemand


      .. tab:: apt

         .. code-block:: sh

            sudo apt install apt-transport-https ca-certificates
            wget -O /tmp/ondemand-release-web_{{ ondemand_version }}.0_all.deb https://apt.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web_{{ ondemand_version }}.0_all.deb
            sudo apt install /tmp/ondemand-release-web_{{ ondemand_version }}.0_all.deb
            sudo apt update

            sudo apt install ondemand

3. Start services
-----------------

   .. tabs::

      .. tab:: RHEL/CentOS 7

        .. code-block:: sh

          sudo systemctl start httpd24-httpd
          sudo systemctl enable httpd24-httpd


      .. tab:: RHEL/Rocky 8

         .. code-block:: sh

          sudo systemctl start httpd
          sudo systemctl enable httpd

      .. tab:: Ubuntu

         .. code-block:: sh

          sudo systemctl start apache2
          sudo systemctl enable apache2

4. Verify installation
----------------------

Now that Open OnDemand is installed and Apache is running, it should be serving
a public page telling you to come back here and setup authentication.  If this
is the case - then you should :ref:`secure your apache <add-ssl>` then :ref:`add authentication <authentication>`.
You may also want to :ref:`enable SELinux <modify-system-security>`.

If you're seeing the default apache page (Ubuntu users will) you will have to :ref:`debug virtualhosts <show-virtualhosts>`
and likely :ref:`configure a servername <ood-portal-generator-servername>`.

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _ohio supercomputer center: https://www.osc.edu/