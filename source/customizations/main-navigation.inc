.. _navbar_guide:

Custom Dashboard Navbar
-----------------------

From OnDemand 2.1, there is a new way of customizing the top navigation bar.

.. figure:: /images/main-navigation-menu.png
   :align: center

We can define a custom left hand side navbar using the configuration property ``nav_bar``.
This will replace the navigation items: *Apps*, *Files*, *Jobs*, *Clusters*, *Interactive Apps*, and *My Interactive Sessions*
in the picture above.

We can, as well, define a custom right hand side navbar using the configuration property ``help_bar``.
This will replace the navigation items: *Develop*, *Help*, *Logged in as* , and *Log Out* in the picture above.

For more information on how to setup these properties, see :ref:`OnDemand configuration files <ondemand-d-ymls>`

A custom navigation definition is a list of navigation items.
A navigation item could be a navigation menu or a navigation link.
A navigation menu contains a list of navigation links with optional link groups.

Navigation Menus
......................

There are several ways of creating a navigation menu.

* **Full navigation menu definition:** full control on the menu links, order, and grouping.
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

.. _applications_based_menu:

* **Menu based on applications:** simpler to configure, order is based on the position in the array.
  Items are automatically grouped based on the applications ``subcategory``. Use the ``apps``
  array to define the app tokens for this navigation menu.

.. code-block:: yaml
  
  nav_bar:
    - title: "My Apps"
      icon: "fas://window-restore"
      apps: [ "sys/Rstudio/*", "sys/bc_desktop" ]

.. figure:: /images/def-apps-menu.png
   :align: center

* **Applications category:** it is possible to create a navigation menu by using the name of an application ``category``
  as defined in the manifest file. The menu title will be the ``category``, applications will be grouped by ``subcategory``.
  It is not possible to set an icon. The ``category`` matching is case insensitive.

.. code-block:: yaml
  
  nav_bar:
    - "interactive apps"

.. figure:: /images/def-category-menu.png
   :align: center

* **Menu template:** these are pre-configured navigation menus that are currently used in the default OnDemand Dashboard navbar.
  The supported templates are: ``all_apps``, ``featured_apps``, ``sessions``, ``develop``, ``help``, ``log_out``, and ``user``.

.. code-block:: yaml
  
  nav_bar:
    - "all_apps"
    - "featured_apps"
    - "sessions"
    - "develop"
    - "help"
    - "log_out"
    - "user"

.. figure:: /images/def-templates-menu.png
   :align: center

.. _navbar_links_guide:

Navigation Links
......................

Navigation links can be used as top level navigation items or as links within a navigation menu.

* **Static links:** these are pre-defined links ready to use with a simple string definition.
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

* **App links:** applications identified by the tokens are added to the menu.
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

* **Profile links:** to create links to change the user profile to the one identified by the ``profile`` property.

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

* **Custom page links:** to create links to a custom page identified by the ``page`` property.

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

* **Full link definition:** to full control of the URL the link goes to. It accepts relative and absolute URLs.

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
