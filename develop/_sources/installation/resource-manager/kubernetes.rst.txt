.. _resource-manager-kubernetes:

Configure Kuberenetes
=====================

TODO table of contents

A YAML cluster configuration file for a Kubernetes resource manager on an HPC
cluster looks like:

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_k8s_cluster.yml
  ---
  v2:
    metadata:
      title: "My K8s Cluster"
    # you may not want a login section. There may not be a login node
    # for your kuberenetes cluster
    login:
      host: "my_k8s_cluster.my_center.edu"
    job:
      adapter: "kubernetes"
      config_file: "~/.kube/config"
      cluster: "ood-prod"
      context: "ood-prod"
      bin: "/usr/bin/kubectl"
      username_prefix: "prod-"
      namespace_prefix: "user-"
      all_namespaces: false
      auto_supplemental_groups: false
      server:
        endpoint: "https://my_k8s_cluster.my_center.edu"
        cert_authority_file: "/etc/pki/tls/certs/kubernetes-ca.crt"
      auth:
        type: "oidc"
      mounts: []


adapter
  This is set to ``kubernetes``.
config_file
  The KUBECONFIG file. *Optional*. Defaults to ~/.kube/config. Sites can also
  set the KUBECONFIG environment varaible, but this configuration has precedence.
cluster
  The cluster name. Saved to and referenced from your KUBECONFIG.
context
  The context to use when issuing kubectl commands. *Optional*. Defaults to cluster
  when using OIDC authentication. Saved to and referenced from your KUBECONFIG.
username_prefix
  The prefix to your users in your KUBECONFIG. Use this prefix to differentiate between
  different clusters (like test and production).
namespace_prefix
  The prefix to your namespace. Use this prefix if you have assertions on what namespaces
  are available. I.e., a Kyverno policy that ensures all namespaces are ``user-\w+``.
all_namespaces
  A boolean to determine if the user will query for pods in other namespaces.  When false
  users will only query in their namespace. If true they will query and display pods from
  all namespaces.
auto_supplemental_groups:
  Automatically populate a container's ``securityContext.supplementalGroups`` with the users
  supplemental groups.
server
  The kubernetes server to communicate with.  This field is a map with ``endpoint`` and
  ``cert_authority_file`` keys.
auth:
  See the notes on `Authentication`_ below.
mounts:
  Site wide mount points for all kubernetes jobs. See the 
  :ref:`documentation on kubernetes mounts <kubernetes-mounts>` for more details.

Per User Kubernetes
*******************

To get kubernetes to act like a Per User resource there are some conventions
we put in place. Users only schedule pods in their own namespaces
and they always run those pods as themselves.

At most users could be allow to read pods from other namespaces (have sufficient
privileges to run ``kubectl get pods --all-namespaces``), but this is not required.
Being able to view pods in other namespaces is only applicable to a feature like
viewing active jobs and seeing pods from other namespaces in that view.

Second is that we specify the `Kubernetes security context`_ such that pods have
the same UID and GID as the actual user.

Open OnDemand will always use the users UID and GID as the runAsUser and runAsGroup.
fsGroup is always the same as runAsGroup. runAsNonRoot is always set to true.
supplementalGroups are empty by default. One can automatically populate them with a
cluster configuration above or specify them for each app individually.

You should have policies in place to enforce these.

Bootstrapping an Open OnDemand Kuberenetes cluster
**************************************************

Before anyone can use your Kubernetes cluster from Open OnDemand, you'll need
to create the `open ondemand kubernetes resources`_ on your cluster.

We ship with `open ondemand provided hooks`_ to bootstrap users when the login
to Open OnDemand. These scripts will create their namespace, a networking policy,
and rolebindings for user and the service accounts in their namespace.

A user ``oakley`` would create the ``oakley`` namespace. If you've configured
to use prefix ``user-``, then the namespace would be ``user-oakley``.

The networking policy ensures that pods cannot communicate inbetween namespaces.

The RoleBindings give user, ``oakley`` in this case, sufficient privileges
to the ``oakley`` namespace.  Refer to the `open ondemand kubernetes resources`_
for details on the roles and privileges created.

Authentication
**************

Here are the current configurations you can list for different types of
authentication.

Managed Authentication
----------------------

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_k8s_cluster.yml
  ---
  v2:
    job:
      # ...
      auth:
        type: 'managed'

This is the simplest case and is the default. The authentication
is managed outside of Open OnDemand. We will not ``set-context``
or ``set-cluster``.

We will pass ``--context`` to kubectl commands if you have it configured
in the cluster config (above). Otherwise, it's assumed that the current context
is set out of bounds.

OIDC Authentication
-------------------

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_k8s_cluster.yml
  ---
  v2:
    job:
      # ...
      auth:
        type: 'odic'

This uses the OIDC credentails that you've logged in with.  When
the dashboard starts up it will ``set-context`` and ``set-cluster``
to what you've configured.

We will pass ``--context`` to kubectl commands. This defaults to
the cluster but can be something different if you configure it so.

GKE Authentication
------------------

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_k8s_cluster.yml
  ---
  v2:
    job:
      # ...
      auth:
        type: 'gke'
        svc_acct_file: '~/.gke/my-service-account-file'

It's expected that you have a service account that can then manipulate
the cluster you're interacting with. Every user should have a cooresponding
service account to interact with GKE. 

When the dasbhoard starts up, we use ``gcloud`` to configure your KUBECONFIG.

Google Cloud's Goolge Kubernetes Engine (GKE) needs some more documentation
on what privileges this serivce account is setup with and how one may bootstrap
it.

Open OnDemand apps in a Kuberenetes cluster
*******************************************

Kuberenetes is so different from other HPC clusters that the interface we have for
other schedulers didn't quite fit.  So Open OnDemand apps developed for kubernetes
clusters look quite different from other schedulers.  Essentially most things we'll
need are packed into the ``native`` key of the ``submit.yml.erb`` files.

See the :ref:`tutorial for a kubernetes app <app-development-tutorials-interactive-apps-k8s-jupyter>`
for more details.


Kyverno Policies
****************

Enforcing Walltimes
*******************

TODO docs about the job-pod-reaper and k8-namespace-reaper

Image pull secrets
******************

OIDC Audicence
**************


.. _kubernetes security context: https://kubernetes.io/docs/reference/kubernetes-api/workload-resources/pod-v1/#security-context
.. _open ondemand provided hooks: https://github.com/OSC/ondemand/tree/master/hooks
.. _open ondemand kubernetes resources: https://github.com/OSC/ondemand/blob/master/hooks/k8s-bootstrap/ondemand.yaml