.. _tutorial-ps-to-quota:

Tutorial: Creating a status app
===============================

Overview of app
---------------

We will make a copy of a status app that displays the running Passenger
processes on the OnDemand host. We will use this as a starting point to
create a new status app that displays quota information in a table.

The app we will be copying is: https://github.com/OSC/ood-example-ps. Running
this app looks like:

.. figure:: /images/app-dev-tutorial-ps-to-quota-1.png
   :align: center

   What app looks like after cloning and launching.

After this tutorial the resulting app will be:

.. figure:: /images/app-dev-tutorial-ps-to-quota-2.png
   :align: center

   What app looks like after modifying in this tutorial.

This assumes you have followed the directions to :ref:`enabling-development-mode` on the
Dashboard.

#. The app uses the custom branded Bootstrap 3 that My Jobs and Active Jobs apps
   use.
#. The navbar contains a link back to the dashboard.
#. On a request, the app runs a shell command, parses the output, and displays
   the result in a table.
#. It is built in Ruby using the `Sinatra framework <http://www.sinatrarb.com/>`__, a lightweight web framework
   similar to `Python's Flask <http://flask.pocoo.org/>`__ and `Node.js's Express <https://expressjs.com/>`__


Benefits
........

This serves as a good starting point for any status app to build for OnDemand,
because

#. the app has the branding matching other OnDemand apps
#. all status apps will do something similar on a request to the app:

   #. get raw data from a shell command or http request
   #. parse the raw data into an intermediate object representation
   #. use that intermediate object representation to display the data formatted
      as a table or graph

#. the app can be deployed without requiring a build step because gem
   dependencies (specified in ``Gemfile`` and ``Gemfile.lock``) are pure ruby
   and versioned with the app under ``vendor/bundle`` 
#. most of the app can be modified without requiring a restart due to proper use
   of Sinatra reloader extension
#. app has a built in scaffold for unit testing using minitest


Files and their purpose
.......................

.. list-table:: Main files
   :header-rows: 1

   * - File
     - Description
   * - config.ru
     - entry point of the Passenger Ruby app
   * - app.rb
     - Sinatra app config and routes; this in a separate file from config.ru so
       that code reloading will work
   * - command.rb
     - class that defines an AppProcess struct, executes ps, and parses the
       output of the ps command producing an array of structs
   * - test/test_command.rb
     - a unit test of the parsing code
   * - views/index.html
     - the main section of the html page template using an implementation of `ERB <https://ruby-doc.org/stdlib-2.2.0/libdoc/erb/rdoc/ERB.htm://ruby-doc.org/stdlib-2.2.0/libdoc/erb/rdoc/ERB.html>`__
       called `erubi <https://github.com/jeremyevans/erub://github.com/jeremyevans/erubi>`__
       which auto-escapes output of ERB tags by default (for security)
   * - views/layout.html
     - the rendered HTML from views/index.html is insterted into this layout,
       where css and javascript files are included

.. list-table:: Other files
   :header-rows: 1

   * - File
     - Description
   * - Gemfile, Gemfile.lock
     - defines gem dependencies for the app (see `Bundler's Rationale <http://bundler.io/rationale.html>`__)
   * - vendor/bundle
     - installed and versioned gem dependencies
   * - tmp/
     - tmp directory is kept so its easier to ``touch tmp/restart.txt`` when you
       want to force Passenger to restart an app
   * - public/
     - serve up static assets like Bootstrap css; in OnDemand, NGINX auto-serves
       all files under public/ directly, without going through the Passenger
       process, which makes this much faster; as a result, each static file is
       in a directory with an explicit version number, so if these files ever
       change we change the version, which is one cache busting strategy
   * - Rakefile
     - this provides a default Rake task for running the automated tests under
       test/, so you can run the tests by running the command ``rake``
   * - test/minitest_helper.rb
     - contains setup code common between all tests

Clone and setup
---------------

#. Login to Open OnDemand, click "Develop" dropdown menu and click the "My Sandbox Apps (Development)" option.
#. Click "New Product" and "Clone Existing App".
#. Fill out the form:

   #. Directory name: quota
   #. Git remote: https://github.com/OSC/ood-example-ps
   #. Check "Create new Git Project from this?"
   #. Click Submit

#. Launch the app by clicking the large blue Launch button. In a new browser
   window/tab you will see the output of a ps command filtered using grep.

#. Switch browser tab/windows back to the dashboard Details view of the app and
   click "Files" button on the right to open the app's directory in the File
   Explorer.


Edit to run and parse quota
---------------------------

The app runs and parses this command:

.. code-block:: sh

   ps aux | grep '[A]pp'

We will change it to run and parse this command:

.. code-block:: sh

   quota -spw

Update test/test_command.rb
...........................

Run the command to get example data. Copy and paste the output into the test, and
update the assertions to expect an array of "quotas" instead of "processes"
with appropriate attributes.

Diff:

.. code-block:: diff

      def test_command_output_parsing
        output = <<-EOF
    -
    -efranz    30328  0.1  0.1 462148 28128 ?        Sl   20:28   0:00 Passenger RackApp: /users/PZS0562/efranz/ondemand/dev/quota
    -
    +Disk quotas for user efranz (uid 10851):
    +     Filesystem  blocks   quota   limit   grace   files   quota   limit   grace
    +10.11.200.32:/PZS0562/  99616M    500G    500G       0    933k   1000k   1000k       0
    EOF
    -    processes = Command.new.parse(output)
    +    quotas = Command.new.parse(output)

    -    assert_equal 1, processes.count
    +    assert_equal 1, quotas.count, "number of structs parsed should equal 1"

    -    p = processes.first
    +    q = quotas.first

    -    assert_equal "efranz", p.user
    -    assert_equal "462148", p.vsz
    -    assert_equal "28128", p.rss
    -    assert_equal "0:00", p.time
    -    assert_equal "Passenger RackApp: /users/PZS0562/efranz/ondemand/dev/quota", p.command
    +    assert_equal "10.11.200.32:/PZS0562/", q.filesystem, "expected filesystem value not correct"
    +    assert_equal "99616M", q.blocks, "expected blocks value not correct"
    +    assert_equal "500G", q.blocks_limit, "expected blocks_limit value not correct"
    +    assert_equal "933k", q.files, "expected files value not correct"
    +    assert_equal "0", q.files_grace, "expected files_grace value not correct"
      end


Resulting test method:

.. code-block:: ruby

    class TestCommand < Minitest::Test

      def test_command_output_parsing
        output = <<-EOF
    Disk quotas for user efranz (uid 10851):
        Filesystem  blocks   quota   limit   grace   files   quota   limit   grace
    10.11.200.32:/PZS0562/  99616M    500G    500G       0    933k   1000k   1000k       0
    EOF
        quotas = Command.new.parse(output)

        assert_equal 1, quotas.count, "number of structs parsed should equal 1"

        q = quotas.first

        assert_equal "10.11.200.32:/PZS0562/", q.filesystem, "expected filesystem value not correct"
        assert_equal "99616M", q.blocks, "expected blocks value not correct"
        assert_equal "500G", q.blocks_limit, "expected blocks_limit value not correct"
        assert_equal "933k", q.files, "expected files value not correct"
        assert_equal "0", q.files_grace, "expected files_grace value not correct"
      end
    end

Update command.rb
.................

Run test by running `rake` command and you will see it fail:

.. code-block:: sh

    $ rake
    Run options: --seed 58990

    # Running:

    F

    Finished in 0.000943s, 1060.4569 runs/s, 1060.4569 assertions/s.

      1) Failure:
    TestCommand#test_command_output_parsing [/users/PZS0562/efranz/ondemand/dev/quota/test/test_command.rb:14]:
    number of structs parsed should equal 1.
    Expected: 1
      Actual: 3

    1 runs, 1 assertions, 1 failures, 0 errors, 0 skips
    rake aborted!
    Command failed with status (1)

    Tasks: TOP => default => test
    (See full trace by running task with --trace)

.. warning::

   To run commands like rake through the shell you need to make sure you are on
   a host that has the correct version of Ruby installed. For OnDemand that likely
   means using Software Collections with the same packages used to install OnDemand.

   With SCL, running rake with rh-ruby22 pacakge looks like:

   ``scl enable rh-ruby22 -- rake``

   With SCL, running git commands using git19 looks like:

   ``scl enable git19 -- git commit -m "initial commit"``

   You can avoid this by loading the SCL packages in your .bashrc or .bash_profile file.
   For example, in my .bash_profile I have:

   .. code-block:: sh

      if [[ ${HOSTNAME%%.*} == webtest04*  ]]
      then
        scl enable rh-ruby22 nodejs010 git19 v8314 python27 -- bash
      fi

Change the command we are using, fix the command output parsing, and fix the struct definition so the unit test passes.

.. code-block:: diff

    class Command
      def to_s
    -    "ps aux | grep '[A]pp'"
    +    "quota -spw"
      end

    -  AppProcess = Struct.new(:user, :pid, :pct_cpu, :pct_mem, :vsz, :rss, :tty, :stat, :start, :time, :command)
    +  Quota = Struct.new(:filesystem, :blocks, :blocks_quota, :blocks_limit, :blocks_grace, :files, :files_quota, :files_limit, :fil

      # Parse a string output from the `ps aux` command and return an array of
      # AppProcess objects, one per process
      def parse(output)
        lines = output.strip.split("\n")
    -    lines.map do |line|
    -      AppProcess.new(*(line.split(" ", 11)))
    +    lines.drop(2).map do |line|
    +      Quota.new(*(line.split))
        end
      end

After the changes part of the command.rb will look like this:

.. code-block:: ruby

    class Command
      def to_s
        "quota -spw"
      end

      Quota = Struct.new(:filesystem, :blocks, :blocks_quota, :blocks_limit, :blocks_grace, :files, :files_quota, :files_limit, :files_grace)

      # Parse a string output from the `ps aux` command and return an array of
      # AppProcess objects, one per process
      def parse(output)
        lines = output.strip.split("\n")
        lines.drop(2).map do |line|
          Quota.new(*(line.split))
        end
      end

Now when we run the test they pass:

.. code-block:: sh

    $ rake
    Run options: --seed 60317

    # Running:

    .

    Finished in 0.000966s, 1035.1494 runs/s, 6210.8963 assertions/s.

    1 runs, 6 assertions, 0 failures, 0 errors, 0 skips

Update app.rb and view/index.html
.................................

Update app.rb:

.. code-block:: diff

    helpers do
      def title
    -    "Passenger App Processes"
    +    "Quota"
      end
    end

    # Define a route at the root '/' of the app.
    get '/' do
      @command = Command.new
    -  @processes, @error = @command.exec
    +  @quotas, @error = @command.exec

      # Render the view
      erb :index
    end


In view/index.html, replace the table with this:

.. code-block:: erb

    <table class="table table-bordered">
      <tr>
        <th>Filesystem</th>
        <th>Blocks</th>
        <th>Blocks Quota</th>
        <th>Blocks Limit</th>
        <th>Blocks Grace</th>
        <th>Files</th>
        <th>Files Quota</th>
        <th>Files Limit</th>
        <th>Files Grace</th>
      </tr>
      <% @quotas.each do |quota| %>
      <tr>
        <td><%= quota.filesystem %></td>
        <td><%= quota.blocks %></td>
        <td><%= quota.blocks_quota %></td>
        <td><%= quota.blocks_limit %></td>
        <td><%= quota.blocks_grace %></td>
        <td><%= quota.files %></td>
        <td><%= quota.files_quota %></td>
        <td><%= quota.files_limit %></td>
        <td><%= quota.files_grace %></td>
      </tr>
      <% end %>
    </table>

These changes should not require an app restart. Go to the launched app and reload the page to see the changes.

Brand App
---------

The app is looking good, but the details page still shows the app title "Passenger App Processes". To change this and the icon, edit the manifest.yml:

.. code-block:: diff

    -name: Passenger App Processes
    -description: Display your running Passenger app proceseses in a table
    +name: Quota
    +description: Display quotas
    +icon: fa://hdd-o

* The icon follows format of ``fa://{FONTAWESOMENAME}`` where you replace ``{FONTAWESOMENAME}`` with an icon from http://fontawesome.io/icons/.
  In this case we are using ``fa-hdd-o`` which we write in the manifest as ``fa://hdd-o``: http://fontawesome.io/icon/hdd-o/

Publish App
-----------

Publishing an app requires two steps:

#. Updating the manifest.yml to specify the category and optionally subcategory, which indicates where in the dashboard menu the app appears.
#. Having an administrator checkout a copy of the production version to a directory under /var/www/ood/apps/sys


Steps:

#. Add category to manifest so app appears in Files menu:

    .. code-block:: diff

        name: Quota
        description: Display quotas
        icon: fa://hdd-o
        +category: Files
        +subcategory: Utilities

#. Version these changes. Click Shell button on app details view, and then commit the changes:

    .. code-block:: sh

       git add .
       git commit -m "update manifest for production"

       # if there is an external remote associated with this, push to that
       git push origin master

#. As the admin, sudo copy or clone this repo to production

    .. code-block:: sh

       # as sudo on OnDemand host:
       cd /var/www/ood/apps/sys
       git clone /users/PZS0562/efranz/ondemand/dev/quota


#. Reload the dashboard.

.. figure:: /images/app-dev-tutorial-ps-to-quota-published.png
   :align: center

   Every user can now launch the Quota from the Files menu.

.. warning::

   Accessing this new app for the first time will cause your NGINX server to restart, killing all websocket connections, which means resetting your active Shell sessions.

