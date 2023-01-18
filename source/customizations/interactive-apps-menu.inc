.. _interactive_apps_menu_guide:

Interactive Apps Menu
----------------------

To define a custom interactive apps menu, use the configuration property ``interactive_apps_menu``.
The custom menu will replace the ``Interactive Apps`` left hand side navigation in the 
*Interactive Apps* and *My Interactive Sessions* pages.

.. figure:: /images/interactive-apps-menu.png
   :align: center


``interactive_apps_menu`` property supports a single navigation item. How to configure navigation items is described in the
:ref:`Custom Dashboard Navbar section <navbar_guide>`

.. code-block:: yaml

    interactive_apps_menu:
      title: "Custom Apps"
      links:
        - group: "Desktop"
        - apps: "sys/bc_desktop"
        - group: "Servers"
        - apps: "sys/Rstudio/*"
