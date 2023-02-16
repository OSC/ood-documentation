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

Limit auto generated menu bars
..............................

As described in the previous section, the system will generate new dropdown
menus for every ``category`` it discovers.

If you wish to add or remove which categories create dropdown menus
use the :ref:`nav_categories configuration property <nav_categories>`.

.. tip::
    Should you need more granular control over the navigation bar,
    read :ref:`fully-customizing-the-navbar` below.

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


Full navigation menu definition
********************************

full control on the menu links, order, and grouping.
  Use the ``links`` array to define the list of navigation links for the menu. 
  Use the ``group`` keyword to create subsections within the navigation menu and organize the links as you require.

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

.. _applications_based_menu:

Menu based on applications
**************************

simpler to configure, order is based on the position in the array.
  Items are automatically grouped based on the applications ``subcategory``. Use the ``apps``
  array to define the app tokens for this navigation menu.

.. code-block:: yaml
  
  nav_bar:
    - title: "My Apps"
      icon: "fas://window-restore"
      apps:
        - "sys/Rstudio/*"
        - "sys/bc_desktop"

.. figure:: /images/def-apps-menu.png
   :align: center

.. _navbar_links_guide:

Navigation Links
****************

Navigation links can be used as top level navigation items or as links within a navigation menu.

Static links
************

 these are pre-defined links ready to use with a simple string definition.
  Currently supported static links are: ``all_apps``, ``sessions``, ``support_ticket``, ``docs``, ``products_dev``, ``products_usr``, ``log_out``, and ``restart``.

.. code-block:: yaml

  nav_bar:
    # Navigation link
    - title: "Menu Item"
      links:
        - "all_apps"
        - "sessions"
        - "support_ticket"
        - "docs"
        - "products_dev"
        - "products_usr"
        - "log_out"
        - "restart"

.. figure:: /images/def-static-links.png
   :align: center

App links
*********

applications identified by the tokens are added to the menu.
  When configured as a top level link, only one application token is supported.
  If the token matches multiple applications, the navigation entry is ignored.

  When configured as a ``links`` array item, the subcategory will not be used to group the matched applications.
  The definition order is respected when rendering the links.
  If grouping is required, use the ``group`` property to add the desired structure as shown in the
  :ref:`applications based menu above. <applications_based_menu>`

.. code-block:: yaml

  nav_bar:
    # Top level link
    - "sys/bc_desktop"
    # Navigation link
    - title: "Menu Item"
      links:
        # within the links property, a string can be used.
        - "sys/bc_desktop"
        # apps property supports a single string token
        - apps: "sys/bc_desktop"
        # apps property supports array of application tokens
        - apps: ["sys/bc_desktop"]

.. figure:: /images/def-apps-link.png
   :align: center

Profile links
*************

to create links to change the user profile to the one identified by the ``profile`` property.

.. code-block:: yaml

  nav_bar:
    # Top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      profile: "team1"
      new_tab: true # optional, defaults to false
    # Navigation link
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          profile: "team1"
          new_tab: true # optional, defaults to false

Custom page links
*****************

to create links to a custom page identified by the ``page`` property.

.. code-block:: yaml

  nav_bar:
    # Top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      page: "documentation"
      new_tab: true # optional, defaults to false
    # Navigation link
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          page: "documentation"
          new_tab: true # optional, defaults to false

Full link definition
********************

to full control of the URL the link goes to. It accepts relative and absolute URLs.

.. code-block:: yaml

  nav_bar:
    # Top level link
    - title: "Title"
      icon: "fa://desktop" # optional, defaults to fas://cog
      url: "/docs"
      new_tab: true # optional, defaults to false
    # Navigation link
    - title: "Menu Item"
      links:
        - title: "Title"
          icon: "fa://desktop" # optional, defaults to fas://cog
          url: "/docs"
          new_tab: true # optional, defaults to false

**Profile links**, **custom page links**, and **full link definitions** will render the same
look and feel navigation link as a menu item or as a top level link. The only difference will be the generated URL.

.. figure:: /images/def-navigation-link.png
   :align: center
