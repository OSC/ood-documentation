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
`Apache Httpd's worker configuration`_. The default configuration may degrade service when
Httpd has to serve many clients (I.e., when you have a lot of customers using Open OnDemand).

We suggest configurations similar to this. 

.. warning:: 
  `ServerLimit` and `ThreadsPerChild` should not exceed the number of cores available. 8
  is given in the example, but will likely need to change.

.. code-block:: apache

  # /opt/rh/httpd24/root/etc/httpd/conf.d/mpm.conf

  LoadModule mpm_event_module modules/mod_mpm_event.so

  <IfModule mpm_event_module>
    ServerLimit            8
    StartServers           2
    MaxRequestWorkers      512
    MinSpareThreads        25
    MaxSpareThreads        75
    ThreadsPerChild        8
    MaxRequestsPerChild    0
    ThreadLimit            512
    ListenBacklog          511
  </IfModule>


.. _Apache Httpd's worker configuration: https://httpd.apache.org/docs/2.4/mod/worker.html
.. _Apache Httpd's documentation: https://httpd.apache.org/docs/current/getting-started.html
.. _Apache's ServerName configuration: https://httpd.apache.org/docs/2.4/mod/core.html#servername
.. _VirtualHost: https://httpd.apache.org/docs/2.4/vhosts/
