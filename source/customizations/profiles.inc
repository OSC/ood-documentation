.. _profiles_guide:

Configuration Profiles
----------------------

.. note::

   The profile based configuration is an experimental feature. Not all properties have been migrated to be compatible.
   See the list of supported properties in the :ref:`configuration documentation <profile_properties>`

Configuration properties can be organized in a hierarchy using profiles. With profiles,
administrators can create different configuration settings within the same OnDemand installation.
A profile can be pre-selected or dynamically changed while using the Dashboard application.

To define profile properties, we have to group them under a profile name within the ``profiles`` keyword.
Multiple profiles can be created using different files, the configuration
logic will aggregate all profiles into a single consolidated object.

.. code-block:: yaml

  profiles:
    profile_name:
      config_property: config_value

OnDemand uses an inheritance and override approach for profiles.
The root profile, this is the default profile created by the system based on all the properties defined outside any profile definition,
provide the default values that all profiles inherit. Then, profile properties can override these values or define new ones as required.

The example below shows how the root profile defines a value for ``pinned_apps`` and ``pinned_apps_menu_length`` properties.
The ``rstudio_group`` profile inherits the property value for ``pinned_apps_menu_length``,
and overrides the value for ``pinned_apps``. As well, it defines a value for the property ``pinned_apps_group_by``.

.. code-block:: yaml

  pinned_apps: [sys/*]
  pinned_apps_menu_length: 10

  profiles:
    rstudio_group:
      pinned_apps: [sys/rstudio]
      pinned_apps_group_by: "department"

.. _profiles_selection_guide:

Manual Profile Selection
........................

The selection of a profile can be done manually by updating the user settings profile. By default the root profile is selected.
Profile selection can be done using configurable navigation links.
These links will update the profile, save the newly selected profile in the user settings file and reload the Dashboard. 

To add profile links to the Help navigation dropdown menu use the configuration property ``profile_links``.
For more information on how to configure profile links, see the :ref:`link definition documentation. <navbar_links_guide>`.

.. code-block:: yaml

  profile_links:
    - group: "Profiles"
    - profile: ""
      title: "Root Profile"
      icon_uri: "fas://cog"
    - profile: rstudio_group
      title: "Rstudio Profile"
      icon_uri: "fas://user"
    - profile: jupyter_group
      title: "Jupiter Profile"
      icon_uri: "fas://user"

.. figure:: /images/def-profiles-links.png
   :align: center

.. tip::
    Use the ``group`` property to add a section header or to organize your profiles as shown above.
    Profile links can be configured as well using the :ref:`Help menu customizations <help_menu_guide>`.

.. note::
    Your profile selection is stored in your OnDemand user settings file.
    The ``profile`` key in this YAML file provides the value used to select your current profile.
    The user settings file is stored in your OnDemand data folder, this is usually ``~/ondemand/data/sys/dashboard/.ood``.
    Manual updates to this file will require an application restart to load the new values.


Automatic Profile Selection
...........................

* **Request Hostname profile selection:** use the current request hostname as the selected profile.
  To enable this feature, set the configuration property ``host_based_profiles`` to ``true``.
  A request to ``https://www.ondemand.com/pun/sys/dashboard`` will use ``www.ondemand.com`` as the selected profile name.

  Configure the profiles using the hostname and the system will use the profile properties automatically.

.. code-block:: yaml

  profiles:
    www.ondemand.com:
      config_property: config_value

.. tip::
    If you have a need to create multiple profile definitions that have the same configuration, you could use aliases.
    This is a feaure of YAML files. You can use YAML ``anchors`` and ``aliases`` to set the same profile configuration
    to more than one definition without duplication. This YAML feature only works when defined and used within the same file.

    The example below creates 4 profiles all with the same configuration:

    .. code-block:: yaml

      profiles:
        www.production.com: &production_profile # Anchor definition
          config_property: config_value
          config_property: config_value
          config_property: config_value
        
        www.local.com: *production_profile # Defining an alias to the previously set anchor.
        www.test.com: *production_profile
        www.staging.com: *production_profile

