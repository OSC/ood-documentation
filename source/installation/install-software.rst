.. _install-software:

Install Software From RPM
=========================

We will use `Software Collections`_ to satisfy majority of the following
software requirements:

- `Apache HTTP Server 2.4`_
- Ruby 2.7 with :command:`rake`, :command:`bundler`, and development
  libraries
- Node.js 12

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

#. Enable the dependency repositories **on CentOS/RHEL 7 only**:

   CentOS 7
     .. code-block:: sh

        sudo yum install centos-release-scl epel-release

   RHEL 7
     .. code-block:: sh

        sudo yum install epel-release
        sudo subscription-manager repos --enable=rhel-server-rhscl-7-rpms
        # Repository 'rhel-server-rhscl-7-rpms' is enabled for this system.

   .. warning::

      For **RedHat** you may also need to enable the *Optional* channel and
      attach a subscription providing access to RHSCL to be able to use this
      repository.

#. Enable dnf modules for dependencies **on CentOS/RHEL 8 only**:

    .. code-block:: sh

       dnf module enable ruby:2.7
       dnf module enable nodejs:12

#. Add Open OnDemand's repository hosted by the `Ohio Supercomputer Center`_:

     .. code-block:: sh

        sudo yum install https://yum.osc.edu/ondemand/{{ ondemand_version }}/ondemand-release-web-{{ ondemand_version }}-1.noarch.rpm

#. Install OnDemand and all of its dependencies:

   .. code-block:: sh

      sudo yum install ondemand

#. (Optional) Install :ref:`authentication-dex` package

   .. note::

      If authenticating against LDAP or wishing to evaluate OnDemand using `ood` user, you must install `ondemand-dex`.
      See :ref:`add-ldap` for details on configuration of LDAP.

   .. code-block:: sh

      sudo yum install ondemand-dex

#. (Optional) Install OnDemand SELinux support if you have SELinux enabled. For details see :ref:`ood_selinux`

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

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _ohio supercomputer center: https://www.osc.edu/
