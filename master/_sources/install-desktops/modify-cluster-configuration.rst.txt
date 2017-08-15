.. _install-desktops-modify-cluster-configuration:

Modify Cluster Configuration
============================

If you haven't already done so, you will need to first have a corresponding
cluster configuration file for the cluster you intend to launch desktops on. It
is recommended you follow the directions on :ref:`add-cluster-config`. In order
to submit interactive Desktop jobs your cluster must be properly configured to
submit jobs, which means the config will have a ``job:`` section.

Modify the cluster configuration file with the necessary information so that
a batch script generated from an interactive app can find the installed
copies of TurboVNC and websockify:

.. code-block:: yaml

   # /etc/ood/config/clusters.d/cluster1.yml
   ---
   v2:
     # ...
     # ... other configuration options ...
     # ...
     batch_connect:
       basic:
         script_wrapper: |
           module restore
           %s
       vnc:
         script_wrapper: |
           module restore
           module load turbovnc/2.1.0
           export WEBSOCKIFY_CMD="/usr/local/websockify/run"
           %s

where we introduced the configuration option ``batch_connect`` that allows us
to add global settings for both a ``basic`` interactive web server as well as a
``vnc`` interactive web server.

In the above case we modify the global setting ``script_wrapper`` for both
``basic`` and ``vnc`` sessions. This allows us to supply Bash code that wraps
around the body of the template script (specified by ``%s``). First, we restore
the module environment to remove any conflicting modules that may have been
loaded by the user's ``.bashrc`` or ``.bash_profile`` files. Then we specify
the required environment needed by the ``vnc`` script to launch websockify and
TurboVNC.

.. note::

   You will most likely need to replace the block of code below in your cluster
   configuration file:

   .. code-block:: yaml

      script_wrapper: |
        module restore
        module load turbovnc/2.1.0
        export WEBSOCKIFY_CMD="/usr/local/websockify/run"
        %s

   with a block that adds the full path to the TurboVNC binaries into the
   ``PATH`` environment variable as well as the corresponding websockify
   launcher into the ``WEBSOCKIFY_CMD`` environment variable.

.. warning::

   Do not forget to include the ``%s`` in the ``script_wrapper`` configuration
   option. Otherwise the actual Bash code that launches the corresponding web
   servers will never be interpolated into the main batch script and run.
