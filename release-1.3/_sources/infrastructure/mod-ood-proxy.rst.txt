.. _mod-ood-proxy:

mod_ood_proxy
=============

`View on GitHub <https://github.com/OSC/mod_ood_proxy>`__

An Apache HTTP Server module implementing the Open OnDemand proxy API.

To get started you will need at a minimum the following prerequisites:

- `Apache HTTP Server`_ version 2.4 with the following modules:

  - mod_lua_
  - mod_env_
  - mod_proxy_
  - mod_proxy_connect_
  - mod_proxy_wstunnel_
  - your choice of :program:`mod_auth_*`

- The Ruby_ language version 2.2 or newer for installation

Please see :ref:`install-software` on how to install the above requirements.

.. toctree::
   :maxdepth: 2
   :caption: Documentation

   mod-ood-proxy/installation
   mod-ood-proxy/usage

.. _apache http server: https://httpd.apache.org/docs/2.4/
.. _mod_lua: https://httpd.apache.org/docs/2.4/mod/mod_lua.html
.. _mod_env: https://httpd.apache.org/docs/2.4/mod/mod_env.html
.. _mod_proxy: https://httpd.apache.org/docs/2.4/mod/mod_proxy.html
.. _mod_proxy_connect: https://httpd.apache.org/docs/2.4/mod/mod_proxy_connect.html
.. _mod_proxy_wstunnel: https://httpd.apache.org/docs/2.4/mod/mod_proxy_wstunnel.html
.. _ruby: https://www.ruby-lang.org/en/
