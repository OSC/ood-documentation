.. _resource-manager-coder:

Coder
==========


Coder

The Coder adapter facilitates communication with Coder API, an open-source project that allows users to create and control
developer workspaces on their preferred clouds and servers. This allows launching virtual machines from Open OnDemand, with OpenStack as an example.

A YAML cluster configuration file for a Coder is defined by:

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_k8s_cluster.yml
  ---
  v2:
  metadata:
      title: "Coder"
  job:
      adapter: "coder"
      host: "your host"
      cluster: "my_coder_instance"
      token: "your Coder API token"  


``adapter``
  This is set to ``coder``.
``cluster``
  The cluster name. 
``token``
  The API token retrieved from Coder UI under ``/settings/tokens`` or by calling ``coder tokens create``.
``host``
  Path to your Coder instance. For testing, you can use default tunnel.


.. warning::

  This adapter doesn't support OIDC yet and instead uses Coder API token. Coder has native support for OIDC, but it needs to be investigated.