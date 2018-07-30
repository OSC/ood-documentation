.. _resource-manager-test:

Test Configuration
==================

.. warning::

   This is an experimental feature right now that may change drastically in the
   future. So always revisit this documentation after upgrading OnDemand and
   attempting to test your cluster configuration.

We currently provide an experimental :command:`rake` task underneath the
:ref:`dashboard` for testing your resource manager configuration in the cluster
configuration files.

#. For all :command:`rake` tasks we will need to be underneath the
   :ref:`dashboard`'s root directory (*this will change in the future*):

   .. code-block:: console

      $ cd /var/www/ood/apps/sys/dashboard

#. We will now list all available tasks that we can run:

   .. code-block:: console

      $ scl enable rh-ruby22 nodejs010 -- bin/rake -T test:jobs
      rake test:jobs           # Test all clusters
      rake test:jobs:cluster1  # Test the cluster: cluster1
      rake test:jobs:cluster2  # Test the cluster: cluster2

   This list is dynamically generated from all the available cluster
   configuration files that reside under
   :file:`/etc/ood/config/clusters.d/{*}.yml`.

#. For now let us test just a single cluster (in our example we use
   ``cluster1``, so you will need to replace it with the name of the cluster
   you configured):

   .. code-block:: console

      $ sudo su $USER -c 'scl enable rh-ruby22 nodejs010 -- bin/rake test:jobs:cluster1 RAILS_ENV=production'
      [sudo] password for user:
      Rails Error: Unable to access log file. Please ensure that /var/www/ood/apps/sys/dashboard/log/production.log exists and is writable (ie, make it writable for user and group: chmod 0664 /var/www/ood/apps/sys/dashboard/log/production.log). The log level has been raised to WARN and the output directed to STDERR until the problem is fixed.
      mkdir -p /home/user/test_jobs
      Testing cluster 'cluster1'...
      Submitting job...
      [2018-04-24 10:15:32 -0400 ]  INFO "execve = [{\"PBS_DEFAULT\"=>\"oak-batch.osc.edu\", \"LD_LIBRARY_PATH\"=>\"/opt/torque/lib64:/opt/rh/v8314/root/usr/lib64:/opt/rh/nodejs010/root/usr/lib64:/opt/rh/rh-ruby22/root/usr/lib64\"}, \"/opt/torque/bin/qsub\", \"-N\", \"test_jobs_cluster1\", \"-S\", \"/bin/bash\", \"-o\", \"/users/appl/jnicklas/test_jobs/output_cluster1_2018-04-24T10:15:32-04:00.log\", \"-l\", \"walltime=00:01:00\", \"-j\", \"oe\"]"
      Got job id '10820525.oak-batch.osc.edu'
      Job has status of queued
      Job has status of queued
      Job has status of queued
      Job has status of queued
      Job has status of completed
      Test for 'cluster1' PASSED!
      Finished testing cluster 'cluster1'

   Please **ignore** the ``Rails Error:`` message as this is just a *warning*
   that doesn't affect your OnDemand installation in any way. We are currently
   tracking this issue in GitHub at `OSC/dashboard#364
   <https://github.com/OSC/ood-dashboard/issues/364>`_.

   .. tip::

      We actually launch the :command:`rake` task with :command:`sudo` to best
      mimic the environment that the OnDemand applications are run under.

      You can run the :command:`rake` task as the current user, but it may lead
      to a *false positive* as your user environment may have the correct
      libraries and paths loaded in it that may not necessarily exist in the
      cleaner OnDemand application environment.

   This creates and submits a batch job that :command:`echo`'s a defined
   string. It then pings the batch server every 5 seconds until the job is
   completed. Finally, it parses the output file looking for the defined
   string. The test passes if it can find the string in the output file.

   If something fails at any point in the chain, then the test fails. This may
   require you to make edits to the corresponding cluster configuration file
   under :file:`/etc/ood/config/clusters.d/` and run the test again.

   .. note::

      If your job fails to submit because you need to supply more submission
      arguments, e.g., a queue, memory requirements, an account, etc. You can
      provide these command line arguments as a string with the environment
      variable ``SUBMIT_ARGS`` as:

      .. code-block:: console

         $ sudo su $USER -c 'scl enable rh-ruby22 nodejs010 -- bin/rake test:jobs:cluster1 RAILS_ENV=production SUBMIT_ARGS="-A myaccount"'

      Note that the ``SUBMIT_ARGS="..."`` is defined at the end of the command.
