.. _nginx-stage-nginx:

``nginx_stage nginx``
=====================

Start or signal the selected user's per-user NGINX (PUN) process.

.. code-block:: sh

   sudo nginx_stage nginx [OPTIONS]

.. program:: nginx_stage nginx

Required Options
----------------

.. option:: -u <user>, --user <user>

   The user of the per-user NGINX process.

General Options
---------------

.. option:: -s <signal>, --signal <signal>

   Send the given signal to the per-user NGINX process.

.. option:: -N, --skip-nginx

   Display the startup command or describe the requested signal without
   executing it.

.. note::

   Under a default installation, the possible signals are
   ``stop/quit/reopen/reload``.

.. note::

   If no signal is specified, then it will attempt to start the user's per-user
   NGINX process.

Shutdown and replacement
------------------------

After successful ``stop`` or ``quit`` signaling, this command waits for both the
PUN socket and PID paths to disappear. A dangling symlink is still an occupied
path. The wait uses a fixed 30-second monotonic deadline and polls every 0.1
second. Lock acquisition and command execution are outside that deadline;
synchronous web-server restart requests can therefore take longer than 30 seconds.

A graceful ``quit`` can remove the listening socket before the master finishes
draining requests or websockets. Startup remains blocked while the recorded
master is alive, even when the socket is gone. A timeout returns an error; it
does not force termination or launch a replacement. Retry startup after the old
master finishes. An administrator who has verified the PUN and accepts
interrupting requests can explicitly request ``--signal=stop`` instead.

Startup, explicit ``stop``/``quit``, app-config replacement and cleanup use a
stable per-user lock beside the PUN config. ``reload`` and ``reopen`` retain their
existing locking behavior. Cleanup skips busy locks and continues to later
users; startup, replacement and explicit shutdown wait for the lock. Keep the
lock file in place.

Before signaling, nginx_stage validates a complete positive decimal PID from
1 through 2147483647, with at most 22 bytes before whitespace is stripped. It
also verifies the executable, exact per-user master command/configuration and
effective UID.
Supported protected executable replacements remain identifiable across package
upgrades; uncertain identities and unreadable process metadata are preserved.
Identity checks and signal delivery use the same open ``/proc/PID`` directory
descriptor, without numeric-PID ``kill`` or an ``nginx -s`` PID-file reread.

Signaling requires Linux ``pidfd_send_signal`` support, readable procfs in the
caller's PID namespace, and ``x86_64``, ``aarch64`` or ``ppc64le`` (also named
``powerpc64le``). Unsupported or denied signaling fails without an unchecked
fallback. Validate the capability and lifecycle behavior on the deployed kernel
and security policy, including native EL8 and enforcing SELinux; see the
`nginx-stage deployment checks
<https://github.com/OSC/ondemand/blob/master/nginx_stage/docs/pun-lifecycle-validation.md>`_.

Successful ``reload`` or ``reopen`` confirms signal delivery. Inspect nginx logs
to confirm acceptance; no separate nginx signal process checks configuration
before delivery. Configured executable, configuration, lock and runtime roots
must exclude untrusted writers. Locks coordinate cooperating commands, and
process titles alone are not a security boundary against privileged processes.

Startup also rejects uncertain PID/process state and an occupied socket beside
a dead or unrelated recorded PID. It does not probe or remove stale sockets.
Do not remove a PID or socket path just to bypass a startup error. See
:ref:`nginx-stage-nginx-clean` for safe stale-state recovery and operator checks.

Examples
--------

To stop Bob's NGINX process:

.. code-block:: sh

   sudo nginx_stage nginx --user 'bob' --signal 'stop'

This sends a ``stop`` signal to Bob's per-user NGINX process.

With :option:`nginx_stage nginx --skip-nginx`, startup prints its command;
a signal preview describes the request without validating the PID or sending
a signal. A preview is not evidence of delivery.
