.. _glossary:

Glossary
========

   Cluster
     Logical set of physical machines with a resource scheduler that users can submit jobs to.

   Compute-node
     The machine where a submitted job runs using information passed from a web-node acting as a proxy.

   Login-node
     Similar to the compute-node but used to interact with the file-system or a container using something like ssh.

   Web-node
     Refers to the front end Apache web-server machine itself which runs Apache and the user's PUN.

   PUN
    The Per User Nginx. An Nginx instance running on the Web-node as the user.
