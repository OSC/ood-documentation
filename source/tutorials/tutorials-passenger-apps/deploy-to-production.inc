Publish App
-----------

Publishing an app requires two steps:

#. Updating the ``manifest.yml`` to specify the category and optionally subcategory, which indicates where in the dashboard menu the app appears.

#. Having an administrator checkout a copy of the production version to a directory under ``/var/www/ood/apps/sys``.


Steps:

#. Add category to manifest so the app appears in the Files menu:

    .. code-block:: diff

        name: Quota
        description: Display quotas
        icon: fa://hdd-o
        +category: Files
        +subcategory: Utilities

#. Version these changes. Click **Shell** button on app details view, and then ``commit`` the changes:

    .. code-block:: sh

       git add .
       git commit -m "update manifest for production"

       # if there is an external remote associated with this, push to that
       git push origin master

#. As the admin, ``sudo copy`` or ``git clone`` this repo to production

    .. code-block:: sh

       # as sudo on OnDemand host:
       cd /var/www/ood/apps/sys
       git clone /users/PZS0562/efranz/ondemand/dev/quota


#. **Reload** the dashboard.

.. figure:: /images/app-dev-tutorial-ps-to-quota-published.png
   :align: center

   Every user can now launch the Quota from the Files menu.

.. warning::

   Accessing this new app for the first time will cause your NGINX server to restart,
   killing all websocket connections, which means resetting your active web-based OnDemand Shell sessions.