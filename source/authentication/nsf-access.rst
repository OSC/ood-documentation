.. _nsf-access:

NSF ACCESS
----------

If your site is a part of the `National Science Foundation`_'s (NSF)
`ACCESS`_ program (formerley `XSEDE`_) you can use their Identity Provider (IDP)
to authenticate users for your Open OnDemand instance.

OIDC Client Registration
************************

You should read the `ACCESS IDP documentation`_ on how to register your Open OnDemand
instance as an Open ID Connect (OIDC) client.

Once you've registered your Open OnDemand instance, you can then configure it accordingly.
Since `ACCESS`_ uses Open ID Connect (OIDC) you can see our :ref:`oidc documentation <authentication-oidc>`
for more details on how to configure Open OnDemand with what CI Logon has provided in
registering your application.

Mapping Users
*************

`ACCESS`_ users have allocations on many `ACCESS`_ resource, of which you are one.
This means they have disperate usernames on all these systems and a unique username
on _your_ system.

As a part of `ACCESS`_ your site likely already has the infrastructure around creating
`ACCESS`_ users on your systems through AMIE protocols which populate gridmap files.

If you already have a ``/etc/grid-security/grid-mapfile`` file, Open OnDemand can be
configured to map users using the gridmap files. See :ref:`gridmap usermapping <the documentation on gridmap files>`_
for how to enable that.


.. _mod_auth_openidc: https://github.com/zmartzone/mod_auth_openidc
.. _National Science Foundation: https://www.nsf.gov/
.. _ACCESS: https://access-ci.org/
.. _XSEDE: https://www.xsede.org/
.. _ACCESS IDP documentation: https://identity.access-ci.org/
