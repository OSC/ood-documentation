.. _authentication:

OOD Authentication
==================

After installing Open OnDemand you must:

- **Configure OOD to work with an apache module** which will connect to your center's authentication solution to generate the correct Apache configuration. 
- **Setup user mapping** to map the remote authenticated user to the corresponding local system user.
- **Configure logout**.

Each of these steps is covered in detail below.

Open OnDemand supports most authentication modules that work with Apache HTTP
Server version 2.4.

.. tip::

    :ref:`Dex <authentication-dex>` is a very good starting option if you can connect
    to LDAP or Active Directory and not an institutional Single Sign-On service.

.. warning::
   No Open OnDemand functionality is available without an Apache module and user mapping 
   configured. When no authentication is supplied Apache will only serve a static page that 
   directs you to this page.

.. toctree::
   :maxdepth: 3
   :caption: Setup Authentication Module, User Map, and Logout

   authentication/overview/configure-authentication
   authentication/overview/map-user
   authentication/overview/configure-logout

