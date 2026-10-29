(app-development-interactive-setup-enable-reverse-proxy)=

# Enable Reverse Proxy

The [reverse proxy] will proxy a request to any specified host and port through
IP sockets. This can be used to connect to Jupyter notebook servers, RStudio
servers, VNC servers, and more! This is disabled by default as it can be a
security risk if not properly setup using a good `host_regex`.

You can read more about how this works in Open OnDemand under
{ref}`ood-portal-generator-configuration-configure-reverse-proxy`.

## Requirements

- a regular expression that best describes all the hosts that you would want a
  user to connect to through the proxy (e.g., `[\w.-]+\.osc\.edu`)

- confirm that if you run the command `hostname` from a compute node it will
  return a string that matches the above regular expression

  ```sh
  hostname
  # n0001.ten.osc.edu
  ```

  :::{note}
  If the {command}`hostname` command gives you a value that cannot be used
  to connect to the compute node from the OnDemand host, then you can
  override it in the cluster configuration with a {command}`bash` command that will
  work, e.g.:

  ```{code-block} yaml
  :emphasize-lines: 16,23

  # /etc/ood/config/clusters.d/cluster1.yml
  ---
  v2:
    metadata:
      title: "Cluster 1"
    login:
      host: "cluster1.my_center.edu"
    job:
      adapter: "..."
      ...
    batch_connect:
      basic:
        script_wrapper: |
          module purge
          %s
        set_host: "host=$(hostname -A | awk '{print $1}')"
      vnc:
        script_wrapper: |
          module purge
          # Add the TurboVNC installation directory to the PATH (note: this may be different on your system)
          export PATH="/opt/TurboVNC/bin:$PATH"
          export WEBSOCKIFY_CMD="/usr/local/websockify/run"
          %s
        set_host: "host=$(hostname -A | awk '{print $1}')"
  ```
  :::

## Steps to Enable in Apache

1. This requires modifying the YAML {ref}`portal configuration file <ood-portal-generator-configuration>`
   located at {file}`/etc/ood/config/ood_portal.yml` as such:

   ```{code-block} yaml
   :emphasize-lines: 3-

   # /etc/ood/config/ood_portal.yml
   ---
   host_regex: '[\w.-]+\.my_center\.edu'
   node_uri: '/node'
   rnode_uri: '/rnode'
   ```

   You can read more about these options under
   {ref}`ood-portal-generator-configuration-configure-reverse-proxy`.

   :::{tip}
   What if my site foregoes the FQDN in the host names for compute nodes, and
   we have compute names that give their hosts as:

   - `ab001` ... `ab100` (for the AB cluster)
   - `pn001` ... `pn500` (for the PN cluster)
   - `xy001` ... `xy125` (for the XY cluster)

   You could then use the following regular expression in your configuration
   file:

   ```yaml
   host_regex: '(ab|pn|xy)\d+'
   node_uri: '/node'
   rnode_uri: '/rnode'
   ```
   :::

   :::{warning}
   Do not add start (`^`, `A`) or end (`$`, `Z`) of string/line
   anchors as this regular expression will be inserted into another regular
   expression.
   :::

   :::{danger}
   Failing to add an appropriate regular expression to the Reverse Proxy
   opens you up to possible phishing attacks. As a malicious party could
   send links to unsuspecting users as:

   ```
   https://ondemand.my_center.edu/rnode/phishing.site.com/80/...
   ```

   And users will implicitly trust the link since it points to the trusting
   domain of `ondemand.my_center.edu`.
   :::

2. Build/install the updated Apache configuration file:

   ```sh
   sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal
   ```

3. {ref}`Restart the Apache service <restart-apache>` to have the changes take effect:

## Verify it Works

We can test that the reverse proxy is now functional by starting up a simple
server on a compute node and connecting to it through the proxy with our
browser.

1. SSH to any compute node that matches the regular expression above:

   ```sh
   ssh n0001.ten.osc.edu
   ```

2. Start up a very simple listening server on a high number port:

   ```sh
   nc -l 5432
   ```

3. In your browser navigate to this server using the Apache reverse proxy with
   the following URL format:

   ```
   http://ondemand.my_center.edu/node/<host>/<port>/...
   ```

   So for our simplified case lets use:

   ```
   http://ondemand.my_center.edu/node/n0001.ten.osc.edu/5432/
   ```

4. Go back to your SSH session and verify that it received the browser
   request:

   ```sh
   nc -l 5432
   # GET /node/n0691.ten.osc.edu/5432/ HTTP/1.1
   # Host: n0691.ten.osc.edu:5432
   # Upgrade-Insecure-Requests: 1
   ...
   ```

   :::{note}
   As we don't have the simple server return anything to the browser, you
   can ignore any errors or warnings you see in your browser.
   :::

[reverse proxy]: https://en.wikipedia.org/wiki/Reverse_proxy
