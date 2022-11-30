.. _nsf-access:

NSF ACCESS
----------

If your site is a part of the `National Science Foundation`_'s (NSF)
`ACCESS`_ program (formerley `XSEDE`_) you can use their Identity Provider (IDP)
`CI Logon`_ to authenticate users for your Open OnDemand instance.

OIDC Client Registration
************************

You should read the `ACCESS IDP documentation`_ on how to register your Open OnDemand
instance as an Open ID Connect (OIDC) client.

Once you've registered your Open OnDemand instance, you can then configure it accordingly.
Since `ACCESS`_ uses Open ID Connect (OIDC) you can see our :ref:`oidc documentation <authentication-oidc>`
for more details on how to configure Open OnDemand with what CI Logon has provided in
registering your application.

Here's an example you can use to get started. Note that ``oidc_client_id`` and ``oidc_client_secret``
are commented out because they are specific to your site.

.. code-block:: yaml
  :emphasize-lines: 3-4

  oidc_uri: "/oidc"
  oidc_provider_metadata_url: "https://cilogon.org/.well-known/openid-configuration"
  # oidc_client_id: "cilogon:/client_id/..."
  # oidc_client_secret: "..."
  oidc_remote_user_claim: "eppn"
  oidc_scope: "openid email org.cilogon.userinfo"
  oidc_session_inactivity_timeout: 28800
  oidc_session_max_duration: 28800
  oidc_state_max_number_of_cookies: "10 true"
  oidc_settings:
    OIDCPassIDTokenAs: "serialized"
    OIDCPassRefreshToken: "On"
    OIDCPassClaimsAs: "environment"
    OIDCStripCookies: "mod_auth_openidc_session mod_auth_openidc_session_chunks mod_auth_openidc_session_0 mod_auth_openidc_session_1"
    OIDCAuthRequestParams: "idphint=https%3A%2F%2Faccess-ci.org%2Fidp"


Shibboleth and InCommon
***********************

If your campus already runs Shibboleth authentication, you have an alternative to the Open ID Connect
configuration above.

`CI Logon`_ provides a bridge from campus authentication, via the InCommon Federation,
to certificate-based and OAuth/OIDC-based research cyberinfrastructure (CI).

The SAML metadata for idp.access-ci.org is not yet published by InCommon. Please manually fetch the
metadata from https://identity.access-ci.org/access-metadata.xml and configure it in a local file
until we can complete the InCommon publication process.

See our :ref:`shibboleth documentation <authentication-shibboleth>` for more information on
Shibboleth authentication.

Mapping Users
*************

`ACCESS`_ users have allocations on many `ACCESS`_ resource, of which you are one.
This means they have disparate usernames on all these systems and a unique username
on _your_ system.

So you'll need an additional utility provided by access `ACCESS`_, namely the
`access-oauth-mapfile`_.

Follow the instructions to install that utility and you'll get a lookup table
in ``/etc/grid-security/access-oauth-mapfile`` like so:

.. code-block:: sh

  annie-oakley@access-ci.org aoakley


You can set the `user_map_cmd`_ in ``ood_portal.yml`` to search this file and return
the local user given the ACCESS username.

.. code-block:: sh

  #!/bin/bash

  MAPPED_USER=$(grep "$1" ./delme.txt | awk '{print $2}')
  if [[ "$MAPPED_USER" != "" ]]; then
    echo -n "$MAPPED_USER"
  else
    echo "$1-not-found"
  fi


.. _mod_auth_openidc: https://github.com/zmartzone/mod_auth_openidc
.. _National Science Foundation: https://www.nsf.gov/
.. _ACCESS: https://access-ci.org/
.. _XSEDE: https://www.xsede.org/
.. _ACCESS IDP documentation: https://identity.access-ci.org/
.. _CI Logon: https://www.cilogon.org/faq
.. _access-oauth-mapfile: https://software.xsede.org/production/access-oauth-mapfile/INSTALL
.. _user_map_cmd: ood-portal-generator-user-map-cmd
