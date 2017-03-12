Infrastructure
==============

The components that make up the Open OnDemand **infrastructure** includes a
proxy layer that all traffic passes through using the securely encrypted SSL
protocol on port 443. The `Apache proxy <https://httpd.apache.org/>`_ parses
the URI and dynamically determines where to route the traffic to. In most cases
the traffic will be routed to the per-user `NGINX <https://www.nginx.com/>`_
(PUN) web server.

The PUN is described as an NGINX server instance running as a system-level user
listening on a `Unix domain socket
<https://en.wikipedia.org/wiki/Unix_domain_socket>`_. File and directory
permissions are used to restrict access to this Unix domain socket such that
only the proxy daemon can communicate with the PUN.

.. toctree::
   :maxdepth: 2
   :caption: Components

   infrastructure/ood-portal-generator
   infrastructure/mod-ood-proxy
   infrastructure/ood-auth-map
   infrastructure/nginx-stage
