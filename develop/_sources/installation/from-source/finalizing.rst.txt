.. _finalizing:

Finalizing From Source Installation
===================================

Now that all the necessary software has been installed to the system there are configuration steps that need to be taken to finalize the build.

- `Update the Apache service environment`_
- `Update the sudoers list`_
- `Add NGINX configs for the core web apps`_
- `Add a cronjob to prune long running PUNs`_
- `Add Apache Config`_

Update the Apache service environment
-------------------------------------

In order to be able to run Passenger we need Apache's service environment to know about the correct version of Ruby:

.. code:: bash

    sudo sed -i 's/^HTTPD24_HTTPD_SCLS_ENABLED=.*/HTTPD24_HTTPD_SCLS_ENABLED="httpd24 rh-ruby25"/' \
    /opt/rh/httpd24/service-environment

Update the sudoers list
-----------------------

The sudoer's list must be updated to permit Apache.

.. code:: bash

    sudo /etc/sudoers.d/ood << EOF
    Defaults:apache !requiretty, !authenticate
    apache ALL=(ALL) NOPASSWD: /opt/ood/nginx_stage/sbin/nginx_stage
    EOF

Add NGINX configs for the core web apps
---------------------------------------

NGINX configs must be generated for all of the core applications otherwise the first user to use each app will be prompted with a first time message.

.. code:: bash

    touch /var/lib/ondemand-nginx/config/apps/sys/activejobs.conf
    touch /var/lib/ondemand-nginx/config/apps/sys/dashboard.conf
    touch /var/lib/ondemand-nginx/config/apps/sys/file-editor.conf
    touch /var/lib/ondemand-nginx/config/apps/sys/files.conf
    touch /var/lib/ondemand-nginx/config/apps/sys/myjobs.conf
    touch /var/lib/ondemand-nginx/config/apps/sys/shell.conf
    /opt/ood/nginx_stage/sbin/update_nginx_stage &>/dev/null || :

Add a cronjob to prune long running PUNs
----------------------------------------

Remove in-active PUNs every 2 hours.

.. code:: bash

    sudo /etc/cron.d/ood << EOF
    #!/bin/bash
    PATH=/sbin:/bin:/usr/sbin:/usr/bin
    0 */2 * * * root [ -f /opt/ood/nginx_stage/sbin/nginx_stage ] && /opt/ood/nginx_stage/sbin/nginx_stage nginx_clean 2>&1 | logger -t nginx_clean
    EOF

Add Apache Config
-----------------

At this point we still will not see an OnDemand page if we visit our web node because the ood-portal configuration has not been generated. Generate a generic one now:

.. code:: bash

    sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

This is the basic OnDemand portal configuration and unless you are using Apache's basic auth for your site you will need to createa custom portal configuration file and re-run the portal generator. More information on the Apache config generator is available in the Configure Authentication section.

Installation Complete
---------------------

At this point installation of OnDemand is complete, and it is time to move on to configuring the application.
