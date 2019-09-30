.. _requirements:

Requirements
============

Software Requirements
---------------------

On the Web node serving OnDemand itself:

- `epel-release`_
- `centos-release-scl`_
- `lsof`_
- `sudo`_
- `ondemand-release-web-latest-1-5.noarch.rpm`_:
    - cjose-0.6.1-1.el7.x86_64.rpm
    - cjose-debuginfo-0.6.1-1.el7.x86_64.rpm
    - cjose-devel-0.6.1-1.el7.x86_64.rpm
    - httpd24-mod_auth_openidc-2.3.11-1.el7.x86_64.rpm
    - httpd24-mod_auth_openidc-debuginfo-2.3.11-1.el7.x86_64.rpm
    - ondemand-apache-{{ondemand_version}}-1.el7.x86_64.rpm
    - ondemand-git-{{ondemand_version}}-1.el7.x86_64.rpm
    - ondemand-nginx-1.14.0-2.p5.3.7.el7.x86_64.rpm
    - ondemand-nginx-debuginfo-1.14.0-2.p5.3.7.el7.x86_64.rpm
    - ondemand-nginx-filesystem-1.14.0-2.p5.3.7.el7.noarch.rpm
    - ondemand-nodejs-{{ondemand_version}}-1.el7.x86_64.rpm
    - ondemand-passenger-5.3.7-2.el7.x86_64.rpm
    - ondemand-passenger-debuginfo-5.3.7-2.el7.x86_64.rpm
    - ondemand-passenger-devel-5.3.7-2.el7.x86_64.rpm
    - ondemand-ruby-{{ondemand_version}}-1.el7.x86_64.rpm
    - ondemand-runtime-{{ondemand_version}}-1.el7.x86_64.rpm
    - ondemand-scldevel-{{ondemand_version}}-1.el7.x86_64.rpm

.. _centos-release-scl: https://www.softwarecollections.org/en/
.. _epel-release: https://fedoraproject.org/wiki/EPEL
.. _lsof: https://en.wikipedia.org/wiki/Lsof
.. _ondemand-release-web-latest-1-5.noarch.rpm: https://openondemand.org/
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

Hardware Requirements
---------------------

At `OSC`_ we have not quantified the minimum hardware requirements for OnDemand. The VMs that run OnDemand have 16 cores and 64GB RAM. According to our Ganglia metrics that is over powered for our normal utilization. We average 150MB memory per PUN and the average CPU percentage per Per User NGINX (PUN) is 4%. Our OnDemand instance serves over 600 unique users each month and at any given time usually has 60-100 PUN processes running.

The Passenger apps that make up the core of OnDemand (that NGINX is configured with), are each killed after a short period (5 minutes) of inactivity from the user, and when users are using NoVNC or connecting to Jupyter Notebook or RStudio on a compute node, Apache is proxying these users, bypassing the PUN completely. So it can happen that 60 PUNs are running but twice the number of users are actually being served.

Another sizing factor that has impacted us in the past is the size of the ``/tmp`` partition.  We have had incidents where ``/tmp`` is exhausted and so have increased the size from 20GB to 50GB.

.. _OSC: https://osc.edu