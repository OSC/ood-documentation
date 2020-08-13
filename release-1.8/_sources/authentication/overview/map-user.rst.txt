.. _authentication-overview-map-user:

Setup User Mapping
==================

Every HTTP request sent to the OnDemand portal triggers a call to the
``user_map_cmd`` to map the remote authenticated user name to the
local system user name. Mapping to the local system user not only restricts
access of OnDemand to local users but it is also required by the OnDemand proxy
to traffic the HTTP data to the user's corresponding per-user NGINX (PUN)
server.

The :ref:`ood-portal-generator` and its corresponding
:ref:`ood-portal-generator-configuration` are used to configure both the system
command that performs the mapping (:ref:`user_map_cmd
<ood-portal-generator-user-map-cmd>`) and the argument fed to the system
command (:ref:`user_env <ood-portal-generator-user-env>`). By default these
configuration options are defined as:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---
   # ...
   user_map_cmd: '/opt/ood/ood_auth_map/bin/ood_auth_map.regex'
   user_env: 'REMOTE_USER'

which uses regex user mapping for the mapping command and ``REMOTE_USER``
(this variable holds the name of the authenticated user by the web server) as
its command line argument.

This is equivalent to calling from the command line:

.. code-block:: sh

   /opt/ood/ood_auth_map/bin/ood_auth_map.regex "$REMOTE_USER"

which just echos back the value of ``REMOTE_USER``.

.. note::

   The default user mapping employed by an OnDemand portal **directly** maps
   the remote authenticated user name to the local user name. So the Apache
   authentication module used is expected to set the correct local user name in
   ``REMOTE_USER``.

Open OnDemand provides two facilities for user mapping. One through regular
expressions (the default) and another through a lookup file.  Both of which
are documented here.  As an alternative you can provide your own custom script
and simply set the ``user_map_cmd`` to use it.

Regex User Mapping
------------------

Usage for the regular expression (regex) user mapping script is below.

.. code-block:: sh

   /opt/ood/ood_auth_map/bin/ood_auth_map.regex [options] <authenticated_user>

With the options:

.. option:: -r <regex>, --regex <regex>

   Default: ``^(.+)$``

   The regular expression used to capture the local system username.

Regex User Mapping Examples
***************************

Here are some examples of how to use the default regex mapping script.

To echo back the username supplied (useful for LDAP authentication
and the default behavior):

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.regex 'bob'
   bob
   $

To capture the local username from an email address.

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.regex --regex '^(\w+)@center.edu$' 'bob@center.edu'
   bob
   $

If no match is found from the supplied regular expression and authenticated username
that an empty string is returned instead:

.. code-block:: sh

   $ /opt/ood/ood_auth_map/bin/ood_auth_map.regex --regex '^(\w+)@center.edu$' 'bob@mit.edu'

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

Custom Mapping
--------------

As mentioned previously the :ref:`ood-portal-generator` configuration options
of interest are:

- :ref:`user_map_cmd <ood-portal-generator-user-map-cmd>`
- :ref:`user_env <ood-portal-generator-user-env>`

Indeed if you need to use the options to the regex or file user mapping scripts
that come with Open OnDemand you'll need to specify them in the ``user_map_cmd``.

After modifying :file:`/etc/ood/config/ood_portal.yml` with the mapping you
want you would then build and install the new Apache configuration file with:

.. code-block:: sh

   sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal

Finally you will need to restart your Apache HTTP Server for the changes to
take effect.
