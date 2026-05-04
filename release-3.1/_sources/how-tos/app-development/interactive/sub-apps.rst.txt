
Sub-Apps and Reconfiguring exsting apps
=======================================

Sub-Apps are a term we use for providing variants of existing apps.
They act as a child to the existing parent application.  That is,
they inheret all the options and scripts from the existing application
and override some or all of options.

You may want to do this to provide variants of existing apps.

In fact, this is how the ``bc_desktop`` application works. Open OnDemand
ships the base app and sites provide sub apps with configurations specific
to their site.

The way it works is this: Let's say you  have an existing application in ``/var/www/ood/apps/sys/my_app``.

You have 2 options for supplying sub-app overrides.

  * Place new ``form.yml`` files in ``/etc/ood/config/apps/my_app``.
  * OR provide new ``form.yml`` files in  ``/var/www/ood/apps/sys/my_app/local``.

There are pros and cons to each scheme. With the former, you sperate the overriedes (the sub-apps)
and the actuall app. The subapps residing in ``/etc/ood`` and the actual apps residing in ``/var/www``.
This would allow you to update one without having to update the other.

With latter scheme you keep the overrides with the main application itself. This has the benefit
of having everything in the same place, perhaps a git repository so that the apps (the main app and
the sub-app) get updated together.

.. _quick-launch-apps:

Quick Launch Apps
..................

Quick launch apps are a special version of Sub-Apps that have all their
from options with hard coded values. Indeed, they're not really options
at all as users will not be able to *choose* anything.

Let's see an example for ``my_app``.

Here we have the regularly defined form for this application and it
has choices for the account to use and the amount of cores to request.

.. code-block:: yaml

  # /var/www/ood/apps/sys/my_app/form.yml
  ---

  # the cluster(s) this app can submit jobs to.
  cluster: "owens"

  # 'form' is a list of form choices for this app. Here we're allowing users to set
  # the account and the number of cores they want to request for this job.
  form:
    - bc_account
    - cores

This will allow users to choose their account and cores.

However, if we use preset values, users only need to click the icon to submit
the job. That is, they will not be given the form to fill out choices, they
will simply submit the job directly with the values that the administrator has
chosen for them.

.. code-block:: yaml

  # /var/www/ood/apps/sys/my_app/local/preset.yml
  # or
  # /etc/ood/config/apps/my_app/preset.yml
  ---

  # the cluster(s) this app can submit jobs to.
  cluster: "owens"

  # this form has values set in the attributes section for all form items.
  # so users will submit a job with account abc123 and request 1 core without
  # being presented with any choice.
  form:
    - bc_account
    - cores
  attributes:
    bc_account:
      value: 'abc123'
    cores:
      value: 1

Now users will be presented with both variants. ``My App`` and
``My App: preset``.  The system used the name ``preset`` based
on the name of the file.