.. _install-software:

Install Software
================

We will use `Software Collections`_ to satisfy majority of the following
software requirements:

- `Apache HTTP Server 2.4`_
- `Ruby 2.4`_ with :command:`rake`, :command:`bundler`, and development
  libraries
- `Node.js 6`_
- `Git 2.9`_

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

#. Enable the EPEL and Software Collections repositories:

   CentOS 6/7
     .. code-block:: sh

        sudo yum install centos-release-scl

   RHEL 6
     .. code-block:: sh

        sudo subscription-manager repos --enable=rhel-server-rhscl-6-rpms
        # Repository 'rhel-server-rhscl-6-rpms' is enabled for this system.

   RHEL 7
     .. code-block:: sh

        sudo subscription-manager repos --enable=rhel-server-rhscl-7-rpms
        # Repository 'rhel-server-rhscl-7-rpms' is enabled for this system.

   .. warning::

      For **RedHat** you may also need to enable the *Optional* channel and
      attach a subscription providing access to RHSCL to be able to use this
      repository.

#. Add Open OnDemand's repository hosted by the `Ohio Supercomputer Center`_:

     .. code-block:: sh

        sudo yum install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.noarch.rpm

#. Install OnDemand and all of its dependencies:

   .. code-block:: sh

      sudo yum install ondemand

#. Install OnDemand SELinux support if you have SELinux enabled. For details see :ref:`ood_selinux`

   .. code-block:: sh

      sudo yum install ondemand-selinux

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


When Installing OnDemand From Source
------------------------------------

Installing OnDemand from RPMs should provide all of the system dependencies. For users attempting to install OnDemand from source on non-CentOS/RHEL systems, it may be useful to know that OnDemand has several other build and run time dependencies that may need to be installed on the web node.


.. list-table:: System dependencies
   :header-rows: 1
   :stub-columns: 1

   * - Program
     - OnDemand Component 
   * - Rsync
     - /var/www/ood/apps/sys/myjobs/app/models/workflow.rb
   * - GNU Timeout
     - /var/www/ood/apps/sys/myjobs/app/models/filesystem.rb
   * - File
     - /var/www/ood/apps/sys/file-editor/app/controllers/pages_controller.rb
   * - Xmllint
     - /opt/ood/ondemand/root/usr/sbin/passenger-status
   * - GNU Wget
     - /opt/ood/mod_ood_proxy/lib/analytics.lua


**Note:** GCC is a build time dependency and is only required when building OnDemand from source.

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _ruby 2.4: https://www.softwarecollections.org/en/scls/rhscl/rh-ruby24/
.. _node.js 6: https://www.softwarecollections.org/en/scls/rhscl/rh-nodejs6/
.. _git 2.9: https://www.softwarecollections.org/en/scls/rhscl/rh-git29/
.. _ohio supercomputer center: https://www.osc.edu/
