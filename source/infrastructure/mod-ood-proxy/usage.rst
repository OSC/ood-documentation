.. _mod-ood-proxy-usage:

Usage
=====

:ref:`mod-ood-proxy` provides a number of handlers listed below that should be
incorporated into the Apache configuration file through the ``LuaHookFixups``
hook. This hook is defined as the *fix anything* phase before the content
handlers are run. This will ensure that any authentication modules are called
before the :ref:`mod-ood-proxy` handlers are loaded.

A minimal Apache configuration file will look like:

.. code-block:: apache

   # Lua configuration
   #
   LuaRoot "/opt/ood/mod_ood_proxy/lib"
   #LogLevel lua_module:info

where ``LuaRoot`` should point to the installation location and ``LogLevel``
can be uncommented if you want a more verbose log.

Also, all configuration for this mod is done through CGI environment variables
specified within your Apache configuration as:

.. code-block:: apache

   # Argument set before LuaHookFixups phase and used by mod_ood_proxy handler
   SetEnv ARG_FOR_LUA "value of argument"

.. toctree::
   :maxdepth: 2
   :caption: Handlers

   handlers/nginx-handler
   handlers/pun-proxy-handler
   handlers/node-proxy-handler
   handlers/analytics-handler
