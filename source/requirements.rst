.. _requirements:

Requirements
============

Software Requirements
---------------------

On the Web node serving OnDemand itself:

- `EPEL repository`_
- `Software Collections repositories`_
- `lsof`_
- `sudo`_
- `OnDemand repository`_:
    - ondemand-{{ondemand_version}}-1.el7.x86_64.rpm
.. _Software Collections repositories: https://www.softwarecollections.org/en/
.. _EPEL repository: https://fedoraproject.org/wiki/EPEL
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

Hardware Requirements
---------------------

At `OSC`_ we have not quantified the minimum hardware requirements for OnDemand. The VMs that run OnDemand have 16 cores and 64GB RAM. According to our Ganglia metrics that is over powered for our normal utilization. We average 150MB memory per PUN and the average CPU percentage per Per User NGINX (PUN) is 4%. Our OnDemand instance serves over 600 unique users each month and at any given time usually has 60-100 PUN processes running.

The Passenger apps that make up the core of OnDemand (that NGINX is configured with), are each killed after a short period (5 minutes) of inactivity from the user, and when users are using NoVNC or connecting to Jupyter Notebook or RStudio on a compute node, Apache is proxying these users, bypassing the PUN completely. So it can happen that 60 PUNs are running but twice the number of users are actually being served.

Another sizing factor that has impacted us in the past is the size of the ``/tmp`` partition.  We have had incidents where ``/tmp`` is exhausted and so have increased the size from 20GB to 50GB.

.. _OSC: https://osc.edu