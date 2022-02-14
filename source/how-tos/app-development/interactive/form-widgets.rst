.. _form-widgets:

Form Widgets
============
  Checkbox (check_box)
  
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

      .. code-block:: yaml

        test_hidden_field:
          widget: "hidden_field"
          value: "Test Hidden Field Value"

==================================================================

  Number Field (number_field)

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

      .. code-block:: yaml

        test_text_area:
          widget: "text_area"
          label: "Test Text Area"
          value: "Test Text Area Value"
          help: |
            Your help message

==================================================================

  Text Field (text_field)

      .. code-block:: yaml

        test_text_field:
          widget: "text_field"
          label: "Test Text Field"
          value: "Test Text Value"
          help: |
            Your help message

==================================================================



.. _markdown: https://en.wikipedia.org/wiki/Markdown
