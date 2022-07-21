.. _authentication-dex:

OpenID Connect with Dex
=======================

`Dex`_ is a lightweight OpenID Connect authentication provider written in Go, and is the default authentication mechanism shipped with Open OnDemand.

Installing OnDemand Dex package
-------------------------------

First the OnDemand yum repos must be enabled, see :ref:`install-software`.

Install the ``ondemand-dex`` RPM:

   .. code-block:: sh

      sudo yum install ondemand-dex

Installing OnDemand Dex from source
-----------------------------------

Requirements:

- Go version 1.16.x with the ``go`` binary in ``PATH``
- Git
- Make

Build and install the ondemand-dex binary:

   .. code-block:: sh

      GOPATH=$(go env GOPATH)
      go get github.com/dexidp/dex
      cd $GOPATH/src/github.com/dexidp/dex
      make build
      sudo install -m 0755 bin/dex /usr/sbin/ondemand-dex

Add the ``ondemand-dex`` user and group:

   .. code-block:: sh

      sudo groupadd -r ondemand-dex
      sudo useradd -r -d /var/lib/ondemand-dex -g ondemand-dex -s /sbin/nologin -c "OnDemand Dex" ondemand-dex

Get ``ondemand-dex`` repo and install web files and systemd unit file

   .. code-block:: sh

      cd /tmp
      git clone https://github.com/OSC/ondemand-dex
      sudo mkdir /usr/share/ondemand-dex
      sudo cp -R ondemand-dex/web /usr/share/ondemand-dex/web
      sudo install -m 0644 ondemand-dex/examples/ondemand-dex.service /etc/systemd/system/ondemand-dex.service

Configuring OnDemand Dex
------------------------

OnDemand Dex is configured by modifying the Open OnDemand Portal :ref:`ood-portal-generator-configuration` file :file:`/etc/ood/config/ood_portal.yml`.

The default location for Dex configurations is :file:`/etc/ood/dex/config.yaml`.

When changes are needed for OnDemand Dex :ref:`restart-apache` and then restart Dex with:

   .. code-block:: sh

      sudo systemctl restart ondemand-dex

.. warning::

   If OnDemand is configured to use SSL and SSL certificates are not configured in Dex,
   the default behavior is for Dex to use copies of the OnDemand certificates for SSL.
   This means when the OnDemand certificates are updated it's necessary to run
   ``update_ood_portal`` to make new copies of the certificates and restart ``ondemand-dex``.

Managing the OnDemand Dex service
---------------------------------

The service for OnDemand Dex is ``ondemand-dex``:

   .. code-block:: sh

      sudo systemctl enable ondemand-dex.service
      sudo systemctl start ondemand-dex.service

Dex Firewall
------------

.. _dex-firewall:

By default when using SSL, Dex will use port ``5554`` for the communication between OnDemand and Dex as well as login interactions with users accessing OnDemand.  The port used for non-SSL is ``5556``.  The port being used by Dex must be externally accessible.

Firewalld example:
   .. code-block:: sh

      $ sudo firewall-cmd --zone=public --add-port=5554/tcp --permanent
      $ sudo firewall-cmd --reload

Iptables example:
   .. code-block:: sh

      $ sudo iptables -I INPUT -p tcp -m tcp --dport 5554 -j ACCEPT
      $ sudo iptables-save > /etc/sysconfig/iptables


Configuring OnDemand Dex for LDAP
---------------------------------

.. _dex-ldap:


Requirements:

- an LDAP server preferably with SSL support (``openldap.my_center.edu:636``)

The following is an example configuration using OpenLDAP.

   .. code-block:: yaml
      :emphasize-lines: 5-

      # /etc/ood/config/ood_portal.yml
      ---

      # ...
      dex:
        connectors:
          - type: ldap
            id: ldap
            name: LDAP
            config:
              host: openldap.my_center.edu:636
              insecureSkipVerify: false
              bindDN: cn=admin,dc=example,dc=org
              bindPW: admin
              userSearch:
                baseDN: ou=People,dc=example,dc=org
                filter: "(objectClass=posixAccount)"
                username: uid
                idAttr: uid
                emailAttr: mail
                nameAttr: gecos
                preferredUsernameAttr: uid
              groupSearch:
                baseDN: ou=Groups,dc=example,dc=org
                filter: "(objectClass=posixGroup)"
                userMatchers:
                  - userAttr: DN
                    groupAttr: member
                nameAttr: cn
   .. note::

      For documentation on Dex LDAP configuration please see the `Dex LDAP docs`_

   .. note::

      If you supply a ``bindPW`` in this file it's recommended to change the file permissions on :file:`/etc/ood/config/ood_portal.yml` to be ``0600`` make the file only readable by ``root``:

         .. code-block:: sh

            sudo chown root:root /etc/ood/config/ood_portal.yml
            sudo chmod 0600 /etc/ood/config/ood_portal.yml

Customizing OnDemand Dex
------------------------

The theme for Dex can be customized to be site-specific, see :ref:`customize_dex_theme`.

OnDemand Dex configuration reference
------------------------------------

.. _dex-configuration:

The OnDemand Dex configuration works by attempting to expose all Dex configuration options as keys nested under the ``dex`` key in :file:`/etc/ood/config/ood_portal.yml`.

The following reference is for :file:`/etc/ood/config/ood_portal.yml` values set under the ``dex`` key.

.. describe:: ssl (Boolean, null)

     Boolean to set if SSL is used, is ``true`` if OnDemand is configured for SSL, otherwise this defaults to ``false``.
     This value is used to determine which listen ports to use for Dex as well as OIDC configurations for OnDemand

.. describe:: http_port (String, Integer)

     The HTTP port used by Dex, default is ``5556``.
     Used to define ``web -> http`` in the Dex configuration as well as OIDC configurations

.. describe:: https_port (String, Integer)

     The HTTPS port used by Dex, default is ``5554``. This value is only set if SSL is enabled.
     Used to define ``web -> https`` in the Dex configuration as well as OIDC configurations

.. describe:: tls_cert (String, null)

     The path to TLS cert used by Dex.
     The default is to use the SSL certificate for OnDemand if OnDemand is configured with SSL.
     Used to define ``web -> tlsCert`` in the Dex configuration.
     If using the OnDemand certificate, a copy is made to ``/etc/ood/dex``.
     The ``ondemand-dex`` user must be able to read this file if configured.

.. describe:: tls_key (String, null)

     The path to TLS key used by Dex.
     The default is to use the SSL key for OnDemand if OnDemand is configured with SSL.
     Used to define ``web -> tlsKey`` in the Dex configuration.
     If using the OnDemand key, a copy is made to ``/etc/ood/dex``.
     The ``ondemand-dex`` user must be able to read this file if configured.

.. describe:: storage_file (String)

     The path to the Dex SQLite storage file.  Defaults to ``/etc/ood/dex/dex.db``.
     Used to define ``storage -> config -> file`` in the Dex configuration.

.. describe:: client_id (String)

     The client ID used for the OnDemand OIDC client.
     The default is to use the ``servername`` for OnDemand, and if that is not defined the host's FQDN is used.
     Sets ``staticClients[0] -> id`` in the Dex configuration as well as OnDemand OIDC configurations.

.. describe:: client_secret (String)

     The client secret used for the OnDemand OIDC client.
     The default is a randomly generated secret stored in ``/etc/ood/dex/ondemand.secret``.
     The value for this configuration can either be the secret string or path to file storing the secret.
     If using a file, the ``ondemand-dex`` user must be able to read the file.
     Sets ``staticClients[0] -> secret`` in the Dex configuration as well as OnDemand OIDC configurations.

.. describe:: client_redirect_uris (Array<String>)

     Additional OIDC client URIs to authorize for the OnDemand client.
     The values provided for this are merged with the default redirect URI generated for OnDemand.
     Sets ``staticClients[0] -> redirectURIs`` in the Dex configuration as well as OnDemand OIDC configurations.

.. describe:: client_name (String)

     The default OIDC client name for Dex. Defaults to ``OnDemand``.
     Sets ``staticClients[0] -> name`` in the Dex configuration.

.. describe:: connectors (Array<Hash>)

     This defines the external connectors used to authenticate users with Dex.
     If this value is not provided the default behavior is to set a static password of ``password`` for user ``ood@localhost``.
     This value is passed directly to the Dex configuration for ``connectors``.
     For an example of LDAP configuration see :ref:`Configuring OnDemand Dex for LDAP <dex-ldap>`.

.. describe:: frontend (Hash)

     This defines various changes for the themes and frontend look of Dex.
     The value provided is passed directly to the Dex configuration for ``frontend``.
     If ``dir`` key is not set the default of ``/usr/share/ondemand-dex/web`` is used.
     If ``theme`` key is not set the default of ``ondemand`` is used.

     Default

       .. code-block:: yaml

          frontend:
            dir: "/usr/share/ondemand-dex/web"
            theme: "ondemand"

.. describe:: grpc (Hash)

     The configuration for Dex's gRPC API.
     Value is passed directly to the Dex configuration

     Example:

       .. code-block:: yaml

          grpc:
            addr: "127.0.0.1:5557"
            tlsCert: "/etc/ood/dex/grpc-server.crt"
            tlsKey: "/etc/ood/dex/grpc-server.key"
            tlsClientCA: "/etc/ood/dex/grpc-ca.crt"

.. describe:: expiry (Hash)

     The configuration for Dex's expirations.
     Value is passed directly to the Dex configuration

     Example:

       .. code-block:: yaml

          expiry:
            signingKeys: "6h"
            idTokens: "24h"

.. _dex: https://github.com/dexidp/dex
.. _dex ldap docs: https://dexidp.io/docs/connectors/ldap/
