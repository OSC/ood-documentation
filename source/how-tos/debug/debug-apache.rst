.. _apache-extra:

Apache httpd tips
=================

..  tip::

  While this page is helpful it is no replacement for `Apache Httpd's documentation`_. If
  you are an administrator responsible for Open OnDemand, you are now an administrator of
  Apache Httpd as well.  As such, you should get comfortable with it as from time to time you will
  have to troubleshoot it.


Log locations
-------------

:ref:`Information about apache log location. <apache-logs>`

.. _restart-apache:

Restart services
----------------

   .. tabs::

      .. tab:: RHEL/CentOS 7

        .. code-block:: sh

          sudo systemctl try-restart httpd24-httpd


      .. tab:: RHEL/Rocky 8 & 9

         .. code-block:: sh

          sudo systemctl try-restart httpd

      .. tab:: Ubuntu

         .. code-block:: sh

          sudo systemctl try-restart apache2

.. _show-virtualhosts:

Show VirtualHosts
-----------------

OpenOnDemand creates it's own `VirtualHost`_ in Apache.  Apache will route
requests based off of the hostname in the request to different VirtualHosts
and the ServerName you may have configured.

Showing virtualhosts can help debug Apache request routing.  The output from these
commands will show you how Apache is routing based off of the ServerName in the VirtualHost.

If you're seeing the default Apache webpage you likely have to :ref:`configure the ServerName <ood-portal-generator-servername>`
which corresponds directly to `Apache's ServerName configuration`_ (and restart Apache).

Or you're using the wrong hostname in your browser.

   .. tabs::

      .. tab:: RHEL/CentOS 7

        .. code-block:: sh

          sudo /opt/rh/httpd24/root/sbin/httpd -S

      .. tab:: RHEL/Rocky 8 & 9

         .. code-block:: sh

          sudo /sbin/httpd -S

      .. tab:: Ubuntu

         .. code-block:: sh

          sudo /sbin/apache2 -S

Performance Tuning
------------------

If you're servicing many clients at time (more than 50) you will likely need to change the
`Apache Httpd's MPM configuration`_. The default configuration may degrade service when
Httpd has to serve many clients (I.e., when you have a lot of customers using Open OnDemand).

We suggest configurations similar to this. 

.. note::
  The most important directives used to control this MPM are `ThreadsPerChild`, which controls 
  the number of threads deployed by each child process and `MaxRequestWorkers`, which controls
  the maximum total number of threads that may be launched.
  
  MaxRequestWorkers * ThreadsPerChild will be your effictive cap on the number of 
  simultaneous requests that will be served.
   

.. code-block:: apache

  # conf.modules.d will vary depending on the platform and version.
  # $APACHE_HOME/conf.modules.d/mpm.conf
  
  # MPM event is actually important for idle VNC connections alive. You may
  # need delete occurences of mpm_prefork_module if you have that configured.
  LoadModule mpm_event_module modules/mod_mpm_event.so

  <IfModule mpm_event_module>

    # ServerLimit is MaxRequestWorkers / ThreadsPerChild then doubled
    ServerLimit            32
    StartServers           2
    MaxRequestWorkers      512
    MinSpareThreads        25
    MaxSpareThreads        75

    # ThreadsPerChild value is MaxRequestWorkers / # cpus for production
    ThreadsPerChild        32
    MaxRequestsPerChild    0
    ThreadLimit            512
    ListenBacklog          511
  </IfModule>


.. _Apache Httpd's MPM configuration: https://httpd.apache.org/docs/2.4/mod/mpm_common.html
.. _Apache Httpd's documentation: https://httpd.apache.org/docs/current/getting-started.html
.. _Apache's ServerName configuration: https://httpd.apache.org/docs/2.4/mod/core.html#servername
.. _VirtualHost: https://httpd.apache.org/docs/2.4/vhosts/
