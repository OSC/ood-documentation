.. _overview.rst:

.. note::
	We take community requests and troubleshoot as well on our discourse at https://discourse.osc.edu/

File Explorer
=============

Common Issues
-------------

		When trying to use certain HTML characters your file name will appear incorrectly. 
		An issue like this could be resolved by not using the HTML characters. Below are screenshots of what may happen if you do.

		.. figure:: /images/file-names-bad1.png
		   :align: center

		.. figure:: /images/file-names-bad2.png
		   :align: center




Issues Table
------------

.. list-table:: Issues Table File Explorer
	:header-rows: 1
	:stub-columns: 1

	* - Issue
	  - Github Link
	* - File names with X?HTML are not fully supported.
	  - `Link <FileNames_>`_
	* - Uploading large files is not reliable.
	  - `Link <LargeFile_>`_
	* - Attempting to download forbidden directory fails silently.
	  - `Link <DoloForb_>`_ 
	* - Viewing large files causes problems.
	  - `Link <ViewFiles_>`_
	* - Upload may leave broken file if upload directory is full.
	  - `Link <BrokeFile_>`_
	* - Incorrect link in tree root.
	  - `Link <TreeRoot_>`_
	* - Small windows cause file table to distort.
	  - `Link <BadView_>`_
	* - Dir/File names wrong with HTML ampersand character codes.
	  - `Link <CharCodes_>`_

.. _FileNames: https://github.com/OSC/ood-fileexplorer/pull/199
.. _LargeFile: https://github.com/OSC/ood-fileexplorer/issues/103
.. _DoloForb: https://github.com/OSC/ood-fileexplorer/issues/185
.. _ViewFiles: https://github.com/OSC/ood-fileexplorer/issues/196
.. _BrokeFile: https://github.com/OSC/ood-fileexplorer/issues/187
.. _TreeRoot: https://github.com/OSC/ood-fileexplorer/issues/173
.. _BadView: https://github.com/OSC/ood-fileexplorer/issues/143
.. _CharCodes: https://github.com/OSC/ood-fileexplorer/issues/160

Dashboard
=========

Common Issues
-------------
		
		The **Rebuild App** button fails to work because of the enviormental variable ``HOME`` is set to nothing and the SCL ruby would complain:

.. code-block:: sh

	rebuild_passenger_rails_app: [{"HOME" => "", "RAILS_ENV" => "production"}, "bin/bundle install --path=vendor/bundle && bin/rake assets:clobber && bin/rake assets:precompile && bin/rake tmp:clear && mkdir -p tmp && touch tmp/restart.txt && echo 'Done!'"] 

.. figure:: /images/rebuild-not-reliable.png
    :align: center

.. note::

	The original intention of setting ``HOME`` to nothing was for the ``bundle install`` command that ran ``git``.

Issues Table
------------

.. list-table:: Issues Table Dashboard
	:header-rows: 1
	:stub-columns: 1

	* - Issue
	  - Github Link
	* - Invalid OOD_LOCALES_ROOT causes NoMethodError.
	  - `Link <NoMethod_>`_ 
	* - Processing erb creates performace issues.
	  - `Link <ERBPer_>`_
	* - Batch connect adapter errors do not contain stack trace.
	  - `Link <BatchEr_>`_
	* - iHPC sessions fail silently.
	  -	`Link <iHPC_>`_ 
	* - noVNC does not play well with Safari. This has to do with BasicAuth and Websockets.
	  - `Link <SafarinoVNC_>`_

.. _NoMethod: https://github.com/OSC/ood-dashboard/issues/465
.. _ERBPer: https://github.com/OSC/ood-dashboard/issues/417
.. _BatchEr: https://github.com/OSC/ood-dashboard/issues/397
.. _iHPC: https://github.com/OSC/ood-dashboard/issues/171
.. _SafarinoVNC: https://github.com/OSC/ood-dashboard/issues/177

Shell
=====

Common Issues
-------------

		Unfortunately, **Microsoft Edge** provides us with a few unintended behaviors when trying to use the ctrl-v action. 
		Below are a few screenshots of what may happen.  
				
		.. figure:: /images/issues-shell-cutpaste1.png
		   :align: center

		.. figure:: /images/issues-shell-cutpaste2.png
		   :align: center	

.. warning::
	In some instances Microsoft Edge will reload the browser when trying to paste and may even be unable to reach the page after reload.

Issues Table
------------

.. list-table:: Issues Table Shell
	:header-rows: 1
	:stub-columns: 1

	* - Issue
	  - Github Link
	* - Ctrl-V paste in MS Edge is not reliable and may not work as intended.
	  - `Link <Edge_>`_
	* - Multi-line select does not work in MS Edge.
	  - `Link <EdgeML_>`_ 
	* - Cat a large file and the shell app freezes while chars print.
	  - `Link <CatIssue_>`_
	* - Safari 8 and 9 does not allow the paste function to work.
	  - `Link <Safari_>`_ 

.. _Edge: https://github.com/OSC/ood-shell/issues
.. _EdgeML: https://github.com/OSC/ood-shell/issues/57
.. _CatIssue: https://github.com/OSC/ood-shell/issues/28
.. _Safari: https://github.com/OSC/ood-shell/issues/16
