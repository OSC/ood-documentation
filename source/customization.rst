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



Add URLs to Help menu
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


Add shortcuts to Files menu
---------------------------

The Files menu by default has a single link to open the Files app in the user's
Home Directory. More links can be added to this menu, for Scratch space and
Project space directories.

Adding more links currently requires adding a custom initializer to the
Dashboard app. Ruby code is placed in the initializer to add one or more Ruby
``Pathname`` objects to the ``OodFilesApp.candidate_favorite_paths`` array, a
global attribute that is used in the Dashboard app.

Start by creating the file
:file:`/etc/ood/config/apps/dashboard/initializers/ood.rb` as such:

.. code-block:: ruby

   # /etc/ood/config/apps/dashboard/initializers/ood.rb

   OodFilesApp.candidate_favorite_paths.tap do |paths|
     # add project space directories
     projects = User.new.groups.map(&:name).grep(/^P./)
     paths.concat projects.map { |p| Pathname.new("/fs/project/#{p}")  }

     # add scratch space directories
     paths << Pathname.new("/fs/scratch/#{User.new.name}")
     paths.concat projects.map { |p| Pathname.new("/fs/scratch/#{p}")  }
   end

- The variable ``paths`` is an array of ``Pathname`` objects that define a list
  of what will appear in the Dashboard menu for Files
- At OSC, the pattern for project paths follows
  :file:`/fs/project/{project_name}`. So above we:

  #. get an array of all user's groups by name
  #. filter that array for groups that start with ``P`` (i.e., ``PZS0002``,
     ``PAW0003``, ...)
  #. using ``map`` we turn this array into an array of ``Pathname`` objects to
     all the possible project directories the user could have.
  #. extend the paths array with this list of paths

- For possible scratch space directories, we look for either
  :file:`/fs/scratch/{project_name}` or :file:`/fs/scratch/{user_name}`

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

Whitelist directories
---------------------

Best place for this is nginx_stage


Set default ssh host
--------------------

COPY FROM

Custom Job Composer Templates
-----------------------------

COPY FROM 

Custom Error Page for Missing Home Directory on Launch
------------------------------------------------------

Some sites have the home directory auto-create on first ssh login, for example
via pam_mkhomedir.so. This introduces a problem if users first access the system
through OnDemand, which expects the existence of a user’s home directory.

In OnDemand <= 1.3 if the user's home directory was missing a non-helpful single
string error would display. Now a friendly error page displays. This error page
can be customized by adding a custom one to ``/etc/ood/config/pun/html/missing_home_directory.html``.

See `this Discourse discussion <https://discourse.osc.edu/t/launching-ondemand-when-home-directory-does-not-exist/53/>`_ for details.


Control which apps appear in the Dashboard Navbar
-------------------------------------------------

In OnDemand 1.3 and earlier, 