.. _customization:

Customization (or the many OOD environment variables)
=====================================================

Setting the PUN Environment With ``nginx_stage.yml``
----------------------------------------------------

The configuration file ``nginx_stage.yml`` is the best way to set the environment which the PUN will use. Defining the mapping ``pun_custom_env`` allows setting Open OnDemand specific variables and is used for branding, message of the day setting, quota warnings, whitelists and other uses. For environment variables that OOD applications may need, are already in the environment and should be exposed to OOD (``$PATH``, ``$LD_LIBRARY_PATH``, etc...) define the sequence ``pun_custom_env_declarations``.

An example of both of these uses may be found in `nginx_stage_example.yml <https://github.com/OSC/ondemand/blob/d85a3982d69746144d12bb808d2419b42ccc97a1/nginx_stage/share/nginx_stage_example.yml#L26-L43>`__

Announcements and Message of the Day (MOTD)
-------------------------------------------

Two hooks for customizing the Dashboard are Announcements and MOTD. Announcements get the classes ``alert alert-warning`` and appear above the ``$OOD_DASHBOARD_LOGO`` . Announcement files are expected to be found at: ``/etc/ood/config/announcement.(md|yml)`` or ``/etc/ood/config/announcements.d/any_file_name.(md|yml)``. To display a MOTD file on the Dashboard ensure that the environment variables ``$MOTD_PATH`` and ``$MOTD_FORMAT`` are set like so:

   .. code-block:: sh

      MOTD_PATH="/path/to/your/motd" # this supports both file and RSS feed URIs
      MOTD_FORMAT="$MOTD_FORMAT_HERE" # markdown, txt, rss

.. note:: Warnings about the announcement file being missing may be present in users' nginx logs. Despite the warning the Dashboard will still function normally without those files being present.

Branding
-------------------

OOD provides several ways to customize the look of an installation.

Title
......

The title appears in the navbar and is controlled by the environment variable ``$OOD_DASHBOARD_TITLE``.

Logos
......

The Dashboard logo is controlled by the environment variable ``$OOD_DASHBOARD_LOGO``. The favicon is expected to exist at the path ``$OOD_PUBLIC_URL/favicon.ico``. For a default OOD installation the favicon will be located at ``/var/www/ood/public/favicon.ico``.

Colors
.......

   .. code-block:: sh

      OOD_BRAND_BG_COLOR='#c8102e'
      OOD_BRAND_LINK_ACTIVE_BG_COLOR='#990c23'

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

.. attention:: Should this go in Configure section?


Set default ssh host
--------------------

Custom Job Composer Templates
-----------------------------

Custom Error Page for Missing Home Directory on Launch
------------------------------------------------------

Some sites have the home directory auto-create on first ssh login, for example
via pam_mkhomedir.so. This introduces a problem if users first access the system
through OnDemand, which expects the existence of a user’s home directory.

In OnDemand <= 1.3 if the user's home directory was missing a non-helpful single
string error would display. Now a friendly error page displays. This error page
can be customized by adding a custom one to ``/etc/ood/config/pun/html/missing_home_directory.html``.

See `this Discourse discussion <https://discourse.osc.edu/t/launching-ondemand-when-home-directory-does-not-exist/53/>`_ for details.

