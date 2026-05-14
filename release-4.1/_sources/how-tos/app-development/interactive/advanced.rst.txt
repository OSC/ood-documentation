.. _app-development-interactive-advanced:

Advanced Interactive Application Configurations
===============================================

Now that you have an application up and running,
here are some advanced features you can use.

Displaying choices made in Session Card
---------------------------------------

If you want to show a form attribute in the session card, you can set the
:ref:`display <display_option>` option to ``true``. For example, to show the 
version of R selected edit ``form.yml`` with:

.. code-block:: yaml
  :emphasize-lines: 3

  attributes:
    r_version:
      display: true # Displays the choice in the card
      widget: "select"
      options:
        - "4.2"
        - "4.1"
