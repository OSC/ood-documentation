.. _install-pun-utility:

Install the PUN Utility
=======================

The PUNs are manipulated and maintained by the :ref:`nginx-stage` utility. This
tool is meant to by run by ``root`` or a user with ``sudoers`` privileges.

#. Clone and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src
      scl enable git19 -- git clone https://github.com/OSC/nginx_stage.git
      cd nginx_stage/
      scl enable git19 -- git checkout v{{ nginx_stage_version }}

#. Install it to its global location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => mkdir -p /opt/ood/nginx_stage
      # => cp ...

   This creates the :ref:`nginx-stage` config
   ``/opt/ood/nginx_stage/config/nginx_stage.yml`` and the ruby binstub/wrapper
   script ``/opt/ood/nginx_stage/bin/ood_ruby``.

   .. note::

      If you run an older Linux OS that creates user accounts starting at id
      500, then you will need to modify ``nginx_stage.yml`` - the configuration
      option ``min_uid: 1000`` accordingly.

#. Give the ``apache`` user ``sudo`` privileges to run the ``nginx_stage``
   command. To do this, generate a ``sudoers_ood`` file in ``~/ood/src``
   directory:

   ::

      Defaults:apache     !requiretty, !authenticate
      apache ALL=(ALL) NOPASSWD: /opt/ood/nginx_stage/sbin/nginx_stage

   and then copy this to ``/etc/sudoers.d/ood``:

   .. code-block:: sh

      sudo cp ~/ood/src/sudoers_ood /etc/sudoers.d/ood
      sudo chmod 440 /etc/sudoers.d/ood

   Our ``/etc/sudoers`` file includes files in ``/etc/sudoers.d``:

   .. code-block:: sh

      sudo tail -n 2 /etc/sudoers
      ## Read drop-in files from /etc/sudoers.d (the # here does not mean a comment)
      #includedir /etc/sudoers.d

#. Schedule a cron job that automatically cleans up inactive user PUNs. To do
   this, generate the file ``/etc/cron.d/ood`` with the following contents:

   .. code-block:: sh

      #!/bin/bash

      PATH=/sbin:/bin:/usr/sbin:/usr/bin
      0 */2 * * * root [ -f /opt/ood/nginx_stage/sbin/nginx_stage  ] && /opt/ood/nginx_stage/sbin/nginx_stage nginx_clean 1>/dev/null

   This will clean up inactive PUNs every two hours.

#. Stage the NGINX configuration files for the system web applications:

   .. code-block:: sh

      sudo mkdir -p /var/lib/nginx/config/apps/sys
      sudo touch /var/lib/nginx/config/apps/sys/dashboard.conf
      sudo touch /var/lib/nginx/config/apps/sys/shell.conf
      sudo touch /var/lib/nginx/config/apps/sys/files.conf
      sudo touch /var/lib/nginx/config/apps/sys/file-editor.conf
      sudo touch /var/lib/nginx/config/apps/sys/activejobs.conf
      sudo touch /var/lib/nginx/config/apps/sys/myjobs.conf
      sudo /opt/ood/nginx_stage/sbin/nginx_stage app_reset --sub-uri=/pun
