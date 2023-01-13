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

.. _module_file_dir:
.. describe:: module_file_dir (String, null)

  Specify a directory where module files per cluster exist. This directory
  should have module spider-json output as indicated by the command below.
  Open OnDemand will read these files and potentially show them in a from.

  ``$LMOD_DIR/spider -o spider-json $MODULEPATH > /some/directory/my_cluster.json``

  Default
    No directory given

    .. code-block:: yaml

      module_file_dir: null

  Example
    Look for json files in the /etc/reporting/modules directory.

    .. code-block:: yaml

      module_file_dir: /etc/reporting/modules

.. _auto_groups_filter:
.. describe:: auto_groups_filter (String, null)

  Specify a filter for the :ref:`automatic form option <auto-bc-form-options>` ``auto_groups``.

    Default
      No filter given. All Unix groups will be shown.

    .. code-block:: yaml

      auto_groups_filter: null

  Example
    Only show Unix groups that start with ``P``.

    .. code-block:: yaml

      auto_groups_filter: '^P.+'

.. _remote_files_enabled:
.. describe:: remote_files_enabled (Boolean, false)

  Enable remote file browsing, editing and downloading.

  Default
    Remote files are disabled.

  .. code-block:: yaml

    remote_files_enabled: false

  Example
    Enable remote filesystems through ``rclone``.

    .. code-block:: yaml

      remote_files_enabled: true