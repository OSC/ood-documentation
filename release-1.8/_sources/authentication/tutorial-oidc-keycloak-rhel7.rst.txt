.. _authentication-tutorial-oidc-keycloak-rhel7:

OpenID Connect via KeyCloak on RHEL7
====================================

This tutorial shows installing Keycloak as an OpenID Connect Identity Provider and configuring OnDemand as an OpenID Client to authenticate with this provider.

Using ``https://ondemand-dev.hpc.osc.edu`` as the example host with OnDemand installed, at the end of the tutorial:

#. Keycloak is running and accessible at ``https://ondemand-idpdev.hpc.osc.edu``
#. In both cases Apache is handling requests. Apache proxies requests for ``https://ondemand-idpdev.hpc.osc.edu`` to the Keycloak server running on the default port of 8080.
#. Attempting to access OnDemand at ``https://ondemand-dev.hpc.osc.edu`` redirects the user to ``https://ondemand-idpdev.hpc.osc.edu`` to first authenticate.

At OSC in production we do two things differently from this tutorial:

#. we keep Keycloak on a separate host from OnDemand
#. we configure Keycloak to use MySQL for Keycloak's database instead of the default H2 file database

These steps have been omitted from the tutorial. For most cases for OnDemand,
the default H2 database is probably sufficient. Also by installing Keycloak on
the same host as OnDemand, we don't need to provision separate SSL certificates
and host, which simplifies the tutorial.

If your site is interested in either of these things and needs assistence,
please let us know by contacting us on the OnDemand Discourse at https://discourse.osc.edu/c/open-ondemand.

.. warning::

   In production we recommend installing Keycloak on a separate host from OnDemand.

.. note::

   This tutorial has only been verified to work with Keycloak 9.0.0.




.. toctree::
   :maxdepth: 2
   :numbered:
   :caption: Tutorial

   tutorial-oidc-keycloak-rhel7/install-keycloak
   tutorial-oidc-keycloak-rhel7/configure-keycloak-webui
   tutorial-oidc-keycloak-rhel7/install_mod_auth_openidc
   tutorial-oidc-keycloak-rhel7/add-custom-theme
   tutorial-oidc-keycloak-rhel7/configure-cilogon
