.. _submit-yml-erb:

submit.yml.erb
==============

This is the file that is submitted to a batch connect job. You can use either
a ``basic`` template or a ``vnc`` template. VNC templates have more options to
configure the VNC related items.

Basic template
..............

  .. code-block:: yaml
  
    batch_connect:
      template: "basic"
      work_dir: nil
      conn_file: "connection.yml"
      conn_params:
        - host
        - port
        - password
      bash_helpers: "..."
      min_port: 2000
      max_port: 65535
      password_size: 8
      header: ""
      footer: ""
      script_wrapper: "%s"
      set_host: "host=$(hostname)"
      before_script: "..."
      before_file: "before.sh"
      run_script: "..."
      script_file: "./script.sh"
      timeout: ""
      clean_script: "..."
      clean_file: "clean.sh"

VNC template
............

All the options above apply along with the options described below.

  .. code-block:: yaml
  
    batch_connect:
      template: "vnc"
      conn_params:
        - host
        - port
        - password
        - spassword
        - display
        - websocket
      websockify_cmd: "/opt/websockify/run"
      vnc_passwd: "vnc.passwd"
      vnc_args: nil
      name: ""
      geometry: ""
      dpi: ""
      fonts: ""
      idle: ""
      extra_args: ""
      vnc_clean: "..."

Option Details
..............

.. toctree::
   :maxdepth: 1

   submit-yml/basic-bc-yml-detailed
   submit-yml/vnc-bc-yml-detailed

Global
......

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