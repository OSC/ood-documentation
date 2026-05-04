.. _advanced-resource-manager-configs:

Advanced Resource Manager Configrations
=======================================

This page details advanced settings for any resource manager
that could be helpful in using Open OnDemand.

Visualization Nodes
-------------------

At OSC we offer ``visualization`` nodes that attach the X11 session
to a GPU so that any rendering can occur on the GPU itself.

We've defined ``vis`` as a `Slurm GRES`_ that jobs can request (i.e.,
some batch connect applications request this `Slurm GRES`_).

We use a `Slurm prolog`_ to do the actual work of attaching the X11
session to the GPU.

Other resource managers may have a similar facility for doing work 
just before the job starts running.

This is an example of that `Slurm prolog`_. 

.. code-block:: bash

  if [[ "$SLURM_LOCALID" == "0" && "$SLURM_JOB_GRES" == *"vis"* ]]; then
    if [ -n "$CUDA_VISIBLE_DEVICES" ]; then
      FIRSTGPU=$(echo $CUDA_VISIBLE_DEVICES | tr ',' "\n" | head -1)
      setsid /usr/bin/X :${FIRSTGPU} -noreset >& /dev/null &
      sleep 2
      if [ -n "$DISPLAY" ]; then
        echo "export OLDDISPLAY=$DISPLAY"
      fi
      echo "export DISPLAY=:$FIRSTGPU"
    fi
  fi


.. _Slurm prolog: https://slurm.schedmd.com/prolog_epilog.html
.. _Slurm GRES: https://slurm.schedmd.com/gres.html
