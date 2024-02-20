.. _overview.rst:

OnDemand's Known Issues
=======================

.. note::
    We take community requests and troubleshoot as well on our Discourse at https://discourse.osc.edu/.

.. File explorer

- `File names with XML or HTML break display`_
- `Problems uploading files`_
- `Downloading forbidden directories fails silently`_
- `Viewing large files causes problems`_
- `Incorrect link in tree root`_

.. Dashboard

- `NoMethodError when using a custom translation file`_
- `Dashboard may be slow due to logic in ERB templates`_
- `Batch Connect sessions do not contain much debugging info`_
- `noVNC does not work with Safari and Apache Basic auth`_

.. Shell

- `Multiline select does not work in MS Edge`_
- `High output programs may freeze the shell`_
- `Paste does not work in older versions of Safari`_

.. Other

- `RStudio and Upgrading Singularity 3 to minor version 5`_

File names with XML or HTML break display
-----------------------------------------

Files whose names that contain XML or HTML special characters (``<, >, &``) break the File Explorer's display. While this does not introduce corrupt the file system it does render the application unusable.

    .. raw:: html
        
        <a href='https://github.com/OSC/ood-fileexplorer/issues/198'>OSC/ood-fileexplorer#198</a>

Work arounds: to be able to manipulate files that break the Files app users can use a graphical SFTP client like `Cyberduck`_ or `FileZilla`_ or the command line.


Problems uploading files
------------------------

The File Explorer uses HTTP PUT and the NGINX temporary directory to upload files. For most usage this arrangement is adequate, but large files (which may exceed the capacity of the temp dir), shakey network connections (which may cause a transfer to stop partway through) can result in an unsatisfactory experience.

If the NGINX temporary directory is on a small partition it is possible to overload it when attempting an upload. In the case that an upload is too large to fit in the upload temp directory the application may send the partially uploaded file to the destination without reporting an error.

    .. raw:: html

        <a href='https://github.com/OSC/ood-fileexplorer/issues/187'>OSC/ood-fileexplorer#187</a>

Work arounds: to be able to upload larger files that fail with the Files app users can use a graphical SFTP client like `Cyberduck`_, `Globus Connect Personal`_, or the command line. Admins should check to ensure that the partition containing the upload temp dir (``/var/run/ondemand-nginx``) is adequate.

Downloading forbidden directories fails silently
------------------------------------------------

When a user attempts to download a directory for which they do not have adequate file system permissions the download action will fail without notifying the user of the error.

    .. raw:: html

        <a href='https://github.com/OSC/ood-fileexplorer/issues/185'>OSC/ood-fileexplorer#185</a>

Workarounds: No work arounds are available.

Viewing large files causes problems
-----------------------------------

When attempting to view large files (multi-megabyte) the File Explorer has been observed to cause right click to stop working in FireFox.

    .. raw:: html

        <a href='https://github.com/OSC/ood-fileexplorer/issues/196'>OSC/ood-fileexplorer#196</a>

Work arounds: if graphical desktops are installed, then use the recommended file viewer / editor for the desired file type. If the correct viewer is not known to the user, but is installed on the system it may be discoverable using the command line program ``xdg-open [file-name]``.

Incorrect link in tree root
---------------------------

In the File Explorer attempting to open the tree menu's root link in a new tab causes an error.

    .. raw:: html

        <a href='https://github.com/OSC/ood-fileexplorer/issues/173'>OSC/ood-fileexplorer#173</a>

Workarounds: No work arounds are available at this time.

NoMethodError when using a custom translation file
--------------------------------------------------

When attempting to use a custom translation file if the directory pointed to by the environment variable ``OOD_LOCALES_ROOT`` does not exist then attempting to load the application will cause an unhandled ``NoMethodError`` to be throw in the application controller.

    .. raw:: html

        <a href='https://github.com/OSC/ood-dashboard/issues/465'>OSC/ood-dashboard#465</a>

Workarounds: Admins are encouraged to first test all changes to their OnDemand instances in a test environment before applying changes to production services.

Dashboard may be slow due to logic in ERB templates
---------------------------------------------------

The Dashboard may be slow as a result of how the menu is built if custom Batch Connect applications have complicated logic in their ``form.yml.erb``.

An example where this may occur is if the ERB templates contain commands that query the cluster's status.

    .. raw:: html

        <a href='https://github.com/OSC/ood-dashboard/issues/417'>OSC/ood-dashboard#417</a>

Workarounds: Reducing the amount of logic inside ERBs is the near-term solution. In the longer term the OnDemand team will be re-evaluating how the Dashboard menu is constructed so that this will no longer be an issue.

Batch Connect sessions do not contain much debugging info
---------------------------------------------------------

When troubleshooting a failed Batch Connect job it may be difficult to diagnose certain errors because the adapter error interface is generic and does not contain a stack trace of what has gone wrong.

    .. raw:: html

        <a href='https://github.com/OSC/ood-dashboard/issues/397'>OSC/ood-dashboard#397</a>

Workarounds: no work around is available to the user; admins may find examples of what went wrong in the NGINX logs for the troubled user.

When a Batch Connect session fails inside of the ``script.sh.erb`` section of its execution the session information is removed from the view and no error message is shown to the user.

    .. raw:: html

        <a href='https://github.com/OSC/ood-dashboard/issues/171'>OSC/ood-dashboard#171</a>

Workarounds: Users or support staff may find logs for failed Batch Connect sessions located in the output directory ``$HOME/ondemand/data/(sys|dev|usr)/dashboard/batch_connect/(sys|dev|usr)/$APP_NAME/output/$UUID/output.log``.

noVNC does not work with Safari and Apache Basic auth
-----------------------------------------------------

OnDemand's Cluster and Interactive Apps do not work with Safari when OnDemand is protected using Basic authentication. This is due to a bug in Safari with using websockets through servers protected using "Basic" auth. 

Workarounds: OnDemand can be installed with another authentication mechanism such as Shibboleth or OpenID Connect. If "Basic" auth is required, Mac users can connect with other browsers like Chrome or Firefox.

Multiline select does not work in MS Edge
-----------------------------------------

Multi-line select does not work in Microsoft Edge (pre-Chromium).

    .. raw:: html

        <a href='https://github.com/OSC/ood-shell/issues/57'>OSC/ood-shell#57</a>

Workarounds: Using another web browser such as FireFox or Chrome.

High output programs may freeze the shell
-----------------------------------------

The Shell may freeze when attempting to display a large amount of content. This error was initially reported by a user running Python Spark from the Shell app, and has been duplicated by simply running ``cat`` against hundreds-of-megabyte files.

    .. raw:: html

        <a href='https://github.com/OSC/ood-shell/issues/28'>OSC/ood-shell#28</a>

Workarounds: When attempting to view the contents of a file using the commands ``less``, ``head`` or ``tail`` instead of ``cat`` will prevent this error. When running a program that may rapidly produce megabytes of output using a native SSH terminal may be preferable, either from the user's personal machine, or from within a graphical session on the cluster. Alternatively redirecting application output to a file or files (stdout/stderr) and then using ``less`` or ``tail`` to view those files can also solve this problem.

Paste does not work in older versions of Safari
-----------------------------------------------

Pasting from the system clipboard is not supported in Safari 8 or 9.

.. raw:: html

    <a href='https://github.com/OSC/ood-shell/issues/16'>OSC/ood-shell#16</a>

Workarounds: At the time of writing the current version of Safari is version 12. Users experiencing this error are highly recommended to upgrade their web browser.

RStudio and Upgrading Singularity 3 to minor version 5
------------------------------------------------------

OnDemand RStudio implementations using Singularity may break when upgrading to Singularity version 3.5 or above. There is an undocumented breaking change where ``LD_LIBRARY_PATH`` is no longer exported to the container by default. Instead the container will default to having ``LD_LIBRARY_PATH=/.singularity.d/libs``. 

Workarounds: Explicitly exporting the variable by using ``SINGULARITYENV_LD_LIBRARY_PATH="$LD_LIBRARY_PATH" singularity ...`` appears sufficient to fix the issue.

.. _Cyberduck: https://cyberduck.io
.. _FileZilla: https://filezilla-project.org/
.. _Globus Connect Personal: https://www.globus.org/globus-connect-personal
