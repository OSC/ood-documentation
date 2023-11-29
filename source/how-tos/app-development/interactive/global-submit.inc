Setting Batch Connect Options Globally
--------------------------------------

All of these configuration items can also be applied globally to the entire cluster
in the cluster definition files under ``/etc/ood/config/clusters.d/``. If set globally,
the option is applied to all applications in that cluster.

Here's an example of how to set the ``header`` configuration for both vnc and basic
templates.

  .. code-block:: yaml

    v2:
      batch_connect:
        basic:
          header: "#!/bin/bash"
        vnc:
          header: "#!/bin/bash"