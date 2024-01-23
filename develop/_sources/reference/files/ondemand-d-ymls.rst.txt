.. _ondemand-d-ymls:

ondemand.d/\*.yml files
=======================

Most of the configurations are now held within yml files in the ``/etc/ood/config/ondemand.d/`` directory.
Open OnDemand will read all the ``.yml`` and ``.yml.erb`` files within this directory for
configurations.

To use a different directory other than this use the ``OOD_CONFIG_D_DIRECTORY`` environment variable
in the ``/etc/ood/config/apps/dashboard/env`` file.

These properties support profile based configuration, see the :ref:`profile configuration documentation. <profiles_guide>`

.. note:: Simple properties (strings and booleans) can be configured using environment variables as well.
          The name of the environment variable will be the property name in capitals prepended with ``OOD_``.
          eg: property ``brand_bg_color`` will be ``OOD_BRAND_BG_COLOR`` enviroment variable.

          We recommend setting environment variables in ``/etc/ood/config/nginx_stage.yml``
          as YAML mappings (key value pairs) in the mapping (hash/dictionary) ``pun_custom_env``.
          Alternatively you can set these in the env files of the dashboard and the apps.

.. warning:: When using environment variables with ``nginx_stage.yml`` file, be careful to set the value using quotes
             i.e. ``OOD_BRAND_BG_COLOR: '#0000ff'``. If you omit the quotes, YAML will see ``#`` as a comment and the value of the ``OOD_BRAND_BG_COLOR`` will be ``nil``


.. _profile_properties:

Configuration Properties with profile support
---------------------------------------------

.. describe:: dashboard_header_img_logo (String, null)

    The url to the logo image for the main navigation. If no logo is configured, the ``dashboard_title``
    property will be used as text.
      
    Default
      No logo image will be shown, just the ``dashboard_title`` text.

      .. code-block:: yaml

        dashboard_header_img_logo: null

    Example
      Show ``/public/logo.png`` as the logo image.

      .. code-block:: yaml

        dashboard_header_img_logo: "/public/logo.png"

.. describe:: disable_dashboard_logo (Bool, false)

    Whether to show the ``dashboard_logo`` property in the homepage welcome message.

    Default
      ``false``, the ``dashboard_logo`` logo will be shown in the homepage welcome message.

      .. code-block:: yaml

        disable_dashboard_logo: false

    Example
      Disable the logo in the welcome message.

      .. code-block:: yaml

        disable_dashboard_logo: true

.. describe:: dashboard_logo (String, null)

  The url to the logo image for the homepage welcome message. If no logo is configured, the ``dashboard_title``
  property will be used as text.

  Default
    No logo image will be shown with the welcome message.

    .. code-block:: yaml

      dashboard_logo: null

  Example
    Show ``/public/welcome.png`` as the welcome message logo image.

    .. code-block:: yaml

      dashboard_logo: "/public/welcome.png"

.. describe:: dashboard_logo_height (Integer, null)

    HTML image overide for the height of the welcome message logo image configured with ``dashboard_logo``

    Default
      ``null``, no override will be applied and the original image height will be used.

      .. code-block:: yaml

        dashboard_logo_height: null

    Example
      Adjust the image height to 150 pixels.

      .. code-block:: yaml

        dashboard_logo_height: "150px"

.. describe:: brand_bg_color (String, null)

  The CSS color override for the main navbar background. Any valid CSS color value can be used.

  Default
    Null, no background color override. The default theme color from the ``navbar_type`` property will be used.

    .. code-block:: yaml

      brand_bg_color: null

  Example
    Use ``#007FFF`` (shade of blue) as the background color for the navbar.

    .. code-block:: yaml

      brand_bg_color: "#007FFF"

.. describe:: brand_link_active_bg_color (String, null)

  The CSS color override for background of the active navigation link in the navbar.
  Any valid CSS color value can be used.

  Default
    Null, no color override. The default theme color from the ``navbar_type`` property will be used.

    .. code-block:: yaml

      brand_link_active_bg_color: null

  Example
    Use ``#007FFF`` (shade of blue) for the background color of the active navigation link.

    .. code-block:: yaml

      brand_link_active_bg_color: "#007FFF"

.. describe:: dashboard_layout (Object, null)

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

.. describe:: pinned_apps_menu_length (Integer, 6)

    The maximum number of pinned apps in the 'Apps' menu bar.

    Default
      Show 6 items in the menu.
      
      .. code-block:: yaml

        pinned_apps_menu_length: 6

    Example
      Show 10 items in the menu.

      .. code-block:: yaml

        pinned_apps_menu_length: 10

.. describe:: pinned_apps_group_by (String, null)

  Group the pinned apps icons by this field in the dashboard.

  Default
    Null, do no group pinned apps by any field.

    .. code-block:: yaml

      pinned_apps_group_by: null

  Example
    Group the pinned apps by ``category``.

    .. code-block:: yaml

      pinned_apps_group_by: "category"

.. describe:: profile_links (Array<Object>, [])

  List of profiles to display in the ``Help`` navigation menu. This will allow users to change profiles.
  For more information see the :ref:`profile selection documentation. <profiles_selection_guide>`

  Default
    Empty list, no profile links will be shown.

    .. code-block:: yaml

      profile_links: []

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

.. describe:: custom_css_files (Array<String>, [])

  List of relative URLs to the CSS files to include in all Dashboard pages.
  These CSS files can be used to customize the look and feel of the Dashboard.

  The relative path will be prefixed with the value of the ``public_url`` property.

  Default
    Empty list, no custom css files will be included.

    .. code-block:: yaml

      custom_css_files: []

  Example
    Add two custom CSS files: ``/myfolder/navigation.css`` and ``/myfolder/pinned_apps.css`` to the Dashboard.

    .. code-block:: yaml

      custom_css_files: ["/myfolder/navigation.css", "/myfolder/pinned_apps.css"]

.. _custom_javascript_files:
.. describe:: custom_javascript_files (Array<String>, [])

  List of relative URLs to custom javascript files to include in all Dashboard pages.
  These javascript files can be used to customize the behavior of the Dashboard.

  The relative path will be prefixed with the value of the ``public_url`` property.

  Default
    Empty list, no custom javascript files will be included.

    .. code-block:: yaml

      custom_javascript_files: []

  Example
    Add two custom Javascript files: ``/myfolder/navigation.js`` and ``/myfolder/pinned_apps.js`` to the Dashboard.

    .. code-block:: yaml

      custom_javascript_files: ["/myfolder/navigation.js", "/myfolder/pinned_apps.js"]

.. describe:: dashboard_title (String, 'Open OnDemand')

    The text to use as the main navigation logo. If the ``dashboard_header_img_logo`` property is defined,
    this property will be used as the HTML image title.

    Default
      ``Open OnDemand`` text

      .. code-block:: yaml

        dashboard_title: "Open OnDemand"

    Example
      Show ``My Institution`` as the logo text.

      .. code-block:: yaml

        dashboard_title: "My Institution"

.. describe:: show_all_apps_link (Bool, false)

  Whether to show the ``All Apps`` link in the navbar.
  This links to the Dashboard page showing all system installed applications.

  Default
    ``false``, the ``All Apps`` link will not be shown in the navbar.

    .. code-block:: yaml

      show_all_apps_link: false

  Example
    Include the ``All Apps`` link in the navbar.

    .. code-block:: yaml

      show_all_apps_link: true

.. describe:: nav_bar (Array<Object>, [])

  An array of navigation items to create a custom navbar.
  This property sets the navigation items for the left hand side navigation menu in the header.

  See the :ref:`documentation on custom navigation <navbar_guide>` for details and examples.

  Default
    Empty array, show the default navbar.
  Example
    See the  :ref:`custom navigation documentation <navbar_guide>`

.. describe:: help_bar (Array<Object>, [])

  An array of navigation items to create a custom help navigation.
  This property sets the navigation items for the right hand side navigation menu on the header.

  See the :ref:`documentation on custom navigation <navbar_guide>` for details and examples.

  Default
    Empty array, show the default help navigation.
  Example
     See the  :ref:`custom navigation documentation <navbar_guide>`

.. describe:: help_menu (Array<Object>, [])

  A single navigation item to add links to the Help dropdown menu.
  This property adds navigation items at the end of any exisiting links in the menu.

  See the :ref:`documentation on adding urls to the Help menu <help_menu_guide>` for details and examples.

  Default
   Empty array, no additional links will be added to the Help menu.
  Example
    See the  :ref:`documentation on adding urls to the Help menu <help_menu_guide>`

.. describe:: interactive_apps_menu (Object, {})

  A single navigation item to create a custom interactive apps menu.
  This property sets the interactive applications to display in the left hand side menu
  on the ``Interactive Apps`` and ``Interactive Sessions`` pages.

  See the :ref:`documentation on interactive apps menu <interactive_apps_menu_guide>` for details and examples.

  Default
    Empty object, No customizations, show the currently installed interactive applications.
  Example
    See the  :ref:`interactive apps menu documentation <interactive_apps_menu_guide>`

.. describe:: custom_pages (Hash<String, Object>, {})

  A hash with the definition of the layouts for the configured custom pages.
  The key is a string with the page code. The value is the custom page layout definition.

  See the :ref:`documentation on custom pages <custom_pages_guide>` for details and examples.

  Default
    Empty hash, No custom pages defined.
  Example
    See the  :ref:`custom pages documentation <custom_pages_guide>`

.. describe:: support_ticket (Object, {})

  Configuration settings to enable and configure the support ticket feature.

  See the :ref:`documentation on Support Ticket <support_ticket_guide>` for details and examples.

  Default
    Empty object, support ticket feature is disabled.
  Example
    See the  :ref:`Support Ticket documentation <support_ticket_guide>`

.. describe:: navbar_type (String, 'dark')
  
  The navbar theme type. There are 2 themes, ``light`` and ``dark``.
  The selected theme will update the colors of the navbar.

  Default
    Set theme to ``dark``.

    .. code-block:: yaml

      navbar_type: "dark"

  Example
    Set theme to ``light``.

    .. code-block:: yaml

      navbar_type: "light"

.. describe:: public_url (String, '/public')

  The prefix url used to load the ``favicon.ico`` and custom CSS files configured with the ``custom_css_files`` property.

  Default
    '/public' prefix url.

    .. code-block:: yaml

      public_url: "/public"

  Example
    Use ``/public/resources`` as the prefix path to load these resources.

    .. code-block:: yaml

      public_url: "/public/resources"

.. describe:: announcement_path (Array<String>, ['/etc/ood/config/announcement.md', '/etc/ood/config/announcement.yml', '/etc/ood/config/announcements.d'])

  The file or directory path to load announcement messages from.

  Default
    The default files are: ``/etc/ood/config/announcement.md``, ``/etc/ood/config/announcement.yml``, and ``/etc/ood/config/announcements.d``

    .. code-block:: yaml

      announcement_path:
        - "/etc/ood/config/announcement.md"
        - "/etc/ood/config/announcement.yml"
        - "/etc/ood/config/announcements.d"


  Example
    Use ``/etc/ood/config/announcement.team1.d/`` as the path to load announcements.

    .. code-block:: yaml

      announcement_path: "/etc/ood/config/announcement.team1.d/"

.. _nav_categories:
.. describe:: nav_categories (Array<String>, ['Apps', 'Files', 'Jobs', 'Clusters', 'Interactive Apps'])

  By default Open OnDemand will create dropdown menus on the navigation bar for certain
  categories listed below.

  Use this property to add or remove which application categories will create dropdown menus
  on the navigation bar.

  Default
    Create dropdown menus on the navigation bar items for the categories ``Apps``, ``Files``, ``Jobs``,
    ``Clusters`` and ``Interactive Apps``.

    .. code-block:: yaml

      nav_categories: ['Apps', 'Files', 'Jobs', 'Clusters', 'Interactive Apps']

  Example
    Only create dropdown menus on the navigation bar for the categories ``Apps``,
    ``Files`` and ``Jobs``.

    .. code-block:: yaml

      nav_categories: ['Apps', 'Files', 'Jobs']

.. _configuration_properties:

Configuration Properties
------------------------

.. describe:: files_enable_shell_button (Bool, true)

  While browsing files, by default, Open OnDemand will show a button to
  shell into that directory location. Use this configuration to disable that
  behaviour.

  Default
    True. Files App has will show a button to open a shell to that location.

    .. code-block:: yaml

      files_enable_shell_button: true

  Example
    Disable the terminal button in the Files App.

    .. code-block:: yaml

      files_enable_shell_button: false


.. _bc_dynamic_js:
.. describe:: bc_dynamic_js (Bool, false)

  Enable dynamic interactive app forms. See :ref:`dynamic-bc-apps` for more information
  on what this feature does.

  Default
    False. Interactive app forms will not be dynamic.

    .. code-block:: yaml

      bc_dynamic_js: true

  Example
    Interactive app forms will be dynamic.

    .. code-block:: yaml

      bc_dynamic_js: true

.. _bc_clean_old_dirs:
.. describe:: bc_clean_old_dirs(Bool, false)

  Interactive Apps create a new directory ``~/ondemand/data/sys/dashboard/batch_connect/...`` every time
  the application is launched.  Over time users may create many directories that hold essentially old
  and useless data.

  When enabled, the system will remove every directory that is older than 30 days.
  See ``bc_clean_old_dirs_days`` below to change the time range. You may wish to keep
  directories for longer or shorter intervals.

  Default
    False. Never delete these directories.

    .. code-block:: yaml

      bc_clean_old_dirs: false

  Example
    Delete these directories after 30 days.

    .. code-block:: yaml

      bc_clean_old_dirs: true

.. describe:: bc_clean_old_dirs_days(Integer, 30)

  If you have ``bc_clean_old_dirs`` above enabled, the system will clean every directory that
  is older than 30 days. This configuration specifies how old a directory (in days) must be to
  be removed.

  The system checks creation time, not modification time.

  Default
    Delete these directories after 30 days if ``bc_clean_old_dirs`` is enabled.

    .. code-block:: yaml

      bc_clean_old_dirs_days: 30

  Example
    Delete these directories after 15 days if ``bc_clean_old_dirs`` is enabled.

    .. code-block:: yaml

      bc_clean_old_dirs_days: 15

.. describe:: host_based_profiles (Bool, false)

  Feature flag to enable automatic selection of configuration profiles based on the hostname of the request.

  Default
    False. Profiles will be selected manually based on the user settings file.

    .. code-block:: yaml

      host_based_profiles: false

  Example
    Enable automatic hostname profile selection.

    .. code-block:: yaml

      host_based_profiles: true

.. describe:: disable_bc_shell (Bool, false)

  Some schedulers like :ref:`resource-manager-lsf` use the the ``-L`` flag to bsub
  for purposes other than setting the shell path. Interactive apps set the shell path
  to ``/bin/bash`` by default using various flags or editing scripts.

  Default
    False. All interactive apps will submit jobs with the shell path flag set.

    .. code-block:: yaml

      disable_bc_shell: false

  Example
    Do not submit interactive jobs with any shell path.

    .. code-block:: yaml

      disable_bc_shell: true

.. describe:: cancel_session_enabled (Bool, false)

  Feature flag to enable the cancellation of active interactive sessions without deleting the session card.

  Default
    False. Active interactive sessions can only be deleted.

    .. code-block:: yaml

      cancel_session_enabled: false

  Example
    Enable interactive sessions cancellations.

    .. code-block:: yaml

      cancel_session_enabled: true

.. _module_file_dir:
.. describe:: module_file_dir (String, null)

  Specify a directory where **cluster specific module files** exist. It's important
  that there be a file for each cluster because the system can then tie those
  modules to that specific cluster.
  
  This directory should have ``module spider-json`` output **for each cluster** 
  as indicated by the command below. Open OnDemand will read these files and
  potentially show them in a from for a cluster called **my_cluster**.

  ``$LMOD_DIR/spider -o spider-json $MODULEPATH > /some/directory/my_cluster.json``

  Default
    Null. No directory given.

    .. code-block:: yaml

      module_file_dir: null

  Example
    Look for json files in the /etc/reporting/modules directory.

    .. code-block:: yaml

      module_file_dir: "/etc/reporting/modules"

.. describe:: user_settings_file (String, '.ood')

  The name of the file to store user settings. This file is used to store the selected profile.
  The path to the file is managed by the configuration variable ``Configuration.dataroot``.
  This is usually: ``~/ondemand/data/sys/dashboard``

  Default
    A file called '.ood'.

    .. code-block:: yaml

      user_settings_file: ".ood"

  Example
    Use ``user_settings.txt`` as the file name for user settings.

    .. code-block:: yaml

      user_settings_file: "user_settings.txt"

.. describe:: facl_domain (String, null)

  The File Access Control List (FACL) domain to use when setting FACLs
  on files or directories.

  Default
    No facl domain given.

    .. code-block:: yaml

      facl_domain: null

  Example
    What we use at OSC.

    .. code-block:: yaml

      facl_domain: "osc.edu"

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

.. _bc_simple_auto_accounts:
.. describe:: bc_simple_auto_accounts (Boolean, false)

  Use a simple accounting scheme that assumes all accounts are available on all
  clusters.

  Default
    False. The account list generated will be a list of all the accounts available
    across all clusters.

    .. code-block:: yaml

      bc_simple_auto_accounts: false

  Example
    Enable simple accounts. This will generate a list of accounts that should be
    available on all clusters.
  
    .. code-block:: yaml

      bc_simple_auto_accounts: true


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


.. describe:: remote_files_validation (Boolean, false)

  Enable validating remote files on startup.

  Default
    Remote file systems will not be validated on startup.

    .. code-block:: yaml

      remote_files_validation: false

  Example
    Remote file systems will be validated on startup.

    .. code-block:: yaml

      remote_files_validation: true

.. _upload_enabled:
.. describe:: upload_enabled (Boolean, true)

  Enable uploading files.

  Default
    File uploads are enabled.

    .. code-block:: yaml

      upload_enabled: true

  Example
    File uploads are disabled. Users will not be able to upload
    files through Open OnDemand.

    .. code-block:: yaml

      upload_enabled: false

.. _downlad_enabled:
.. describe:: download_enabled (Boolean, true)

  Enable downloading files.

  Default
    File downloads are enabled.

    .. code-block:: yaml

      download_enabled: true

  Example
    File downloads are disabled. Users will not be able to download
    files through Open OnDemand.

    .. code-block:: yaml

      download_enabled: false

.. describe:: hide_app_version (Boolean, false)

  Hide the interactive application's version.

  Default
    Interactive application versions are shown.

    .. code-block:: yaml

      hide_app_version: false

  Example
    Never show interactive application versions.

    .. code-block:: yaml

      hide_app_version: true

.. _globus_endpoints:
.. describe:: globus_endpoints (Array<Object>, null)

  Add a Globus button to the file browser that opens the current directory
  in the Globus transfer web app.

  Note that ``endpoint_path`` is the path that Globus will initialize to
  and is very likely to be ``/`` regardless of the actual storage path.

  Default
    Null, do not enable the Globus button

  Example
    Use a single endpoint for the whole filesystem.

    .. code-block:: yaml

       globus_endpoints:
         - path: "/"
           endpoint: "716de4ac-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
           endpoint_path: "/"

  Example
    Use multiple endpoints.

    .. code-block:: yaml

       globus_endpoints:
         - path: "/home"
           endpoint: "716de4ac-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
           endpoint_path: "/home"

         - path: "/project"
           endpoint: "9f1fe759-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
           endpoint_path: "/project"

  Example
    When pathnames differ between the filesystem and endpoint.

    .. code-block:: yaml

       globus_endpoints:
         - path: "/project"
           endpoint: "9f1fe759-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
           endpoint_path: "/"

  Example
    Reference the home directory of the current user.

    .. code-block:: yaml

      globus_endpoints:
        - path: "<%=  Etc.getpwnam(Etc.getlogin).dir %>"
          endpoint: "9f1fe759-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
          endpoint_path: "/"

.. _google_analytics_tag_id:

.. describe:: google_analytics_tag_id (String, nil)

  Configure Google Analytics by supplying a tag id.

  Default
    Google Analytics is disabled.

    .. code-block:: yaml

      google_analytics_tag_id: nil

  Example
    Google Analytics is enabled and will upload data to the
    tag id ``abc123``.

    .. code-block:: yaml

      google_analytics_tag_id: 'abc123'


.. _motd_render_html:
.. describe:: motd_render_html (Boolean, false)

  Render HTML in the Message of the Day (MOTD).  This
  configuration was added because some MOTD formats like
  RSS can generate HTML that is potentially unsafe.

  Default
    The Message of the day will not render HTML.

    .. code-block:: yaml

      motd_render_html: false

  Example
    The Message of the day will render HTML.

    .. code-block:: yaml

      motd_render_html: true
