.. _authentication-overview-map-user:

Setup User Mapping
==================

Every authenticated HTTP request sent to the OnDemand portal has a ``REMOTE_USER``.
This ``REMOTE_USER`` can be an email like ``annie.oakley@osc.edu`` and needs to be
mapped to a Linux system user like ``aoakley``.

This is what we call user mapping.  Mapping apache's ``REMOTE_USER`` from an
authenticated request to a Linux system user.

Mapping to the local system user not only restricts access of OnDemand to local users
but it is also required by the OnDemand proxy to traffic the HTTP data to the user's
corresponding per-user NGINX (PUN) server.

Versions prior to 2.0 relied on :ref:`user_map_cmd <ood-portal-generator-user-map-cmd>` to do this.
Since 2.0 you should use the simpler and faster `user_map_match`_.

Both with variations will be discussed here.


Remote User
-----------

It's worth discussusing where ``REMOTE_USER`` is comfing from.  When apache
has successfully authenticates a request it sets the variable ``REMOTE_USER``
from, well, the remote.

This is generally a return value from the authentication system like an
:ref:`open id connect provider <authentication-oidc>`.  It's common for this
to be an email address.

You *can* configure `user_env`_ to use something other than ``REMOTE_USER``, but
it's unlikely you should need to.

If you're using an OpenID Connect provider you may need to set 
`oidc_remote_user_claim`_ as this setting
tells apache how to set ``REMOTE_USER`` from the claim response.


Reguluar Expression User Mapping
--------------------------------

The simplest and fastest way to map a ``REMOTE_USER`` to a system user is through
:ref:`user_map_match <ood-portal-generator-user-map-match>`.  It isn't directly
regular expression matching, but it's close enough for most use cases.
See it's documentation for examples and more.

Dex Automatic Configuration
---------------------------

When using the OpenId Connector `dex`_ and setting `oidc_remote_user_claim`_
to ``email`` we automatically set `user_map_match`_ to ``^([^@]+)@.*$`` as
a convienience.

User Map Command for Advanced Mappings
--------------------------------------

Versions prior to 2.0 provided a default `user_map_cmd`_ in
``/opt/ood/ood_auth_map/bin/ood_auth_map.regex``.  We no longer distribute
this file.

Sites instead need to write their own mapping script should they need
this capability.  Set this custom mapping script in the `user_map_cmd`_ 
configuration and be sure to make this mapping script executable.

.. warning::
  Be aware, this script is executed on every request.

Let's take a simple example.  It uses bash's builtin regular expression matching
against ``([^@]+)@osc.edu`` - an osc dot edu email address.  If that matches against 
``$1`` (the ``REMOTE_USER``), then we return an all lowercase version of the first part
of an email address.

The contract this script has with ood is that ``REMOTE_USER`` is passed into it
as the first arguement, ``$1``.  The script will return 0 and output the match if
it can correctly map the user. Otherwise, if it fails, it will output nothing and
exit 1.

.. code-block:: sh

  #!/bin/bash

  REX="([^@]+)@osc.edu"
  INPUT_USER="$1"

  if [[ $INPUT_USER =~ $REX ]]; then
    MATCH="${BASH_REMATCH[1]}"
    echo "$MATCH" | tr '[:upper:]' '[:lower:]'
  else
    # can't write to standard out or error, so let's use syslog
    logger -t 'ood-mapping' "cannot map $INPUT_USER"

    # and exit 1
    exit 1
  fi

If I were to run and test this script - it would return values like these:

.. code-block:: sh

  $ /opt/site/custom_mapping.sh Annie.Oakley@osc.edu
  annie.oakley
  $ /opt/site/custom_mapping.sh jessie@osc.edu
  jessie
  $ /opt/site/custom_mapping.sh jessie.owens@harvard.edu
  $ echo $?
  $ 1
  $ journalctl -t ood-mapping
  -- Journal begins at Tue 2020-06-02 06:45:03 EDT, ends at Wed 2022-01-19 15:11:37 EST. --
  Jan 19 15:03:14 localhost.localdomain ood-mapping[149352]: cannot map jessie.owens@harvard.edu
  $


File User Mapping
-----------------

This script parses a mapfile with each entry given in the following format:

::

   "authenticated_username" local_username


and separated by newlines. The script will systematically parse each line in
the mapfile looking for a match to the ``authenticated_username``. When a match
is found it breaks from the scan and outputs the ``local_username`` to
``STDOUT``.

.. warning::
  Be aware, this script is executed and reads a user mapping file on every request.

.. code-block:: sh

   /opt/ood/ood_auth_map/bin/ood_auth_map.mapfile [OPTIONS] <REMOTE_USER>

.. program:: ood_auth_map.mapfile

The options for this script are:

.. option:: -f <file>, --file <file>

   Default: ``/etc/grid-security/grid-mapfile``

   File used to scan for matches.

Examples for the MapFile script
*******************************

To scan the default grid-mapfile using a URL-encoded authenticated username:

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.mapfile 'http%3A%2F%2Fcilogon.org%2FserverA%2Fusers%2F58606%40cilogon.org'
   bob
   $

To scan a custom mapfile using an authenticated username:

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.mapfile --file '/path/to/mapfile' 'opaque_remote_username'
   bob
   $

If no match is found within the mapfile for the supplied
authenticated username that an empty string is returned instead:

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.mapfile 'this_remote_username_does_not_exist'

   $

Debugging User Mapping
----------------------

When debugging user mapping, it's always helpful to increase the `lua_log_level`_ to
debug.

In doing so you'll see messages like that detail the mapping input, output and 
times like ``Mapped 'jeff@localhost' => 'jeff' [0.089 ms]``.

The full message would look like this.

.. code-block:: sh

  /var/log/httpd/error.log:[Wed Jan 19 20:45:36.955855 2022] [lua:debug] [pid 39:tid 140070995539712] @/opt/ood/mod_ood_proxy/lib/ood/user_map.lua(21): [client 10.0.2.100:40172] Mapped 'jeff@localhost' => 'jeff' [0.089 ms], referer: http://localhost:5556/



.. _dex: authentication-dex
.. _user_map_match: ood-portal-generator-user-map-match
.. _user_map_cmd: ood-portal-generator-user-map-cmd
.. _user_env: ood-portal-generator-user-env
.. _oidc_remote_user_claim: ood-portal-generator-user-map-match
.. _lua_log_level: ood-portal-generator-lua-log-level