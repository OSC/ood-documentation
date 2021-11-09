.. _glossary:

Glossary
========

   Cluster
     Logical set of physical machines with a resource scheduler that users can submit jobs to.

   Compute-node
     Where the actual compute happens using information passed from a web-node or submitted scripts. Generally these nodes:
    
       * Run as authenticated user.
       * Can use the web-node forms for data to start a job.
       * Can use submitted scripts from the shell or job-composer for resource managers like SLURM, Torque, etc.
       * The Per-User NGINX serves web apps in Ruby and NodeJS and is how users submit jobs and start interactive apps.
  
   Login-node
     Allows you to interact with a compute node live to submit computations and see the results in a REPL fashion with examples like:
  
     * Jupyter
     * Rstudio
     * Ansys

   Web-node
     Refers to the Apache web server front-end:
      
      * Authenticates user.
      * Runs as apache user.
      * Handles authentication and tracking the user session.
      * Tracks the various `fs` paths that it will associate with the compute nodes which it submits requests to using form data.
      * Reverse proxies each user to her PUN via Unix domain sockets.
      * Reverse proxies to interactive apps running on compute nodes (RStudio, Jupyter, VNC desktop) via TCP sockets.
