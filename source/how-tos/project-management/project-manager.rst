.. _project_manager:

Project Manager
===============

.. contents:: Table of Contents
  :depth: 2
  :local:

Overview
--------

A new feature in version 4.1, the Project Manager provides a suite of tools to leverage
the Open OnDemand features from batch connect apps for each user's own personal scripts, 
track and organize their job history, assemble individual jobs into large-scale workflows,
and easily share and collaborate on these projects with their team.

The basic element of a project is the **launcher**, which is a paired form and script
that can submit jobs to the scheduler. By selecting different options in the form, a user
can change both scheduler parameters (account, resources, etc.), or change the behavior 
of the script itself through environment variables.

All of the scripts, input data, and output data for a project's launchers are stored in the 
**project directory**. This directory can be freely organized according to individual
needs, allowing users to customize for anything from large one-time jobs to long-term
projects with jobs that are repeated many times.

**Workflows** allow users to connect their launchers together with dependency relationships,
enabling them to build self-contained systems that can be run with a single click. These
systems can be as simple or intricate as needed, and are easily assembled through an 
intuitive graphical interface.

The single most important theme of all these features is **flexibility**. As the examples 
demonstrate, there is no one way to structure scripts, organize directories, or
manage complexity within a project. The Project Manager is designed to give users an 
efficient and intuitive way to leverage the most powerful features of Open OnDemand in 
whatever way works best for them and their needs.

Setup
-----

For individual projects, there is no setup required. Anybody with the permissions 
to submit jobs to your scheduler will also be able to use all of the launcher and
workflow tools of the Project Manager after updating to v4.1. In order for users 
to collaborate together they will need a properly configured shared directory,
meeting the minimum permissions described below.


.. _project_manager_collaboration:

Collaboration
.............

Collaborative projects require properly configured directories to exist in, which may 
vary on the types of collaboration you would like to enable. Like other actions in 
Open OnDemand, it will operate as the logged in user and never exceed the UNIX 
permissions of the directories and files it operates on. This means there are several
different approaches you may want to take depending on your file system's account and 
permission management approach.

.. _project_manager_shared_project_root:

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

Templates
.........

For specific applications, it can be helpful to create a project with basic scripts, launchers, 
and workflows customized to that application. For this use case, administrators can copy any
valid project directory to the ``OOD_PROJECT_TEMPLATE_DIR`` directory, which defaults to 
``/etc/ood/config/apps/dashboard/projects``, or ``OOD_APP_CONFIG_ROOT/projects``, if 
``OOD_APP_CONFIG_ROOT`` is defined in your environment. 

Note that unlike ``OOD_APP_CONFIG_ROOT``, the template directory can also be set within profiles 
to manage which templates a user can select by setting ``project_template_dir`` in the 
:ref:`ondemand-d-ymls`. This allows you to organize your templates into directories for each 
profile, in addition to limiting template visibility by restricting read permissions on the 
individual template directories.

.. _launcher_default_items:

Launchers
.........

All launchers are required to have a ``cluster`` and a ``script`` selection in their form by
default. These fields cannot be removed by editing the launcher, as any launcher without these
fields will be rejected by the scheduler. While these are sufficient for the general case,
if your center requires additional parameters, these can be supplied with the ``launcher_default_items``
key in your :ref:`ondemand-d-ymls`. 

For example, OSC does not allow jobs to be submitted without the ``account`` field. To prevent
support tickets from users attempting to run launchers without this field, we add the following
line to ``/etc/ood/config/ondemand.d/ondemand.yml``

.. code-block:: yaml

   launcher_default_items: [ auto_accounts ]

Which ensures that all new launchers begin with ``cluster``, ``script``, and ``account`` fields. 

This can be used to add any :ref:`predefined attribute <app-development-interactive-form-predefined-attributes>`,
:ref:`automatic predefined attribute <auto-bc-form-options>`, or :ref:`global attribute <global_bc_form_items>`
and unlike ``cluster`` and ``script``, these additional default fields _can_ be removed by the user. 

Note that if you have predefined attributes or custom global attributes that are not present as options
in the launcher editor, adding them as default items is the only way to use them in launcher forms.
