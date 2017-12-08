.. _authentication-tutorial-oidc-keycloak-rhel7-install-mod_auth_openidc:

Configure OnDemand to authenticate with Keycloak
================================================

OnDemand's Apache needs to use mod_auth_openidc to be able to act as an OpenID
Connect client to Keycloak. We will install mod_auth_openidc and modify
OnDemand's Apache configs to enable authentication via Keycloak.

Install mod_auth_openidc
------------------------

These directions are for installing from source.

#. Install dependencies for building mod_auth_openidc

   .. code-block:: sh

      yum install httpd24-httpd-devel openssl-devel curl-devel jansson-devel pcre-devel autoconf automake

#. Install cjose

   .. code-block:: sh

      wget https://github.com/zmartzone/mod_auth_openidc/releases/download/v2.3.0/cjose-0.5.1.tar.gz
      tar xzf cjose-0.5.1.tar.gz
      cd cjose-0.5.1
      ./configure
      make
      sudo make install

#. Install mod_auth_openidc

   .. code-block:: sh

      wget https://github.com/zmartzone/mod_auth_openidc/releases/download/v2.3.2/mod_auth_openidc-2.3.2.tar.gz
      tar xzf mod_auth_openidc-2.3.2.tar.gz
      cd mod_auth_openidc-2.3.2

      export MODULES_DIR=/opt/rh/httpd24/root/usr/lib64/httpd/modules
      export APXS2_OPTS="-S LIBEXECDIR=${MODULES_DIR}"
      export APXS2=/opt/rh/httpd24/root/usr/bin/apxs
      export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
      ./autogen.sh
      ./configure --prefix=/opt/rh/httpd24/root/usr --exec-prefix=/opt/rh/httpd24/root/usr --bindir=/opt/rh/httpd24/root/usr/bin --sbindir=/opt/rh/httpd24/root/usr/sbin --sysconfdir=/opt/rh/httpd24/root/etc --datadir=/opt/rh/httpd24/root/usr/share --includedir=/opt/rh/httpd24/root/usr/include --libdir=/opt/rh/httpd24/root/usr/lib64 --libexecdir=/opt/rh/httpd24/root/usr/libexec --localstatedir=/opt/rh/httpd24/root/var --sharedstatedir=/opt/rh/httpd24/root/var/lib --mandir=/opt/rh/httpd24/root/usr/share/man --infodir=/opt/rh/httpd24/root/usr/share/info --without-hiredis
      make
      sudo make install

#. Add file ``/opt/rh/httpd24/root/etc/httpd/conf.modules.d/auth_openidc.conf`` with contents:

   .. code-block:: none

      LoadModule auth_openidc_module modules/mod_auth_openidc.so



.. note::

   https://github.com/zmartzone/mod_auth_openidc does provide rpms for
   both cjose and mod_auth_openidc. However, we have yet to verify this works with
   the SCL Apache package we use.

   `Release v2.3.2 Downloads <https://github.com/zmartzone/mod_auth_openidc/releases/tag/v2.3.2>`_
   at bottom of the page includes an rpm for RHEL7, that is presumably built
   against Apache 2.4, so that might work.
   The RHEL6 rpm will not, however, as it is built against Apache 2.2
   You will need the dependent module cjose-0.5.1-1.el7.centos.x86_64.rpm
   (see `Downloads for v2.3.0 <https://github.com/zmartzone/mod_auth_openidc/releases/tag/v2.3.0>`_).

   Both of these rpms actually install the modules to a different locations than
   the SCL package, so if you use the rpm, you will need to copy the files to
   the appropriate location in the SCL Apache.



Re-generate main config using ood-portal-generator
-----------------------------------------------------------

#. In the ood-portal-generator's config.yml file, add these lines:

   .. code-block:: yaml

      # List of Apache authentication directives
      # NB: Be sure the appropriate Apache module is installed for this
      # Default: (see below, uses basic auth with an htpasswd file)
      auth:
        - 'AuthType openid-connect'
        - 'Require valid-user'

      # Redirect user to the following URI when accessing logout URI
      # Example:
      #     logout_redirect: '/oidc?logout=https%3A%2F%2Fwww.example.com'
      # Default: '/pun/sys/dashboard/logout' (the Dashboard app provides a simple
      # HTML page explaining logout to the user)
      logout_redirect: '/oidc?logout=https%3A%2F%2Fwebdev07.hpc.osc.edu'

      # Sub-uri used by mod_auth_openidc for authentication
      # Example:
      #     oidc_uri: '/oidc'
      # Default: null (disable OpenID Connect support)
      oidc_uri: '/oidc'

   Notice that we are

    * changing the Authentication directives for openid-connect
    * specifying /oidc to be the sub-uri used by mod_auth_openidc
    * specifying that /logout should redirect to this /oidc sub-uri to handle logout
      and specifying after logout, the user should be redirected back to OnDemand
      (which in this tutorial's case is ``https%3A%2F%2Fwebdev07.hpc.osc.edu``,
      the query param escaped format of ``https://webdev07.hpc.osc.edu``)

#. Using this modified config, regenerate the Apache config, and then install it:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake
      scl enable rh-ruby22 -- rake install


   The effect of this change in the Apache config (in case you want to apply the changes manually) are:

   #. Change the authentication directives for all of the Locations that require authentication i.e.:

      .. code-block:: diff

           <Location "/nginx">
         -    AuthType basic
         -    AuthName "Private"
         -    AuthBasicProvider ldap
         -    AuthLDAPURL "ldaps://openldap1.infra.osc.edu:636 openldap2.infra.osc.edu:636 openldap3.infra.osc.edu:636 openldap4.infra.osc.edu
         -    AuthLDAPGroupAttribute memberUid
         -    AuthLDAPGroupAttributeIsDN off
         +    AuthType openid-connect
               Require valid-user
         -    RequestHeader unset Authorization

             LuaHookFixups nginx.lua nginx_handler
           </Location>

   #. Update the ``Redirect "logout"`` directive

      .. code-block:: diff

         -  Redirect "/logout" "/pun/sys/dashboard/logout"
         -
         +  Redirect "/logout" "/oidc?logout=https%3A%2F%2Fwebdev07.hpc.osc.edu"

   #. Add the ``<Location "/oidc">`` directive

      .. code-block:: none

         # OpenID Connect redirect URI:
         #
         #     http://localhost:80/oidc
         #     #=> handled by mod_auth_openidc
         #
         <Location "/oidc">
           AuthType openid-connect
           Require valid-user
         </Location>

Add Keycloak config to OnDemand Apache for mod_auth_openidc
-----------------------------------------------------------

#. Add the file /opt/rh/httpd24/root/etc/httpd/conf.d/auth_openidc.conf with the contents:

   .. code-block:: none

     OIDCProviderMetadataURL https://webdev07.hpc.osc.edu:8443/auth/realms/ondemand/.well-known/openid-configuration
     OIDCClientID        "webdev07.hpc.osc.edu"
     OIDCClientSecret    "1111111-1111-1111-1111-111111111111"
     OIDCRedirectURI      https://webdev07.hpc.osc.edu/oidc
     OIDCCryptoPassphrase "4444444444444444444444444444444444444444"

     # Keep sessions alive for 8 hours
     OIDCSessionInactivityTimeout 28800
     OIDCSessionMaxDuration 28800

     # Set REMOTE_USER
     OIDCRemoteUserClaim preferred_username

     # Don't pass claims to backend servers
     OIDCPassClaimsAs environment

     # Strip out session cookies before passing to backend
     OIDCStripCookies mod_auth_openidc_session mod_auth_openidc_session_chunks mod_auth_openidc_session_0 mod_auth_openidc_session_1

   #. OIDCClientID: replace with the client id specified when installing the client in Keycloak admin interface
   #. OIDCClientSecret: replace ``1111111-1111-1111-1111-1111111111111`` with client secret specified from the Install tab of the client in Keycloak admin interface
   #. OIDCCryptoPassphrase: replace ``4444444444444444444444444444444444444444`` with random generated password. I used ``openssl rand -hex 20``.
   #. Verify the OIDCProviderMetadataURL uses the correct realm and the port Apache exposes to the world for Keycloak by accessing the URL.

#. Change permission on file to be readable by apache and no one else:

   .. code-block:: sh

      sudo chgrp apache /opt/rh/httpd24/root/etc/httpd/conf.d/auth_openidc.conf
      sudo chmod 640 /opt/rh/httpd24/root/etc/httpd/conf.d/auth_openidc.conf

#. Then restart OnDemand's Apache. OnDemand should now be authenticating using KeyCloak.

   .. code-block:: sh

      # stop both
      sudo systemctl stop keycloak
      sudo systemctl stop httpd24-httpd

      # start Apache FIRST, then start Keycloak
      sudo systemctl start httpd24-httpd
      sudo systemctl start keycloak

.. warning::

   If when starting Apache you see this error:

   .. code-block:: none

      Job for httpd24-httpd.service failed because the control process exited
      with error code. See "systemctl status httpd24-httpd.service" and
      "journalctl -xe" for details.

   You may need to first stop Keycloak, then start Apache, then start Keycloak.


.. note::

   We prevent OIDC_CLAIM headers from being passed through to the PUN
   by specifying in this file to pass claims as environment, instead of
   as HTTP headers, since Apache won't pass any environment off to the
   PUN when proxying requests, but would pass HTTP headers.
