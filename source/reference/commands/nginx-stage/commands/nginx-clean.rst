.. _nginx-stage-nginx-clean:

``nginx_stage nginx_clean``
===========================

This command attempts to stop per-user NGINX (PUN) processes without active
connections and recover stale or disabled-user runtime state.

.. code-block:: sh

   sudo nginx_stage nginx_clean [OPTIONS]

.. program:: nginx_stage nginx_clean


..  note::
  Since 4.0 ``nginx_clean`` also cleans per-user NGINX (PUN) processes
  for users that have been disabled (removed from LDAP).

General Options
---------------

.. option:: -f, --force

   Ignore the active connection count when deciding which running PUNs to stop.
   PID validation and stale-state safety checks still apply. This option does
   not authorize unlinking a live orphaned listener or uncertain socket state.

.. option:: -u <user>, --user <user>

   Restrict signaling, recovery and metadata changes to the selected user.
   Enumeration may still look up other accounts.

.. option:: -N, --skip-nginx

   Report cleanup candidates without signaling, probing sockets or removing
   files. Account lookup still occurs during enumeration.

Examples
--------

To kill all PUN processes with no active connections:

.. code-block:: sh

   sudo nginx_stage nginx_clean

This prints selected users. Inspect diagnostics: a printed name does not prove
that shutdown or cleanup succeeded.

To request cleanup regardless of active connection counts, subject to safety
checks:

.. code-block:: sh

   sudo nginx_stage nginx_clean --force

To **only** display the users with PUN processes that have no active
connections:

.. code-block:: sh

   sudo nginx_stage nginx_clean --skip-nginx

This will not kill the PUN processes.


Shutdown and stale-state recovery
---------------------------------

Cleanup holds the user's lifecycle lock through shutdown, metadata deletion and
per-user runtime-directory removal. After successful shutdown signaling, it
waits up to 30 seconds for both socket and PID paths to disappear. A timeout
reports an error without forcing termination. A live master whose socket has
already disappeared is preserved, including with ``--force``.

For a dead recorded master or malformed active-user PID, only an absent socket
or a confirmed refused stale socket permits PID cleanup. Actual sockets are
probed once with a nonblocking connection. Listening sockets, symlinks, ordinary
files, full backlogs and inconclusive errors are preserved. A socket's type,
device and inode are rechecked before unlinking it. Symlinked malformed PID
files are preserved. This protects orphaned workers that still serve requests.

The lock coordinates cooperating nginx_stage commands, not external writers.
Configured runtime, lock and retry-record roots must exclude untrusted writers.
The identity recheck does not make unlink atomic against external replacement.

Disabled-user cleanup and retries
---------------------------------

Candidates come from PID files and explicit ``<pun-config>.cleanup_pending``
records. Old configs, secrets and empty runtime directories alone are not
candidates. Shared PID parent directories and lifecycle lock files are retained.

After taking the lock, cleanup rechecks account availability. It skips an
account that has become resolvable. Otherwise it creates a private pending
record beside the stable config lock before shutdown can remove the PID.
Successful shutdown precedes secret/config deletion and runtime-directory
removal. A partial failure retains the record so a fresh cleaner can finish
after the PID is gone. Do not delete the record to hide a failed cleanup.

.. warning::

   Disabled-user classification currently treats ``User.new`` raising
   ``ArgumentError`` as a disabled account. Failed user or primary-group lookup
   during LDAP/SSSD trouble can therefore trigger incorrect cleanup. Check
   directory-service health before running cleanup, and stop scheduled cleanup
   while investigating an outage. A dry run does not establish that lookup
   results are reliable.

Operator recovery
-----------------

#. Check both user and primary-group lookup health before concluding that an
   account was deleted.
#. Record the warnings and configured paths. Inspect ownership, permissions and
   symlinks without following unknown targets. Do not put secret contents in
   logs or support requests.
#. Correlate the PUN configuration with the master/worker tree, command line,
   process start times, open files and listener information. A PID, process name
   or UID alone is not proof of identity. Preserve live orphaned workers.
#. If the verified master is draining, wait for it to finish or explicitly
   request ``stop`` if interrupting requests is acceptable. Do not bypass the
   startup guard by deleting its PID or socket.
#. Resolve the reported failure and rerun targeted cleanup with ``--user``.
   If ownership remains uncertain, establish that no master, worker or competing
   startup owns the affected entries before repairing those specific paths.
   There is no safe general command to blindly delete ambiguous runtime state.
