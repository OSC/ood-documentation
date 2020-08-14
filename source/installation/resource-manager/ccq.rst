.. _resource-manager-cloudy-cluster:

Configure Cloudy Cluster (beta)
===============================

A YAML cluster configuration file for a Cloudy Cluster resource manager on an HPC
cluster looks like:

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
       adapter: "ccq"
       image: "my-default-image"
       cloud: "gcp"
       scheduler: "my_scheduler"
       bin: "/path/to/other/CCQ"
       jobid_regex: "different job_id regex: (?<job_id>\\d+) "
       # bin_overrides:
         # ccqstat: "/usr/local/bin/ccqstat"
         # ccqdel: ""
         # ccqsub: ""

with the following configuration options:

adapter
  This is set to ``ccq``.
image
  The default cloud image to use when launching jobs. There is no default.
cloud
  The cloud provider being used. Valid options are ``gcp`` or ``aws``. Defaults to ``gcp``.
scheduler
  The name of the scheduler being used. There is no default.
bin
  The path to the CCQ client installation binaries. Defaults to ``/opt/CloudyCluster/srv/CCQ``.
jobid_regex
  The regular expression to extract the job id from the ccqstat output. Defaults to ``job id is: (?<job_id>\\d+) you``.
  You should only need this if the ccqstat output changes format. If you are required to reconfigure, you'll need to
  extract the named group ``job_id`` as the default does.
bin_overrides
    Replacements/wrappers for CCQ's job submission and control clients. *Optional*

  Supports the following clients:

  - `ccqstat`
  - `ccqdel`
  - `ccqsub`

Common Issues
-------------

Prompted for input
******************

You may see this error when you initially try to start a job.  

.. code-block:: text

  The /opt/CloudyCluster/srv/CCQ/ccqsub command was prompted. You need 
  to generate the certificate manually in a shell by running 'ccqstat'
  and entering your username/password

This is because CCQ libraries require a certificate to be generated to communicate with the 
backend servers.  To remediate you'll simply have to login through a shell terminal and generate
a certificate. Do this by running the ``ccqstat`` command and entering your username and password
when prompted. If you're successful, the command will generate a ``ccqCert.cert`` in your home
directory that subsequent invocations will use.

Note these certificates expire, so you may have to generate them every so often or specify
a very distant expiry date when you do generate them.