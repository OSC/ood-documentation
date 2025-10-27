.. _resource-manager-slurm:

Slurm
=====

A YAML cluster configuration file for a Slurm resource manager on an HPC
cluster looks like:

.. warning::
  Open OnDemand's Slurm support defaults to issuing CLI commands with
  the ``--export`` flag set to ``NONE``, when Slurm's default is ``ALL``.
  This can cause issues with jobs that require ``srun``.

  Workarounds are currently to ``export SLURM_EXPORT_ENV=ALL``
  in a :ref:`script_wrapper <script_wrapper>` before any job scripts run.

  Alternatively, you can use ``copy_environment`` below with the caveat
  that the PUNs environment is very different from regular shell sessions.

.. important::
  The name of this YAML file should be equivalent to ``ClusterName`` in your
  cluster's ``.conf`` file.  This is important for the OnDemand system to automatically
  discover information from ``sacctmgr``.

.. code-block:: yaml
   :emphasize-lines: 8-

   # /etc/ood/config/clusters.d/my_cluster.yml
   ---
   v2:
      metadata:
        title: "My Cluster"
      login:
        host: "my_cluster.my_center.edu"
      job:
        adapter: "slurm"
        cluster: "my_cluster"
        bin: "/path/to/slurm/bin"
        conf: "/path/to/slurm.conf"
        # bin_overrides:
          # sbatch: "/usr/local/bin/sbatch"
          # squeue: ""
          # scontrol: ""
          # scancel: ""
        copy_environment: false

with the following configuration options:

``adapter``
  This is set to ``slurm``.
``cluster``
  The Slurm cluster name. **Optional**. This is passed to SLURM as ``-M <cluster>`` for some commands.

  .. warning::
    Using the ``cluster`` option is discouraged. This is because maintenance
    outages on the Slurm database will propagate to Open OnDemand.  Instead sites
    should use different ``conf`` files for each cluster to limit maintenance outages.
``bin``
  The path to the Slurm client installation binaries.
``conf``
  The path to the Slurm configuration file for this cluster. **Optional**.
``submit_host``
  A different, optional host to ssh to and *then* issue commands. **Optional**.
``bin_overrides``
  Replacements/wrappers for Slurm's job submission and control clients. **Optional**.

  Supports the following clients:

  - `sbatch`
  - `squeue`
  - `scontrol`
  - `scancel`

``copy_environment``
  Copies the environment of the PUN when issuing CLI commands. Default behavior
  for Open OnDemand is to use ``--export=NONE`` flag. Setting this to true will
  cause Open OnDemand to issue CLI commands with ``--export=ALL``. Though this may
  cause issues as the PUN's environment is very different than a regular shell session.

.. note::

   If you do not have a multi-cluster Slurm setup you can remove the ``cluster:
   "my_cluster"`` line from the above configuration file.

.. tip::

   When installing Slurm ensure that all nodes on your cluster including the node running the Open OnDemand server have the same `MUNGE <https://dun.github.io/munge/>`_ key installed. Read the `Slurm Quick Start Administrator Guide <https://slurm.schedmd.com/quickstart_admin.html>`_ for more information on installing and configuring Slurm itself.
