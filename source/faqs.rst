.. _faq:

FAQ
==================

.. contents:: On this page
   :local:
   :depth: 2

Overview
--------

Who uses Open OnDemand?
^^^^^^^^^^^^^^^^^^^^^^^

Open OnDemand is currently used by thousands of institutions in academia and 
business in more than 100 countries `across the world <https://openondemand.org/#locations>`_.

OnDemand allows system administrators to quickly and easily connect many 
researchers to institutional compute resources and provides an accessible 
platform for researchers to run common software without computing expertise.

Who funds/supports OnDemand?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

While being open source and community supported, OnDemand has also been the 
recipient of over $10 million of `NSF grants <https://openondemand.org/about-us#our-history-vision>`_ that 
has enabled teams at OSC, MGHPCC, TAMU, and the University of Maryland to 
dedicate full time staff towards enhancing and maintaining the project.

How secure is OnDemand?
^^^^^^^^^^^^^^^^^^^^^^^

OnDemand integrates seamlessly with common institutional authorization methods 
and utilizes the security and permissions capability of the underlying operating 
system to manage user groups and levels of access. OnDemand is trusted and used 
by U.S. Federal agencies and cutting-edge technology enterprises alike, and we 
regularly test against known attacks, scan dependencies, and release security 
patches for all supported releases.

How are CVEs detected, handled, and reported to the community?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GitHub automatically scans our codebase and warns about potential 
risks, which are evaluated by our development team. Based on this evaluation 
we then make appropriate patches and publish the full report—detailing the 
issue, severity, versions affected, and what patches were made for which 
releases at the following URL:

- `Security advisories <https://github.com/OSC/ondemand/security/advisories?state=published>`_

Resources
---------

How do I start using OnDemand at my institution?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We publish and maintain our :ref:`installation guide <installation>`, which 
walks you through supported operating systems, required dependencies, and 
integration with authenticators and schedulers. Open OnDemand maintains RPM 
distributions to build the production instance and upgrading, so most of 
the setup work is integration with the institutional services you already 
use.

Will OnDemand be able to run my custom tools?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OnDemand is designed to be a platform for all varieties of HPC applications, 
seen in the wide variety of applications that users across the community have 
developed for their systems. Contained in the official OnDemand distribution 
are shell and desktop apps, giving you the same familiar access points to your 
HPC resources that your users are accustomed to. Many apps are run using 
Passenger, which supports Ruby on Rails, WSGI, and Node.js apps, in addition 
to “interactive apps,” which streamline the startup and access of software 
tools like MATLAB and Jupyter. Detailed instructions on app development—as 
well as tutorials for developing both Passenger and interactive apps—can be 
found in the :ref:`app development how-tos <app-development>`.

How customizable is OnDemand?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OnDemand is highly customizable, giving you full control over layout and 
appearance wherever possible. A detailed analysis of customizable features 
can be found in the :ref:`customizations overview <customizations>`.

Where do I go for help if I have problems with my OnDemand instance?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The first place to bring any issue you encounter with OnDemand is our community 
`Discourse <https://discourse.openondemand.org/>`_. The discourse connects you 
with a large OnDemand community that can give advice and share solutions to 
many common problems or questions. Our full-time developers are also very 
active on discourse, investigating problems and offering individualized 
solutions and expert advice. 

We also offer 
`Open OnDemand Office Hours <https://discourse.openondemand.org/t/open-ondemand-monthly-open-office-hours/1728>`_, 
a monthly virtual meeting with the OnDemand development team to help diagnose and solve persistent issues.

How many people are typically required to maintain an institutional instance? How does this scale?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Institutions typically find that OnDemand configuration and maintenance is easily handled by a 
single system administrator without significant impact on other duties they may have. While the 
initial setup can require some time and troubleshooting, future updates and continued maintenance are generally
light work. Scaling issues could arise if the login node hosting your OnDemand instance is overloaded, and may 
require moving the instance to a new machine or allocating more resources towards it.
