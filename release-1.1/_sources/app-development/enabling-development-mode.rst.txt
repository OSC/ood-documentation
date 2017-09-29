.. _enabling-development-mode:

Enabling App Development
========================


1. Enable App Development Mode in Dashboard
-------------------------------------------

Enable App Development Mode in the Dashboard in two ways:

A. Enable for every user using environment variable
...................................................

In the root of the dashboard app, add these contents to a file ``.env.local``:


.. code-block:: sh

  OOD_APP_DEVELOPMENT=1

If this env var is present, ``Configuration.app_development_enabled`` will be
in the Dashboard app will be set to true, and the Develop dropdown will
appear.


B. Enable for specific users using custom initializer
.....................................................

Create a custom initializer file in the Dashboard app: ``config/initializers/ood.rb``

Add whatever Ruby code you want to set the ``Configuration.app_development_enabled`` flag.
This code will run as the user. This code also has access to the `ood_support
library <http://www.rubydoc.info/github/OSC/ood_support>`__ in which we provide
some helper classes to work with User's and Groups.

If you want to restrict displaying the Develop dropdown to a list of users,
you can do this:

.. code-block:: ruby

  Configuration.app_development_enabled = %w(
    bgohar efranz bmcmichael
  ).include?(OodSupport::User.new.name)

If you want to restrict app development mode to group membership, you could
do this:

.. code-block:: ruby

  Configuration.app_development_enabled = OodSupport::Process.groups.include?(
    OodSupport::Group.new(name: "devgrp")
  )

Or if you know the id of the group, this will avoid reading the ``/etc/group``
file:

.. code-block:: ruby

  Configuration.app_development_enabled = Process.groups.include?(5014)


2. Specify Development Shell Host
---------------------------------

When developing apps, you will eventually need to access the shell. It may be
necessary to have shell access to a host that has the same SCL packages that
OnDemand provides.

The developer app detail views provide a convenient "Shell" button to open a
Shell with the starting directory to be the directory of the application.

If the host with these SCL packages is different from the default host for the
OOD shell app, you can specify this host by setting ``OOD_DEV_SSH_HOST``
environment variable.

For example, at OSC we have provisioned a development host at apps-test.awesim.org
that developers can ssh to, which has a version of OnDemand running and
therefore has all the SCL packages installed. That host is ``apps-test.awesim.org``
so we set in the ``.env.local`` file ``OOD_DEV_SSH_HOST="apps-test.awesim.org"``.
