.. _nginx-stage-configuration:

Configuration
=============

Many of the options in the per-user NGINX staging and configuration can be
configured within :program:`nginx_stage`. In a default installation this
YAML configuration file is located at::

  /etc/ood/config/nginx_stage.yml

On a fresh installation you may need to create this file or copy the default
file from::

  /opt/ood/nginx_stage/share/nginx_stage_example.yml

In most cases it is recommended that you don't edit this file as the chosen
defaults should work out of the box for most scenarios.

.. warning::

   Modifying application specific configuration options or URI options can have
   unintended consequences for some of the Open OnDemand applications, so be
   sure you know what you are doing.

Configuration Options
---------------------

.. describe:: ondemand_version_path (String)

   path to the OnDemand version file

   Default
     Set to default path

     .. code-block:: yaml

        ondemand_version_path: "/opt/ood/VERSION"

   Example
     Supply a custom version file with a different version in it

     .. code-block:: yaml

        ondemand_version_path: "/path/to/VERSION"

.. describe:: ondemand_portal (String, null)

   unique name of this OnDemand portal used to namespace multiple hosted
   portals

   Default
     Do not set a custom namespace for this portal

     .. code-block:: yaml

        ondemand_portal: null

   Example
     Use a custom namespace for this portal

     .. code-block:: yaml

        ondemand_portal: "custom"

   .. note::

      If this is not set then most apps will use the default namespace
      ``ondemand``.

.. describe:: ondemand_title (String, null)

   title of this OnDemand portal that apps *should* display in their navbar

   Default
     Do not set a custom title for this portal

     .. code-block:: yaml

        ondemand_title: null

   Example
     Use a custom title for this portal

     .. code-block:: yaml

        ondemand_title: "My Custom Portal"

   .. note::

      If this is not set then most apps will use the default title ``Open
      OnDemand``.

.. describe:: template_root (String)

   the root directory containing the ERB templates used in generating the NGINX
   configuration files

   Default
     Set to default installation location

     .. code-block:: yaml

        template_root: "/opt/ood/nginx_stage/templates"

   Example
     Use custom templates

     .. code-block:: yaml

        template_root: "/path/to/my/templates"

.. describe:: proxy_user (String)

   the user name that the Apache proxy runs as so permissions can be added to
   the Unix domain sockets

   Default
     Set to the typical apache user

     .. code-block:: yaml

        proxy_user: "apache"

   Example
     Use a different user for the Apache proxy

     .. code-block:: yaml

        proxy_user: "proxy_user"

.. describe:: nginx_bin (String)

   the path to the NGINX binary

   Default
     Use NGINX installed by OnDemand Software Collections

     .. code-block:: yaml

        nginx_bin: "/opt/ood/ondemand/root/usr/sbin/nginx"

   Example
     NGINX is installed in a different directory

     .. code-block:: yaml

        nginx_bin: "/path/to/sbin/nginx"

.. describe:: nginx_signals (Array<String>)

   valid signals that can be sent to the NGINX process

   Default
     Supported NGINX signals

     .. code-block:: yaml

        nginx_signals: [stop, quit, reopen, reload]

   Example
     Further restrict valid signals

     .. code-block:: yaml

        nginx_signals: [stop]

   .. note::

      This option is sent as ``-s signal`` to the `NGINX command line`_.

.. describe:: mime_types_path (String)

   the path to the system-installed NGINX ``mime.types`` file

   Default
     Use the NGINX installed by OnDemand Software Collections file

     .. code-block:: yaml

        mime_types_path: "/opt/ood/ondemand/root/etc/nginx/mime.types"

   Example
     Use a custom mime file

     .. code-block:: yaml

        mime_types_path: "/path/to/custom/mime.types"

.. describe:: passenger_root (String)

   the ``locations.ini`` file that describes Passenger installation

   Default
     Use the file supplied by Passenger from OnDemand Software Collections

     .. code-block:: yaml

        passenger_root: "/opt/ood/ondemand/root/usr/share/ruby/vendor_ruby/phusion_passenger/locations.ini"

   Example
     Use a custom file

     .. code-block:: yaml

        passenger_root: "/path/to/custom/locations.ini"

.. describe:: passenger_ruby (String)

   the path to the Ruby binary that Passenger uses for itself and web apps

   Default
     Use the Ruby wrapper script supplied by this code

     .. code-block:: yaml

        passenger_ruby: "/opt/ood/nginx_stage/bin/ruby"

   Example
     Use the binary supplied by Ruby 2.4 installed by Software Collections

     .. code-block:: yaml

        passenger_ruby: "/opt/rh/rh-ruby25/root/usr/bin/ruby"

.. describe:: passenger_nodejs (String, null)

   the path to the Node.js binary that Passenger uses for web apps

   Default
     Use the Node.js wrapper script supplied by this code

     .. code-block:: yaml

        passenger_nodejs: "/opt/ood/nginx_stage/bin/node"

   Example
     Use the binary supplied by Node.js installed by Software Collections

     .. code-block:: yaml

        passenger_nodejs: "/opt/rh/rh-nodejs6/root/usr/bin/node"

.. describe:: passenger_python (String, null)

   the path to the Python binary that Passenger uses for web apps

   Default
     Use the Python wrapper script supplied by this code

     .. code-block:: yaml

        passenger_python: "/opt/ood/nginx_stage/bin/python"

   Example
     Use the system-installed Python binary

     .. code-block:: yaml

        passenger_python: "/usr/bin/python"

.. describe:: pun_config_path (String)

   the interpolated path to the user's PUN config file

   Default
     Namespace the user config files by their user name

     .. code-block:: yaml

        pun_config_path: "/var/lib/ondemand-nginx/config/puns/%{user}.conf"

   Example
     Namespace configs under user directories

     .. code-block:: yaml

        pun_config_path: "/var/lib/ondemand-nginx/config/puns/%{user}/nginx.conf"

.. describe:: pun_tmp_root (String)

   the interpolated root directory used for NGINX tmp directories

   Default
     Namespace under user directories

     .. code-block:: yaml

        pun_tmp_root: "/var/lib/ondemand-nginx/tmp/%{user}"

   Example
     Use a custom namespace for root directory

     .. code-block:: yaml

        pun_tmp_root: "/path/to/%{user}-tmp"

   .. warning::

      NGINX will store the full request body in this location before sending it
      to the Passenger app. The size of the disk partition this directory
      resides in will limit the maximum file upload size.

.. describe:: pun_access_log_path (String)

   the interpolated path to the NGINX access log

   Default
     Namespace access logs under user directories

     .. code-block:: yaml

        pun_access_log_path: "/var/log/ondemand-nginx/%{user}/access.log"

   Example
     Use a custom location for the access log file

     .. code-block:: yaml

        pun_access_log_path: "/custom/path/access-%{user}.log"

.. describe:: pun_error_log_path (String)

   the interpolated path to the NGINX error log

   Default
     Namespace error logs under user directories

     .. code-block:: yaml

        pun_error_log_path: "/var/log/ondemand-nginx/%{user}/error.log"

   Example
     Use a custom location for the error log file

     .. code-block:: yaml

        pun_error_log_path: "/custom/path/error-%{user}.log"

.. describe:: pun_pid_path (String)

   the interpolated path to the NGINX pid file

   Default
     Namespace pid files under user directories

     .. code-block:: yaml

        pun_pid_path: "/var/run/ondemand-nginx/%{user}/passenger.pid"

   Example
     Use a custom location for the pid files

     .. code-block:: yaml

        pun_pid_path: "/custom/path/pid-%{user}.pid"

.. describe:: pun_socket_path (String)

   the interpolated path to the NGINX socket file

   Default
     Namespace socket files under user directories

     .. code-block:: yaml

        pun_pid_path: "/var/run/ondemand-nginx/%{user}/passenger.sock"

   Example
     Use a custom location for the socket files

     .. code-block:: yaml

        pun_pid_path: "/custom/path/socket-%{user}.sock"

   .. warning::

      The root directory containing the Unix domain socket file will have
      restricted permissions so that only the Apache proxy user can access this
      socket file.

   .. danger::

      Currently :ref:`mod-ood-proxy` will only look for socket files following the
      format::

        $OOD_PUN_SOCKET_ROOT/<user>/passenger.sock

      It is not recommended to alter ``pun_pid_path`` unless you know what you
      are doing.

.. describe:: pun_sendfile_root (String)

   the root directory that NGINX serves files from using sendfile_

   Default
     Serve all files on file system

     .. code-block:: yaml

        pun_sendfile_root: "/"

   Example
     Only serve files under home directories

     .. code-block:: yaml

        pun_sendfile_root: "/home"

   .. warning::

      All URL requests to sendfile_ will be relative to the
      ``pun_sendfile_root``. If you alter this configuration option you may
      break certain web applications that expect it under ``/``.

.. describe:: pun_sendfile_uri (String)

   the internal URL path used by NGINX to serve files from using sendfile_ (not
   directly accessible by the client browser)

   Default
     Serve files under a unique path

     .. code-block:: yaml

        pun_sendfile_uri: "/sendfile"

   Example
     Server files under a custom URL path

     .. code-block:: yaml

        pun_sendfile_root: "/custom/files"

.. describe:: pun_app_configs (Array<Hash>)

   a list of interpolated hashes that define what wildcard app config file
   paths to include in a user's NGINX config (the hashes are arguments for
   ``app_config_path``)

   Default
     Serve a user's dev apps, all shared apps, all system apps through NGINX

     .. code-block:: yaml

        pun_app_configs:
          -
            env: dev
            name: "*"
            owner: "%{user}"
          -
            env: usr
            name: "*"
            owner: "*"
          -
            env: sys
            name: "*"
            owner: "*"

   Example
     Serve only system apps through NGINX

     .. code-block:: yaml

        pun_app_configs:
          -
            env: dev
            name: "*"
            owner: "%{user}"

.. describe:: app_config_path (Hash)

   an interpolated hash detailing the path to the NGINX app configs for each
   app type

   Default
     A recommended solution for app config locations

     .. code-block:: yaml

        app_config_path:
          dev: "/var/lib/ondemand-nginx/config/apps/dev/%{owner}/%{name}.conf"
          usr: "/var/lib/ondemand-nginx/config/apps/usr/%{owner}/%{name}.conf"
          sys: "/var/lib/ondemand-nginx/config/apps/sys/%{name}.conf"

.. describe:: app_root (Hash)

   an interpolated hash detailing the root directory where the app is installed
   for each app type

   Default
     A recommended solution for app deployment locations

     .. code-block:: yaml

        app_root:
          dev: "~%{owner}/ondemand/dev/%{name}"
          usr: "/var/www/ood/apps/usr/%{owner}/gateway/%{name}"
          sys: "/var/www/ood/apps/sys/%{name}"

   .. note::

      A common solution is to map the user shared app location as a symlink to
      the user's home directory::

        /var/www/ood/apps/usr/<owner>/gateway => ~<owner>/ondemand/share

      This allows the owner of the app to update the app in real time as well
      as maintain file permissions.

   .. warning::

      Modifying this configuration option may break how the Dashboard app
      searches for apps.

.. describe:: app_request_uri (Hash)

   an interpolated hash detailing the URL path used to access the given type of
   app (not including the base-URI)

   Default
     A recommended solution for app request URL's

     .. code-block:: yaml

        app_request_uri:
          dev: "/dev/%{name}"
          usr: "/usr/%{owner}/%{name}"
          sys: "/sys/%{name}"

   .. note::

      Modifying this will require you also modify ``app_request_regex``.

   .. warning::

      Modifying this configuration option may break how the various apps link
      to each other.

.. describe:: app_request_regex (Hash)

   a hash detailing the regular expressions used to determine the type of app
   and its corresponding parameters from a URL request (this should match what
   you used in ``app_request_uri``)

   Default
     A recommended solution for app request URL regular expressions

     .. code-block:: yaml

        app_request_regex:
          dev: "^/dev/(?<name>[-\\w.]+)"
          usr: "^/usr/(?<owner>[\\w]+)/(?<name>[-\\w.]+)"
          sys: "^/sys/(?<name>[-\\w.]+)"

   .. note::

      Modifying anything in this configuration option other than the
      whitelisted characters will require you modify ``app_request_uri`` as
      well.

.. describe:: app_token (Hash)

   an interpolated hash detailing a uniquely identifiable string for each app

   Default
     A recommended solution for generating app tokens

     .. code-block:: yaml

        app_token:
          dev: "dev/%{owner}/%{name}"
          usr: "usr/%{owner}/%{name}"
          sys: "sys/%{name}"

   .. note::

      Not currently used and may be deprecated in the future.

.. describe:: app_passenger_env (Hash)

   a hash detailing the `Passenger environment`_ to run the type of app under

   Default
     A recommended solution for setting Passenger environments

     .. code-block:: yaml

        app_passenger_env:
          dev: "development"
          usr: "production"
          sys: "production"

   .. warning::

      Modifying this configuration option can lead to unintended consequences
      for web apps such as issues with serving their assets.

.. describe:: user_regex (String)

   regular expression used to validate a given user name

   Default
     Username can consist of any characters typically found in an email address

     .. code-block:: yaml

        user_regex: '[\w@\.\-]+'

   Example
     Restrict user name to just alphanumeric characters

     .. code-block:: yaml

        user_regex: '\w+'

.. describe:: min_uid (Integer)

   the minimum user id required to start a per-user NGINX process as

   Default
     User id's typically start at ``1000``

     .. code-block:: yaml

        min_uid: 1000

   Example
     Using CentOS 6

     .. code-block:: yaml

        min_uid: 500

   .. note::

      For RHEL6 and CentOS 6 the user id's begin at ``500``.

.. describe:: disabled_shell (String)

   restrict starting a per-user NGINX process as a user with the given shell

   Default
     For OSC restrictions

     .. code-block:: yaml

        disabled_shell: "/access/denied"

   .. note::

      This will only restrict access to a per-user NGINX process started with
      the :ref:`nginx-stage-pun` command (used by the Apache proxy). This
      doesn't restrict the other administrative commands
      :ref:`nginx-stage-nginx` and :ref:`nginx-stage-nginx-clean` when manually
      starting and stopping the NGINX process.

.. _nginx command line: https://www.nginx.com/resources/wiki/start/topics/tutorials/commandline/
.. _sendfile: http://nginx.org/en/docs/http/ngx_http_core_module.html#sendfile
.. _passenger environment: https://www.phusionpassenger.com/library/config/nginx/reference/#passenger_app_env
