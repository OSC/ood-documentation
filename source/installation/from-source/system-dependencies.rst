.. _system_dependencies:

Install System Dependencies
===========================

What follows is a list of the various programs and runtimes that are necessary to run OnDemand on the web node.

  .. note::

    Although newer versions of Ruby and NodeJS are available OnDemand applications are built against specific versions of their runtimes and are not safe to blindly upgrade.

.. Pulled from OSC/ondemand-packaging/web/ondemand-runtime/*.spec
.. Pulled from OSC/ondemand/packaing/ondemand.spec
.. Does anything need cjose? which is in OSC/ondemand-packaging

- Apache - Mod_ldap
- Apache - Mod_ssl
- Apache 2.4
- Apache development libs
- centos-release-scl - CentOS/RHEL specific
- cronie
- curl
- epel-release - CentOS/RHEL specific
- file
- Git 2.9
- lsof
- lua
- make
- Nginx 1.14.0
- NodeJS 6
- NodeJS - NPM
- Passenger 5.3.7
- rsync
- Ruby - Bundler
- Ruby - development libraries
- Ruby - Gem
- Ruby - Rake
- Ruby 2.4
- sqlite3
- sqlite3 - development libraries
- sudo
- timeout
- wget
- xmllint