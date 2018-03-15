.. _install-software:

Install Software
================

We will use `Software Collections`_ to satisfy majority of the following
software requirements:

- `Apache HTTP Server 2.4`_
- `NGINX 1.6`_
- `Phusion Passenger 4.0`_
- `Ruby 2.2`_ with :command:`rake`, :command:`bundler`, and development
  libraries
- `Node.js 0.10`_
- `Git 1.9`_

.. note::

   This tutorial is run from the perspective of an account that has
   :command:`sudo` access but is not root.

#. Enable the Software Collections repository:

   CentOS 6/7
     .. code-block:: console

        $ sudo yum install centos-release-scl

   RHEL 6
     .. code-block:: console

        $ sudo subscription-manager repos --enable=rhel-server-rhscl-6-rpms
        Repository 'rhel-server-rhscl-6-rpms' is enabled for this system.

   RHEL 7
     .. code-block:: console

        $ sudo subscription-manager repos --enable=rhel-server-rhscl-7-rpms
        Repository 'rhel-server-rhscl-7-rpms' is enabled for this system.

   .. warning::

      For **RedHat** you may also need to enable the *Optional* channel and
      attach a subscription providing access to RHSCL to be able to use this
      repository.

#. Add Open OnDemand's repository hosted by the `Ohio Supercomputer Center`_:

   .. code-block:: console

      $ sudo yum install https://yum.osc.edu/ondemand/latest/ondemand-release-web-{{ ondemand_version }}-1.el7.noarch.rpm

#. Install OnDemand and all of its dependencies:

   .. code-block:: console

      $ sudo yum install ondemand

.. _software collections: https://www.softwarecollections.org/en/
.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _nginx 1.6: https://www.softwarecollections.org/en/scls/rhscl/nginx16/
.. _phusion passenger 4.0: https://www.softwarecollections.org/en/scls/rhscl/rh-passenger40/
.. _ruby 2.2: https://www.softwarecollections.org/en/scls/rhscl/rh-ruby22/
.. _node.js 0.10: https://www.softwarecollections.org/en/scls/rhscl/nodejs010/
.. _git 1.9: https://www.softwarecollections.org/en/scls/rhscl/git19/
.. _ohio supercomputer center: https://www.osc.edu/
