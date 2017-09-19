.. _tutorial-ps-to-quota:

Tutorial: Creating a status app
===============================

We will make a copy of a status app that displays the user's running Passenger
processes on the OnDemand host to display the user's quota information in a
table.

The app we will be copying is: https://github.com/OSC/ood-example-ps. Running
this app looks like:

**add screenshot**

After this tutorial the resulting app will be:

**add screenshot**

This assumes you have followed the directions to :ref:`enabling-development-mode` on the
Dashboard.


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

Overview of app
---------------

#. The app uses the custom branded Bootstrap 3 that My Jobs ande ActiveJobs apps
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



Edit to run and parse quota
---------------------------

Update test
...........



Update command.rb
.................

Update app.rb and view/index.html
.................................


Brand App
---------

Update manifest.yml
...................

icon, name, category, description by editing file

link to font-awesome icons (4.7.0)

Update app.rb
.............

title in app

Publish App
-----------

ensure category matches a header that is configured to display as a menu

