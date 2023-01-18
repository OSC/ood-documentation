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

Links can be added the Help navigation menu to select the custom pages.
These links can be configured using the configuration property ``page_links``.

.. code-block:: yaml

  page_links:
    - page: "documentation"
      title: "Site Documentation"
      icon_uri: "fas://book"

.. figure:: /images/def-page-links.png
   :align: center

.. tip::
    If you require to update the ``Custom Pages`` header text, use the translation properties to set a new value.
    :ref:`See the customize text documentation <customization_localization>`
