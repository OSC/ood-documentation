.. _cluster-config-schema:

Cluster Config Schema v2
========================

The cluster config controls many OnDemand features including job submission, shell access, names in menus.

*****************
First an example:
*****************

Below is the production configuration for OSC's Owens cluster.

.. code-block:: yaml

  ---
  v2:
    metadata:
      title: "Owens"
      url: "https://www.osc.edu/supercomputing/computing/owens"
      hidden: false
    login:
      host: "owens.osc.edu"
    job:
      adapter: "torque"
      host: "owens-batch.ten.osc.edu"
      lib: "/opt/torque/lib64"
      bin: "/opt/torque/bin"
      version: "6.0.1"
    custom:
      pbs:
        host: "owens-batch.ten.osc.edu"
        lib: "/opt/torque/lib64"
        bin: "/opt/torque/bin"
        version: "6.0.1"
      moab:
        host: "owens-batch.ten.osc.edu"
        bin: "/opt/moab/bin"
        version: "9.0.1"
        homedir: "/var/spool/moab"
      rsv_query:
        torque_host: "owens-batch.ten.osc.edu"
        torque_lib: "/opt/torque/lib64"
        torque_bin: "/opt/torque/bin"
        torque_version: "6.0.1"
        moab_host: "owens-batch.ten.osc.edu"
        moab_bin: "/opt/moab/bin"
        moab_version: "9.0.1"
        moab_homedir: "/var/spool/moab"
        acls:
          - adapter: "group"
            groups:
              - "sysall"
              - "sappall"
              - "clntall"
            type: "blacklist"
    batch_connect:
        basic:
          script_wrapper: "module restore\n%s"
        vnc:
          script_wrapper: "module restore\nmodule load ondemand-vnc\n%s"

.. warning::
  Quick warning: be aware that YAML requires the use of spaces as indentation characters, tabs are not permitted by `the YAML spec`_.

.. _the YAML spec: http://yaml.org/spec/1.2/spec.html#id2777534

************
A Break Down
************

v2:
###

Version 2 is the current schema, and is the top level mapping for the cluster configuration.

.. code-block:: yaml

  ---
  v2:

meta:
#####

Meta describes how the cluster will be displayed to the user

.. code-block:: yaml

  metadata:
      # title: is the display label that will be used anywhere the cluster is referenced
      title: "Owens"
      # url: provides the ability to show a link to information about the cluster
      url: "https://www.osc.edu/supercomputing/computing/owens"
      # hidden: setting this to true causes Ondemand to not show this cluster to the user, the cluster is still available for use by other applications
      hidden: false

login:
######

Login controls what hosts should be used when trying to SSH via the Shell app. Used by the Dashboard and the Job Composer (MyJobs).

.. code-block:: yaml

    login:
      host: "owens.osc.edu"

job:
####

The job mapping is specific to a cluster's resource manager.

.. code-block:: yaml

    job:
      adapter: "torque"
      host: "owens-batch.ten.osc.edu"
      lib: "/opt/torque/lib64"
      bin: "/opt/torque/bin"
      version: "6.0.1"

bin_overrides:
--------------

`bin_overrides` adds the ability for a site to specify full paths to alternatives to the configured resource manager's client executables. This advanced feature allows a site considerable flexibilty to write wrappers to handle logging, environment or default setting, or use 3rd party API compatible alternative clients without having to alter the resource manager installation.

.. warning ::
    `bin_overrides` is an advanced feature. OOD relies both on return codes from clients, and on parsing the standard output in order to get information about submitted jobs. Care and testing is recommended.

.. code-block :: yaml

    # An example in Slurm
    job:
      adapter: "slurm"
      bin: "/opt/slurm/bin"
      conf: "/opt/slurm/etc/slurm.conf"
      bin_overrides:
          squeue: "/usr/local/slurm/bin/squeue_wrapper"
          # Override just want you want/need to
          # scontrol: "/usr/local/slurm/bin/scontrol_wrapper"
          sbatch: "/usr/local/slurm/bin/sbatch_wrapper"
          # Will be ignored because bsub is not a command used in the Slurm adapter
          bsub: "/opt/lsf/bin/bsub"

Adapter support for this feature is mixed. For example for Slurm `sbatch`, `scontrol`, `scancel` and `squeue` are all supported. For Torque only `qsub` is supported. Unsupported options are ignored.

custom:
#######

The custom mapping is a space that is available for extension, and does not have a schema. In OSC's usage the custom namespace has been used to provide more cluster-specific information for in-house custom applications.

batch_connect:
##############

Batch connect controls the defaults for interactive applications such as Jupyter or interactive desktops.

.. code-block:: yaml

    batch_connect:
        basic:
          script_wrapper: "module restore\n%s"
        vnc:
          script_wrapper: "module restore\nmodule load ondemand-vnc\n%s"

Script wrappers may contain Bash statements, and are useful for setting up a default environment, and or cleaning up after a script. The keys `basic` and `vnc` refer to the two types of batch connect application templates. `script_wrapper's` have the content of a batch connect script interpolated into them. String interpolation is performed using `sprintf`, with the script's content replacing the `%s`.

.. note::

  The user is responsible for providing the `%s` that is used to place the script content. If a `script_wrapper` is provided without `%s` then batch connect applications are unlikely to work properly.