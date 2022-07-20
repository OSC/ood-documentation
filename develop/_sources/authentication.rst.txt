.. _authentication:

Authentication
==============

Open OnDemand supports most authentication modules that work with Apache HTTP
Server version 2.4. The following :ref:`authentication-overview` section
provides an introduction to setting up these generic authentication modules
with an Open OnDemand installation. Tutorials will also be provided with the
focus on setting up some of the more common authentication modules (e.g.,
OpenID Connect with KeyCloak).

After installing Open OnDemand you **must** add authentiction of some kind
to generate the correct apache configuration.  When no authentiction is
supplied Apache will only serve a static page that directs you here.

No Open OnDemand functionality is available without authentiction.

.. note::

   If you managed to install an Apache authentication module at your center
   that currently does not have a tutorial listed below we would greatly
   appreciate it if you could take the time to contribute a detailed
   walkthrough.


.. tip::

    :ref:`Dex <authentication-dex>` is a very good starting option if you can connect
    to LDAP or Active Directory and not an institutional Single Sign-On service.

.. toctree::
   :maxdepth: 2

   authentication/overview
   authentication/oidc
   authentication/dex
   authentication/shibboleth
   authentication/cas
   authentication/tutorial-oidc-keycloak-rhel7
   authentication/duo-2fa-with-keycloak
   authentication/adfs-with-auth-mellon
   authentication/insecure
