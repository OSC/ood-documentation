.. _ondemand-d-ymls:

ondemand.d/\*.yml files
=======================

Most of the configurations are now held within yml files in the ``/etc/ood/config/ondemand.d/`` directory.
Open OnDemand will read all the ``.yml`` and ``.yml.erb`` files within this directory for
configurations.

Profiles
-------------

For more complex requirements, these configurations can be organized using profiles. With profiles,
administrators can create different configuration settings within the same OnDemand installation.
The selection of a profile can be configured to be manually selected by the user or automatically
selected based on request data like the domain.

To create a new profile, we simply have to add a new configuration entry under the ``profiles`` key:

.. code-block:: yaml

  profiles:
    profile_name:
      config_property: config_value



To simplify the configuration, OnDemand uses an inheritance and override approach for profiles.
The root configuration provides default properties that all profiles inherit.
Then, each profile can overridde these properties or define new ones as needed.

The example below shows how the root profile defines a value for ``pinned_apps`` and ``pinned_apps_menu_length``.
The ``rstudio_group`` profile inherits the property value for ``pinned_apps_menu_length``,
and overrides the value for ``pinned_apps`` just to the RStudio application.
As well, it defines the property ``pinned_apps_group_by``.

.. code-block:: yaml

  pinned_apps: [sys/*]
  pinned_apps_menu_length: 10

  profiles:
    rstudio_group:
      pinned_apps: [sys/rstudio]
      pinned_apps_group_by: "department"

.. note::

   The profile based configuration is an experimental feature. Not all properties support profile based configuration.
   See the list below for the list of supported properties.

To use a different directory other than this use the ``OOD_CONFIG_D_DIRECTORY`` environment variable
in the ``/etc/ood/config/apps/dashboard/env`` file.

Profile Configuration Properties
--------------------------------

.. describe:: dashboard_header_img_logo (String, null)

    The url to the logo image for the main navigation. If no logo is configured, the ``dashboard_title``
    property will be used as text.

    Default
      No logo image will be shown, just the ``dashboard_title`` text.
    Example
      Show ``/public/logo.png`` as the logo image.

      .. code-block:: yaml

        dashboard_header_img_logo: "/public/logo.png"

.. describe:: dashboard_title: (String, 'Open OnDemand')

    The text to use as the main navigation logo. If the ``dashboard_header_img_logo`` property is defined,
    this property will be used as the HTML image title.

    Default
      ``Open OnDemand`` text
    Example
      Show ``My Institution`` as the logo text.

      .. code-block:: yaml

        dashboard_title: "My Institution"

.. describe:: dashboard_logo (String, null)

  The url to the logo image for the homepage welcome message. If no logo is configured, the ``dashboard_title``
  property will be used as text.

  Default
    No logo image will be shown with the welcome message.
  Example
    Show ``/public/welcome.png`` as the welcome message logo image.

    .. code-block:: yaml

      dashboard_logo: "/public/welcome.png"

.. describe:: dashboard_logo_height (Integer, null)

    HTML image overide for the height of the welcome message logo image configured with ``dashboard_logo``

    Default
      ``null``, no override will be applied and the original image height will be used.
    Example
      Adjust the image height to 150

      .. code-block:: yaml

        dashboard_logo_height: "150"

.. describe:: disable_dashboard_logo (Bool, false)

    Whether to show the ``dashboard_logo`` property in the homepage welcome message.

    Default
      ``false``, the ``dashboard_logo`` logo will be shown in the homepage welcome message.
    Example
      Disable the logo in the welcome message.

      .. code-block:: yaml

        disable_dashboard_logo: true

.. describe:: public_url (String, '/public')

  The prefix url used to load the ``favicon.ico`` and custom CSS files configured with the ``custom_css_files`` property.

  Default
    '/public' prefix url.
  Example
    Use ``/public/resources`` as the prefix path to load these resources.

    .. code-block:: yaml

      public_url: "/public/resources"

.. describe:: brand_bg_color (String, null)

  The CSS color override for the main navbar background. Any valid CSS color value can be used.

  Default
    Null, no background color override. The default theme color from the ``navbar_type`` property will be used. 
  Example
    Use ``#007FFF`` (shade of blue) as the background color for the navbar.

    .. code-block:: yaml

      brand_bg_color: "#007FFF"

.. describe:: brand_link_active_bg_color (String, null)

  The CSS color override for background of the active navigation link in the navbar.
  Any valid CSS color value can be used.

  Default
    Null, no color override. The default theme color from the ``navbar_type`` property will be used. 
  Example
    Use ``#007FFF`` (shade of blue) for the background color of the active navigation link.

    .. code-block:: yaml

      brand_link_active_bg_color: "#007FFF"

.. describe:: dashboard_layout: (Object, null)

  Specify the dashboard layout.  Rearrange existing widgets
  and add more custom widgets. See the 
  :ref:`documentation on custom dashboard layouts <dashboard_custom_layout>`
  for details and examples.

  Default
    Null, do not change the default dashboard layout.
  Example
    See the  :ref:`dashboard layout documentation <dashboard_custom_layout>`
  
.. describe:: pinned_apps (Array<Object>, null)

  An array of pinned app objects specifying what apps to pin to the dashboard.
  See the :ref:`documentation on pinned apps <dashboard_pinned_apps>` for details
  and examples.

  Default
    Null, don't pin any apps to the dashboard.
  Example
    See the  :ref:`pinned apps documentation <dashboard_pinned_apps>`

.. describe:: pinned_apps_menu_length: (Integer, 6)

    The maximum number of pinned apps in the 'Apps' menu bar.

    Default
      6, show a maximum of 6 pinned apps.
    Example
      Show 10 items in the menu.

      .. code-block:: yaml

        pinned_apps_menu_length: 10

.. describe:: pinned_apps_group_by: (String, null)

  Group the pinned apps icons by this field in the dashboard.

  Default
    Null, do no group pinned apps by any field.
  Example
    Group the pinned apps by ``category``.

    .. code-block:: yaml

      pinned_apps_group_by: "category"

.. describe:: profile_links: (Array<Object>, [])

  List of profiles to display in the ``Help`` menu. This will allow users to change profiles.

  Default
    Empty list, no profile links will be shown.
  Example
    Add a link to the ``default`` and ``ondemand`` profiles to the ``Help`` menu.

    .. code-block:: yaml

      profile_links:
        - id: ""
          name: "Default"
          icon: "house-user"
        - id: "ondemand"
          name: "OnDemand Profile"
          icon: "user"

.. describe:: custom_css_files: (Array<String>, [])

  List of relative URLs to the CSS files to include in all Dashboard pages.
  These CSS files can be used to customize the look and feel of the Dashboard.

  The relative path will be prefixed with the value of the ``public_url`` property.

  Default
    Empty list, no custom css files will be included.
  Example
    Add two custom CSS files: ``/myfolder/navigation.css`` and ``/myfolder/pinned_apps.css`` to the Dashboard.

    .. code-block:: yaml

      custom_css_files: ["/myfolder/navigation.css", "/myfolder/pinned_apps.css"]

.. describe:: show_all_apps_link: (Bool, false)

  Whether to show the ``All Apps`` link in the navbar.
  This links to the Dashboard page showing all system installed applications.

  Default
    ``false``, the ``All Apps`` link will not be shown in the navbar.
  Example
    Include the ``All Apps`` link in the navbar.

    .. code-block:: yaml

      show_all_apps_link: true

.. describe:: nav_categories: (Array<String>, NavConfig.categories)

  List of application categories used to sort and filter the applications that appear in the navbar.

  Default
    ``['Apps', 'Files', 'Jobs', 'Clusters', 'Interactive Apps']``,
    the default list of categories as configured with the ``NavConfig.categories`` variable.
  Example
    Set the categories to ``['Apps', 'Files', 'Jobs']``

    .. code-block:: yaml

      nav_categories: ["Apps", "Files", "Jobs"]

.. describe:: navbar_type: (String, 'dark')
  
  The navbar theme type. There are 2 themes, ``light`` and ``dark``.
  The selected theme will update the colors of the navbar.

  Default
    ``dark``,
  Example
    Set theme to ``light``

    .. code-block:: yaml

      navbar_type: "light"

.. describe:: nav_bar: (Array<Object>, [])

  An array of navigation items to create a custom navbar.
  This property sets the navigation items for the left hand side navigation menu in the header.

  See the :ref:`documentation on custom navigation <navbar_guide>` for details and examples.

  Default
    Empty array, show the default navbar.
  Example
    See the  :ref:`custom navigation documentation <navbar_guide>`

.. describe:: help_bar: (Array<Object>, [])

  An array of navigation items to create a custom help navigation.
  This property sets the navigation items for the right hand side navigation menu on the header.

  See the :ref:`documentation on custom help navigation <helpbar_guide>` for details and examples.

  Default
    Empty array, show the default help navigation.
  Example
    See the  :ref:`custom help navigation documentation <helpbar_guide>`

.. describe:: interactive_apps_menu: (Object, {})

  A single navigation item to create a custom interactive apps menu.
  This property sets the interactive applications to display in the left hand side menu
  on the ``Interactive Apps`` and ``Interactive Sessions`` pages.

  See the :ref:`documentation on interactive apps menu <interactive_apps_menu_guide>` for details and examples.

  Default
    Empty object, No customizations, show the currently installed interactive applications.
  Example
    See the  :ref:`interactive apps menu documentation <interactive_apps_menu_guide>`

.. describe:: custom_pages: (Hash<String, Object>, {})

  A hash with the definition of the layouts for the configured custom pages.
  The key is a string with the page code. The value is the custom page layout definition.

  See the :ref:`documentation on custom pages <custom_pages_guide>` for details and examples.

  Default
    Empty hash, No custom pages defined.
  Example
    See the  :ref:`custom pages documentation <custom_pages_guide>`


Configuration Properties
------------------------

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
    Look for json files in the /etc/reporing/modules directory.

    .. code-block:: yaml

      module_file_dir: /etc/reporing/modules
