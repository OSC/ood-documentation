.. _core_apps:

Install OnDemand Core Applications
==================================

  .. note::

    The OnDemand team is in the process of moving core applications to a monolithic repository which will significantly simplify installation.

OnDemand's core applications are stored in their own Github repositories and should be cloned to ``/var/www/ood/apps/sys/$APP``:

  - `ood-activejobs`_: ``/var/www/ood/apps/sys/activejobs``
  - `ood-dashboard`_: ``/var/www/ood/apps/sys/dashboard``
  - `ood-fileeditor`_: ``/var/www/ood/apps/sys/file-editor``
  - `ood-fileexplorer`_: ``/var/www/ood/apps/sys/files``
  - `ood-myjobs`_ : ``/var/www/ood/apps/sys/myjobs``
  - `ood-shell`_: ``/var/www/ood/apps/sys/shell``

  .. _ood-activejobs: https://github.com/OSC/ood-activejobs/
  .. _ood-dashboard: https://github.com/OSC/ood-dashboard/
  .. _ood-fileeditor: https://github.com/OSC/ood-fileeditor/
  .. _ood-fileexplorer: https://github.com/OSC/ood-fileexplorer/
  .. _ood-myjobs: https://github.com/OSC/ood-myjobs/
  .. _ood-shell: https://github.com/OSC/ood-shell/

Each application has its own dependencies which need to be installed (from either NPM or Ruby Gems) by running the following:

  .. code-block:: sh

    cd /var/www/ood/apps/sys/$APP
    # We have both Node and Rails applications, let's just cover both in a single command
    sudo NODE_ENV=production RAILS_ENV=production scl enable rh-nodejs6 rh-ruby24 rh-git29 -- bin/setup

  .. note::

    For systems without Software Collections the ``scl enable ... --`` portion will be unnecessary so long as the correct versions of NodeJS, Ruby and Git are available at build time.