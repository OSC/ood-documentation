.. _install-software:

Install Software
================

Open OnDemand uses these packages, among many others.

- `Apache HTTP Server 2.4`_
- Ruby 3.0 with :command:`rake`, :command:`bundler`, and development
  libraries
- Node.js 18

Some operating systems use `Software Collections`_ to satisfy these.

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

.. warning::

   Be sure to check :ref:`Supported Operating Systems and Architectures <os-support>` before proceeding with install to verify
   you are on a supported operating system and architecture.

..  warning::

  If you are an administrator responsible for Open OnDemand, you are now an administrator of
  Apache Httpd as well.  As such, you should get comfortable with it as from time to time you will
  have to troubleshoot it.

1. Enable Dependencies
----------------------

.. tabs::

   .. tab:: CentOS 7

      .. code-block:: sh

         sudo yum install centos-release-scl epel-release


   .. tab:: RockyLinux/Alma Linux 8

      .. code-block:: sh

         sudo dnf config-manager --set-enabled powertools
         sudo dnf install epel-release
         sudo dnf module enable ruby:3.1 nodejs:18

   .. tab:: RockyLinux/Alma Linux 9

      .. code-block:: sh

         sudo dnf config-manager --set-enabled crb
         sudo dnf install epel-release
         sudo dnf module enable ruby:3.1 nodejs:18


   .. tab:: RHEL 8

      .. code-block:: sh

         sudo dnf install epel-release
         sudo dnf module enable ruby:3.1 nodejs:18
         sudo subscription-manager repos --enable codeready-builder-for-rhel-8-x86_64-rpms


   .. tab:: RHEL 9

      .. code-block:: sh

         sudo dnf install epel-release
         sudo dnf module enable ruby:3.1 nodejs:18
         sudo subscription-manager repos --enable codeready-builder-for-rhel-9-x86_64-rpms

2. Add repository and install
-----------------------------

   .. tabs::

      .. tab:: RedHat/CentOS 7

         .. code-block:: sh

            sudo yum install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.el7.noarch.rpm

            sudo yum install ondemand

      .. tab:: RedHat/Rocky Linux/AlmaLinux 8

         .. code-block:: sh

            sudo dnf install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.el8.noarch.rpm

            sudo dnf install ondemand

      .. tab:: RedHat/Rocky Linux/AlmaLinux 9

         .. code-block:: sh

            sudo dnf install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.el9.noarch.rpm

            sudo dnf install ondemand

      .. tab:: Ubuntu 20.04

         .. code-block:: sh

            sudo apt install apt-transport-https ca-certificates
            wget -O /tmp/ondemand-release-web_{{ ondemand_version }}.1-focal_all.deb https://apt.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web_{{ ondemand_version }}.1-focal_all.deb
            sudo apt install /tmp/ondemand-release-web_{{ ondemand_version }}.1-focal_all.deb
            sudo apt update

            sudo apt install ondemand

      .. tab:: Ubuntu 22.04

         .. code-block:: sh

            sudo apt install apt-transport-https ca-certificates
            wget -O /tmp/ondemand-release-web_{{ ondemand_version }}.1-jammy_all.deb https://apt.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web_{{ ondemand_version }}.1-jammy_all.deb
            sudo apt install /tmp/ondemand-release-web_{{ ondemand_version }}.1-jammy_all.deb
            sudo apt update

            sudo apt install ondemand

      .. tab:: Debian 12

         .. code-block:: sh

            sudo apt install apt-transport-https ca-certificates
            wget -O /tmp/ondemand-release-web_{{ ondemand_version }}.1-bookworm_all.deb https://apt.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web_{{ ondemand_version }}.1-bookworm_all.deb
            sudo apt install /tmp/ondemand-release-web_{{ ondemand_version }}.1-bookworm_all.deb
            sudo apt update

            sudo apt install ondemand

      .. tab:: Amazon Linux 2023

         .. code-block:: sh

            sudo dnf install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.amzn2023.noarch.rpm

            sudo dnf install ondemand

3. Start services
-----------------

   .. tabs::

      .. tab:: RHEL/CentOS 7

        .. code-block:: sh

          sudo systemctl start httpd24-httpd
          sudo systemctl enable httpd24-httpd


      .. tab:: RHEL/Rocky 8 & 9

         .. code-block:: sh

          sudo systemctl start httpd
          sudo systemctl enable httpd

      .. tab:: Ubuntu & Debian

         .. code-block:: sh

          sudo systemctl start apache2
          sudo systemctl enable apache2

      .. tab:: Amazon Linux 2023

         .. code-block:: sh

          sudo systemctl start httpd
          sudo systemctl enable httpd

4. Verify installation
----------------------

Now that Open OnDemand is installed and Apache is running, it should be serving
a public page telling you to come back here and setup authentication.

If this is the case - then you need to :ref:`add authentication <authentication>`.
The installation will not move forward without adding authentication.

After adding authentication, but before actually testing that it works, you should
:ref:`secure your Apache <add-ssl>`. This way you never send credentials over plain HTTP.

You may also want to :ref:`enable SELinux <modify-system-security>`.

If you're seeing the default Apache page (Ubuntu & Debian users will) you will have to :ref:`debug virtualhosts <show-virtualhosts>`
and likely :ref:`configure a servername <ood-portal-generator-servername>`.

Building From Source
--------------------

Building from source is left as an exercise to the reader. 
     
It's not particularly difficult to build the code, but installing it with all the various files is. Should you be interested, 
review the ``Dockerfile`` and packaging specs for what would be involved.

- https://github.com/OSC/ondemand/blob/master/Dockerfile
- https://github.com/OSC/ondemand/tree/master/packaging

If you'd like a package built for a system that we don't currently support, feel free to open a ticket!

- https://github.com/OSC/ondemand/issues/new

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _ohio supercomputer center: https://www.osc.edu/
