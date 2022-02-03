.. _dynamic-bc-apps:

Batch connect apps with dynamic behavior
========================================

.. note::
  This feature was added in version 2.0.

Prior to version 2.0, sites would have to make their own custom `form.js` to
add dynamic behavior for batch connect forms.  While sites can still have their
own custom javascript, 2.0 added out of the box support for common use cases based
on configuration.

.. warning::
  Form fields use underscores (``_``) as a word separator and these directives use hyphens (``-``).
  So when referencing the element ``node_type`` you will need to reference it as ``node-type``.

To enable any of the dynamic batch connect capabilities described in this page,
set the ``OOD_BC_DYNAMIC_JS`` environment variable in the dashboard's env file.

.. code:: sh

  # /etc/ood/config/apps/dashboard/env
  OOD_BC_DYNAMIC_JS=true

Your own ``form.js``
********************

If we don't support what you need for your application to be dynamic, then you can add your
own ``form.js`` in the root of the project. It is free form javascript, so most anything is
allowed. `jQuery`_ is available to interact with elements.


Hiding select options
*********************

The ``data-option-for`` directive allows you to hide select choices of an element based on
the current value of a different select element.

Let's use this example: We have two clusters, ``oakley`` and ``ruby``. The ``oakley`` cluster
has GPUs but ``ruby`` does not.

So, we'd like to give the choice of ``node_type`` to show ``gpu`` when the user has
the ``oakley`` cluster selected, but not when ``ruby`` is selected.

Everything is shown by default so we need to configure the app such that
``gpu`` option is hidden when the ``ruby`` cluster is chosen.

Open OnDemand provides ``data-option-for`` directive for this use case.

With this one configuration we're telling the OnDemand system that ``gpu`` is not an option
for the ``ruby`` cluster.  It will then hide it every time the cluster ``ruby`` is chosen.

.. code-block:: yaml
  :emphasize-lines: 8

  attributes:
    node_type:
      widget: select
      options:
        - 'standard'
        - [ 
            'gpu', 'gpu',
            data-option-for-cluster-ruby: false
          ]

.. tip::
  This example shows toggling options based on the cluster, but this feature
  generically support any field and value.


Hiding entire elements
**********************

The ``data-hide`` directive allows you to hide another element based on
the current value of a select element.

Let's continue examples involving GPUs. We'd like to provide users
with options for `CUDA`_ versions.

But using Nvidia's `CUDA`_ libraries only makes sense when the user is requesting GPUs.
So, we want to hide the ``cuda_version`` element when a users chooses standard ``node_type``.

Here's the example YAML for this app with two select widgets.  This
instructs the webpage to hide the ``cuda_version`` when the ``standard`` 
``node_type`` is selected.

.. code-block:: yaml
  :emphasize-lines: 7

  attributes:
    node_type:
      widget: select
      options:
        - [ 
            'standard', 'standard' 
            data-hide-cuda-version: true
          ]
        - 'gpu'


Dynamic Min and Maxes
*********************

The ``data-min`` and ``data-max`` directives allow you to set the minimum and
maximum values of another element based on the current value of a select element.

Sites have node types of all shapes and sizes. Some sites even have
heterogenous clusters where there are different node types in the cluster.

This feature allows for setting the minimum and maximum values for input
fields like the number of cores to request.

Let's see an example. We have `standard`` nodes in both clusters, but they're
different sizes. In the ``oakley`` cluster nodes have a total 28 cores and in the
``ruby`` cluster they have 40.

In this example ``data-max-num-cores-for-cluster-oakley`` is attached to the standard
node type. This config is saying, when the ``node_type`` is ``standard`` 
and the ``cluster`` is ``oakley`` set maximum ``num_cores`` to 28.

.. code-block:: yaml

  attributes:
    node_type:
      widget: select
      options:
        - [ 
            'standard', 'standard',
            data-max-num-cores-for-cluster-oakley: 28,
            data-max-num-cores-for-cluster-ruby: 40,
          ]
        - [
            'gpu', 'gpu',
            data-max-num-cores: 1,
            data-min-num-cores: 1,
          ]

This example also illustrates a simpler variant of this directive attached to ``gpu``. 
This configuration doesn't have a for clause, so it will set the minimum and maximum
values for ``num_cores`` when ``gpu`` is selected, regardless of which cluster is selected.


Setting values based on other elements
**************************************

The ``data-set`` directive allows you to set a value on a different element based
on the current value of a select element.

Let's use charge-back accounts as an example.  Let's imagine we want to set the charge-back
account automatically based on the selection of node type.

In this example, when ``standard`` ``node_type`` is chosen, the ``charge_account`` element
will be automatically set to ``standard-charge-code``.

.. code-block:: yaml

  form:
    - charge_account
    - node_type
  attributes:
    node_type:
      widget: select
      options:
        - [ 
            'standard', 'standard',
            data-set-charge-account: 'standard-charge-code'
          ]
        - [
            'gpu', 'gpu',
            data-set-charge-account: 'gpu-charge-code',
          ]


.. _CUDA: https://developer.nvidia.com/cuda-toolkit
.. _jQuery: https://jquery.com/
