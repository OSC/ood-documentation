.. _app-development-add-jupyter-software-requirements:

Software Requirements
=====================

The Jupyter app requires the following software to be installed on the
**compute** nodes that that batch job is meant to run on, **NOT** the OnDemand
node:

- `Jupyter Notebook`_ 4.2.3+ (earlier versions are untested by may work for
  you)
- `OpenSSL`_ 1.0.1+ (used to hash the Jupyter Notebook server password)

**Optional** (but recommended) software:

- `Anaconda`_ 4.3.13+ and its `Jupyter Notebook extensions`_ that allow the
  users to define custom environment-based kernels from within the Jupyter
  notebook dashboard
- `Lmod`_ 6.0.1+ or any other CLI tool used to load appropriate environments
  within the batch job before launching the Jupyter Notebook Server, e.g.,

  .. code-block:: shell

     module restore
     module load python/3

.. warning::

   Do **NOT** install the above software on the **OnDemand node**. The above
   software requirements are **ONLY** for the **compute nodes** you intend on
   launching the Jupyter Notebook Server on within batch jobs.

.. _jupyter notebook: http://jupyter.readthedocs.io/en/latest/
.. _openssl: https://www.openssl.org/
.. _anaconda: https://www.continuum.io/anaconda-overview
.. _jupyter notebook extensions: https://docs.continuum.io/anaconda/user-guide/tasks/use-jupyter-notebook-extensions
.. _lmod: https://www.tacc.utexas.edu/research-development/tacc-projects/lmod
