.. _customization:

Customization
=============


Announcements
-------------

To add an announcement message that appears at the top of the dashboard you can create a file at ``/etc/ood/config/announcement.(md|yml)`` or ``/etc/ood/config/announcements.d/any_file_name.(md|yml)``.

On each request the dashboard will check for the existence of this file. If it exists, the contents will be converted using markdown converter to HTML and displayed inside a bootstrap alert.

For example, if I create an announcement.md file with the contents:

   .. code-block:: md

      **NOTICE:** There will be a two day downtime on February 21-22, 2017. OSC
      OnDemand will be unavailable during this period. For details, please visit
      [http://bit.ly/2jhfyh7](http://bit.ly/2jhfyh7).

the user would see this message at the top of the dashboard:

.. figure:: /images/dashboard-announcement.png
   :align: center

   Example of the Dashboard announcement.

If the announcement file has the extension ``yml`` and is a yaml file it is first rendered using ERB and then the resulting file is parsed as YAML. The valid keys are:

.. list-table:: Config Files
   :stub-columns: 1

   * - type
     - warning, info, success, or danger
     - this is the Bootstrap alert style
   * - msg
     - string containing markdown formatted message
     - if this is a blank string (only whitespace), the alert will not display

Because the announcement is rendered via ERB you can do some interesting things, like stop showing the announcement past a specified date:

   .. code-block:: erb

      type: warning
      msg: |
        <% if Time.now < Time.new(2018, 9, 24, 12, 0, 0) %>
        A **Ruby Partial Downtime** for 4 hours on Monday, September 24 from 8:00am to 12:00pm
        will prevent SSH login to Ruby nodes and and Ruby VDI sessions.
        <% end %>

.. note:: Warnings about the announcement file being missing may be present in users' nginx logs. Despite the warning the Dashboard will still function normally without those files being present.

Message of the Day (MOTD)
-------------------------

You can configure the Dashboard to display the /etc/motd file on the front page - the same file that is displayed when ssh-ing to a login node.

To display a MOTD file on the Dashboard ensure that the environment variables ``$MOTD_PATH`` and ``$MOTD_FORMAT`` are set, where

   .. code-block:: sh

      MOTD_PATH="/etc/motd" # this supports both file and RSS feed URIs
      MOTD_FORMAT="txt" # markdown, txt, rss

.. figure:: /images/dashboard_motd.png
   :align: center

   Message of the Day appears in the body of the index page.

We recommend setting this in ``/etc/ood/config/apps/dashboard/env``.


Branding
-------------------

.. _branding:

You can customize the logo, favicon, title, and navbar colors of OnDemand.

.. figure:: /images/dashboard_branding_logo_and_colors.png
   :align: center


We recommend setting these environment variables in ``/etc/ood/config/nginx_stage.yml`` as YAML mappings (key value pairs) in the mapping (hash/dictionary) ``pun_custom_env``. Alternatively you can set these in the env files of the dashboard and the apps. Currently only the dashboard uses the colors in the navbar.


.. list-table:: Branding
   :header-rows: 1
   :stub-columns: 1

   * - Feature
     - Environment Variable
     - Details
   * - Title
     - OOD_DASHBOARD_TITLE
     - The title appears in the navbar and is controlled by the environment variable ``$OOD_DASHBOARD_TITLE``. The default value is "Open OnDemand".
   * - Logo
     - OOD_DASHBOARD_LOGO
     - The default value for ``OOD_DASHBOARD_LOGO`` is ``/public/logo.png`` and this should be the URL to the logo. By default if you place a logo.png at ``/var/www/ood/public/logo.png`` it will be accessible via the URL ``https://your.ondemand.institution.edu/public/logo.png``.
   * - Favicon
     - OOD_PUBLIC_URL
     - The favicon is expected to exist at the path ``$OOD_PUBLIC_URL/favicon.ico``. For a default OOD installation the favicon will be located at ``/var/www/ood/public/favicon.ico``.
   * - Brand background color
     - OOD_BRAND_BG_COLOR
     - Controls the background color of the navbar in the dashboard
   * - Brand foreground color
     - OOD_BRAND_LINK_ACTIVE_BG_COLOR
     - Controls the background color the active link in the navbar in the dashboard
   * - Replace header title with logo
     - OOD_DASHBOARD_HEADER_IMG_LOGO
     - Value should be url to logo i.e. ``/public/logo.png``.  the background color the active link in the navbar in the dashboard
   * - Use white text on black background for navbar.
     - OOD_NAVBAR_TYPE
     - By default we use ``inverse`` for this value, which specifies to use `Bootstrap 3's inverted navbar <https://getbootstrap.com/docs/3.3/components/#navbar-inverted>`_ where text is white and background is black (or dark grey). You can set this to ``default`` to use black text on light grey background if it fits your branding better.


.. figure:: /images/dashboard_navbar_branding_bluered.png
   :align: center

   Nav bar if I set ``OOD_BRAND_BG_COLOR`` to ``#0000ff`` and ``OOD_BRAND_LINK_ACTIVE_BG_COLOR`` to ``#ff0000`` and ``OOD_DASHBOARD_TITLE`` to ``OSC OnDemand``


.. warning:: If setting in nginx_stage.yml, careful to set the value using quotes i.e. ``OOD_BRAND_BG_COLOR: '#0000ff'``. If you omit the quotes, YAML will see ``#`` as a comment and the value of the ``OOD_BRAND_BG_COLOR`` will be ``nil``



Add URLs to Help Menu
---------------------

These URLs can be specified, which will appear in the Help menu and on other locations of the Dashboard. We recommend setting this in ``/etc/ood/config/apps/dashboard/env``.

.. list-table:: Dashboard URLs
   :header-rows: 1
   :stub-columns: 1

   * - Name
     - Environment variable
     - Example value
   * - Support URL
     - OOD_DASHBOARD_SUPPORT_URL
     - https://www.osc.edu/contact/supercomputing_support
   * - Support Email
     - OOD_DASHBOARD_SUPPORT_EMAIL
     - oschelp@osc.edu
   * - User Documentation
     - OOD_DASHBOARD_DOCS_URL
     - https://www.osc.edu/ondemand
   * - Developer Documentation
     - OOD_DASHBOARD_DEV_DOCS_URL
     - https://osc.github.io/ood-documentation/master/app-development.html (link appears in Develop dropdown if developer mode enabled for user)
   * - Change Password URL
     - OOD_DASHBOARD_PASSWD_URL
     - https://my.osc.edu
   * - Custom Help URL (Also requires locale ``en.dashboard.nav_help_custom``)
     - OOD_DASHBOARD_HELP_CUSTOM_URL
     - https://idp.osc.edu/auth/realms/osc/account/identity


Add Shortcuts to Files Menu
---------------------------

.. _add-shortcuts-to-files-menu:

The Files menu by default has a single link to open the Files app in the user's
Home Directory. More links can be added to this menu, for Scratch space and
Project space directories.

Adding more links currently requires adding a custom initializer to the
Dashboard app. Ruby code is placed in the initializer to add one or more Ruby
``FavoritePath`` objects to the ``OodFilesApp.candidate_favorite_paths`` array, a
global attribute that is used in the Dashboard app.

Start by creating the file
:file:`/etc/ood/config/apps/dashboard/initializers/ood.rb` as such:

.. code-block:: ruby

  # /etc/ood/config/apps/dashboard/initializers/ood.rb

  OodFilesApp.candidate_favorite_paths.tap do |paths|
    # add project space directories
    projects = User.new.groups.map(&:name).grep(/^P./)
    paths.concat projects.map { |p| FavoritePath.new(Pathname.new("/fs/project/#{p}"))  }

    # add scratch space directories
    paths << FavoritePath.new(Pathname.new("/fs/scratch/#{User.new.name}"))

    # Project scratch has an optional title field.
    paths.concat projects.map { |p| FavoritePath.new(Pathname.new("/fs/scratch/#{p}"), title: "Scratch")  }
  end

- The variable ``paths`` is an array of ``FavoritePath`` objects that define a list
  of what will appear in the Dashboard menu for Files
- At OSC, the pattern for project paths follows
  :file:`/fs/project/{project_name}`. So above we:

  #. get an array of all user's groups by name
  #. filter that array for groups that start with ``P`` (i.e., ``PZS0002``,
     ``PAW0003``, ...)
  #. using ``map`` we turn this array into an array of ``FavoritePath`` objects to
     all the possible project directories the user could have.
  #. extend the paths array with this list of paths

- For possible scratch space directories, we look for either
  :file:`/fs/scratch/{project_name}` or :file:`/fs/scratch/{user_name}`
- Additionally project scratch directories have a 'title' attribute and will
  with in the dropdown with both the title and the path.

On each request, the Dashboard will check for the existence of the directories
in ``OodFilesApp.candidate_favorite_paths`` array and whichever directories
exist and the user has access to will appear as links in the Files menu under
the Home Directory link.

.. figure:: /images/files_menu_shortcuts_osc.png
   :align: center

   Shortcuts to scratch and project space directories in Files menu in OSC OnDemand.

- You must restart the Dashboard app to see a configuration change take effect.
  This can be forced from the Dashboard itself by selecting
  *Help* → *Restart Web Server* from the top right menu.

If you access the Dashboard, and it crashes, then you may have made a mistake
in ``ood.rb`` file, whose code is run during the initialization of the Rails
app.

Whitelist Directories
---------------------

By setting a colon delimited WHITELIST_PATH environment variable, the Job Composer, File Editor, and Files app respect the whitelist in the following manner:

1. Users will be prevented from navigating to, uploading or downloading, viewing, editing files that is not an eventual child of the whitelisted paths
2. Users will be prevented from copying a template directory from an arbitrary path in the Job Composer if the arbitary path that is not an eventual child of the whitelisted paths
3. Users should not be able to get around this using symlinks

We recommend setting this environment variable in ``/etc/ood/config/nginx_stage.yml`` as a YAML mapping (key value pairs) in the mapping (hash/dictionary) ``pun_custom_env`` i.e. below would whitelist home directories, project space, and scratch space at OSC:

.. code:: yaml

   pun_custom_env:
     WHITELIST_PATH: "/users:/fs/project:/fs/scratch"

.. warning:: This is not yet used in production at OSC, so we consider this feature "experimental" for now.

.. warning:: This whitelist is not enforced across every action a user can take in an app (including the developer views in the Dashboard). Also, it is enforced via the apps themselves, which is not as robust as using cgroups on the PUN.

Set Default SSH Host
--------------------

In ``/etc/ood/config/apps/shell/env`` set the env var ``DEFAULT_SSHHOST`` to change the default ssh host. Otherwise it will default to "localhost" i.e. add the line ``DEFAULT_SSHHOST="localhost"``.

This will control what host the shell app ssh's to when the URL accessed is ``/pun/sys/shell/ssh/default`` which is the URL other apps will use (unless there is context to specify the cluster to ssh to).

Shell App SSH Command Wrapper
-----------------------------

.. _ssh-wrapper:

Since OOD 1.7 you can use an ssh wrapper script in the shell application instead of just the ssh command.

This is helpful when you pass add additional environment variable through ssh (``-o SendEnv=MY_ENV_VAR``) or ensure some ssh command options be used.

To use your ssh wrapper configure ``OOD_SSH_WRAPPER=/usr/bin/changeme`` to point to your script in ``/etc/ood/config/apps/shell/env``. Also be sure to make your script executable.

Here's a simple example of what a wrapper script could look like.

.. code:: shell

  #!/bin/bash

  args="-o SendEnv=MY_ENV_VAR"

  exec /usr/bin/ssh "$args" "$@"

Fix Unauthorized WebSocket Connection in Shell App
--------------------------------------------------

If you see a 401 error when attempting to launch a Shell app session, where the request URL starts with wss:// and the response header includes ``X-OOD-Failure-Reason: invalid origin``, you may need to set the ``OOD_SHELL_ORIGIN_CHECK`` configuration option.

There is a security feature that adds proper CSRF_ protection using both the Origin request header check and a CSRF_ token check.

The Origin check uses X-Forwarded-Proto_ and X-Forwarded-Host_ that Apache mod_proxy_ sets to build the string that is used to compare with the Origin request header the browser sends in the WebSocket upgrade request.

In some edge cases this string may not be correct, and as a result valid WebSocket connections will be denied. In this case you can either set ``OOD_SHELL_ORIGIN_CHECK`` env var to the correct https string, or disable the origin check altogether by setting ``OOD_SHELL_ORIGIN_CHECK=off`` (or any other value that does not start with "http") in the ``/etc/ood/config/apps/shell/env`` file.

Either way the CSRF token will still provide protection from this vulnerability.

.. code:: text

  # /etc/ood/config/apps/shell/env
  # to disable it, just configure it with something that doesn't start with http
  OOD_SHELL_ORIGIN_CHECK='off'

  # to change it simply specify the http(s) origin you want to verify against.
  OOD_SHELL_ORIGIN_CHECK='https://my.other.origin'

.. _CSRF: https://owasp.org/www-community/attacks/csrf
.. _X-Forwarded-Proto: https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Forwarded-Proto
.. _X-Forwarded-Host: https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Forwarded-Host
.. _mod_proxy: https://httpd.apache.org/docs/2.4/mod/mod_proxy.html

Custom Job Composer Templates
-----------------------------

Below explains how job templates work for the Job Composer and how you can add your own. `Here is an example of the templates we use at OSC for the various clusters we have <https://github.com/OSC/osc-ood-config/tree/5440c0c2f3e3d337df1b0306c9e9d5b80f97a7e4/ondemand.osc.edu/apps/myjobs/templates>`_


Job Templates Overview
......................

"Job Composer" attempts to model a simple but common workflow. When creating a new batch job to run a simulation a user may:

1. copy the directory of a job they already ran or an example job
2. edit the files
3. submit a new job

"Job Composer" implements these steps by providing the user job template directories and the ability to make copies of them: (1) Copy a directory, (2) Edit the files, and (3) Submit a new job.

1. Copy a directory of a job already ran or an example job

   1. User can create a new job from a "default" template. A custom default template can be defined at ``/etc/ood/config/apps/myjobs/templates/default`` or under the app deployment directory at ``/var/www/ood/apps/sys/myjobs/templates/default``. If no default template is specified, the default is ``/var/www/ood/apps/sys/myjobs/example_templates/torque``
   2. user can select a directory to copy from a list of "System" templates the admin copied to ``/etc/ood/config/apps/myjobs/templates`` or under the app deployment directory at ``/var/www/ood/apps/sys/myjobs/templates`` during installation
   3. user can select a directory to copy from a list of "User" templates that the user has copied to ``$HOME/ondemand/data/sys/myjobs/templates``
   4. user can select a job directory to copy that they already created through "Job Composer" from ``$HOME/ondemand/data/sys/myjobs/projects/default``

2. Edit the files

   1. user can open the copied job directory in the File Explorer and edit files using the File Editor

3. Submit a new job

   1. user can use the Job Options form specify which host to submit to, what file is the job script
   2. user can use the web interface to submit the job to the batch system
   3. after the job is completed, the user can open the directory in the file explorer to view results

Job Template Details
....................

A template consists of a folder and a `manifest.yml` file.

The folder contains files and scripts related to the job.

The manifest contains additional metadata about a job, such as a name, the default host, the submit script file name, and any notes about the template.

.. code:: yaml

    name: A Template Name
    host: ruby
    script: ruby.sh
    notes: Notes about the template, such as content and function.

In the event that a job is created from a template that is missing from the `manifest.yml`, "Job Composer" will assign the following default values:

- ``name`` The name of the template folder.
- ``host`` The cluster id of the first cluster with a valid resource_mgr listed in the OOD cluster config
- ``script`` The first ``.sh`` file appearing in the template folder.
- ``notes`` The path to the location where a template manifest should be located.

Job Composer Script Size Limit
------------------------------

Since 1.7 the Job composer shows users 'Suggested file(s)' and 'Other valid file(s)'. Other valid files are
_any_ files less than ``OOD_MAX_SCRIPT_SIZE_KB`` which defaults to 65 (meaning 65kb).

To reconfigure this, simply set the environment variable in the job composers' env file
``/etc/ood/config/apps/myjobs/env`` like so:

.. code:: sh

  # show any file less than or equal to 15 kb
  OOD_MAX_SCRIPT_SIZE_KB=15

Custom Error Page for Missing Home Directory on Launch
------------------------------------------------------

Some sites have the home directory auto-create on first ssh login, for example
via ``pam_mkhomedir.so``. This introduces a problem if users first access the system
through OnDemand, which expects the existence of a user’s home directory.

In OnDemand <= 1.3 if the user's home directory was missing a non-helpful single
string error would display. Now a friendly error page displays. This error page
can be customized by adding a custom one to ``/etc/ood/config/pun/html/missing_home_directory.html``.

See `this Discourse discussion <https://discourse.osc.edu/t/launching-ondemand-when-home-directory-does-not-exist/53/>`_ for details.

.. _dashboard-navbar-config:

Control Which Apps Appear in the Dashboard Navbar
-------------------------------------------------

Apps contain a manifest.yml file that specify things like the title, icon, category, and possibly subcategory. The Dashboard searchs the search paths for all the possible apps and uses the manifests of the apps it finds to build the navbar (navigation menu) at the top of the page. Apps are placed in the top level menus based on the category, and then in dropdown menu sections based on subcategory.

In OnDemand 1.3 and earlier, a Ruby array (``NavConfig.categories``) stored a whitelist of categories that could appear in the navbar. This whitelist acts both as a sort order for the top level menus of apps and a whitelist of which apps will appear in the menu. The only way to modify this whitelist is to do so in a Dashboard initializer. You would add a file ``/etc/ood/config/apps/dashboard/initializers/ood.rb`` and add this line:

.. code:: ruby

   NavConfig.categories << "Reports"


Then an app that specifies "Reports" as the category in the manifest would appear in the "Reports" menu.

In OnDemand 1.4 we changed the behavior by adding a new boolean variable ``NavConfig.categories_whitelist`` which defaults to false. If false, whitelist mode is disabled, and the ``NavConfig.categories`` only exists to act to enforce a sort order and all apps found with a valid category will be available to launch.

Below are different configuration options and the resulting navbar if you had installed:

- OnDemand with a cluster configured that accepts job submissions and shell access
- at least one interactive app
- at least one custom app that specifies "Reports" as the category

.. list-table:: Navbar Configuration
   :header-rows: 1

   * - Configuration
     - Resulting Navbar
     - Reason
   * - Default configuration
     - "Files", "Jobs", "Clusters", "Interactive Apps", "Reports"
     - whitelist mode is false, so whitelist now only enforces sort order
   * - ``NavConfig.categories_whitelist=true`` in ``/etc/ood/config/apps/dashboard/initializers/ood.rb``
     - "Files", "Jobs", "Clusters", "Interactive Apps"
     - whitelist mode is enabled and since "Reports" is not in the whitelist it is omitted
   * - ``NavConfig.categories=[]`` in ``/etc/ood/config/apps/dashboard/initializers/ood.rb``
     - "Clusters", "Files", "Interactive Apps", "Jobs", "Reports"
     - the app categories appear in alphabetical order since whitelist mode is disabled
   * - ``NavConfig.categories=[]`` and ``NavConfig.categories_whitelist=true`` in ``/etc/ood/config/apps/dashboard/initializers/ood.rb``
     - no app menus appear!
     - whitelist mode is enabled, so only apps in ``NavConfig.categories`` would appear, and since that is an empty list, no apps appear in the navbar

.. _customization_localization:

Customize Text in OnDemand
--------------------------

Using Rails support for Internationaliation (i18n), we have internationalized many strings in the Dashboard and the Job Composer apps.

Initial translation dictionary files with defaults that work well for OSC and using the English locale (``en``) have been added (``/var/www/ood/apps/sys/dashboard/config/locales/en.yml`` and ``/var/www/ood/apps/sys/myjobs/config/locales/en.yml``). Sites wishing to modify these strings in order to provide site specific replacements for English, or use a different locale altogether, should do the following:

#. Copy the translation dictionary file (or create a new file with the same stucture of the keys you want to modify) to ``/etc/ood/config/locales/en.yml`` and modify that copy.
#. If you want apps to look for these dictionary files in a different location than ``/etc/ood/config/locales/en.yml`` you can change the location by defining ``OOD_LOCALES_ROOT`` environment variable.
#. The default locale is "en". You can use a custom locale. For example, if you want the locale to be French, you can create a ``/etc/ood/config/locales/fr.yml`` and then configure the Dashboard to use this locale by setting the environment variable ``OOD_LOCALE=fr`` where the locale is just the name of the file without the extension. Do this in either the nginx_stage config or in the Dashboard and Job Composer env config file.

In each default translation dictionary file the values that are most site-specific (and thus relevant for change) appear at the top.

.. list-table:: OnDemand Locale Files
  :header-rows: 1
  :stub-columns: 1

  * - File path
    - App
    - Translation namespace
  * - ``/var/www/ood/apps/sys/dashboard/config/locales/en.yml``
    - `Dashboard`_
    - ``dashboard``
  * - ``/var/www/ood/apps/sys/myjobs/config/locales/en.yml``
    - `Job Composer`_
    - ``jobcomposer``
  * - ``/etc/ood/config/locales/en.yml``
    - All localizable apps will check this path, unless ``OOD_LOCALES_ROOT`` is set.
    - Any

.. warning::

  Translations have certain variables passed to them for example ``%{support_url}``. Those variables may be used or removed from the translation. Attempting to use a variable that is not available to the translation will crash the application.

.. note::

  Localization files are YAML documents; remember that YAML uses spaces for indentation NOT tabs per the `YAML spec`_.

.. note::

  OnDemand uses the convention that translations that accept HTML with be suffixed with ``_html``. Any other translation will be displayed as plain text.

.. Links for the OnDemand 1.7.0 release versions of these apps
.. _Dashboard: https://github.com/OSC/ondemand/blob/master/apps/dashboard/config/locales/en.yml
.. _Job Composer: https://github.com/OSC/ondemand/blob/master/apps/myjobs/config/locales/en.yml

.. _Yaml spec: https://yaml.org/spec/1.2/spec.html#id2777534

Change the Dashboard Tagline
............................

.. code-block:: yaml

   en:
     dashboard:
       welcome_html: |
         %{logo_img_tag}
         <p class="lead">OnDemand provides an integrated, single access point for all of your HPC resources.</p>
       motd_title: "Message of the Day"

The ``welcome_html`` interpolates the variable ``logo_img_tag`` with the default
logo, or the logo specified by the environment variable ``OOD_DASHBOARD_LOGO``.

You may omit this variable in the value you specify for ``welcome_html`` if you prefer.

Change quota messages in the Dashboard
.......................................

Two messages related to file system usage that sites may want to change:

  - ``quota_additional_message`` - gives the user advice on what to do if they see a quota warning
  - ``quota_reload_message`` - tells the user that they should reload the page to see their quota usage change, and by default also tells users that the quota values are updated every 5 minutes

Customize Text in the Job Composer's options form
.................................................

The OSC-default value for ``options_account_help`` says that the account field is optional unless a user is a member of multiple projects.

Items of note include what to call Accounts which might also be Charge Codes, or Projects. At OSC entering an account is optional unless a user is a member of multiple projects which is reflected in the default value for the string ``options_account_help``.

Disable Safari Warning on Dashboard
-----------------------------------

We currently display an alert message at the top of the Dashboard mentioning
that we don't currently support the Safari browser. This is because of an issue
in Safari where it fails to connect to websockets if the Apache proxy uses
Basic Auth for user authentication (on by default for new OOD installations).

If you ever change the authentication mechanism to a cookie-based mechanism
(e.g., Shibboleth or OpenID Connect), then it is recommended you disable this
alert message in the dashboard.

You can do this by modifying the ``/etc/ood/config/apps/dashboard/env`` file as such:

.. code:: sh

   DISABLE_SAFARI_BASIC_AUTH_WARNING=1


Disk Quota Warnings on Dashboard
--------------------------------

You can display warnings to users on the Dashboard if their
disk quota is nearing its limit. This requires an auto-updated (it is
recommended to update this file every **5 minutes** with a cronjob) JSON file
that lists all user quotas. The JSON schema for version `1` is given as:

.. code:: json

   {
     "version": 1,
     "timestamp": 1525361263,
     "quotas": [
       {
         ...
       },
       {
         ...
       }
     ]
   }

Where ``version`` defines the version of the JSON schema used, ``timestamp``
defines when this file was generated, and ``quotas`` is a list of quota objects
(see below).

You can configure the Dashboard to use this JSON file (or files) by setting the
environment variable ``OOD_QUOTA_PATH`` as a colon-delimited list of all JSON
file paths in the ``/etc/ood/config/apps/dashboard/env`` file. In addition to
pointing to files ``OOD_QUOTA_PATH`` may also contain HTTP(s) or FTP protocol
URLs. Colons used in URLs are correctly handled and are not treated as delimiters.

.. warning::

  Sites using HTTP(s) or FTP for their quota files may see slower dashboard load
  times, depending on the responsiveness of the server providing the quota file(s).

The default threshold for displaying the warning is at 95% (`0.95`), but this
can be changed with the environment variable ``OOD_QUOTA_THRESHOLD``.

An example is given as:

.. code:: sh

   # /etc/ood/config/apps/dashboard/env

   OOD_QUOTA_PATH="/path/to/quota1.json:https://example.com/quota2.json"
   OOD_QUOTA_THRESHOLD="0.80"


Individual User Quota
.....................

If the quota is defined as a ``user`` quota, then it applies to only disk
resources used by the user alone. This is the default type of quota object and
is given in the following format:


.. warning:: A block must be equal to 1 KB for proper conversions.


Individual Fileset Quota
........................

If the quota is defined as a ``fileset`` quota, then it applies to all disk
resources used underneath a given volume. This requires the object to be
repeated for **each user** that uses disk resources under this given volume.
The format is given as:

.. code:: json

   {
     "type": "fileset",
     "user": "user1",
     "path": "/path/to/volume2",
     "block_usage": 500,
     "total_block_usage": 1000,
     "block_limit": 2000,
     "file_usage": 1,
     "total_file_usage": 5,
     "file_limit": 10
   }

Where ``block_usage`` and ``file_usage`` are the disk resource usages attributed to
the specified user only.

.. note:: For each user with resources under this fileset, the above object will be repeated with just ``user``, ``block_usage``, and ``file_usage`` changing.

Balance Warnings on Dashboard
--------------------------------

.. _balance-warnings-on-dashboard:

You can display warnings to users on the Dashboard if their
resource balance is nearing its limit. This requires an auto-updated (it is
recommended to update this file daily with a cronjob) JSON file
that lists all user balances. The JSON schema for version `1` is given as:

.. code:: json

    {
      "version": 1,
      "timestamp": 1525361263,
      "config": {
        "unit": "RU",
        "project_type": "project"
      },
      "balances": [
        {
          ...
        },
        {
          ...
        }
      ]
    }

Where ``version`` defines the version of the JSON schema used, ``timestamp``
defines when this file was generated, and ``balanaces`` is a list of quota objects
(see below).

The value for ``config.unit`` defines the type of units for balances and
``config.project_type`` would be project, account, or group, etc.
Both values are used in locales and can be any string value.

You can configure the Dashboard to use this JSON file (or files) by setting the
environment variable ``OOD_BALANCE_PATH`` as a colon-delimited list of all JSON
file paths.

.. warning::

  Sites using HTTP(s) or FTP for their balance files may see slower dashboard load
  times, depending on the responsiveness of the server providing the quota file(s).

The default threshold for displaying the warning is at ``0``, but this
can be changed with the environment variable ``OOD_BALANCE_THRESHOLD``.

An example is given as:

.. code:: sh

   # /etc/ood/config/apps/dashboard/env

   OOD_BALANCE_PATH="/path/to/balance1.json:/path/to/balance2.json"
   OOD_BALANCE_THRESHOLD=1000

User Balance
............

If the balance is defined as a ``user`` balance, then it applies to only that user. Omit the ``project`` key:

.. code:: json

   {
     "user": "user1",
     "value": 10
   }

Project Balance
...............

If the balance is defined as a ``project`` balance, then it applies to a project/account/group, whatever is defined for ``config.project_type``:

.. code:: json

   {
     "user": "user1",
     "project": "project1",
     "value": 10
   }

Maintenance Mode
-----------------

.. _maintenance-mode:

As an administrator you may want to have some downtime of the Open OnDemand service for various reasons,
while still telling your customers that the downtime is expected.

You can do this by setting Open OnDemand in 'Maintenance Mode'. Apache will serve 
``/var/www/ood/public/maintenance/index.html`` which you can change or brand to be your own. Changes
to this file will persist through upgrades.

Apache returns this html file and a 503 response code to all users who's IP does not match one of the
configured whitelist regular expressions.  The whitelist is to allow staff, localhost or a subset of
your users access while restricting others.

In this example we allow access to anyone from ``192.168.1..*`` which is the 192.168.1.0/24 CIDR and
the single IP '10.0.0.1'.

These are the settings you'll need for this functionality.

.. code:: yaml

  # /etc/ood/config/ood_portal.yml
  use_rewrites: true
  use_maintenance: true
  maintenance_ip_whitelist:
    # examples only! Your ip regular expressions will be specific to your site.
    - '192.168.1..*'
    - '10.0.0.1'

To start maintenance mode (and thus start serving this page) simply ``touch /etc/ood/maintenance.enable``
to create the necessary file. When your downtime is complete just remove the file and all the
traffic will be served normally again.  The existence of this file is what starts or stops maintenance
mode, not it's content, so you will not need to restart apache or modify it's config files for this to
take affect.

Grafana support
---------------

.. _grafana-support:

It's possible to display Grafana graphs within the ActiveJobs app when a user expands a given job.

Grafana must be configured to support embedded panels and at this time it is also required to have a anonymous organization.  Below are configuration options are needed to support displaying Grafana panels in ActiveJobs. Adjust `org_name` to match whatever organization you wish to be anonymous.

.. warning::

   Changing a Grafana install to support anonymous access can cause unintended consequences for how authenticated users interact with Grafana.
   It's recommended to test anonymous access on a non-production Grafana install if you do not already support anonymous access.

.. code:: shell

   [auth.anonymous]
   enabled = true
   org_name = Public
   org_role = Viewer

   [security]
   allow_embedding = true

The dashboard used by OSC is the `OnDemand Clusters <https://grafana.com/grafana/dashboards/12093>`_ dashboard.

Settings used to access Grafana are configured in the cluster config.  The following is an example from OSC:

.. code:: yaml

   custom:
     grafana:
       host: "https://grafana.osc.edu"
       orgId: 3
       dashboard:
         name: "ondemand-clusters"
         uid: "aaba6Ahbauquag"
         panels:
           cpu: 20
           memory: 24
       labels:
         cluster: "cluster"
         host: "host"
         jobid: "jobid"

When viewing a dashboard in Grafana choose the panel you'd wish to display and select `Share`.
Then choose the `Embed` tab which will provide you with the iframe URL that will need to be generated within OnDemand.
The time ranges and values for labels (eg: `var-cluster=`) will be autofilled by OnDemand.

* ``orgId`` is the ``orgId`` query parameter
* The dashboard ``name`` is the last segment of the URI before query parameters
* The ``uid``` is the UID portion of URL that is unique to every dashboard
* The ``panelId`` query parameter will be used as the value for either ``cpu`` or ``memory`` depending on the panel you have selected
* The values for ``labels`` are how OnDemand maps labels in Grafana to values expected in OnDemand. The ``jobid`` key is optional, the others are required.

Disable Host Link in Batch Connect Card
---------------------------------------

Batch connect cards like this have links to the compute node on which the job is currently running (highlighted).

.. figure:: /images/bc-card-w-hostlink.png
  :align: center

However, some sites may want to disable this feature because they do not allow ssh sessions on the compute
nodes.

To disable this, simply set the environment variable in the dashboards' env file
``/etc/ood/config/apps/dashboard/env`` to a falsy value (0, false, off).

.. code:: sh

  # don't show ssh link in batch connect card
  OOD_BC_SSH_TO_COMPUTE_NODE=off

Set Illegal Job Name Characters
-------------------------------

.. _set-illegal-job-name-characters:

If you encounter an issue in running batch connect applications complaining about invalid
job names like the error below.

``Unable to read script file because of error: ERROR! argument to -N option must not contain /``

To resolve this set ``OOD_JOB_NAME_ILLEGAL_CHARS`` to ``/`` for all OOD applications in the
``pun_custom_env`` attribute of the ``/etc/ood/config/nginx_stage.yml`` file.

.. code-block:: yaml

  # /etc/ood/config/nginx_stage.yml
  pun_custom_env:
    - OOD_JOB_NAME_ILLEGAL_CHARS: "/"
