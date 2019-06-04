.. _enabling-development-mode:

Enabling App Development
========================

There are three steps to enabling app development:

1. The PUN must have the config set so the app root looks to the path in the user's home directory, or whatever per-user path dev apps should reside. This is configurable in the nginx_stage, though the default template string can be used as is.
2. The Dashboard app needs to be informed that developer mode is enabled for the user, in order to show the Develop dropdown. By default, the Dashboard does this based on the existence of the path specified by ``OOD_DEV_APPS_ROOT`` which is set by taking the parent path of the interpolated value of ``app_root`` for dev apps (`see the example nginx_stage.yml config file <https://github.com/OSC/ondemand/blob/d85a3982d69746144d12bb808d2419b42ccc97a1/nginx_stage/share/nginx_stage_example.yml#L145-L159>`_). There are also other options for configuring the Dashboard at the bottom of this page.
3. Specify the development host, if it will differ from the default host for the shell app by setting it in ``OOD_DEV_SSH_HOST`` environment variable for the dashboard in the file ``/etc/ood/config/apps/dashboard/env``. When developing apps, it is necessary to have access to the same versions of Ruby and NodeJS that are running on the OnDemand node. If the default ssh host is not the OnDemand node, then setting ``OOD_DEV_SSH_HOST`` to a host developers can ssh to with the same Software Collection (SCL) packages will help.

In OnDemand 1.3, the app root for a dev app was set in the PUN config to ``'~%{owner}/%{portal}/dev/%{name}'``. This means for a user with the home directory ``/home/efranz`` in a default OnDemand install the root directory for the dev apps would be ``/home/efranz/ondemand/dev``. If a user did ``mkdir -p ~/ondemand/dev`` and reloaded the Dashboard app, the Develop dropdown would appear and users could deploy apps in their home directory and launch them.

In OnDemand 1.4, the app root for a dev app has been changed to ``'/var/www/ood/apps/dev/%{owner}/gateway/%{name}'``. So for user ``efranz`` this would be ``/var/www/ood/apps/dev/efranz/gateway/``. To enable efranz to develop apps, the administrator can then do the following:

.. code:: sh

   sudo mkdir -p /var/www/ood/apps/dev/efranz
   cd /var/www/ood/apps/dev/efranz
   sudo ln -s /home/efranz/ondemand/dev gateway

Then a user can create the dev directory in their home directory i.e. ``/home/efranz/ondemand/dev``.

If you want to revert to the previous functionality of 1.3, where every user can run dev apps in their home directory, `use the second example mapping here <https://github.com/OSC/ondemand/blob/d85a3982d69746144d12bb808d2419b42ccc97a1/nginx_stage/share/nginx_stage_example.yml#L156-L159>`_ in the ``/etc/ood/config/nginx_stage.yml`` config file. If you do this, it is recommended that you treat the node that OnDemand is running on as a login node, as you are effectively giving those users shell access by letting them run arbitrary code on the OnDemand node (of course the UID of the processes are still their regular user UID).

By default the Dashboard will assume it is running in "Developer mode" if the dev apps root directory exists (specified by the environment variable ``OOD_DEV_APPS_ROOT``). If you want to change this behavior, these are the options:

.. list-table:: Dashboard configuration for app development

   * - Action
     - Result
   * - Set ``OOD_APP_DEVELOPMENT=1`` in ``/etc/ood/config/apps/dashboard/env``
     - Developer mode will always be enabled in the Dashboard providing a Develop Dropdown. This can help with discoverability, as user's do not need to create the dev root directory prior to seeing the Develop dropdown. This only makes sense if every user can develop apps.
   * - Set ``Configuration.app_development_enabled`` to true based on one or more Ruby statements in ``/etc/ood/config/apps/dashboard/initializers/ood.rb``
     - Code in the initializer runs as the user. This code also has access to the `ood_support library <http://www.rubydoc.info/github/OSC/ood_support>`__ in which we provide some helper classes to work with User's and Groups.

       If you want to restrict app development mode to group membership, you could
       do this:

       .. code-block:: ruby

          Configuration.app_development_enabled = OodSupport::Process.groups.include?(
            OodSupport::Group.new("devgrp")
          )

       Or if you know the id of the group, this will avoid reading the ``/etc/group``
       file:

       .. code-block:: ruby

          Configuration.app_development_enabled = Process.groups.include?(5014)

       Or a specific user list:

       .. code-block:: ruby

          Configuration.app_development_enabled = %w(
            bgohar efranz bmcmichael
          ).include?(OodSupport::User.new.name)
      

.. note::

   The way app development is enabled is a bit clunky. We will be exploring
   other options to reduce the load on the admin in supporting app developers
   in the future. If you have any thoughts or ideas please share them on our
   `Discourse instance. <https://discourse.osc.edu/>`_
