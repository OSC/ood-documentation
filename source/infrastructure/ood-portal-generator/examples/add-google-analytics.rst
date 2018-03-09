.. _add-google-analytics:

Add Google Analytics
--------------------

To support this project we recommend enabling Google Analytics with the
following options:

.. code-block:: yaml

   # /etc/ood/config/ood_portal.yml
   ---

   analytics:
     id: UA-79331310-4
     url: "http://www.google-analytics.com/collect"

This will collect various metrics and submit them to OSC's Google Analytics
account.

Build the Apache configuration file and install it.

.. note::

   Please contact us if you'd like access to your center's Google Analytics
   data. This will require us to generate a new Property ID for your center
   that we can then share with you.
