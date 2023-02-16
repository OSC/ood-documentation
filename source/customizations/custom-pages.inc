.. _custom_pages_guide:

Custom Pages
------------

Custom pages allow administrators to add custom content to new dashboard pages.
These new pages are configured using layouts and widgets, in the same way as 
:ref:`customizing the layout for the dashboard <dashboard_custom_layout>`.

To create a custom page, add a layout under a new ``page_code`` to the ``custom_pages`` property object.
For more information on how to setup dashboard properties, see :ref:`OnDemand configuration files <ondemand-d-ymls>`

Custom pages have their own URL based on their ``page_code``: ``/sys/pun/dashboard/custom/page_code``.

The example configuration below creates a custom page with the page_code: ``documentation``.
It will render a layout with the ``pinned_apps`` widget under the URL: ``/sys/pun/dashboard/custom/documentation``.

.. code-block:: yaml

  custom_pages:
    documentation:
      rows:
        - columns:
            - width: 12
              widgets:
                - "pinned_apps"

.. figure:: /images/custom-pages-documentation.png
   :align: center

Links to the custom pages can be added the Help dropdown menu.
To add links to the Help menu use the configuration property ``help_menu``.
See the :ref:`documentation on adding urls to the Help menu <help_menu_guide>` for details and examples.

Adding custom pages links uses the same notation and attributes as when created for the custom Dashboard navbar.
See `menus-based-on-links`_.

.. code-block:: yaml

  # Adding a link to the custom page with page_code = "documentation"
  help_menu:
    - group: "Custom Pages"
    - page: "documentation"
      title: "Site Documentation"
      icon: "fas://book"

.. figure:: /images/def-page-links.png
   :align: center
