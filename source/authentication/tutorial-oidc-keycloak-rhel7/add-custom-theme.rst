.. _authentication-tutorial-oidc-keycloak-rhel7-add-custom-theme:

Add Custom Theme
================================================================

Custom themes are added to a realm by

1. adding the theme directory to ``/opt/keycloak-3.1.0.Final/themes``
2. selecting the theme via Admin Web UI >> Realm Settings >> Themes

Each theme is selectable based on the directory name of the theme. Themes can
extend other themes.

Here are two links to get started with a custom theme:

1. Currently version `v0.0.1 of OSC's Keycloak theme <https://github.com/OSC/keycloak-theme/tree/v0.0.1>`__
   can be used as a starting point for modification. This theme is based off of
   the default ``keycloak`` theme which itself is based off the ``base`` theme.
   Files to modify include:

   - ``login/login.ftl`` file for the footer links:
     https://github.com/OSC/keycloak-theme/blob/v0.0.1/login/login.ftl#L63-L73
   - ``login/resources/img/ondemand-logo.png`` add a logo with this name here
   - ``login/resources/img/favicon.ico`` replace with your own or remove
   - ``login/messages/messages_en.properties`` replace text with text
     appropriate for your center

2. See the Keycloak documentation for themes: http://www.keycloak.org/docs/3.1/server_development/topics/themes.html 

Remember after adding a theme you still need to configure your realm in the
Keycloak admin UI to use the theme for the login pages.

.. note::

   Soon we will offer an ood-keycloak base theme that be easier to extended to
   provide most of the common themeing a site might like to perform. It will
   also work well for OTP views.

