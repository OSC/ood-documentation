.. _project_manager:

Project Manager
===============

Overview
--------


Setup
-----

For individual projects, there is no setup required. Anybody with the permissions 
to submit jobs to your scheduler will also be able to use all of the launcher and
workflow tools of the Project Manager after updating to v4.1. In order for users 
to collaborate together they will need a properly configured shared directory,
meeting :ref:`these minimum permissions <project_manager_shared_project_root>` 


.. _project_manager_collaboration:

Collaboration
-------------
Collaborative projects need properly configured directories to exist in, which may 
vary on the types of collaboration you would like to enable. Like other actions in 
Open OnDemand, it will operate as the logged in user and never exceed the UNIX 
permissions of the directories and files it operates on. This means there are several
different approaches you may want to take depending on your file system's account and 
permission management approach.

.. _project_manager_shared_project_root:

Shared Project Root
-------------------

The project manager provides the ``OOD_SHARED_PROJECT_PATH`` environment variable to 
help potential collaborators discover potential projects to import. While this is 
not necessary for collaboration, it is a recommended step to make it easier to locate.
The ``OOD_SHARED_PROJECT_PATH`` is a list of base locations for shared projects, allowing
you to add as many locations as you need for different types of users and projects. 
The Project Manager will only allow users to import projects from locations that they
have access to, so there is no danger in adding paths that are not accessible to certain 
users.

Because many centers use group-based permission schemes, the Project Manager expects that
each directory in ``OOD_SHARED_PROJECT_PATH`` has a set of subdirectories with finer permissions,
and will only look for projects in these subdirectories. 

For example, a center may have a shared project folder ``/fs/shared/projects``, and a series of subdirectories
``/fs/shared/projects/developers``, ``/fs/shared/projects/staff``, ``/fs/shared/projects/students``.


In this example, they would set ``OOD_SHARED_PROJECT_PATH=/fs/shared/projects``, allowing developers
to create collaborative projects like ``/fs/shared/projects/developers/project1``, which are then 
easily accessible to others in the ``developers`` group (likewise for ``staff`` and ``students``).

While the Project Manager automates the permissions settings on project-specific folders, these can
never exceed the permissions of the ``SHARED_PROJECT_ROOT`` or any group-level subdirectory, so it 
is important to ensure that your directory structure meets these minimum requirements.

#. Any directory in ``OOD_SHARED_PROJECT_PATH`` and above must have at minimum ``r-x`` permissions
   for all potential collaborators.

#. Any group directory directly below ``OOD_SHARED_PROJECT_PATH`` should have ``rwx`` permissions 
   for the group
