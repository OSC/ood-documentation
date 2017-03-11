Add Cluster Configuration Files
===============================

**(Optional step)**

The Dashboard, File Explorer, and Shell Access can work without cluster
connection config files. These config files are required for:

- enable Shell Access to multiple named hosts outside of the local host OOD is
  running on
- use Active Jobs, My Jobs, or any other app that works with batch jobs

#. Create default directory for config files:

   .. code-block:: sh

      sudo mkdir -p /etc/ood/config/clusters.d

#. Add one config file for each host you want to provide access to. Each config
   file is a YAML file and must have the ``.yml`` suffix.

Here is the minimal YAML config required to specify a host that can be accessed
via Shell Access app. The filename is ``oakley.yml``:

.. code-block:: yaml

   ---
   v1:
     title: "Oakley"
     cluster:
       type: "OodCluster::Cluster"
       data:
         servers:
           login:
             type: "OodCluster::Servers::Ssh"
             data:
               host: "oakely.osc.edu"

- a cluster contains one ore more servers, with server names ``login``,
  ``resource_mgr`` and ``scheduler``
- special server keywords are:

  - ``login``
  - ``resource_mgr``
  - ``scheduler``
  - ``ganglia``

For Active Jobs and My Jobs to work, a cluster configuration must specify a
``resource_mgr`` to use.

.. code-block:: yaml

   ---
   v1:
     title: "Oakley"
     cluster:
       type: "OodCluster::Cluster"
       data:
         servers:
           login:
             type: "OodCluster::Servers::Ssh"
             data:
               host: "oakely.osc.edu"
           resource_mgr:
             type: "OodCluster::Servers::Torque"
             data:
               host: "oak-batch.osc.edu"
               lib: "/opt/torque/lib64"
               bin: "/opt/torque/bin"
               version: "6.0.1"

The name of the file becomes the key for this host. So ``oakley.yml`` cluster
config will have a key ``oakley``. My Jobs and other OOD apps that cache
information about jobs they manage will associate job metadata with this key.
