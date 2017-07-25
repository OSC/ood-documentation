.. _install-desktops-modify-cluster-configuration:

Modify Cluster Configuration
============================

If you haven't already done so, you will need to first have a corresponding
cluster configuration file for the cluster you intend to launch desktops on. It
is recommended you follow the directions on :ref:`add-cluster-config`.

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
       vnc:
         script_wrapper: |
           module load turbovnc/2.1.0
           export WEBSOCKIFY_CMD="/usr/local/websockify/run"
           %s

where we introduced the configuration option ``batch_connect`` which allows us
to add global settings for both a ``basic`` interactive web server as well as a
``vnc`` interactive web server.

In the above case we modify the global setting ``script_wrapper`` just for
``vnc`` sessions. This allows us to supply Bash code that wraps around the body
of the template script (specified by ``%s``). So we prepend to the body of the
script the required environment needed by the script to launch websockify and
TurboVNC.

.. note::

   You will most likely need to replace the block of code below in your cluster
   configuration file:

   .. code-block:: yaml

      script_wrapper: |
        module load turbovnc/2.1.0
        export WEBSOCKIFY_CMD="/usr/local/websockify/run"
        %s

   with a block that adds the full path to the TurboVNC binaries into the
   ``PATH`` environment variable as well as the corresponding websockify
   launcher into the ``WEBSOCKIFY_CMD`` environment variable.
