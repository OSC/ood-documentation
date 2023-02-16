.. _customizations:

Customizations
==============

.. tip::
  Check out the :ref:`pun-environment` for an overview of how environment variables can be
  added.

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

.. _motd_customization:

Message of the Day (MOTD)
-------------------------

You can configure the Dashboard to display the /etc/motd file on the front page - the same file that is displayed when ssh-ing to a login node.

To display a MOTD file on the Dashboard ensure that the environment variables ``$MOTD_PATH`` and ``$MOTD_FORMAT`` are set, where

   .. code-block:: sh

      MOTD_PATH="/etc/motd" # this supports both file and RSS feed URIs
      MOTD_FORMAT="txt" # markdown, txt, rss, markdown_erb, txt_erb

.. tip::
    The ``_erb`` formats support ERB rendering to generate more dynamic messages.

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


We recommend setting these values using the :ref:`OnDemand configuration properties <ondemand-d-ymls>`.
Currently only the dashboard uses the colors in the navbar.

.. list-table:: Branding
   :header-rows: 1
   :stub-columns: 1

   * - Feature
     - Property
     - Details
   * - Title
     - dashboard_title
     - The title appears in the navbar and is controlled by the property ``dashboard_title``. The default value is "Open OnDemand".
   * - Logo
     - dashboard_logo
     - The default value for ``dashboard_logo`` is ``/public/logo.png`` and this should be the URL to the logo. By default if you place a logo.png at ``/var/www/ood/public/logo.png`` it will be accessible via the URL ``https://your.ondemand.institution.edu/public/logo.png``.  SVG logo format is also supported.
   * - Logo height
     - dashboard_logo_height
     - The CSS height of the dashboard logo.
   * - Favicon
     - public_url
     - The favicon is expected to exist at the path ``$public_url/favicon.ico``. For a default OOD installation the favicon will be located at ``/var/www/ood/public/favicon.ico``.
   * - Brand background color
     - brand_bg_color
     - Controls the background color of the navbar in the dashboard
   * - Brand foreground color
     - brand_link_active_bg_color
     - Controls the background color the active link in the navbar in the dashboard
   * - Replace header title with logo
     - dashboard_header_img_logo
     - Value should be url to logo i.e. ``/public/logo.png``.  the background color the active link in the navbar in the dashboard
   * - Use white text on black background for navbar.
     - navbar_type
     - By default we use ``inverse`` for this value, which specifies to use `Bootstrap 3's inverted navbar <https://getbootstrap.com/docs/3.3/components/#navbar-inverted>`_ where text is white and background is black (or dark grey). You can set this to ``default`` to use black text on light grey background if it fits your branding better.

.. note:: It is possible to configure these settings using environment variables, although this is deprecated.
          For information about the properties and environment variables, see the :ref:`OnDemand configuration documentation <ondemand-d-ymls>`.

.. figure:: /images/dashboard_navbar_branding_bluered.png
   :align: center

   Nav bar if I set ``brand_bg_color`` to ``#0000ff`` and ``brand_link_active_bg_color`` to ``#ff0000`` and ``dashboard_title`` to ``OSC OnDemand``

Custom CSS files
................

For more control on the look and feel of the dashboard pages, use custom CSS files.
These CSS files will be added to all dashboard pages and loaded last to have precedence over default styles.

Add your CSS file references to the ``custom_css_files`` array property.
Drop the files into the Apache public assets folder, the default location is: ``/var/www/ood/public``.
The system will prepend the ``/public`` URL path, based on the ``public_url`` property, to load the files correctly.

**Example:** to load the following CSS file: ``/var/www/ood/public/myfolder/custom-branding.css``, add the configuration below.
This will result in a CSS tag added to all dashboard pages with the path: ``/public/myfolder/custom-branding.css``.

.. code-block:: yaml

  custom_css_files: ["/myfolder/custom-branding.css"]

.. _help_menu_guide:

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

Since OnDemand 2.1, custom links can be added to the Help menu using the configuration property ``help_menu``.
Links will be inserted at the end of the core links already included in the menu by the OnDemand codebase.

``help_menu`` supports all the link definitions developed for the custom navigation configuration.
For more information on how to create custom links, see `menus-based-on-links`_.

For information about how to configure properties, see the :ref:`OnDemand configuration documentation <ondemand-d-ymls>`.

.. code-block:: yaml

  help_menu:
    - group: "Documentation"
    - title: "Jupyter Docs"
      icon: "fas://book"
      url: "https://mydomain.com/path/jupyter"
    - title: "Support Docs"
      icon: "fas://book"
      url: "https://mydomain.com/path/support/docs"
    - group: "Custom Pages"
    - page: "rstudio_guide"
      title: "RStudio Guide"
      icon: "fas://window-restore"
    - group: "Profiles"
    - profile: "team1"
      title: "Team 1"
      icon: "fas://user"

.. figure:: /images/help_menu_links.png
   :align: center


.. _add-shortcuts-to-files-menu:

Add Shortcuts to Files Menu
---------------------------

The Files menu by default has a single link to open the Files app in the user's
Home Directory. More links can be added to this menu, for Scratch space and
Project space directories.

Adding more links currently requires adding a custom initializer to the
Dashboard app. Ruby code is placed in the initializer to add one or more Ruby
``FavoritePath`` (or ``Pathname`` for backwards compatibility)  objects to the ``OodFilesApp.candidate_favorite_paths`` array, a
global attribute that is used in the Dashboard app.

``FavoritePath`` is instantiated with a single ``String`` or ``Pathname`` argument, the
directory path, and with an optional keyword argument ``title`` specifying a
human readable title for that path.

Start by creating the file
:file:`/etc/ood/config/apps/dashboard/initializers/ood.rb` as such:

.. code-block:: ruby

  # /etc/ood/config/apps/dashboard/initializers/ood.rb

  Rails.application.config.after_initialize do
    OodFilesApp.candidate_favorite_paths.tap do |paths|
      # add project space directories
      projects = User.new.groups.map(&:name).grep(/^P./)
      paths.concat projects.map { |p| FavoritePath.new("/fs/project/#{p}")  }

      # add User scratch space directory
      paths << FavoritePath.new("/fs/scratch/#{User.new.name}")

      # Project scratch is given an optional title field
      paths.concat projects.map { |p| FavoritePath.new("/fs/scratch/#{p}", title: "Scratch")  }
    end
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

.. include:: customizations/profiles.inc

.. include:: customizations/main-navigation.inc
.. include:: customizations/interactive-apps-menu.inc

.. _set-upload-limits:

Set Upload Limits
-----------------

By default, the file size upload limit is 10737420000 bytes (~10.7 GB).

If you want set this to a lower value, set the ``FILE_UPLOAD_MAX`` configuration
in the file apps' configuration file ``/etc/ood/config/apps/shell/env``.

If you want to set it to a higher value set ``nginx_file_upload_max``
in ``/etc/ood/config/nginx_stage.yml`` to the desired value. If you have
``FILE_UPLOAD_MAX`` set from above, unset it.

If the values differ, the files app will choose the smaller of the two as the maximum
upload limit.

.. warning::
   Both of these configurations are expected to be numbers only (no characters)
   and in units of bytes. The default value of 10737420000 bytes is ~10.7 GB or ~10.0 Gib.

   Values like ``1000M`` or ``20G`` will not be accepted and may cause errors.

If you want to disable file upload altogether, set ``FILE_UPLOAD_MAX`` to 0 and leave
the ``nginx_file_upload_max`` configuration alone (or comment it out so the default
is used).

Block or Allow Directory Access
-------------------------------

By default, all directories are open and accessible through Open OnDemand (barring POSIX file permissions. Open OnDemand
can never read files the user cannot read).

By setting a colon delimited `OOD_ALLOWLIST_PATH` environment variable, the Job Composer, File Editor, and Files app
respect the allowlist in the following manner:

1. Users will be prevented from navigating to, uploading, downloading, viewing, or editing files that are not an eventual child of the allowlisted paths
2. Users will be prevented from copying a template directory from an arbitrary path in the Job Composer if the arbitrary path that is not an eventual child of the allowlisted paths
3. Users should not be able to get around this using symlinks

We recommend setting this environment variable in ``/etc/ood/config/nginx_stage.yml`` as a YAML mapping (key value pairs) in the mapping (hash/dictionary) ``pun_custom_env`` i.e. below would a list that allows access to home directories, project space, and scratch space at OSC:

.. code:: yaml

   pun_custom_env:
    OOD_ALLOWLIST_PATH: "/users:/fs/project:/fs/scratch"

.. warning:: This is not yet used in production at OSC, so we consider this feature "experimental" for now.

.. warning:: This allowlist is not enforced across every action a user can take in an app (including the developer views in the Dashboard). Also, it is enforced via the apps themselves, which is not as robust as using cgroups on the PUN.

.. _set-default-ssh-host:

Set Default SSH Host
--------------------

.. warning::
   The shell app does not work out of the box because all SSH hosts have to be explicitly allowed
   through the allowlist (see the section below).

   Because there are no hosts configured, no hosts are allowed.

In ``/etc/ood/config/apps/shell/env`` set the env var ``OOD_DEFAULT_SSHHOST`` to change the default ssh host.
Since 1.8, there is no out of the box default (in previous versions it was 'localhost', but this has been removed).

This will control what host the shell app ssh's to when the URL accessed is ``/pun/sys/shell/ssh/default`` which is the URL other apps will use (unless there is context to specify the cluster to ssh to).

Since 1.8 you can also set the default ssh host in the cluster configuration as well. Simply add
default=true attribute to the login section like the example below.

.. code-block:: yaml

   # /etc/ood/config/clusters.d/my_cluster.yml
   ---
   v2:
     metadata:
       title: "My Cluster"
     login:
       host: "my_cluster.my_center.edu"
       default: true

.. _set-ssh-allowlist:

Set SSH Allowlist
-----------------

In 1.8 and above we stopped allowing ssh access by default.  Now you have explicitly set
what hosts users will be allowed to connect to in the shell application.

Every cluster configuration with ``v2.login.host`` that is not hidden (it has
``v2.metadata.hidden`` attribute set to true) will be added to this allowlist.

To add other hosts into the allow list (for example compute nodes) add the configuration
``OOD_SSHHOST_ALLOWLIST`` to the ``/etc/ood/config/apps/shell/env`` file.

This configuration is expected to be a colon (:) separated list of GLOBs.

Here's an example of of this configuration with three such GLOBs that allow for shell
access into any compute node in our three clusters.

.. code:: shell

  # /etc/ood/config/apps/shell/env
  OOD_SSHHOST_ALLOWLIST="r[0-1][0-9][0-9][0-9].ten.osc.edu:o[0-1][0-9][0-9][0-9].ten.osc.edu:p[0-1][0-9][0-9][0-9].ten.osc.edu"

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

Hiding Job Arrays
------------------------------

When composing a new job, the job arrays field is shown on supported clusters. To Hide this field even on 
supported clusters, an option was added.

To reconfigure this, simply set the environment variable in the job composers' env file
``/etc/ood/config/apps/myjobs/env`` like so:

.. code:: sh

  # Don't show job arrays field even on supported clusters
  OOD_HIDE_JOB_ARRAYS=True

Custom Error Page for Missing Home Directory on Launch
------------------------------------------------------

Some sites have the home directory auto-create on first ssh login, for example
via ``pam_mkhomedir.so``. This introduces a problem if users first access the system
through OnDemand, which expects the existence of a user’s home directory.

In OnDemand <= 1.3 if the user's home directory was missing a non-helpful single
string error would display. Now a friendly error page displays. This error page
can be customized by adding a custom one to ``/etc/ood/config/pun/html/missing_home_directory.html``.

The default error page looks like this:

.. figure:: /images/customization_homedirmissing_default.png
   :align: center

An example of a custom error page has been provided at ``/opt/ood/nginx_stage/html/missing_home_directory.html.example.pam_mkhomedir`` and can be copied to ``/etc/ood/config/pun/html/missing_home_directory.html``. This example directs the user to first click a link to open the shell app which will create the home directory. The shell app's default host must be configured to be a host that is appropriate for this purpose. The custom error page looks like this:

.. figure:: /images/customization_homedirmissing_pammkdir.png
   :align: center



See `this Discourse discussion <https://discourse.osc.edu/t/launching-ondemand-when-home-directory-does-not-exist/53/>`_ for details.

.. _dashboard_pinned_apps:

Pinning Applications to the Dashboard
-------------------------------------

In version 2.0 you can now pin app Icons to the dashboard that link to the application form.

When configured a widget like the one below will appear on the dashboard's landing page.

.. figure:: /images/pinned_apps.png

The configuration for what apps to pin allows for three variants.

You can configure specific apps with a string of the type ``router/app_name``. 
For example ``sys/jupyter`` is the system installed app named jupyter.

Secondly you can configure globs like ``sys/*`` to pin all system installed apps. Or
Maybe ``sys/minimal_*`` to pin all system installed apps that begin with 'minimal'.

Lastly you can choose to pin apps based off of fields in their ``manifest.yml`` file.
You can match by type, category, subcategory and metadata fields.  These matches are
cumulative. Meaning an app has to match *all* of these to be pinned.  In the examples below
there is a configuration of type sys and category minimal. This configuration will only pin
system installed apps that are in the minimal category.  An app has to meet *both* these
criteria to be pinned to the dashboard.
  

Full examples are below:

.. code:: yaml

  # /etc/ood/config/ondemand.d/ondemand.yml
  pinned_apps:
    - sys/jupyter           # pin a specific system installed app called 'jupyter'
    
    - sys/bc_desktop/desk1  # pinned desktop app must contain exact desktop name - 'desk1'
 
    - 'sys/*'               # pin all system install apps. This also works for usr/* and dev/*
  
    - category: 'minimal'   # pin all the apps in the 'minimal' category
  
    - type: sys             # pin all system installed apps in the minimal category.
      category: 'minimal'

    # pin all system installed apps in the minimal category and the 
    # class instruction subcategory
    - type: sys
      category: 'minimal'
      subcategory: 'class_instruction'

    # pin all system installed apps in the minimal category, the 
    # class instruction subcategory and the metadata field 'field_of_science'
    # with an exact match on biology
    - type: sys             
      category: 'minimal'
      subcategory: 'class_instruction'
      field_of_science: 'biology'

    # pin any app with an exact match on the metadata field_of_science of biology
    - field_of_science: 'biology'

    # pin any app with an glob match *bio* on the metadata field_of_science
    - field_of_science: '*bio*'


Administrators can also configure the pinned apps to be grouped by any field
in the ``manifest.yml`` including metadata fields with the ``pinned_apps_group_by``
configuration.

This will create a row and a heading for each group like so (the image was generated
from grouping by category):

.. figure:: /images/grouped_pinned_apps.png

One can also change the menu length in the 'App's menu item. If you've
pinned more than 6 apps and you want to them to show up in this dropdown
list, simply increase the length with the option below.

.. code:: yaml

  # /etc/ood/config/ondemand.d/ondemand.yml
  pinned_apps_menu_length: 6        # the default number of items in the dropdown menu list
  pinned_apps_group_by: category    # defaults to nil, no grouping

Pinned Apps customizations
..........................

To customize the text, icon, or color of the pinned app tile,
use the ``tile`` configuration property in the application ``manifest`` or ``form``.
The ``form`` values will take precedence over any set in the ``manifest``.
All the values are optional and any set will override the default from the application.

.. code:: yaml

  tile:
    title: "Custom Title"
    icon: fa://desktop
    border_color: "red"
    sub_caption: |
      Custom Text Line 1
      Text Line 2
      Text Line 3

The CSS for the pinned app tiles has been optimized to support upto three lines of text for the ``sub_caption`` property.

.. figure:: /images/custom_pinned_apps.png

.. _dashboard_custom_layout:

Custom layouts in the dashboard
-------------------------------

Administrators can now customize what widgets appear on the dashboard and how they're
layed out on the page.

In it's simplest form this feature allows for a rearrangement of existing widgets. As
of 2.1 the existing widgets are:

- ``pinned_apps`` - Pinned Apps described above
- ``recently_used_apps`` - the four most recently used interactive applications.
  Launching these applications will start a new interactive session with the previously submitted parameters.
- ``sessions`` - the three most recent active interactive sessions
- ``motd`` - the Message of the Day
- ``xdmod_widget_job_efficiency`` - the XDMoD widget for job efficiency
- ``xdmod_widget_jobs`` - the XDMoD widget for job information

This feature also allows for administrators to *add* custom widgets.
Simply drop new files into ``/etc/ood/config/apps/dashboard/views/widgets`` and reference them
in the configuration. These partial files can be any format Rails recognizes, notably ``.html`` or
``.html.erb`` extensions.

Also if you use subdirectories under widgets, they can be referenced by relative paths. For example
``views/widgets/cluster/_my_cluster_widget.html.erb`` would be referenced in the configuration
as ``cluster/my_cluster_widget``.

.. warning::

 Rails expects files to be prefixed with an underscore. For example if you configured ``my_new_widget``
 the filename should be ``_my_new_widget.html``.

Without setting this configuration, the dashboard will arrange itself depending on what features are
enabled. For example if both pinned apps and XDMoD features are enabled it will arrange itself accordingly
based on a default layout.

Here's the default configuration when all of these features are enabled.

.. code:: yaml

  # /etc/ood/config/ondemand.d/ondemand.yml
  dashboard_layout:
    rows:
      - columns:
        - width: 8
          widgets:
            - pinned_apps
            - motd
        - width: 4
          widgets:
            - xdmod_widget_job_efficiency
            - xdmod_widget_jobs

``rows`` are an array of row elements. Each row element has a ``columns`` field which is an array
column elements. Each column element two fields. A ``width`` field that specifies the width in the
`bootstrap grid layout`_ which defaults to 12 columns in total. It also has a ``widgets`` field which
is an array of existing or newly added widgets to render in that column.

.. _bootstrap grid layout: https://getbootstrap.com/docs/4.0/layout/grid/

.. _customization_localization:

Customize Text in OnDemand
--------------------------

Using Rails support for Internationalization (i18n), we have internationalized many strings in the Dashboard and the Job Composer apps.

Initial translation dictionary files with defaults that work well for OSC and using the English locale (``en``) have been added (``/var/www/ood/apps/sys/dashboard/config/locales/en.yml`` and ``/var/www/ood/apps/sys/myjobs/config/locales/en.yml``). Sites wishing to modify these strings in order to provide site specific replacements for English, or use a different locale altogether, should do the following:

#. Copy the translation dictionary file (or create a new file with the same structure of the keys you want to modify) to ``/etc/ood/config/locales/en.yml`` and modify that copy.
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
       {},
       {}
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


.. _balance-warnings-on-dashboard:

Balance Warnings on Dashboard
--------------------------------

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
        {},
        {}
      ]
    }

Where ``version`` defines the version of the JSON schema used, ``timestamp``
defines when this file was generated, and ``balances`` is a list of quota objects
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


.. _maintenance-mode:

Maintenance Mode
-----------------


As an administrator you may want to have some downtime of the Open OnDemand service for various reasons,
while still telling your customers that the downtime is expected.

You can do this by setting Open OnDemand in 'Maintenance Mode'.
While Maintenance mode is active, Apache will not serve requests for paths outside the
``/public/maintenance/*`` wildcard. Instead, it will serve the ``/var/www/ood/public/maintenance/index.html``
file, which you can change or brand to be your own. Changes to this file will persist through upgrades.
Any assets (e.g., images, stylesheets, or javascript) needed by the HTML file should be placed
in the ``/var/www/ood/public/maintenance/`` directory. You can also put symbolic links into the
``/var/www/ood/public/maintenance/`` directory, if you want to reuse assets located elsewhere in your
file system.

While in maintenance mode, Apache returns the HTML file and a 503 response code to all users whose
IP does not match one of the configured allowlist regular expressions.
The allowlist is to allow staff, localhost or a subset of your users access while restricting others.

In this example we allow access to anyone from ``192.168.1..*`` which is the 192.168.1.0/24 CIDR and
the single IP '10.0.0.1'.

These are the settings you'll need for this functionality.

.. code:: yaml

  # /etc/ood/config/ood_portal.yml
  use_rewrites: true
  use_maintenance: true
  maintenance_ip_allowlist:
    # examples only! Your ip regular expressions will be specific to your site.
    - '192.168.1..*'
    - '10.0.0.1'

To start maintenance mode (and thus start serving this page) simply ``touch /etc/ood/maintenance.enable``
to create the necessary file. When your downtime is complete just remove the file and all the
traffic will be served normally again.  The existence of this file is what starts or stops maintenance
mode, not it's content, so you will not need to restart apache or modify it's config files for this to
take affect.


.. _grafana-support:

Grafana support
---------------

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
       cluster_override: "mysite"

When viewing a dashboard in Grafana choose the panel you'd wish to display and select `Share`.
Then choose the `Embed` tab which will provide you with the iframe URL that will need to be generated within OnDemand.
The time ranges and values for labels (eg: `var-cluster=`) will be autofilled by OnDemand.

* ``orgId`` is the ``orgId`` query parameter
* The dashboard ``name`` is the last segment of the URI before query parameters
* The ``uid`` is the UID portion of URL that is unique to every dashboard
* The ``panelId`` query parameter will be used as the value for either ``cpu`` or ``memory`` depending on the panel you have selected
* The values for ``labels`` are how OnDemand maps labels in Grafana to values expected in OnDemand. The ``jobid`` key is optional, the others are required.
* The ``cluster_override`` can override the cluster name used to make requests to Grafana if the Grafana cluster name varies from OnDemand cluster name.

.. _disable-host-link-batch-connect:

Disable Host Link in Batch Connect Session Card
-----------------------------------------------

Batch connect session cards like this have links to the compute node on which the job is currently running (highlighted).

.. figure:: /images/bc-card-w-hostlink.png
  :align: center

However, some sites may want to disable this feature because they do not allow ssh sessions on the compute
nodes.

To disable this, simply set the environment variable in the dashboards' env file
``/etc/ood/config/apps/dashboard/env`` to a falsy value (0, false, off).

.. code:: sh

  # don't show ssh link in batch connect card
  OOD_BC_SSH_TO_COMPUTE_NODE=off

If you wish to disable on a per-cluster basis, you can set the following in your :ref:`cluster YAML configuration <cluster-config-schema>`.

.. code-block:: yaml
   :emphasize-lines: 3-

   v2:
      # ...
      batch_connect:
        ssh_allow: false

.. _set-illegal-job-name-characters:

Set Illegal Job Name Characters
-------------------------------

If you encounter an issue in running batch connect applications complaining about invalid
job names like the error below.

``Unable to read script file because of error: ERROR! argument to -N option must not contain /``

To resolve this set ``OOD_JOB_NAME_ILLEGAL_CHARS`` to ``/`` for all OOD applications in the
``pun_custom_env`` attribute of the ``/etc/ood/config/nginx_stage.yml`` file.

.. code-block:: yaml

  # /etc/ood/config/nginx_stage.yml
  pun_custom_env:
    - OOD_JOB_NAME_ILLEGAL_CHARS: "/"

.. _customize_dex_theme:

Customize Dex Theme
-------------------

It's possible to use a customized theme when authenticating with Dex when using OnDemand's default authentication.
Refer to the upstream `Dex template docs`_ for additional information on templating Dex.

The simplest approach is to copy the OnDemand theme and make changes.  This is idea if you wish to make the following changes:

- Change navigation or login page logos
- Change favicon
- Change CSS styles

.. code-block:: sh

   cp -r /usr/share/ondemand-dex/web/themes/ondemand /usr/share/ondemand-dex/web/themes/mycenter

To update the theme you must modify ``/etc/ood/config/ood_portal.yml`` and regenerate the Dex configuration:

.. code-block:: yaml
   :emphasize-lines: 3-

   dex:
   # ...
     frontend:
       theme: mycenter

The default ``ondemand`` theme can also be configured using the following configuration keys within ``/etc/ood/config/ood_portal.yml``:

.. code-block:: yaml
   :emphasize-lines: 4-

   dex:
   # ...
     frontend:
       issuer: "MyCenter OnDemand"
       extra:
         navLogo: "/path/to/custom/nav-logo.png"
         loginLogo: "/path/to/custom/logo.png"
         loginTitle: "Log in with your Center username and password"
         loginButtonText: "Log in with your Center account"
         usernamePlaceholder: "center-username"
         passwordPlaceholder: "center-password"
         loginAlertMessage: "Login services will be down during center maintenance between 8:00 AM EST and 10:00 AM EST"
         loginAlertType: "warning"

Changes are applied by running ``update_ood_portal`` and restarting the ``ondemand-dex`` service.

.. code-block:: sh

   sudo /opt/ood/ood-portal-generator/sbin/update_ood_portal
   sudo systemctl restart ondemand-dex.service

.. _dex template docs: https://dexidp.io/docs/templates/

.. _xdmod_integration:

XDMoD Integration
-----------------


XDMoD Integration requires XDMoD 9+, OnDemand 1.8+, and the ability to facilitate single sign on between the two services. Currently this has been demonstrated to work using OpenID Connect via Keycloak as well as a modified instance of Dex Identity Provider to support sessions.

.. figure:: /images/customization_xdmod.png
   :align: center

   Example of XDMoD Job Efficiency reports in the OnDemand Dashboard.

Steps to enable the XDMoD reports in the OnDemand Dashboard:

#. Configure OnDemand with XDMoD host URL in PUN /etc/ood/config/nginx_stage.yml

   .. code-block:: yaml

      pun_custom_env:
        OOD_XDMOD_HOST: "https://xdmod.osc.edu"

#. Add OnDemand host as domain to XDMoD portal settings for CORS /etc/xdmod/portal_settings.ini

   .. code-block:: none

      domains = "https://ondemand.osc.edu"

#. Configure identity provider to include OnDemand host in HTTP `Content-Security-Policy for frame-ancestors <https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy/frame-ancestors>`_ since OnDemand uses iFrames to trigger SSO with XDMoD when a user logs in. Below is what we ensured Content-Security-Policy header for frame-ancestors was set to when configuring Keycloak:

   .. code-block:: none

      frame-ancestors https://*.osc.edu 'self'

#. If you want the XDMoD links in the OnDemand Job Composer you also need to configure OnDemand with XDMoD resource id in each cluster config. For example, in the hpctoolset the resource_id for the hpc cluster is 1 in XDMoD, so we modify /etc/ood/config/clusters.d/hpc.yml to add a xdmod map to the custom map at the bottom of the file:

   .. code-block:: yaml
      :emphasize-lines: 10-

      v2:
       metadata:
         title: "HPC Cluster"
       login:
         host: "frontend"
       job:
         adapter: "slurm"
         cluster: "hpc"
         bin: "/usr/bin"
       custom:
         xdmod:
           resource_id: 1

#. In the Job Composer, Open XDMoD job links will include a warning message that the job may not appear in XDMoD for up to 24 hours after the job completed. The message is to address the gap of time between the job appearing as completed in the Job Composer and the job appearing in Open XDMoD after the ingest and aggregation script is run. This message appears from the time the Job Composer becomes aware of the job completion status, till an elapsed time specified in seconds by the locale key ``en.jobcomposer.xdmod_url_warning_message_seconds_after_job_completion`` which defaults to 24 hours (86400 seconds) with a text message specified by locale key  ``en.jobcomposer.xdmod_url_warning_message``. To disable this message, set the value you your locale file under ``/etc/ood/config/locales``. For example, in the default locale we have these values:

   .. code-block:: yaml

      en:
        jobcomposer:
          xdmod_url_warning_message: "This job may not appear in Open XDMoD until 24 hours after the completion of the job."
          xdmod_url_warning_message_seconds_after_job_completion: 86400


   Which results in these warning messages appearing in Job Composer:

   .. figure:: /images/customization_xdmod_jobcomposer_warning_1.png
      :align: center
   .. figure:: /images/customization_xdmod_jobcomposer_warning_2.png
      :align: center


.. _remote-file-systems:

Accessing Remote File Systems
-----------------------------

Since 2.1 you can use ``rclone`` to interact with remote file systems.  Since
every command in Open OnDemand is issued *as the user*, the user themselves
are required to setup their ``rclone`` remomtes.

You can refer to the `OSC's rclone documentation`_ on how to configure rclone
remotes.

To enable this feature ensure that ``rclone`` is installed on the same machine
that Open OnDemand is installed. You also have to enable the feature through
the :ref:`configuration entry for enabling remote filesystems <remote_files_enabled>`.

Cancel Interactive Sessions
---------------------------

We can now cancel an interactive session from the session panel without deleting the session card.
This functionality will allow users to remove the job from the scheduler and keep the information in the OnDemand interface.

This feature is disabled behind a feature toggle. To enable it, set the configuration property ``cancel_session_enabled: true``.
For more information on how to configure properties, see :ref:`configuration documentation <configuration_properties>`.

When enabled, the cancel button will appear for active sessions.
When the session is cancelled, the job will be cancelled in the scheduler,
the status will change to ``completed``, and the session card will be kept.
For completed sessions, the system will only show the delete button.

.. figure:: /images/cancel_session.png
  :align: center

.. include:: customizations/custom-pages.inc
.. include:: customizations/support-ticket.inc

.. _OSC's rclone documentation: https://www.osc.edu/resources/getting_started/howto/howto_use_rclone_to_upload_data
.. _2.0 documentation for controling the navbar: https://osc.github.io/ood-documentation/release-2.0/customization.html#control-which-apps-appear-in-the-dashboard-navbar
