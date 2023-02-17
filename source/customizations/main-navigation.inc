.. _navbar_guide:

Changing the Navigation bar
---------------------------

There are a couple ways to change the navigation bar in Open OnDemand, some
are simpler than others.

This section provides the outline of how the navigation bar is generated to begin
with, then details the various ways to modify it.

Once you understand how the navigation bar is generated automatically,
you can take steps to custimize it as you see fit.

.. _understanding-default-nav-bar:

Understanding the default navigation bar
........................................

Some navigation menus and links are built-in to the system. The system
will generate dropdown menus for ``Files``, ``Jobs``, ``Clusters`` and
``Interactive Apps`` automatically. It will also generate the link for
``My Interactive Sessions`` by default.

Here's an image of you'd expect to see by default.

.. figure:: /images/main-navigation-menu.png
    :align: center
    :alt: An image of the default navigation bar showing dropdown menus for files, jobs, clusters, interactive apps, and my interactive apps.

Open OnDemand is a platform for other applications, like Jupyter & RStudio.
As such, the default navigation bar builds itself based on what applications
it has discovered.  The system will search ``/var/www/ood/apps/sys/`` for these
applications.

Every application should have :ref:`app-development-manifest`.  The system reads
these manifests files and builds additional dropdown menus (or adds to existing menus)
based on the ``category`` field.

By default, the system will generate a new dropdown menu for every ``category``
it encounters.  Within each dropdown menu it will add seperators for each
``subcategory`` it encounters.

.. _limit-auto-generated-menu-bars:

Limit auto generated menu bars
..............................

As described in the previous section, the system will generate new dropdown
menus for every ``category`` it discovers.

If you wish to add or remove which categories create dropdown menus
use the :ref:`nav_categories configuration property <nav_categories>`.

.. tip::
    Should you need more granular control over the navigation bar,
    read :ref:`fully-customizing-the-navbar` below.

.. warning::

  Prior to 2.1, controlling which categories appear in the navigation bar was controlled
  by a Ruby initializer that you needed to modify. While the 2.x series will still support
  this scheme, Open OnDemand 3.0 will not.  3.0 will only support the ``nav_categories``
  property.

  Here is the `2.0 documentation for controling the navbar`_.

Using manifests to create menu items
....................................

As described in :ref:`understanding-default-nav-bar`, the system automatically
creates dropdown menus based on the applications it encounters.

So, with that knowledge, one can create or add to dropdown menus by creating
applications with the correct information in their `manifest.yml <app-development-manifest>`_.

It's fairly simple to make this application. Simply create the directory in the correct location
and create a `manifest.yml <app-development-manifest>`_.

* sudo mkdir /var/www/ood/apps/sys/<NEW MENU ITEM>
* sudo vi /var/www/ood/apps/sys/<NEW MENU ITEM>/manifest.yml

  .. code-block:: yaml

    ---
    # This is the text that will show up in the dropdown menu.
    name: Add Menu Items to the navbar

    # This will create the 'Links' dropdown menu if it doesn't already exist.
    category: Links
    description: |-
      A description of what the menu item does.
    icon: fa://clock-o   # icon for the link.
    url: 'https://openondemand.org/'

    # open link in new browser window or same browser window.
    new_window: true

.. tip::
    This scheme may be fine with one or two additional links. Should you need
    more granular control over the navigation bar, read :ref:`fully-customizing-the-navbar`
    below.

.. _fully-customizing-the-navbar:

Fully customizing the navigation bar
....................................

Since 2.1, Open OnDemand provides a way to completely control the navigation bar
through the ``nav_bar`` and ``help_bar`` :ref:`ondemand-d-ymls` configuration properties.

.. warning::
  As described in :ref:`understanding-default-nav-bar`, the system auto-generates
  dropdown menus based on the applications it discovers.  If the ``nav_bar`` or
  ``help_bar`` configurations are set, the system will **only** show what you've defined.

Before we look at how to modify it in detail, let's look at what the default
configuration would be (without showing any discovered apps).

.. code-block:: yaml

    # 'nav_bar' is the left side of the navigation bar.
    nav_bar:
      # 'apps' dropdown menu is shown if you've set 'pinned_apps'.
      - apps
      - files
      - jobs
      - clusters
      - interactive apps
      - my interactive sessions

      # 'all apps' is disabled by default, but would be next if you set 'show_all_apps_link'.
      # - all apps

    # 'help_bar' is the right side of the navigation bar.
    help_bar:
      - develop
      - help
      - user
      - logout

The configuration above would be equvialent to the default navigation bar as described
in :ref:`understanding-default-nav-bar`.

As menus are dynamically discovered *from your system*, this documentation can only cover
how a fresh install - with no other applications - would behave.

A custom navigation definition is a list of navigation items.
A navigation item could be a navigation menu or a navigation link.
A navigation menu contains a list of navigation links with optional link groups.

There are several ways of creating a navigation menu.

Menus by Application category
*****************************

One of the easiest ways to create menus is to create them based off of
the applications categories.

The title of the dropdown menu will be the ``category`` itself, and menu items
(applications) will be grouped by their ``subcategory``. It is not possible to
set an icon. The ``category`` matching is case insensitive.

Here's an example using the ``interactive apps`` ``category``. Just like the default
navigation bar, this will generate a dropdown menu of all the applications the system
has discovered in that ``category``.

As you can see from the image, the system has discovered eight applications in two
subcategories.

.. code-block:: yaml

  nav_bar:
    - "interactive apps"

.. figure:: /images/def-category-menu.png
    :align: center
    :alt: An open dropdown menu titled "Interactive Apps". The first submenu is titled "Desktops" and has two list items. The second submenu is titled "Servers" and has six list items.

Predefined templates
*********************

As you can see from the example default configuration in `fully-customizing-the-navbar`_, there
are several pre-defined navigation menus that you can use.

A complete list of predefined templates is:

* ``all_apps`` - The link to the all applications page.
* ``apps`` - A drop down menu of ``pinned_apps``. Note that you need to set ``pinned_apps`` for this to show up.
*  ``sessions`` - The link to "My Interactive Sessions" page.
* ``develop`` - The dropdown menu for developers, titled "Develop".
* ``help`` - The "Help" dropdown menu.
* ``log_out`` - The link to logout, titled "Logout".
* ``user`` - The "Logged in as <user>" text.

Here's an example of defining all of them and what that would look like.

.. code-block:: yaml

  nav_bar:
    - "all_apps"
    - "apps"
    - "sessions"
    - "develop"
    - "help"
    - "log_out"
    - "user"

.. figure:: /images/def-templates-menu.png
    :align: center
    :alt: An image of the navigation bar. From left to right the items are "All Apps" link, "Apps" dropdown menu, "My Interactive Sesssions" link, "Develop" drop down menu, "Help" drop down menu, "Logout" link and 'logged in as ood' text.

.. _menus-based-on-applications:

Menus based on applications
***************************

You can create dropdown menus based on applications the system can discover.

Menu items are automatically grouped based on the applications ``subcategory``.
Use the ``apps`` array to define the app tokens for this navigation menu.

The order of the menu items is based on the order you've defined.

.. code-block:: yaml

  nav_bar:
    - title: "My Apps"
      icon: "fas://window-restore"
      apps:
        - "sys/Rstudio/*"
        - "sys/bc_desktop"

.. figure:: /images/def-apps-menu.png
    :align: center
    :alt: An open dropdown menu titled "My Apps". The menu shows two submenus. The first is titled "Servers" and has five list items for all the discovered through the "sys/Rstudio/*" configuration. The second submenu is titled "Desktops" and has one list item for the discovered through the "sys/bc_desktop" configuration.


.. _menus-based-on-links:

Menus based on links
********************

Menus based on links provide even more granular control on how the dropdown menu is generated.

As seen in the previous sections, using an ``apps`` array will automatically generate
submenus based on the ``subcategory`` of the applications that have been discovered.

When using links, we can override this behaviour to provide different titles to
the submenus, or with no submenus and subtitles at all.

Let's look at this example using the same application tokens, but using ``links`` instead
of ``apps``. The system will discover and generate list items for the same eight applications,
only without **any** submenus.  It is simply a list of all the discovered applications with
no further grouping.

.. code-block:: yaml

  nav_bar:
    - title: "My Apps"
      icon: "fa://code"
      links:
        - "sys/Rstudio/*"
        - "sys/bc_desktop"

.. figure:: /images/app-links-no-group.png
    :align: center
    :alt: An open dropdown menu titled "My Apps". The menu has no submenus. It simply lists all eight the apps.

To add submenus, simply use the ``group`` attribute.

When ``links`` are used with the ``group`` attribute, the discovered applications
will now be grouped and submenu titles created based on the configuration provided.

This will look and feel similar to `menus-based-on-applications`_ with the exception
being that submenus are defined by the ``group`` configuration instead of the ``subcategory``
of the applications in the list.

.. code-block:: yaml

  nav_bar:
    - title: "My Apps"
      icon: "fa://code"
      links:
        - group: "RStudio"
        - "sys/Rstudio/*"
        - group: "Remote"
        - "sys/bc_desktop"

.. figure:: /images/def-full-menu.png
    :align: center
    :alt: An image showing one open drop down menu titled "My Apps". The first submenu, titled "Rstudio" has five list items that have been discovered through the "sys/Rstudio/*" configuration. The second submenu, titled "Remote" has one list item that has been discovered through the "sys/bc_desktop" configuration.

.. tip::
  You can also used predefined links (described above) in the ``links`` section here.


.. _menus-for-profile-links:

Menus for profile links
***********************

If you've enabled `Profiles <profiles_guide>` you can create navigation bar menus and
links to those profiles through the ``profile`` attribute.

.. code-block:: yaml

  nav_bar:
    # Single top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      profile: "team1"
      new_tab: true # optional, defaults to false

    # Dropdown menu
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          profile: "team1"
          new_tab: true # optional, defaults to false

.. _menus-for-custom-pages:

Menus for custom pages
**********************

If you've enabled `custom_pages_guide`_ you can create navigation menus
or single links directly to those pages through the the ``page`` attribute.

.. code-block:: yaml

  nav_bar:
    # Single top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      page: "documentation"
      new_tab: true # optional, defaults to false

    # Dropdown menu
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          page: "documentation"
          new_tab: true # optional, defaults to false

.. _menus-for-urls:

Menus for URLs
**************

You can even create menu items for relative and absolute URLs to link anywhere
through the ``url`` attribute.

.. code-block:: yaml

  nav_bar:
    # Single top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      url: "/docs"
      new_tab: true # optional, defaults to false

    # Dropdown menu
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          url: "https://openondemand.org/"
          new_tab: true # optional, defaults to false

.. figure:: /images/def-navigation-link.png
    :align: center
    :alt: An image of the navigation bar with a single link "Title" and an open dropdown menu titled "Menu Item". The dropdown menu has one list item titled "Title".
