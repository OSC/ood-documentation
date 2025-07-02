.. _authentication:

Authentication
==============

Open OnDemand supports most authentication modules that work with Apache HTTP
Server version 2.4. The following :ref:`authentication-overview` section
provides an introduction to setting up these generic authentication modules
with an Open OnDemand installation.

.. tip::

    :ref:`Dex <authentication-dex>` is a very good starting option if you can connect
    to LDAP or Active Directory and not an institutional Single Sign-On service.


After installing Open OnDemand **you must configure OOD to work with an apache module** 
which will connect to your center's authentication solution
to generate the correct Apache configuration. Also, **you must setup user mapping**  
to map the remote authenticated user to the corresponding local system user for OOD 
to work.

When no authentication is supplied Apache will only serve a static page that 
directs you to this page.

.. warning::
   No Open OnDemand functionality is available without an Apache module and user mapping 
   configured.

.. toctree::
   :maxdepth: 4
   :caption: How OOD Authentication Works

   authentication/overview


Authentication Solutions
------------------------
After reading how Apache modules integrate with OOD and setting up the user map, 
Open OnDemand can then be integrated with your center's authentication solution 
by following one of the tutorials below.

.. note::

   If you managed to install an Apache authentication module at your center
   that currently does not have a tutorial listed below we would greatly
   appreciate it if you could take the time to contribute a detailed
   walk-through.

.. toctree::
   :maxdepth: 4
   :caption: Known OOD Integrated Solutions

   authentication/oidc
   authentication/dex
   authentication/shibboleth
   authentication/cas
   authentication/tutorial-oidc-keycloak-rhel7
   authentication/duo-2fa-with-keycloak
   authentication/adfs-with-auth-mellon
   authentication/nsf-access
   authentication/insecure
