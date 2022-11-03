.. _requirements:

Requirements
============

Supported Operating Systems
---------------------------

.. _os-support:

At this time OnDemand only supports the following operating systems:

- RedHat/CentOS 7
- RedHat/Rocky Linux/AlmaLinux 8
- Ubuntu 18.04
- Ubuntu 20.04

Software Requirements
---------------------

On the Web node serving OnDemand itself:

- `Software Collections repositories`_
- `lsof`_
- `sudo`_
- `OnDemand repository`_:
    - ondemand-{{ondemand_version}}-1.el7.x86_64.rpm

.. _Software Collections repositories: https://www.softwarecollections.org/en/
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

Browser Requirements
--------------------

.. _browser-requirements:

.. warning::

    No IE 11 support. If you are a site that requires IE 11 support and are willing to contribute developer time to the project to support this, please reach out to us.

To have the best experience using OnDemand, use the latest versions of `Google Chrome`_, `Mozilla Firefox`_ or `Microsoft Edge`_.
Use any modern browser that supports ECMAScript 2016.

Google Chrome has the widest range of support since the :doc:`applications/shell` uses ``hterm.js`` which is supported officially by Google.
Chrome currently is the only web browser that natively supports the copy and paste functionality in ``noVNC``.
Other browsers can do copy and pasting manually through the ``noVNC`` tool drawer.

Sites have reported problems with Safari when using the :doc:`applications/shell` or ``noVNC``. Safari is also known to cause problems with WebSockets and Basic Auth.

.. _`Google Chrome`: https://www.google.com/chrome/
.. _`Mozilla Firefox`: https://www.mozilla.org/en-US/firefox/new/
.. _`Microsoft Edge`: https://www.microsoft.com/en-us/edge