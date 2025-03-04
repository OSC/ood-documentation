.. _resource-manager-systemd:

Systemd
=======

Open OnDemand can use SystemD timers to schedule a 'job'.  Sites can use this adapter for short
lived jobs or to use resources outside of your compute pool (like login nodes).


The adapter is similar to the linuxhost adaptor with the following options:


``submit_host``
  The address to submit to.
``ssh_hosts``
  System names that are connected to via ssh (list all posabilities if the above is a RR-DNS name).
``timeout``
  is used to set a 'walltime' after which the job is killed.
``debug``
  enable debugging for the cluster.
``strict_host_checking``
  will force SSH to use strict host checking.
``ssh_keyfile``
  If you want to provide a non-standard ssh identify file (equivalent to the -i option in SSH).

Example Cluster Configuration
-----------------------------

A YAML cluster configuration file for a Linux host might look like:

.. code-block:: yaml
   :emphasize-lines: 10-

   # /etc/ood/config/clusters.d/owens_login.yml
   ---
   v2:
     metadata:
       title: "Owens"
       url: "https://www.osc.edu/supercomputing/computing/owens"
       hidden: true
     login:
       host: "owens.osc.edu"
     job:
       adapter: "systemd"
       submit_host: "owens.osc.edu"  # This is the head for a login round robin
       ssh_hosts: # These are the actual login nodes
         - owens-login01.hpc.osc.edu
         - owens-login02.hpc.osc.edu
         - owens-login03.hpc.osc.edu
       site_timeout: 7200
       debug: true
       # Enabling strict host checking may cause the adapter to fail if the user's known_hosts does not have all the roundrobin hosts
       strict_host_checking: false
       ssh_keyfile: "~/.ssh/non_standard_key_location.pem"

