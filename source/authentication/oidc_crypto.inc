The ``update_ood_portal`` program now requires ``oidc_crypto_passphrase`` when using OIDC
authentication. Centers **must** provide this or the program will fail.

.. warning::
  The ``systemd`` unit for ``httd`` and ``apache2`` ignore this failure. When this program
  fails in a ``systemd`` unit, new configurations will not be applied until
  ``oidc_crypto_passphrase`` is set.