.. _system_dependencies:

Install System Dependencies
===========================

Non-OSC Provided Deps
---------------------

Install packages from your regular RPM servers.

  .. code-block:: sh

    sudo yum install centos-release-scl lsof sudo git

OSC Provided Deps
-----------------

Install system specific versions of system dependencies. This is the most annoying/challenging part to do 'from source' and so we are going to use OSC provided RPMs.

Many of OnDemand's system level dependencies are available from ``https://yum.osc.edu/ondemand/$ONDEMAND_RELEASE/web/$ENTERPRISE_LINUX_VERSION/x86_64/`` and need to be installed to the node that will become the OnDemand web server.

  .. code-block:: sh

    # To install deps for OnDemand 1.8.x on CentOS 7:
    sudo yum install \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-runtime-1.8-1.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-ruby-1.8-1.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-passenger-6.0.4-6.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-nodejs-1.8-1.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-nginx-1.17.3-6.p6.0.4.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/ondemand-apache-1.8-1.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/httpd24-mod_auth_openidc-2.4.1-1.el7.x86_64.rpm \
        https://yum.osc.edu/ondemand/1.8/web/el7/x86_64/cjose-0.6.1-1.el7.x86_64.rpm
