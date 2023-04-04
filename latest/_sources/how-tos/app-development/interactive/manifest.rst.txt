.. _app-development-manifest:

Manifest yml files
==================

Every app (interactive and passenger) needs a ``manifest.yml`` file to describe it
to the Open OnDemand platform.

.. code:: yaml

  ---
  name: My Cool Biology App
  category: Interactive Apps
  subcategory: Biology
  role: batch_connect
  description: |
    This is a multi-line description that will be shown throughout the
    dashboard.
  # metadata:
  #   field_of_science: botany

name
  The name of the app. This will be shown in menu bars and on icons.
category
  The category of the app. This is used to group apps in navigation menus.
subcategory
  The subcategory of the app. This is used to group apps within the 
  navigation menu lists.
role
  The role of the app. Here ``batch_connect`` has special meaning to Open
  OnDemand and is required to indicate it's a batch connect app. Otherwise
  it's assumed to be a Passenger app.
description
  The description of the app. This will be used for additional text when hovering
  over icons.
icon (Optional)
  Apps default to look for an icon.png or icon.svg in their root directory,
  but this overrides that to specify the icon.
url (Optional)
  The url of the application. By default this is generated dynamically but
  can be overridden.
metadata (Optional)
  These are key value pairs you can add to apps for extra grouping capabilities.
new_window (Optional)
  A boolean (``true`` or ``false``) flag to toggle if the app should open a new
  window when clicked.


