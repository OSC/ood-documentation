.. _prometheus:

Prometheus Monitoring
=========================

.. _ondemand_exporter: https://github.com/OSC/ondemand_exporter
.. _ondemand_exporter Latest Release: https://github.com/OSC/ondemand_exporter/releases/latest
.. _Grafana Dashboard: https://grafana.com/grafana/dashboards/13465
.. _Process Exporter: https://github.com/ncabatoff/process-exporter

OnDemand provides the `ondemand_exporter`_ that allows for monitoring some metrics specific to OnDemand.

General metrics provided:

- Number of active PUNs and type of apps running
- Types of web connections for OnDemand
- Aggregate PUN resource consumption
- Passenger app resource consumption aggregated by app

Dependencies:

- OnDemand >= 1.8
- **RPM Installs** - ondemand-passenger >= 6.0.4-6

Install via RPM
--------------------------

For RHEL/CentOS 7 and RHEL/Rocky Linux 8 systems the `ondemand_exporter`_ can be installed via RPM.

.. code-block:: sh

   sudo yum install ondemand_exporter

The RPM will install the following files that should work out of the box:

- **RHEL/CentOS 7 only**: /opt/rh/httpd24/root/etc/httpd/conf.d/ondemand_exporter.conf
- **RHEL/Rocky Linux 8 only**: /etc/httpd/conf.d/ondemand_exporter.conf
- /etc/sudoers.d/ondemand_exporter

Ensure that the new Apache configuration is loaded by restarting Apache

RHEL/CentOS 7

 .. code-block:: sh

    sudo systemctl restart httpd24-httpd

RHEL/Rocky Linux 8

 .. code-block:: sh

    sudo systemctl restart httpd

Start the service

  .. code-block:: sh

     sudo systemctl start ondemand_exporter

Install from Source
--------------------

Check for the `ondemand_exporter Latest Release`_ version number.  Replace ``VERSION`` with latest release version

.. warning::

   If Passenger was not installed using ``ondemand-passenger`` RPM then it is required that before starting
   the ``ondemand_exporter`` daemon you must specify the path to ``passenger-status`` via the ``--path.passenger-status`` flag.

.. code-block:: sh

   VERSION="0.8.0"
   ARCHIVE="ondemand_exporter-${VERSION}.linux-amd64"
   wget -O /tmp/${ARCHIVE}.tar.gz https://github.com/OSC/ondemand_exporter/releases/download/v${VERSION}/${ARCHIVE}.tar.gz
   tar xf /tmp/${ARCHIVE}.tar.gz -C /tmp
   sudo install -o root -g root -m 0755 /tmp/${ARCHIVE}/ondemand_exporter /usr/bin/ondemand_exporter
   sudo install -o root -g root -m 0440 /tmp/${ARCHIVE}/files/sudo /etc/sudoers.d/ondemand_exporter
   sudo install -o root -g root -m 0644 /tmp/${ARCHIVE}/files/ondemand_exporter.service /etc/systemd/system/
   sudo systemctl daemon-reload

RHEL/CentOS 7

  .. code-block:: sh

     sudo install -o root -g root -m 0440 /tmp/${ARCHIVE}/files/apache.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ondemand_exporter.conf
     sudo systemctl restart httpd24-httpd

RHEL/Rocky Linux 8

  .. code-block:: sh

     sudo install -o root -g root -m 0440 /tmp/${ARCHIVE}/files/apache.conf /etc/httpd/conf.d/ondemand_exporter.conf
     sudo systemctl restart httpd

**(Optional)** If Passenger was not installed via ``ondemand-passenger`` RPM. Adjust the path to ``passenger-status`` as needed

  .. code-block:: sh

     sudo mkdir /etc/systemd/system/ondemand_exporter.service.d
     sudo cat > /etc/systemd/system/ondemand_exporter.service.d/passenger-status.conf <<'EOF'
     [Service]
     Environment="PASSENGER_STATUS=/usr/sbin/passenger-status"
     EOF

Start the service

  .. code-block:: sh

     sudo systemctl start ondemand_exporter


Test Prometheus Exporter
-------------------------

By default the exporter listens on port ``9301`` and can be tested using ``curl``.

.. code-block:: sh

   curl http://localhost:9301/metrics

Prometheus Configuration
-------------------------

The following is an example of how to configure the Prometheus scrape if the OnDemand host is ``web.example.com`` and the OnDemand ServerName is ``ondemand.example.com``.

.. code-block:: yaml

   - job_name: ondemand
     metrics_path: /metrics
     scrape_timeout: 20s
     scrape_interval: 2m
     static_configs:
     - targets:
       - web.example.com:9301
       labels:
         environment: production
         service: ondemand.example.com

Grafana Dashboard
------------------

An example `Grafana Dashboard`_ is available.

Process Exporter
-----------------

If you're site is using the `Process Exporter`_ with Prometheus the following is an example configuration that can be used to collect metrics similar to the `ondemand_exporter`_ about running processes for OnDemand.

.. code-block:: yaml

   process_names:
   - name: ood-pun
     comm:
     - nginx
     - Passenger
     - Passenger NodeA
     - PassengerAgent
     - ruby
   - name: "{%raw %}{{.Comm}}:{{.Username}}{% endraw %}"
     cmdline:
     - ".+"

The above example only makes sense on a host that is only running OnDemand and not other services that might also be using NGINX, Passenger or Ruby.
