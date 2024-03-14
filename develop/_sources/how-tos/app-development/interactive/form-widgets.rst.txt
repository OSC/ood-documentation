.. _form-widgets:

Form Widgets
============
  Checkbox (check_box)
    A checkbox. Note that you can change the checked and unchecked values. For example changing
    them from ``1`` and ``0`` to ``yes`` and ``no``.
  
      .. code-block:: yaml

        test_checkbox:
          widget: check_box
          checked_value: 1
          unchecked_value: 0
          label: "Test Checkbox"
          help: |
            Your help message

==================================================================

  Hidden Field (hidden_field)
    A hidden field that will not be shown, but will still be in the HTML.

      .. code-block:: yaml

        test_hidden_field:
          widget: "hidden_field"
          value: "Test Hidden Field Value"

==================================================================

  Number Field (number_field)
    A number field.

      .. code-block:: yaml

        num_cores:
          widget: "number_field"
          label: "Number of cores"
          value: 1
          help: |
            Your help message
          min: 1
          max: 28
          step: 1

==================================================================

  Radio Button (radio_button)
    Note that in the options below, the text to display is on the left of the comma, and the select value is on the right of the comma.
    The value: key represents the default selection.

      .. code-block:: yaml

        mode:
          widget: "radio_button"
          value: "1"
          help: |
            Your help message
          options:
            - ["Jupyter Lab", "1"] 
            - ["Jupyter Notebook", "0"]

==================================================================

  Resolution Field (resolution_field)
    Change the resolution for interactive applications that use VNC.

      .. code-block:: yaml

        test_resolution_field:
          widget: "resolution_field"
          label: "Test Resolution Field"
          required: true
          help: |
            Your help message

==================================================================

  Select Field (select)
    Note that in the options below, the text to display is on the left of the comma, and the select value is on the right of the comma.

      .. code-block:: yaml

        version:
          widget: "select"
          label: "JupyterLab Version"
          options:
            - [ "3.0",  "app_jupyter/3.0.17" ]
            - [ "2.3",  "app_jupyter/2.3.2" ]
            - [ "2.2",  "app_jupyter/2.2.10" ]
            - [ "1.2",  "app_jupyter/1.2.21" ]
          help: |
            Your help message

==================================================================

  TextArea Field (text_area)
    A text area.  This allows for multiple lines of text input.

      .. code-block:: yaml

        test_text_area:
          widget: "text_area"
          label: "Test Text Area"
          value: "Test Text Area Value"
          help: |
            Your help message

==================================================================

  Text Field (text_field)
    A text field.  This only allows for a single line of text input.

      .. code-block:: yaml

        test_text_field:
          widget: "text_field"
          label: "Test Text Field"
          value: "Test Text Value"
          help: |
            Your help message

.. _path_selector:

==================================================================

  Path Selector (path_selector)
    A Path Selector. This is a special OnDemand feature that is not
    directly an HTML input type. It builds a ``text_field`` input
    type, but also provides a button that will provide a modal that
    allows users to navigate through directories to select a path.

    This is useful in forms where a path must be selected and you
    want to allow your users to choose an arbirary path.

    ``directory`` is the initial directory the path selector will open
    to when the users opens the modal. This defaults to the users' HOME.

    ``show_hidden`` is a boolean flag to show hidden files or not. This
    defaults to false - it will not show hidden files.

    ``show_files`` is a boolean flag to show files or not. This defaults
    to true - it will show files.

    ``favorites`` allows you to override the :ref:`favorite paths you've added
    in files menu <add-shortcuts-to-files-menu>`.

      .. code-block:: yaml

        path:
          widget: "path_selector"
          directory: "/fs/ess/project"
          show_hidden: true
          show_files: false
          favorites:
            - /fs/ess
            - /fs/scratch

==================================================================


.. _markdown: https://en.wikipedia.org/wiki/Markdown
