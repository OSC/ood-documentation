Additional configurations needed.
---------------------------------

Here is a list of additional configurations that are needed to achieve full
compliance with the `WCAG`_ 2.2 guidelines.  Open OnDemand cannot ship with
as they may be site specific.


* `WCAG criterion 2.4.5 "Multiple Ways"`_: Centers need to enable the :ref:`show_all_apps_link configuration <show_all_apps_link>`
  to complete this criteria.
* `WCAG criterion 3.2.6 "Consistent Help"`_: Centers need to :ref:`extend the help menu <help_menu_guide>`
  to complete this criteria.
* Links should open in the current tab or give warning when they open in a new tab or window.
  This is to adhere to `WCAG Technique G200 "New Tabs"`_ and `WCAG Technique G201 "Advanced warning for new tabs"`_.
  Note this applies any custom :ref:`menus-for-custom-pages` your center may have created.

.. _WCAG: https://www.w3.org/WAI/standards-guidelines/wcag/
.. _WCAG criterion 3.2.6 "Consistent Help": https://www.w3.org/TR/WCAG22/#consistent-help
.. _WCAG criterion 2.4.5 "Multiple Ways": http://www.w3.org/TR/WCAG20/#navigation-mechanisms-mult-loc

.. _WCAG Technique G200 "New Tabs": https://www.w3.org/WAI/WCAG22/Techniques/general/G200
.. _WCAG Technique G201 "Advanced warning for new tabs": https://www.w3.org/WAI/WCAG22/Techniques/general/G201