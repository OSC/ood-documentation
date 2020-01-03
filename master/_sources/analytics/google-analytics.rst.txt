.. _google-analytics:

Adding Google Analytics
========================

.. _Google service accounts: https://cloud.google.com/iam/docs/service-accounts
.. _Google IAM roles: https://cloud.google.com/iam/docs/understanding-roles
.. _Google Analytics: https://analytics.google.com/analytics/web

If you wish you can setup your Open-OnDemand instance to send usage data to Google Analytics
(GA) that you can then query and report on, this page walks through how to do just that.

.. note::

  You'll need to have a `Google Analytics`_ account setup as a prerequisite to this.

  To query GA You'll need to have to have a service account setup with the appropriate permissions. See
  info on `Google service accounts`_ and `Google IAM roles`_ for more details on that.


Configure Open OnDemand
--------------------------
Add your google analytics id your ood_portal.yml file.

.. code-block:: yaml

  # /etc/ood/config/ood_portal.yml
  ---

  analytics:
    # the id will be specific to your account, but url is likely the same
    id: UA-99999999-1
    url: "http://www.google-analytics.com/collect"

This configuration will generate a block similar to this in your apache's 
``ood-portal.conf`` file (after running the ood-portal-generator). 

.. code-block:: apache

  <Location "/pun">
    ...

    SetEnv OOD_ANALYTICS_TRACKING_URL "http://www.google-analytics.com/collect"
    SetEnv OOD_ANALYTICS_TRACKING_ID  "UA-99999999-1"
    LuaHookLog analytics.lua analytics_handler
  </Location>

Configure Google Analytics
------------------------------

You'll need to create all of these custom dimensions and custom metrics in the appropriate GA
account(s). 

.. warning::

  Order matters here! Index numbers are given to ensure you create and define these
  items in the correct order.  Otherwise Google Analytics will be incorrectly indexing
  these metrics.

  As an example say Username gets index 3 instead of index 1. Now when you query for 
  `dimension3` thinking it's timestamps, you'll get back usernames instead!

.. table:: GA custom dimensions
   :widths: auto

   =================== ======== ============
    Name                 Index    Scope
   =================== ======== ============
   Username                1        User
   Session ID              2        Session
   Timestamp               3        Hit
   Remote Username         4        Hit
   Request Method          5        Hit
   Request Status          6        Hit
   Document Referrer       7        Hit
   =================== ======== ============

.. table:: GA custom metrics
   :widths: auto

   =================== ======== ============ ================
    Name                 Index    Scope      Formatting Type
   =================== ======== ============ ================
   Proxy Time             1        Hit            Integer
   User Map Time          2        Hit            Integer
   =================== ======== ============ ================

Querying Google Analytics
---------------------------

.. _GA client libraries: https://developers.google.com/analytics/devguides/reporting/core/v3/libraries

Now that you have Open-OnDemand sending information to GA and it's all configured correctly,
you can now query GA for this information, parse it and present it in any fashion you like. 

Here's a small portion of how we query GA in ruby, but there are many `GA client libraries`_ 
available. 

This example is not complete and is only meant to illustrate how to query GA given the defined
metric set above. Let's go through each of these things. 

.. code-block:: ruby

  # Dimensions - here we want dimensions 1, 3 and something called pagePath which is the web 
  # page requested. pagePath is a google predefined dimension that we populated. Dimensions 1 
  # and 3 were created above and are the username and timestamp (this is why the order in 
  # which they're defined is important).
  DIMENSIONS = %w(
    ga:dimension3
    ga:dimension1
    ga:pagePath
  )

  # we only want to report the hit metrics
  METRICS    = %w(
    ga:hits
  )

  # First we specify the host so that we only get metrics from a specific host. Secondly, 
  # we filter only only 200 responses (dimension6 is status code) and we don't want to 
  # report on file editor edits.
  FILTERS    = %W(
    ga:hostname==#{HOST};ga:dimension6==200;ga:pagePath!=/pun/sys/file-editor/edit
  )

  # now we can create our analytics object and make the query
  analytics = Google::Apis::AnalyticsV3::AnalyticsService.new

  # Here we query for the data that we want. A lot of things are omitted in this example
  # for brevity like START_DATE (dynamic query times like the first day of the month) 
  # or GA_PROFILE (part of our credentials). And the fact that this is in a loop paginating
  # the results, updating 'start_index' and only requesting STEP_SIZE (10,000 in our case)
  # results at a time.
  results = analytics.get_ga_data(
    "ga:#{GA_PROFILE}",
    START_DATE,
    END_DATE,
    METRICS.join(','),
    dimensions:  DIMENSIONS.empty? ? nil : DIMENSIONS.join(','),
    filters:     FILTERS.empty?    ? nil : FILTERS.join(','),
    sort:        SORT.empty?       ? nil : SORT.join(','),
    start_index: start_index,
    max_results: STEP_SIZE
  )

  target = open('my-report', "w")

  # now we can write out the results in a format that I want for my reporting.
  results.rows.each do |row|
    begin
      app = row[2]
      row[2] = parse_uri(app, user: row[1])
      row << app
      target.write "#{row.join('|')}\n"
  end


More Info
-----------

.. _GA measurement protocol: https://developers.google.com/analytics/devguides/collection/protocol/v1/reference
.. _analytics lua code: https://github.com/OSC/ondemand/blob/master/mod_ood_proxy/lib/analytics.lua

For reference, here's more detailed information about implementations and protocols described
in this document.

See our `analytics lua code`_ for the implementation of how we're extracting this information, 
parsing it and sending it to Google.

See the `GA measurement protocol`_ for more details on the format we're sending this data in.