.. _authentication-insecure:

Insecure Options
================
.. danger::

    **Never** allow a production Open OnDemand installation to accept 
    credentials over unencrypted connections.

There are other insecure options Apache still ships modules for 
such as ``mod_auth_basic``. With Basic auth, the user’s password is
Base-64-encoded and sent on *every* HTTP request, so even behind TLS the
credential is exposed far more often than with modern single-sign-on
solutions.

For these reasons, Open OnDemand strongly discourages enabling Basic auth, 
even when it is backed by PAM, LDAP, or any other password store. 

Questions on these topics will be linked back to this page.
