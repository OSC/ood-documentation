.. _logging:

Logging
=======

This page provides an overview of the locations Open OnDemand writes logs and useful session data and 
provides context around these locations.

In general administrators will want to note whether they need to see:

- System type logs for authentication to the :ref:`web-node <glossary>` itself or OOD's own configuration.
- Session data for things like connecting to interactive apps (Jupyter, Rstudio, Codeserver, etc.) from 
  the user's PUN, which is already running on the web-node.

System Logs
-----------

These logs will provide information around authentication and internal Open OnDemand errors. They are very useful 
when initially installing and configuring Open OnDemand.

.. _apache-logs:

**Apache Logs**

For logs relating to issues about: 

 - Authenticating to the web-node
 - Configuring OnDemand 

There are two locations to check depending on what information is needed:

:file:`/var/log/httpd/<hostname>_error.log`

- OnDemand will log to this location for its own configuration errors.

:file:`/var/log/httpd/<hostname>_access.log`

- Where OnDemand will log succsseful logins.

.. warning::

    There are no entries for failed logins.

**NGINX Logs**

The NGINX logs are the output of the user :ref:`PUN <glossary>`. These logs will capture things relevant 
to a *particular user* such as:

- Debuggin issues related to job submissions for a user. For example, commands being issued to the scheduler 
  (``sbatch``, ``qsub``, etc) can be seen here by searching for ``execve``.
- Issues related to PUNs crashing and/or pages not rendering correctly.

These logs are located at:

:file:`/var/log/ondemand-nginx/<user>`

.. note::

    These logs by default have ``root:root`` ownership. It may be beneficial 
    to ``chown`` an appropriate staff group on these files for troubleshooting down the road.

Session Data
------------
These files will provide information around connections between the user's PUN and a 
:ref:`compute-node <glossary>`. 

These logs provide *information around connections* and are also *the working directory of the job and location 
of* ``stderr`` *and* ``stdout`` for a job (typically to ``output.log``). Other apps will also output 
information they may need there as well for connections and errors.


.. note::

    The files will be *owned by the user* and so admins will need to ensure they are either 
    able to substitue user or escalate to root in order to see these files.

In general the session data or job submission files for apps across the dashboard, such as the Job Composer, 
Batch Connect, or Frame-renderer, all start from the root of:

:file:`~/ondemand/data/sys/`

.. _interactive-app-logs:

**Interactive Apps**

User session data for batch connect apps can be seen from a *user's* home directory at:

:file:`~/ondemand/data/sys/dashboard/batch_connect/sys/<app>/output/<session id>/output.log`

This file is used for the session data presented on the interactive apps page and data 
used to connect to the batch connect app.

.. note::

    There may be more than one file in the ``<session id>`` directory, but in the Interactive Apps 
    page you can match the Session ID you see there to the directory with the desired ``output.log`` to 
    debug.

One important thing to note is if trying to launch a Jupyter or Rstudio session and encountering failures, the 
``output.log`` would show you things like what modules are being loaded and what kernels are available.

**Example**

Suppose a user is having trouble connecting to a Codeserver session they created. 
To see what data is being used by this batch connect app for the connection, look in:

.. code-block:: sh
    
    cat ~/ondemand/data/sys/dashboard/batch_connect/sys/<app>/output/<session id>/output.log
    
This should result in output that will give the logging information around what happened as this session 
was started to include ports, address, app version, and the token used for the connection. 

You would also see any ``ERROR`` and ``WARN`` messages as well which will likely be beneficial to debug failed 
connections or launches.
