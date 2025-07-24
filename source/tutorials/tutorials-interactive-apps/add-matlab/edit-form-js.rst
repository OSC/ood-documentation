.. _app-development-tutorials-interactive-apps-add-matlab-edit-form-js:

Edit ``form.js``
================

OnDemand supports dynamic interactive forms using a file named ``~/ondemand/dev/bc_my_center_matlab/form.js``. This file is free-form; anything that can be done with client-side JavaScript may be done in this file. OSC has used this file to:

- Limit the user's CPU/memory selection options to the type of hardware that they are requesting (`OSC MATLAB JavaScript`_)
- Show or hide a license field based on whether the user is permitted to use the OSC academic license or if they are required to use a different license provider (`OSC ANSYS JavaScript`_)
- Implement a file picker using the File Explorer's API, `Webpack`_, and `VueJS`_ (`bc_js_filepicker`_)

Other site have used this file to:

- Enable popups for invalid field values right away instead of waiting until the `submit` button is pressed:

  .. code-block:: js

    form = document.getElementById("new_batch_connect_session_context");
    form.addEventListener("change", () => form.reportValidity());

- Mark fields as invalid for site-specific reasons:

  .. code-block:: js

    // example: no GPUs in the CPU partition
    auto_queues_field = document.getElementById("batch_connect_session_context_auto_queues");
    gpus_field = document.getElementById("batch_connect_session_context_gpus");
    function validate_gpu_against_partition() {
      if ((auto_queues_field.value == "cpu") && (parseInt(gpus_field.value) > 0)) {
        gpus_field.setCustomValidity("You cannot use a GPU in the CPU queue!");
      } else {
        gpus_field.setCustomValidity(""); // valid
      }
    }
    gpus_field.addEventListener("change", validate_gpu_against_partition);
    auto_queues_field.addEventListener("change", validate_gpu_against_partition);

.. warning::

    Be aware that client side validation provided by JavaScript is not perfect and any critical values should be validated / sanitized server side in ``script.sh.erb`` or ``submit.yml.erb``.

.. note::

    This file is not required and may be empty or not exist.

.. _bc_js_filepicker: https://github.com/OSC/bc_js_filepicker
.. _jquery: https://jquery.com/
.. _osc ansys javascript: https://github.com/OSC/bc_osc_ansys_workbench/blob/master/form.js
.. _osc matlab javascript: https://github.com/OSC/bc_osc_matlab/blob/master/form.js
.. _vuejs: https://vuejs.org/
.. _webpack: https://webpack.js.org/
