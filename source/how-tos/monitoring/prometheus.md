(prometheus)=

# Prometheus Monitoring

OnDemand provides the [ondemand_exporter] that allows for monitoring some metrics specific to OnDemand.

General metrics provided:

- Number of active PUNs and type of apps running
- Types of web connections for OnDemand
- Aggregate PUN resource consumption
- Passenger app resource consumption aggregated by app

Dependencies:

- OnDemand >= 1.8
- **RPM Installs** - ondemand-passenger >= 6.0.4-6

## Install via RPM

For `yum` or `dnf` based systems the [ondemand_exporter] can be installed via RPM.

```sh
sudo yum install ondemand_exporter
```

The RPM will install the following files that should work out of the box:

- **RHEL/Rocky/AlmaLinux 8 & 9 only**: `/etc/httpd/conf.d/ondemand_exporter.conf`
- `/etc/sudoers.d/ondemand_exporter`

Ensure that the new Apache configuration is loaded by restarting Apache

```{eval-rst}
.. tabs::

   .. tab:: RHEL/Rocky/Alma Linux 8 & 9

      .. code-block:: sh

         sudo systemctl restart httpd
```

Start the service

> ```sh
> sudo systemctl start ondemand_exporter
> ```

## Install from Source

Check for the [ondemand_exporter Latest Release] version number. Replace `VERSION` with latest release version

:::{warning}
If Passenger was not installed using `ondemand-passenger` RPM then it is required that before starting
the `ondemand_exporter` daemon you must specify the path to `passenger-status` via the `--path.passenger-status` flag.
:::

```sh
VERSION="0.10.0"
ARCHIVE="ondemand_exporter-${VERSION}.linux-amd64"
wget -O /tmp/${ARCHIVE}.tar.gz https://github.com/OSC/ondemand_exporter/releases/download/v${VERSION}/${ARCHIVE}.tar.gz
tar xf /tmp/${ARCHIVE}.tar.gz -C /tmp
sudo install -o root -g root -m 0755 /tmp/${ARCHIVE}/ondemand_exporter /usr/bin/ondemand_exporter
sudo install -o root -g root -m 0440 /tmp/${ARCHIVE}/files/sudo /etc/sudoers.d/ondemand_exporter
sudo install -o root -g root -m 0644 /tmp/${ARCHIVE}/files/ondemand_exporter.service /etc/systemd/system/
sudo systemctl daemon-reload
```

```{eval-rst}
.. tabs::

   .. tab:: RHEL/Rocky/Alma Linux 8 & 9

      .. code-block:: sh

         sudo install -o root -g root -m 0440 /tmp/${ARCHIVE}/files/apache.conf /etc/httpd/conf.d/ondemand_exporter.conf
         sudo systemctl restart httpd
```

**(Optional)** If Passenger was not installed via `ondemand-passenger` RPM. Adjust the path to `passenger-status` as needed

> ```sh
> sudo mkdir /etc/systemd/system/ondemand_exporter.service.d
> sudo cat > /etc/systemd/system/ondemand_exporter.service.d/passenger-status.conf <<'EOF'
> [Service]
> Environment="PASSENGER_STATUS=/usr/sbin/passenger-status"
> EOF
> sudo systemctl daemon-reload
> ```

Start the service

> ```sh
> sudo systemctl start ondemand_exporter
> ```

## Test Prometheus Exporter

By default the exporter listens on port `9301` and can be tested using `curl`.

```sh
curl http://localhost:9301/metrics
```

## Prometheus Configuration

The following is an example of how to configure the Prometheus scrape if the OnDemand host is `web.example.com` and the OnDemand ServerName is `ondemand.example.com`.

```yaml
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
```

## Grafana Dashboard

An example [Grafana Dashboard] is available.

## Process Exporter

If you're site is using the [Process Exporter] with Prometheus the following is an example configuration that can be used to collect metrics similar to the [ondemand_exporter] about running processes for OnDemand.

```yaml
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
```

The above example only makes sense on a host that is only running OnDemand and not other services that might also be using NGINX, Passenger or Ruby.

[grafana dashboard]: https://grafana.com/grafana/dashboards/13465
[ondemand_exporter]: https://github.com/OSC/ondemand_exporter
[ondemand_exporter latest release]: https://github.com/OSC/ondemand_exporter/releases/latest
[process exporter]: https://github.com/ncabatoff/process-exporter
