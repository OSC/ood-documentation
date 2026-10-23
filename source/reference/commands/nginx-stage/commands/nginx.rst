.. _nginx-stage-nginx:

``nginx_stage nginx``
=====================

This command will start an NGINX process as the user as well as
control this process.

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

   Skip the execution of the per-user NGINX process.

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
second. Lock acquisition and nginx execution are outside that deadline.

A graceful ``quit`` can remove the listening socket before the master finishes
draining requests or websockets. Startup remains blocked while the recorded
master is alive, even when the socket is gone. A timeout returns an error; it
does not force termination or launch a replacement. Retry startup after the old
master finishes. An administrator who has verified the PUN and accepts
interrupting requests can explicitly request ``--signal=stop`` instead.

Startup, explicit ``stop``/``quit``, app-config replacement and cleanup use a
stable per-user lock beside the PUN config. ``reload`` and ``reopen`` retain their
existing locking behavior. Keep the lock file in place.

Signals validate the PID file before executing nginx. The file must contain a
positive decimal PID in range and be at most 22 bytes before whitespace is
stripped. A valid PID does not prove process identity or prevent PID reuse;
nginx rereads the file when signaling. Configured lock and runtime roots must
exclude untrusted writers.

Do not remove a PID or socket path just to bypass a startup error. See
:ref:`nginx-stage-nginx-clean` for safe stale-state recovery and operator checks.

Examples
--------

To stop Bob's NGINX process:

.. code-block:: sh

   sudo nginx_stage nginx --user 'bob' --signal 'stop'

This sends a ``stop`` signal to Bob's per-user NGINX process.

If you run :option:`nginx_stage nginx --skip-nginx`, it will
**only** display the system command that would have been called.
