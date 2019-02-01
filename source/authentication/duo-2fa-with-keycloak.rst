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

#. Because Keycloak doesn’t actually know there is a possible challenge
   response using SSSD you have to setup Duo to have ``autopush=yes`` and ``prompts=1``
   so that the 2FA automatically sends a push notification to the person’s
   phone.

#. (Optional) Require Duo based on group membership or username list

   If you want to make Duo optional you could do so via group memberships. This works by changing ``groups`` config for pam_duo to something like ``groups=ood_duo``.

   You can also limit based on group membership using the contents of a file that lists users that require Duo.  This is done by modifying the keycloak PAM stack.  The file ``/etc/security/ondemand-duo.conf`` is a list of usernames, one username per line, that must use Duo to authenticate with Keycloak.  The modified PAM configuration at ``/etc/pam.d/keycloak``:

   .. code::

      auth    required   pam_sss.so
      auth    [default=1 success=ok] pam_listfile.so onerr=fail item=user sense=allow file=/etc/security/ondemand-duo.conf
      auth    required   pam_duo.so
      account required   pam_sss.so
