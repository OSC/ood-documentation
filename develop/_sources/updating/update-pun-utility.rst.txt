.. _update-pun-utility:

Update the PUN Utility
======================

The PUN utility is maintained by the :ref:`nginx-stage` project. Assuming you
previously installed it with :ref:`install-pun-utility` you can update it with
the following directions.

Do I need to update?
--------------------

Latest version: ``v0.2.1``

You can compare this to the locally installed :ref:`nginx-stage` with the
following command:

.. code-block:: sh

   /opt/ood/nginx_stage/sbin/nginx_stage -v
   #=> nginx_stage, version 0.2.1

where the version number should be given at the end of the line. If the version
numbers match then you can skip this update.

Instructions to update
----------------------

#. Fetch the latest changes and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src/nginx_stage
      scl enable git19 -- git fetch
      scl enable git19 -- git checkout v0.2.1

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/nginx_stage
      # => cp ...

   .. note::

      This will not override your previous configuration file located at::

        /opt/ood/nginx_stage/config/nginx_stage.yml

      as well as the ruby binstub/wrapper script located at::

        /opt/ood/nginx_stage/bin/ood_ruby

#. Clean up app configuration files that point to nonexistant apps:

   .. code-block:: sh

      sudo /opt/ood/nginx_stage/sbin/nginx_stage app_clean

#. Rebuild all the app configuration files in case the template has changed:

   .. code-block:: sh

      sudo /opt/ood/nginx_stage/sbin/nginx_stage app_reset --sub-uri=/pun

#. Shutdown all user PUNs that do not currently have active connections:

   .. code-block:: sh

      sudo /opt/ood/nginx_stage/sbin/nginx_stage nginx_clean

   This is so that the user configuration files are regenerated when the user's
   PUN starts back up. Any PUNs that do not get shutdown (they had an active
   connection) will eventually be shutdown when the user eventually
   disconnects due to the cron job.
