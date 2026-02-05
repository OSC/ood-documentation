.. _requirements:

Requirements
============

Supported Operating Systems
---------------------------

.. _os-support:

At this time OnDemand only supports the following operating systems and architectures:

.. role::  raw-html(raw)
    :format: html

.. csv-table:: Operating System and Architecture Support
   :header: "","``x86_64``","``aarch64/arm64``","``ppc64le``"
   :stub-columns: 1

   "RedHat/Rocky Linux/AlmaLinux 8",:raw-html:`&#9989;`,:raw-html:`&#9989;`,:raw-html:`&#9989;`
   "RedHat/Rocky Linux/AlmaLinux 9",:raw-html:`&#9989;`,:raw-html:`&#9989;`,:raw-html:`&#9989;`
   "RedHat/Rocky Linux/AlmaLinux 10",:raw-html:`&#9989;`,:raw-html:`&#10067;`,:raw-html:`&#9989;`
   "Ubuntu 22.04",:raw-html:`&#9989;`,:raw-html:`&#9989;`,:raw-html:`&#10060;`
   "Ubuntu 24.04",:raw-html:`&#9989;`,:raw-html:`&#9989;`,:raw-html:`&#10060;`
   "Debian 12",:raw-html:`&#9989;`,:raw-html:`&#9989;`,:raw-html:`&#10060;`
   "Amazon Linux 2023",:raw-html:`&#9989;`,:raw-html:`&#10067;`,:raw-html:`&#10060;`

.. note::

    Items marked with :raw-html:`&#10067;` are available upon request.
    Open a `Github Issue <https://github.com/OSC/ondemand/issues>`_ or post the request on `Discourse <https://discourse.openondemand.org/>`_

Software Requirements
---------------------

On the Web node serving OnDemand itself:

- `lsof`_
- `sudo`_
- `OnDemand repository`_:
    - ``ondemand-{{ondemand_version}}-1.el9.x86_64.rpm``

.. _lsof: https://en.wikipedia.org/wiki/Lsof
.. _OnDemand repository: https://openondemand.org/
.. _sudo: https://www.sudo.ws/

And on the Compute node(s):

.. note::

    The following are required for using OnDemand with interactive applications such as desktop environments, Jupyter Notebooks and RStudio. If you do not intend to install interactive applications then these are not necessary.

- `nmap-ncat`_
- `TurboVNC`_ 2.1+
- `websockify`_ 0.8.0+

.. _nmap-ncat: https://nmap.org/ncat/
.. _turbovnc: https://turbovnc.org/
.. _websockify: https://github.com/novnc/websockify

Software Bill of Materials
-------------------------
A complete and up to date Software Bill of Materials (SBOM) for OnDemand can be found at `SBOM for OnDemand <https://osc.github.io/ondemand-sbom/>`_.

.. tabs::

    .. tab:: RockyLinux 8

        .. code-block:: sh

            sh
            cronie
            curl
            diffutils
            file
            git
            libxml2
            libxslt
            lsof
            lua-posix
            make
            ondemand-apache = 4.0.3-1.el8
            ondemand-gems-4.0.0-1
            ondemand-gems-4.0.1-1
            ondemand-gems-4.0.2-1
            ondemand-gems-4.0.3-1
            ondemand-gems-4.0.5-1
            ondemand-gems-4.0.6-1
            ondemand-gems-4.0.7-1
            ondemand-gems-4.0.8-1
            ondemand-nginx = 1.26.1-1.p6.0.23.ood4.0.3.el8
            ondemand-nginx = 1.26.1-2.p6.0.23.ood4.0.3.el8
            ondemand-nginx = 1.26.1-3.p6.0.23.ood4.0.3.el8
            ondemand-nodejs = 4.0.3-1.el8
            ondemand-passenger = 6.0.23-1.ood4.0.3.el8
            ondemand-passenger = 6.0.23-2.ood4.0.3.el8
            ondemand-passenger = 6.0.23-3.ood4.0.3.el8
            ondemand-ruby = 4.0.3-1.el8
            ondemand-runtime = 4.0.3-1.el8
            python3
            rclone
            rsync
            sudo
            systemd
            wget
            zlib


    .. tab:: RockyLinux 9

        .. code-block:: sh

            sh
            cronie
            curl
            diffutils
            file
            git
            libxml2
            libxslt
            lsof
            lua-posix
            make
            ondemand-apache = 4.0.3-1.el9
            ondemand-gems-4.0.0-1
            ondemand-gems-4.0.1-1
            ondemand-gems-4.0.2-1
            ondemand-gems-4.0.3-1
            ondemand-gems-4.0.5-1
            ondemand-gems-4.0.6-1
            ondemand-gems-4.0.7-1
            ondemand-gems-4.0.8-1
            ondemand-nginx = 1.26.1-1.p6.0.23.ood4.0.3.el9
            ondemand-nginx = 1.26.1-2.p6.0.23.ood4.0.3.el9
            ondemand-nginx = 1.26.1-3.p6.0.23.ood4.0.3.el9
            ondemand-nodejs = 4.0.3-1.el9
            ondemand-passenger = 6.0.23-1.ood4.0.3.el9
            ondemand-passenger = 6.0.23-2.ood4.0.3.el9
            ondemand-passenger = 6.0.23-3.ood4.0.3.el9
            ondemand-ruby = 4.0.3-1.el9
            ondemand-runtime = 4.0.3-1.el9
            python3
            rclone
            rsync
            sudo
            systemd
            wget
            zlib

    .. tab:: Ubuntu 20.04

        .. code-block:: sh

            libc6 (>= 2.29)
            libgcc-s1 (>= 3.0)
            libruby2.7 (>= 2.7.0)
            libsqlite3-0 (>= 3.7.10)
            libstdc++6 (>= 9)
            ruby  
            apache2  
            sudo  
            lsof  
            lua-posix  
            tzdata  
            file  
            nodejs (>= 20.0)
            nodejs (<< 21.0)
            ondemand-nginx (>= 1.26.1.p6.0.23.ood4.0.3)
            ondemand-nginx (<< 1.27)
            ondemand-passenger (>= 6.0.23.ood4.0.3)
            ondemand-passenger (<< 6.0.24)

    .. tab:: Ubuntu 22.04

        .. code-block:: sh

            libc6 (>= 2.34)
            libgcc-s1 (>= 3.0)
            libruby3.0 (>= 3.0.0~preview2)
            libsqlite3-0 (>= 3.7.10)
            libstdc++6 (>= 11)
            ruby  
            apache2  
            sudo  
            lsof  
            lua-posix  
            tzdata  
            file  
            nodejs (>= 20.0)
            nodejs (<< 21.0)
            ondemand-nginx (>= 1.26.1.p6.0.23.ood4.0.3)
            ondemand-nginx (<< 1.27)
            ondemand-passenger (>= 6.0.23.ood4.0.3)
            ondemand-passenger (<< 6.0.24)

    .. tab:: Ubuntu 24.04

        .. code-block:: sh

            libc6 (>= 2.38)
            libgcc-s1 (>= 3.0)
            libruby3.2 (>= 3.2.2)
            libsqlite3-0 (>= 3.7.10)
            libstdc++6 (>= 13.1)
            ruby  
            apache2  
            sudo  
            lsof  
            lua-posix  
            tzdata  
            file  
            nodejs (>= 20.0)
            nodejs (<< 21.0)
            ondemand-nginx (>= 1.26.1.p6.0.23.ood4.0.3)
            ondemand-nginx (<< 1.27)
            ondemand-passenger (>= 6.0.23.ood4.0.3)
            ondemand-passenger (<< 6.0.24)

Along with the listed operating system dependencies, Open OnDemand also requires various Ruby gems and Node.js packages for its application layer. 
These application dependencies are managed by Bundler and Yarn respectively, and are installed automatically when Open OnDemand is built from source or 
installed via the provided packages. For a complete list of application dependencies, please refer to the top-level `Gemfile`_, the dashboard `Gemfile.lock`_, 
and `package.json`_ files in the Open OnDemand source repository.

.. _Gemfile: https://github.com/OSC/ondemand/blob/master/Gemfile
.. _Gemfile.lock: https://github.com/OSC/ondemand/blob/master/apps/dashboard/Gemfile.lock
.. _package.json: https://github.com/OSC/ondemand/blob/master/apps/dashboard/package.json

Hardware Requirements
---------------------

At `OSC`_ we have not quantified the minimum hardware requirements for OnDemand. The VMs that run OnDemand have 16 cores and 64GB RAM. According to our Ganglia metrics that is over powered for our normal utilization. We average 150MB memory per PUN and the average CPU percentage per Per User NGINX (PUN) is 4%. Our OnDemand instance serves over 600 unique users each month and at any given time usually has 60-100 PUN processes running.

The Passenger apps that make up the core of OnDemand (that NGINX is configured with), are each killed after a short period (5 minutes) of inactivity from the user, and when users are using NoVNC or connecting to Jupyter Notebook or RStudio on a compute node, Apache proxies these users, bypassing the PUN completely. So it can happen that 60 PUNs are running but twice the number of users are actually being served.

Another sizing factor that has impacted us in the past is the size of the ``/tmp`` partition.  We have had incidents where ``/tmp`` is exhausted and so have increased the size from 20GB to 50GB.

.. _OSC: https://osc.edu

Browser Requirements
--------------------

.. _browser-requirements:

.. warning::

    No IE 11 support. If you are a site that requires IE 11 support and are willing to contribute developer time to the project to support this, please reach out to us.

To have the best experience using OnDemand, use the latest versions of `Google Chrome`_, `Mozilla Firefox`_ or `Microsoft Edge`_.
Use any modern browser that supports ECMAScript 2016.

Google Chrome has the widest range of support since the shell application uses ``hterm.js`` which is supported officially by Google.
Chrome currently is the only web browser that natively supports the copy and paste functionality in ``noVNC``.
Other browsers can do copy and pasting manually through the ``noVNC`` tool drawer.

Sites have reported problems with Safari when using the shell application or ``noVNC``. Safari is also known to cause problems with WebSockets and Basic Auth.

.. _`Google Chrome`: https://www.google.com/chrome/
.. _`Mozilla Firefox`: https://www.mozilla.org/en-US/firefox/new/
.. _`Microsoft Edge`: https://www.microsoft.com/en-us/edge
