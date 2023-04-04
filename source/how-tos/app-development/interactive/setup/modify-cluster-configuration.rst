.. _app-development-interactive-setup-modify-cluster-configuration:

Modify Cluster Configuration
============================

If you haven't already done so, you will need to first have a corresponding
cluster configuration file for the cluster you intend to submit
interactive batch jobs to. It is recommended you follow the directions
on :ref:`add-cluster-config`.

This is a simple example that ensures modules are always being purged and
``vnc`` applications have the right environment variables for `TurboVNC`_ and `websockify`_.

.. code-block:: yaml
   :emphasize-lines: 11-

   # /etc/ood/config/clusters.d/example_cluster.yml
   ---
   v2:
     metadata:
       title: "Example Cluster"
     login:
       host: "example.my_center.edu"
     job:
       adapter: "..."
       ...
     batch_connect:
       basic:
         script_wrapper: |
           module purge
           %s
       vnc:
         script_wrapper: |
           module purge
           export PATH="/usr/local/turbovnc/bin:$PATH"
           export WEBSOCKIFY_CMD="/usr/local/websockify/run"
           %s

In this example we're :ref:`setting batch connect options globally <global-bc-settings>`
that wrap the ``basic`` and ``vnc`` scripts.  That's important, because it means *any*
batch connect app used on this cluster will use these settings.

This example uses :command:`bash` code that wraps around the body Open OnDemand provided
scripts (the variable ``%s``). First, we purge the module environment to remove any conflicting modules that may have
been loaded by the user's ``.bashrc`` or ``.bash_profile`` files. Then we
set environment variables needed by the ``vnc`` script to launch `TurboVNC`_ and `websockify`_.

.. note::

  This is an example of how to :ref:`set batch connect options globally <global-bc-settings>`.  You
  will likely need use different values.

.. warning::

   Do not forget to include the ``%s`` in the ``script_wrapper`` configuration
   option. Otherwise the actual :command:`bash` code that launches the
   corresponding web servers will never be interpolated into the main batch
   script and run.

.. _turbovnc: https://turbovnc.org/
.. _websockify: https://github.com/novnc/websockify
