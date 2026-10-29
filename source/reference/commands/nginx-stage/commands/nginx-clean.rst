.. _nginx-stage-nginx-clean:

``nginx_stage nginx_clean``
===========================

Stop eligible per-user NGINX (PUN) processes and recover stale or disabled-user
runtime state. For resolvable accounts, ordinary cleanup preserves PUNs with
detected Passenger application sessions.

.. code-block:: sh

   sudo nginx_stage nginx_clean [OPTIONS]

.. program:: nginx_stage nginx_clean


.. note::

   Since 4.0, cleanup also handles accounts that no longer resolve, such as users
   removed from LDAP. This differs from setting a disabled login shell.

General Options
---------------

.. option:: -f, --force

   Bypass session detection. Process identity, PID/socket safety checks and
   lifecycle locking still apply. Live orphaned listeners and uncertain runtime
   state are preserved.

.. option:: -u <user>, --user <user>

   Restrict signaling, recovery and metadata changes to the selected user.
   Enumeration may still look up other accounts.

.. option:: -N, --skip-nginx

   Report a snapshot without signaling, probing sockets, deleting files, or
   creating/acquiring lifecycle locks. Account lookup still occurs. Pending
   records are retained, and the snapshot can become stale.

Examples
--------

To run ordinary cleanup:

.. code-block:: sh

   sudo nginx_stage nginx_clean

This prints selected users. Inspect diagnostics: a printed name does not prove
that shutdown or cleanup succeeded.

To request cleanup regardless of detected sessions, subject to safety checks:

.. code-block:: sh

   sudo nginx_stage nginx_clean --force

To preview the ordinary cleanup selection:

.. code-block:: sh

   sudo nginx_stage nginx_clean --skip-nginx

To restrict either real cleanup or a preview to Bob, add ``--user bob``.


Shutdown and stale-state recovery
---------------------------------

Cleanup tries each user's lifecycle lock without waiting. A busy user is
preserved with a diagnostic while cleanup continues to later candidates. The
lock remains held through shutdown, metadata deletion and per-user runtime
directory removal. Successful shutdown signaling waits up to 30 seconds for both
socket and PID paths to disappear; see :ref:`nginx-stage-nginx` for the deadline
and replacement rules. A live master whose socket has disappeared is preserved,
including with ``--force``.

Session detection counts Passenger application processes only after a
successful process listing or exit status 1 with only the ``CMD`` header and
empty stderr. Timeouts, other unsuccessful results and execution failures
preserve the PUN and report an error; cleanup continues to later candidates.
``--force`` explicitly bypasses this detection.

For dead or unrelated PID records or malformed active-user PIDs, PID cleanup
requires an absent socket or a confirmed refused stale socket. Actual sockets are
probed once with a nonblocking connection. Listening sockets, symlinks, ordinary
files, full backlogs and inconclusive errors are preserved. A socket's type,
device and inode are rechecked before unlinking it. Symlinked malformed PID
files are preserved. Socket state is removed before the stale PID record.
For resolvable users with socket-only state, cleanup removes only a confirmed
stale socket. Active-user recovery retains configuration and secrets. These
checks protect orphaned workers that still serve requests.

The lock coordinates cooperating nginx_stage commands, not external writers.
Configured runtime, lock and retry-record roots must exclude untrusted writers.
The identity recheck does not make unlink atomic against external replacement.

Disabled-user cleanup and retries
---------------------------------

Candidates come from PID paths, socket-only state and explicit
``<pun-config>.cleanup_pending`` records. Old configs, secrets and empty runtime
directories alone are not candidates. Shared PID parent directories and lifecycle lock files are retained.

After taking the lock, cleanup rechecks account availability. A still-resolving
passwd record with failed full user/group lookup preserves PUN state and reports
an error. For a restored account, cleanup validates and cancels its safe pending
record instead of performing disabled-user deletion; normal active-user cleanup
still applies.

Cleanup creates a private pending record beside the stable config lock before
shutdown can remove the PID. It rejects existing symlinks, non-regular files,
another owner's files and group/other-writable records. It retains the record
until verified shutdown
or safe stale-state recovery, secret/config deletion and runtime-directory
cleanup finish. A fresh cleaner can retry partial failures after the PID is gone.
Do not delete the record to hide a failed cleanup.

.. warning::

   A complete NSS/LDAP/SSSD outage that makes passwd lookup report no account
   remains indistinguishable from deletion. Check account-provider health and
   stop scheduled cleanup while investigating an outage. A dry run does not
   establish that lookup results are reliable.

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

For changes to configured paths or executables, follow the `nginx-stage migration
guidance
<https://github.com/OSC/ondemand/blob/master/nginx_stage/README.md#configuration-path-or-executable-changes>`_
before running old and new lifecycle callers together.
