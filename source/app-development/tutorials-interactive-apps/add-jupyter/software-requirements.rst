.. _app-development-tutorials-interactive-apps-add-jupyter-software-requirements:

Software Requirements
=====================

The Jupyter app requires the following software to be installed on the
**compute** nodes that that batch job is meant to run on, **NOT** the OnDemand
node:

- `Jupyter Notebook`_ 4.2.3+ (earlier versions are untested by may work for
  you)
- `OpenSSL`_ 1.0.1+ (used to hash the Jupyter Notebook server password)

**Optional** (but recommended) software:

- `Lmod`_ 6.0.1+ or any other CLI tool used to load appropriate environments
  within the batch job before launching the Jupyter Notebook Server, e.g.,

  .. code-block:: console

     $ module purge
     $ module load python

.. warning::

   Do **NOT** install the above software on the **OnDemand node**. The above
   software requirements are **ONLY** for the **compute nodes** you intend on
   launching the Jupyter Notebook Server on within batch jobs.

.. _jupyter notebook: http://jupyter.readthedocs.io/en/latest/
.. _openssl: https://www.openssl.org/
.. _lmod: https://www.tacc.utexas.edu/research-development/tacc-projects/lmod
