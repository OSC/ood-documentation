.. _authentication-duo-2fa-with-keycloak:

Two Factor Auth using Duo with Keycloak
=======================================

These are the steps to setup two factor authentication with Duo using Keycloak.

#. Have Keycloak perform authentication through SSSD running on the Keycloak server.
#. Follow the `Keycloak docs for using SSSD <https://www.keycloak.org/docs/latest/server_admin/index.html#sssd-and-d-bus>`_ except use a modified ``/etc/pam.d/keycloak``:

   .. code::

      auth    required   pam_sss.so
      auth    required   pam_duo.so
      account required   pam_sss.so

#. Setting something like ``groups=*,!root`` in ``/etc/duo/pam_duo.conf`` and the PAM config is enough to require Duo


If you want to make Duo optional you could do so via group memberships. This works by changing groups config for pam_duo.

You could also do clever things with the PAM stack to use pam_duo based on other conditions.

.. warning::

   Because Keycloak doesn’t actually know there is a possible challenge
   response using SSSD you have to setup Duo to have autopush=yes and prompts=1
   so that the 2FA automatically sends a push notification to the person’s
   phone.

