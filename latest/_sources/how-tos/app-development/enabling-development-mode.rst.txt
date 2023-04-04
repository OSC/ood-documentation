.. _enabling-development-mode:

Enabling App Development
========================

Enable in OnDemand v1.6+:
.........................

Here are example steps to enable a user "efranz", assuming efranz's home directory is at ``/home/efranz``:

#. Create a symlink so OnDemand finds efranz's apps:

   .. code:: sh

      sudo mkdir -p /var/www/ood/apps/dev/efranz
      cd /var/www/ood/apps/dev/efranz
      sudo ln -s /home/efranz/ondemand/dev gateway


#. Have efranz access the Dashboard, and efranz will see the Develop dropdown


Enable in OnDemand v1.4 & v1.5:
...............................

Here are example steps to enable a user "efranz", assuming efranz's home directory is at ``/home/efranz``:

#. Create a symlink so OnDemand finds efranz's apps:

   .. code:: sh

      sudo mkdir -p /var/www/ood/apps/dev/efranz
      cd /var/www/ood/apps/dev/efranz
      sudo ln -s /home/efranz/ondemand/dev gateway

#. Create dev directory ``/home/efranz/ondemand/dev`` where efranz's dev apps will go (or ask efranz to do that)
#. Have efranz access the Dashboard, and efranz will see the Develop dropdown


Enable in OnDemand v1.3:
........................

Here are example steps to enable a user "efranz", assuming efranz's home directory is at ``/home/efranz``:

#. Create dev directory ``/home/efranz/ondemand/dev`` where efranz's dev apps will go (or ask efranz to do that)
#. Have efranz access the Dashboard, and efranz will see the Develop dropdown. (if this doesn't happen, )

.. note::

   The rest of the documentation below assumes you are working with OnDemand 1.4+.


Specify dedicated host for development (optional)
....................................................

The default host for the shell app is typically a login node. If this node does not contain a similar environment as the host OnDemand is installed on, including access to Software Collection (SCL) packages, it may be useful to provide developers a dedicated development host they can SSH to. This could even be the OnDemand host itself. If you configure the OnDemand dashboard to know about the dedicated development host, the dashboard will present links to open the shell app to this host.

To specify a dedicated development host so OnDemand, set ``OOD_DEV_SSH_HOST`` environment variable for the dashboard in the file ``/etc/ood/config/apps/dashboard/env``. For example at OSC one of our OnDemand installs uses ondemand-test.osc.edu for the development host so we have this line: `OOD_DEV_SSH_HOST="ondemand-test.osc.edu" <https://github.com/OSC/osc-ood-config/blob/bde54e4c5a9fd756f74ac981f8c607320e9a0bf0/ondemand.osc.edu/apps/dashboard/env#L20>`_


Make everyone a developer by default (optional)
...............................................

To revert to the way developer enabling worked in OnDemand 1.3, change the nginx_stage app_root configuration for dev apps by modifying /etc/ood/config/nginx_stage.yml and replacing

.. code-block:: yaml
   :emphasize-lines: 2

   app_root:
     dev: '/var/www/ood/apps/dev/%{owner}/gateway/%{name}'
     usr: '/var/www/ood/apps/usr/%{owner}/gateway/%{name}'
     sys: '/var/www/ood/apps/sys/%{name}'


with


.. code-block:: yaml
   :emphasize-lines: 2

   app_root:
     dev: '~%{owner}/%{portal}/dev/%{name}'
     usr: '/var/www/ood/apps/usr/%{owner}/gateway/%{name}'
     sys: '/var/www/ood/apps/sys/%{name}'

Then users can just create the directory ``~/ondemand/dev`` and the Develop dropdown will appear.

.. warning:: If you do this, it is recommended that you treat the node that OnDemand is running on as a login node, as you are effectively giving those users shell access by letting them run arbitrary code on the OnDemand node (of course the UID of the processes are still their regular unprivileged user UID).

If you do this, you still might want to restrict who sees the Develop dropdown in the Dashboard. To do that you can explicitly show or hide the dropdown in the Dashboard by setting ``Configuration.app_development_enabled`` to true based on one or more Ruby statements in the initializer ``/etc/ood/config/apps/dashboard/initializers/ood.rb``. Code in the initializer runs as the user. This code also has access to the `ood_support library <http://www.rubydoc.info/github/OSC/ood_support>`__ in which we provide some helper classes to work with User's and Groups. For example:


    .. code-block:: ruby

      Rails.application.config.after_initialize do
        Configuration.app_development_enabled = OodSupport::Process.groups.include?(
          OodSupport::Group.new("devgrp")
        )
      end

    Or if you know the id of the group, this will avoid reading the ``/etc/group``
    file:

    .. code-block:: ruby

      Rails.application.config.after_initialize do
        Configuration.app_development_enabled = Process.groups.include?(5014)
      end

    Or a specific user list:

    .. code-block:: ruby

      Rails.application.config.after_initialize do
        Configuration.app_development_enabled = %w(
          bgohar efranz bmcmichael
        ).include?(OodSupport::User.new.name)
      end
