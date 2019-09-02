.. _overview.rst:

OnDemand's Known Issues
=======================

.. note::
    We take community requests and troubleshoot as well on our Discourse at https://discourse.osc.edu/.

.. File explorer

- `File names with XML or HTML break display`_
- `Uploading large files is not reliable`_
- `Downloading forbidden directories fails silently`_
- `Viewing large files causes problems`_
- `File upload may leave an incomplete file`_
- `Incorrect link in tree root`_

.. Dashboard

- `Rebuild app action in developer view may fail`_
- `NoMethodError when using a custom translation file`_
- `Dashboard may be slow due to logic in ERB templates`_
- `Batch Connect adapter errors do not contain stack trace`_
- `Batch Connect sessions may fail silently`_
- `noVNC does not work with Safari and Apache BasicAuth`_

.. Shell

- `Multiline select does not work in MS Edge`_
- `High output programs may freeze the shell`_
- `Paste does not work in older versions of Safari`_

File names with XML or HTML break display
-----------------------------------------

Files whose names that contain XML or HTML special characters (``<, >, &``) break the File Explorer's display. While this does not introduce corrupt the file system it does render the application unusable.

.. raw:: html
    
    <a href='https://github.com/OSC/ood-fileexplorer/issues/198'>OSC/ood-fileexplorer#198</a>


Uploading large files is not reliable
-------------------------------------

The File Explorer uses HTTP PUT and the NGINX temporary directory to upload files. For most usage this arrangement is adequate, but large files (which may exceed the capacity of the temp dir), shakey network connections (which may cause a transfer to stop partway through) can result in an unsatisfactory experience.

Downloading forbidden directories fails silently
------------------------------------------------

When a user attempts to download a directory for which they do not have adequate file system permissions the download action will fail without notifying the user of the error.

.. raw:: html

    <a href='https://github.com/OSC/ood-fileexplorer/issues/185'>OSC/ood-fileexplorer#185</a>

Viewing large files causes problems
-----------------------------------

When attempting to view large files (multi-megabyte) the File Explorer has been observed to cause right click to stop working in FireFox.

.. raw:: html

    <a href='https://github.com/OSC/ood-fileexplorer/issues/196'>OSC/ood-fileexplorer#196</a>

File upload may leave an incomplete file
----------------------------------------

If the NGINX temporary directory is on a small partition it is possible to overload it when attempting an upload. In the case that an upload is too large to fit in the upload temp directory the application may send the partially uploaded file to the destination without reporting an error.

.. raw:: html

    <a href='https://github.com/OSC/ood-fileexplorer/issues/187'>OSC/ood-fileexplorer#187</a>

Incorrect link in tree root
---------------------------

In the File Explorer attempting to open the tree menu's root link in a new tab causes an error.

.. raw:: html

    <a href='https://github.com/OSC/ood-fileexplorer/issues/173'>OSC/ood-fileexplorer#173</a>

Rebuild app action in developer view may fail
---------------------------------------------

???

NoMethodError when using a custom translation file
--------------------------------------------------

When attempting to use a custom translation file if the directory pointed to by the environment variable ``OOD_LOCALES_ROOT`` does not exist then attempting to load the application will cause an unhandled ``NoMethodError`` to be throw in the application controller.

.. raw:: html

    <a href='https://github.com/OSC/ood-dashboard/issues/465'>OSC/ood-dashboard#465</a>

Dashboard may be slow due to logic in ERB templates
---------------------------------------------------

The Dashboard may be slow as a result of how the menu is built if custom Batch Connect applications have complicated logic in their ``form.yml.erb``.

An example where this may occur is if the ERB templates contain commands that query the cluster's status.

.. raw:: html

    <a href='https://github.com/OSC/ood-dashboard/issues/417'>OSC/ood-dashboard#417</a>

Batch Connect adapter errors do not contain stack trace
-------------------------------------------------------

When troubleshooting a failed Batch Connect job it may be difficult to diagnose certain errors because the adapter error interface is generic and does not contain a stack trace of what has gone wrong.

.. raw:: html

    <a href='https://github.com/OSC/ood-dashboard/issues/397'>OSC/ood-dashboard#397</a>

Batch Connect sessions may fail silently
----------------------------------------

When a Batch Connect session fails inside of the ``script.sh.erb`` section of its execution the session information is removed from the view and no error message is shown to the user.

.. raw:: html

    <a href='https://github.com/OSC/ood-dashboard/issues/171'>OSC/ood-dashboard#171</a>


noVNC does not work with Safari and Apache BasicAuth
----------------------------------------------------

As currently configured, the Cluster and Interactive Apps of Open OnDemand do not work with Safari. This is due to a bug in Safari with using websockets through servers protected using "Basic" auth. Open OnDemand can be installed with another authentication mechanism such as Shibboleth or OpenID Connect. If "Basic" auth is required, Mac users can connect with other browsers like Chrome or Firefox.

Multiline select does not work in MS Edge
-----------------------------------------

Multi-line select does not work in Microsoft Edge (pre-Chromium).

.. raw:: html

    <a href='https://github.com/OSC/ood-shell/issues/57'>OSC/ood-shell#57</a>

High output programs may freeze the shell
-----------------------------------------

The shell may freeze when attempting to display a large amount of content. This error was initially reported by a user running Python Spark, and has been duplicated by simply running ``cat`` against hundreds-of-megabyte files.

.. raw:: html

    <a href='https://github.com/OSC/ood-shell/issues/28'>OSC/ood-shell#28</a>

Paste does not work in older versions of Safari
-----------------------------------------------

Pasting from the system clipboard is not supported in Safari 8 or 9.

.. raw:: html

    <a href='https://github.com/OSC/ood-shell/issues/16'>OSC/ood-shell#16</a>
