.. _submit-yml-erb:

submit.yml.erb
==============

This is the file that is submitted to a batch connect job. It is comprised
of a ``script`` and a ``batch_connect`` attribute.  The ``batch_connect``
attribute can either be a ``basic`` template if your app is already an
http server or a ``vnc`` template if you need VNC capabilities.

These are reference pages, you can see 
:ref:`app-development-interactive-submit` for a broader overview.

.. toctree::
   :maxdepth: 2

   submit-yml/basic-bc-options
   submit-yml/vnc-bc-options
   submit-yml/script

Simple Example
--------------

  .. code-block:: yaml

      # a simple script.yml.erb file

      script:
        native:
          - "-n"
          - "1"
      batch_connect:
        template: "basic"
        header: "#!/bin/bash"

.. include:: ../../how-tos/app-development/interactive/global-submit.inc