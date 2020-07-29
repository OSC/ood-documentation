.. _job-composer:

Job Composer App
================

(formerly called "My Jobs")

`View on GitHub <https://github.com/OSC/ondemand/tree/master/apps/myjobs>`__

.. figure:: /images/my-jobs-app.png
   :align: center

   Example of the Job Composer App displaying jobs generated from templates.

This Open OnDemand application provides a web-based utility for creating and
managing batch jobs from template directories. This application is built with
the `Ruby on Rails`_ web application framework.

The Job Composer App attempts to model a simple but common workflow that typical
users of an HPC center use. When users create new batch jobs they will follow
the given workflow:

#. Copy a directory of a previous job, either one of their previous jobs or a
   job from a group member
#. Make minor modifications to the input files
#. Submit this new job

The Job Composer app replicates this through "templates" which are just directories
with common job input files. The user will be able to create their own template
from a job directory they have access to on the file system or they can use one
provided to them from a system-installed location. This system-installed
location is located at::

  /var/www/ood/apps/sys/myjobs/templates

Once a user has chosen a template that will meet their needs, they can create a
job from it. This essentially just copies the template directory and its
contents to a new job directory under the user's home directory::

  ~/ondemand/data/apps/sys/myjobs/projects/default

The user can then modify these input files and then submit the job.

The Job Composer app also provides integrated support for launching the Files App in
the currently chosen job or template, giving the user a web-interface for
modifying the files in the directory. It also provides support for launching
the Shell App in the job directory for direct access to the terminal when
needed.

Usage
-----

This app is deployed on the OnDemand Server under the following path on the
local file system::

  /var/www/ood/apps/sys/myjobs

and can be accessed with the following browser request:

.. http:get:: /pun/sys/myjobs

   Launches the Job Composer App web-based utility.

Templates
~~~~~~~~~

A template is a directory with input files for a job as well as a
``manifest.yml`` file. The manifest contains metadata about the corresponding
job:

.. code-block:: yaml

   # ./manifest.yml
   ---
   name: Example Template
   host: cluster1
   script: my_job.sh
   notes: Notes about the template that describes its function to the user

In the event that a job is created from a template that has no manifest or has
missing metadata, the Job Composer app will assign the following default values:

name
  The template directory name
host
  The first cluster with a valid Resource Manager Server in the OOD cluster
  config
script
  The first ``*.sh`` appearing in the template directory
notes
  The path to this manifest if it existed

How it Works
------------

Requirements needed for the Job Composer App to work on your local HPC network:

- OnDemand Server
- Resource Manager Server (e.g., Torque/PBS Batch Server)
- Shared File System

.. _my-jobs-diagram:
.. figure:: /images/my-jobs-diagram.png
   :align: center

   Diagram detailing how the Job Composer App interacts with the HPC infrastructure.

:numref:`my-jobs-diagram` details how the Job Composer App works on a local HPC
system. The user's PUN running on the OnDemand Server launches the Ruby on
Rails Job Composer app through Passenger_ as the user. The Job Composer app reads from a
database all the previous recorded jobs. It then queries the Resource Manager
Server using either a library call or fork'ing a binary (e.g., ``qstat``) and
parsing the output for the status of all the remaining jobs, followed by
generating a table of information that is displayed to the user.

For the currently selected job it will access the Shared File System to display
information about the contents of the job directory (e.g., input and output
files).

For job submission the Job Composer app will communicate the job submission and its
arguments to the Resource Manager Server again through either a library call or
fork'ing a binary (e.g., ``qsub``) and parsing the output for the job id.

.. _ruby on rails: http://rubyonrails.org/
.. _passenger: https://www.phusionpassenger.com/
