.. _ood_infrastructure:

Install OnDemand Infrastructure
===============================

OnDemand's core infrastructure is stored in a Github repository located at https://github.com/osc/ondemand, and it is installed to ``/opt/ood``.

  .. code-block:: sh

    cd /opt/ood
    git init
    git remote add origin https://github.com/osc/ondemand
    git pull origin master

.. warning::

    We need to perform the ``git init`` and ``pull`` instead of a ``clone`` because ``/opt/ood`` already exists because it is created by one of the other RPMs that we have installed, and ``git`` will refuse to clone into an existing directory with contents.

This will install the following components:

  - `mod_ood_proxy`_
  - `nginx_stage`_
  - `ood_auth_map`_
  - `ood_portal_generator`_

.. _mod_ood_proxy: /infrastructure/mod-ood-proxy.html
.. _nginx_stage: /infrastructure/nginx_stage.html
.. _ood_auth_map: /infrastructure/ood_auth_map.html
.. _ood_portal_generator: /infrastructure/ood_portal_generator.html

These dependencies are self contained and do not require additional build steps. When installing from source there will some other directories (i.e. 'packaging') but they are not relevant at runtime.