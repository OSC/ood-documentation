.. _install-software:

Install Software From Package
=============================

We will use `Software Collections`_ to satisfy majority of the following
software requirements:

- `Apache HTTP Server 2.4`_
- Ruby 2.7 with :command:`rake`, :command:`bundler`, and development
  libraries
- Node.js 12

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

1. Enable the dependency repositories:

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

2. Add Open OnDemand's repository hosted by the `Ohio Supercomputer Center`_ and install:

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

#. (Optional) Install :ref:`authentication-dex` package

   .. note::

      If authenticating against LDAP or wishing to evaluate OnDemand using `ood` user, you must install `ondemand-dex`.
      See :ref:`add-ldap` for details on configuration of LDAP.

   .. tabs::

      .. tab:: yum/dnf

         .. code-block:: sh

            sudo yum install ondemand-dex


      .. tab:: apt

         .. code-block:: sh

            sudo apt install ondemand-dex

#. (Optional) Install OnDemand SELinux support if you have SELinux enabled. For details see :ref:`ood_selinux`

   .. tabs::

      .. tab:: yum/dnf

         .. code-block:: sh

            sudo yum install ondemand-selinux

      .. tab:: apt

          Not available for Debian systems.

.. note::

   For some older systems, user ids (UID) may start at ``500`` and not the
   expected ``1000``. If this true for your system, you will need to modify the
   :file:`/etc/ood/config/nginx_stage.yml` configuration file to allow these
   users access to OnDemand:

   .. code-block:: yaml
      :emphasize-lines: 9

      # /etc/ood/config/nginx_stage.yml
      ---

      # ...

      # Minimum user id required to generate per-user NGINX server as the requested
      # user (default: 1000)
      #
      min_uid: 500

      # ...

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _ohio supercomputer center: https://www.osc.edu/
