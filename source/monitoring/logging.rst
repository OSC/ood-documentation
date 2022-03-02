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

**Apache Logs**

For logs relating to issues about: 

 - Authenticating to the web-node
 - Configuring OnDemand 

Look in either of:

:file:`/var/log/httpd/<hostname>_error.log`

- OnDemand will log to this location for its own configuration errors.

:file:`/var/log/httpd/<hostname>_access.log`

- Where OnDemand will log succsseful logins.

.. warning::

    There are no entries for failed logins.

**NGINX Logs**

For logs relating to issues about:

 - Users trying to connect to a :ref:`login-node <glossary>` from their PUN check:

:file:`/var/log/ondemand-nginx/<user>`

.. note::

    These logs by default have ``root:root`` ownership. It may be beneficial 
    to ``chown`` an appropriate staff group on these files for troubleshooting down the road.

Session Data
------------
Though not logs per-se, these files will provide information around connections between the user's PUN and a 
:ref:`login-node<glossary>`, such as an interactive app like Jupyter.

.. note::

    The files will be *owned by the user* and so admins will need to ensure they are either 
    able to substitue user or escalate to root in order to see these files.

In general the session data or job submission files for apps across the dashboard, such as the Job Composer, Batch Connect, 
or Frame-renderer, all start from the root of:

:file:`~/ondemand/data/sys/`

**Batch Connect**
User session data for batch connect apps can be seen from a *user's* home directory at:

:file:`~/ondemand/data/sys/dashboard/batch_connect/db/<session-file>`

This file is used for the session data presented on the interactive apps page and data 
used to connect to the batch connect app.

.. note::

    There may be more than one file in this directory, and sometimes you will have to look through 
    various files to find the correct session data being used by looking at things like the ``created_at`` 
    field in the file.

**Example**

Suppose a user is having trouble connecting to a Codeserver session they created. 
To see what data is being used by this batch connect app for the connection, look in:

.. code-block:: sh
    
    cat ~/ondemand/data/sys/dashboard/batch_connect/db/<session-file>
This will output a json object which will give the information to debug 
any issues this session is having when connecting, such as ``id``, ``token``, ``cluster_id``, 
and ``job_id``.