.. _ondemand-d-ymls:

ondemand.d/\*.yml files
=======================

Some configurations are held within yml files in the ``/etc/ood/config/ondemand.d/`` directory.
Open OnDemand will read all the ``.yml`` and ``.yml.erb`` files within this directory for
configurations.

To use a different directory other than this use the ``OOD_CONFIG_D_DIRECTORY`` environment variable
in the ``/etc/ood/config/apps/dashboard/env`` file.

.. describe:: pinned_apps (Array<Object>, null)

    An array of pinned app objects specifying what apps to pin to the dashboard.
    See the :ref:`documentation on pinned apps <dashboard_pinned_apps>` for details
    and examples.

    Default
      Don't pin any apps to the dashboard.

      .. code-block:: yaml

        pinned_apps: null


.. describe:: pinned_apps_menu_length: (Integer, 6)

    The maximum number of pinned apps in the 'Apps' menu bar.

    Default
      Show a maximum of 6 pinned apps.

      .. code-block:: yaml

        pinned_apps_menu_length: 6

    Example
      Show 10 items in the menu.

      .. code-block:: yaml

        pinned_apps_menu_length: 10


.. describe:: pinned_apps_group_by: (String, null)

  Group the pinned apps icons by this field in the dashboard.

  Default
    Do no group pinned apps by any field.

    .. code-block:: yaml

      pinned_apps_group_by: null

  Example
    Group the pinned apps by category.

    .. code-block:: yaml

      pinned_apps_group_by: "category"


.. describe:: dashboard_layout: (Object, null)

  Specify the dashboard layout.  Rearrange existing widgets
  and add more custom widgets. See the 
  :ref:`documentation on custom dashboard layouts <dashboard_custom_layout>`
  for details and examples.

  Default
    Do not change the default dashboard layout.

    .. code-block:: yaml

      dashboard_layout: null

.. describe:: files_enable_shell_button: (Bool, true)

  Specify if the Files App has a shell button to open files in.

  Default
    Files App has access to shell button.

    .. code-block:: yaml

      files_enable_shell_button: true

  Example
    Disable the terminal button in the Files App.

    .. code-block:: yaml

      files_enable_shell_button: false