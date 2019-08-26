.. _requirements:

Requirements
============

Software Requirements
---------------------

Web node:

- `epel-release`_
- `centos-release-scl`_
- `lsof`_
- `sudo`_
- `ondemand-release-web-latest-1-2.el7.noarch.rpm`_: the central OnDemand RPM
    - `Apache HTTP Server 2.4`_
    - `Git 2.9`_
    - `Node.js 6`_
    - `Ruby 2.4`_ with :command:`rake`, :command:`bundler`, and development libraries

.. _apache http server 2.4: https://www.softwarecollections.org/en/scls/rhscl/httpd24/
.. _centos-release-scl: https://www.softwarecollections.org/en/
.. _epel-release: https://fedoraproject.org/wiki/EPEL
.. _git 2.9: https://www.softwarecollections.org/en/scls/rhscl/rh-git29/
.. _lsof: https://en.wikipedia.org/wiki/Lsof
.. _node.js 6: https://www.softwarecollections.org/en/scls/rhscl/rh-nodejs6/
.. _ondemand-release-web-latest-1-2.el7.noarch.rpm: https://openondemand.org/
.. _ruby 2.4: https://www.softwarecollections.org/en/scls/rhscl/rh-ruby24/
.. _sudo: https://www.sudo.ws/

Compute node:

- `nmap-ncat`_
- `TurboVNC`_ 2.1+
- `websockify`_ 0.8.0+

.. _nmap-ncat: https://nmap.org/ncat/
.. _turbovnc: https://turbovnc.org/
.. _websockify: https://github.com/novnc/websockify

Hardware Requirements
---------------------

We have not yet quantified the minimum hardware requirements for OnDemand. At OSC our VMs that we run OnDemand on are over powered for our needs. We have 16 cores and 64GB RAM for OSC OnDemand which is overkill based on Ganglia usage. Our Ganglia graphs show we average 150MB memory per PUN and average CPU percentage per PUN is 4%. Our OnDemand instance serves over 600 unique users each month and at any given time we usually have 60-100 Per User NGINX (PUNs) processes running.

The Passenger apps that make up the core of OnDemand (that NGINX is configured with), are each killed after a short period (5 minutes) of inactivity from the user, and when users are using NoVNC or connecting to Jupyter Notebook or RStudio on a compute node, Apache is proxying these users, bypassing the PUN completely. So it can happen that 60 PUNs are running but twice the number of users are actually being served.

Another sizing factor that has impacted us in the past is the size of /tmp.  We’ve had in the past occasions where /tmp is exhausted and have had to increase the size from 20GB to 50GB.
