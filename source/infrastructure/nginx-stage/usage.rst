Usage
=====

The :program:`nginx_stage` is meant to be run as a privileged process so that
it can fork and kill processes owned by other users, as well as read and write
to ``root`` owned files and directories. It is therefore recommended to run it
under a :program:`sudo` environment.

.. note::

   All options to :program:`nginx_stage` can be specified as URL-encoded
   strings to avoid having to escape special characters in the shell.

At any point you can display a quick reference of the capabilities offered by
:program:`nginx_stage` with:

.. code-block:: sh

   nginx_stage [COMMAND] --help

.. toctree::
   :maxdepth: 2
   :caption: Commands

   commands/pun
   commands/app
   commands/app-reset
   commands/app-list
   commands/app-clean
   commands/nginx
