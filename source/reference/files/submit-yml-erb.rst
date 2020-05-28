.. _submit-yml-erb:

submit.yml.erb
==============

This is the file that is submitted to a batch connect job. It is comprised
of a ``script`` and a ``batch_connect`` attribute.  The ``batch_connect``
attribute can either be a ``basic`` template if your app is already an
http server or a ``vnc`` template if you need VNC capabilities.


Simple Example
..............

  .. code-block:: yaml

      # a simple script.yml.erb file

      script:
        native:
          - "-n"
          - "1"
      batch_connect:
        template: "basic"
        header: "#!/bin/bash"


Details on Submit Attributes
............................

.. toctree::
   :maxdepth: 1

   submit-yml/basic-bc-options
   submit-yml/vnc-bc-options
   submit-yml/script-options

Setting Batch Connect Options Globally
......................................

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