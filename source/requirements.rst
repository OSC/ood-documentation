.. _requirements:

Requirements
============

Software Requirements
---------------------

Web node:

#. TODO

Compute node:

#. TODO

Hardware Requirements
---------------------

We haven’t yet quantified the requirements for OnDemand. At OSC our VMs that we run OnDemand on are over powered for our needs. We have 16 cores and 64GB RAM for OSC OnDemand which is overkill based on Ganglia usage. Our Ganglia graphs show we average 150MB memory per PUN and average CPU percentage per PUN is 4%. Our OnDemand instance serves over 600 unique users each month and at any given time we usually have 60-100 Per User NGINX (PUNs) processes running.

The Passenger apps that make up the core of OnDemand (that NGINX is configured with), are each killed after a short period (5 minutes) of inactivity from the user, and when users are using NoVNC or connecting to Jupyter Notebook or RStudio on a compute node, Apache is proxying these users, bypassing the PUN completely. So it can happen that 60 PUNs are running but twice the number of users are actually being served.

Another sizing factor that has impacted us in the past is the size of /tmp.  We’ve had in the past occasions where /tmp is exhausted and have had to increase the size from 20GB to 50GB.
