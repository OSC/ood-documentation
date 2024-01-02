.. _resource-manager-kubernetes:

Kubernetes
==========

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
    batch_connect:
      ssh_allow: false


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

.. note::

   The ``batch_connect.ssh_allow`` is important to disable OnDemand from rendering links to SSH into your
   Kubernetes worker nodes when Batch Connect apps are running.

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

Bootstrapping the Kuberenetes cluster
*************************************

Before anyone can use your Kubernetes cluster from Open OnDemand, you'll need
to create the `open ondemand kubernetes resources`_ on your cluster.

Below is an example of adding the necessary resources:

.. code-block:: sh

  kubectl apply -f https://raw.githubusercontent.com/OSC/ondemand/master/hooks/k8s-bootstrap/ondemand.yaml


Bootstrapping OnDemand web node to communicate with Kubernetes
**************************************************************

The OnDemand web node ``root`` user must be configured
to use the ``ondemand`` service account deployed by the `open ondemand kubernetes resources`_ and
be able to execute ``kubectl`` commands.

First deploy ``kubectl`` to the OnDemand web node.
Replace ``$VERSION`` with the version of the Kubernetes controller, eg. ``1.21.5``.

.. code-block:: sh

  wget -O /usr/local/bin/kubectl https://storage.googleapis.com/kubernetes-release/release/v$VERSION/bin/linux/amd64/kubectl
  chmod +x /usr/local/bin/kubectl


Tokens for Bootstrapping
------------------------

The ``root`` user on the OnDemand web node needs a kubernetes token to bootstrap users.
Specifically to create user namespaces and give the users sufficient privileges in their
namespace.

Service account tokens are not generated automatically since Kubernetes 1.24.  You have two
options here: You can either create a non-expiring token for the service account and save it
as a secret or you can create a crontab entry to refresh the ``root`` users token.  Both are
described here.

.. tip::
  Kubernetes recommends that you use rotating tokens, so we recommend the same.

To do use rotating tokens, you can use the ``kubectl create token`` API to create  a token
and save it in a crontab entry. Here's an example of what you could use to create new tokens
for the ``root`` user.  The tokens last 9 hours, so you can set a crontab entry for every 8 hours
to refresh your tokens before they expire.

.. code-block:: sh

  #!/bin/bash

  set -e

  if command -v kubectl >/dev/null 2>&1;
  then
    CMD_USER=$(whoami)
    if [ "$CMD_USER" == "root" ]; then
      TOKEN=$(kubectl create token ondemand --namespace=ondemand --duration 9h)
      kubectl config set-credentials ondemand@kubernetes --token="$TOKEN"
    else
      >&2 echo "this program needs to run as 'root' and you are $CMD_USER."
      exit 1
    fi
  fi


If you wish to create a non-expiring token, you will need to create the secret through a
``kubectl apply`` command on the yaml below.

Next extract the ``ondemand`` ServiceAccount token.  Here is an example command to extract
the token using an account that has ClusterAdmin privileges:

.. code-block:: yaml

  # token.yml
  apiVersion: v1
  kind: Secret
  type: kubernetes.io/service-account-token
  metadata:
    name: token
    namespace: ondemand
    annotations:
      kubernetes.io/service-account.name: ondemand

.. code-block:: sh

  kubectl apply -f token.yml
  TOKEN=$(kubectl describe serviceaccount ondemand -n ondemand | grep Tokens | awk '{ print $2 }')
  kubectl describe secret $TOKEN -n ondemand | grep "token:"

Below are example commands to bootstrap the kubeconfig for ``root`` user on the OnDemand web node
using the token from above.  Run these commands as ``root`` on the OnDemand web node.

.. code-block:: sh

  kubectl config set-cluster kubernetes --server=https://$CONTROLLER:6443 --certificate-authority=$CACERT
  kubectl config set-credentials ondemand@kubernetes --token=$TOKEN
  kubectl config set-context ondemand@kubernetes --cluster=kubernetes --user=ondemand@kubernetes
  kubectl config use-context ondemand@kubernetes

Replace the following values:

- ``$CONTROLLER`` with the Kubernetes Controller FQDN or IP address
- ``$CACERT`` the path to Kubernetes cluster CA cert
- ``$TOKEN`` the token for ``ondemand`` ServiceAccount

Below is an example of verifying the kubeconfig is valid:

.. code-block:: sh

  kubectl cluster-info

Deploy Hooks to bootstrap users Kubernetes configuration
********************************************************

We ship with `open ondemand provided hooks`_ to bootstrap users when the login
to Open OnDemand. These scripts will create their namespace, a networking policy,
and rolebindings for user and the service accounts in their namespace.

A user ``oakley`` would create the ``oakley`` namespace. If you've configured
to use prefix ``user-``, then the namespace would be ``user-oakley``.

The networking policy ensures that pods cannot communicate inbetween namespaces.

The RoleBindings give user, ``oakley`` in this case, sufficient privileges
to the ``oakley`` namespace.  Refer to the `open ondemand kubernetes resources`_
for details on the roles and privileges created.

You'll need to employ :ref:`PUN pre hooks <ood-portal-generator-pun-pre-hook>`
to bootstrap your users to this cluster.

You'll also have to modify ``/etc/ood/config/hooks.env`` because `open ondemand provided hooks`_
require a ``HOOKENV`` environment variable.

Here's what you'll have to edit in the ``hook.env.example`` file we ship.

.. code-block:: text

  # /etc/ood/config/hook.env

  # required if you changed the items in the cluster.d file
  K8S_USERNAME_PREFIX=""
  NAMESPACE_PREFIX=""

  # required
  NETWORK_POLICY_ALLOW_CIDR="127.0.0.1/32"

  # required if you're using OIDC
  IDP_ISSUER_URL="https://idp.example.com/auth/realms/main/protocol/openid-connect/token"
  CLIENT_ID="changeme"
  CLIENT_SECRET="changeme"

  # required if you're using a secret registry
  IMAGE_PULL_SECRET=""
  REGISTRY_DOCKER_CONFIG_JSON="/some/path/to/docker/config.json"

  # enable if are enforcing walltimes through the job pod reaper
  # see 'Enforcing walltimes' below.
  USE_JOB_POD_REAPER=false

You can refer to `osc's prehook`_ but we'll also provide this example.
As you can see in this pre hook, the username is passed in to the script
which then defines the ``HOOKENV`` and calls two `open ondemand provided hooks`_.

``k8s-bootstrap-ondemand.sh`` boostraps the user in the kubernetes cluster as described
above.

Since we use OIDC at OSC we use ``set-k8s-creds.sh`` to add or update the user in their
``~/.kube/config`` with the relevant OIDC credentials.

.. code-block:: shell

  #!/bin/bash

  for arg in "$@"
  do
    case $arg in
      --user)
      ONDEMAND_USERNAME=$2
      shift
      shift
      ;;
  esac
  done

  if [ "x${ONDEMAND_USERNAME}" = "x" ]; then
    echo "Must specify username"
    exit 1
  fi

  HOOKSDIR="/opt/ood/hooks"
  HOOKENV="/etc/ood/config/hook.env"

  /bin/bash "$HOOKSDIR/k8s-bootstrap/k8s-bootstrap-ondemand.sh" "$ONDEMAND_USERNAME" "$HOOKENV"
  /bin/bash "$HOOKSDIR/k8s-bootstrap/set-k8s-creds.sh" "$ONDEMAND_USERNAME" "$HOOKENV"


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

For OIDC authentication the tokens provided to OnDemand users must be seen as valid for Kubernetes in order for that
token to be used to authenticate with Kubernetes.
First both OnDemand and Kubernetes must be using the same OIDC provider.
In order for the OnDemand token to work with Kubernetes, it's simplest to
configure an :ref:`audience <oidc_k8_audience>` on the OnDemand OIDC client.
An alternative approach would be to update the pre-PUN hooks to perform a :ref:`token exchange <oidc_k8_token_exchange>`.
Another approach would be to use the same OIDC client configuration for OnDemand and Kubernetes.

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

.. _oidc_k8_audience:

OIDC Audience
-------------

The simplest way to have the OnDemand OIDC tokens be valid for Kubernetes is to update the OnDemand
client configuration to include the audience of the Kubernetes client.

Keycloak
^^^^^^^^

In the Keycloak web UI, logged in as the admin user:

#. Navigate to ``Clients`` then choose the OnDemand client.
#. Choose the ``Mappers`` tab and click ``Create``

  #. Fill in a ``Name`` and select ``Audience`` for ``Mapper Type``

  #. For ``Included Client Audience`` choose the Kubernetes client entry

  #. Turn on both ``Add to ID token`` and ``Add to access token``

.. _oidc_k8_token_exchange:

OIDC Token Exchange
-------------------

Keycloak
^^^^^^^^

Refer to the `Keycloak token exchange documentation <https://www.keycloak.org/docs/latest/securing_apps/#_token-exchange>`_

Open OnDemand apps in a Kuberenetes cluster
*******************************************

Kuberenetes is so different from other HPC clusters that the interface we have for
other schedulers didn't quite fit.  So Open OnDemand apps developed for kubernetes
clusters look quite different from other schedulers.  Essentially most things we'll
need are packed into the ``native`` key of the ``submit.yml.erb`` files.

See the :ref:`tutorial for a kubernetes app that behaves like HPC compute <app-development-tutorials-interactive-apps-k8s-like-hpc-jupyter>` as well as
the :ref:`tutorial for a kubernetes app <app-development-tutorials-interactive-apps-k8s-jupyter>`
for more details.


Kyverno Policies
****************

Once Kubernetes is available to OnDemand, it's possible for users to use ``kubectl`` to submit arbirary pods to
Kubernetes. To ensure proper security with Kubernetes a policy engine such as `Kyverno`_ can be used to ensure certain
security standards.

For OnDemand, many of the `Kyverno baseline and restricted sescurity policies`_ will work.  There are also policies that
can be deployed to ensure the UID/GID of user pods match that user's UID/GID on the HPC clusters.
Some `example policies`_ do things such as enforce UID/GID and other security standards for OnDemand.
These policies rely heavily on the fact that OnDemand usage in Kubernetes using a namespace prefix.

The policies enforcing UID/GID and supplemental groups are using data supplied by
the `k8-ldap-configmap`_ tool that generates ConfigMap resources based on LDAP data.
This tool runs as a deployment inside the Kubernetes cluster.

Enforcing Walltimes
*******************

In order to enforce that OnDemand pods are shut down after so much time, it's necessary to deploy a service that can
cleanup pods that have run past their walltime.  Also because OnDemand is bootstrapping
a namespace per user it's useful to cleanup unused namespaces.

The OnDemand pods will have the ``pod.kubernetes.io/lifetime`` annotation set that
is read by `job-pod-reaper`_ that will kill pods that have reached their walltime.
The `job-pod-reaper`_ service runs as a Deployment inside Kubernetes and will kill
any pods based on the lifetime annotation.
Below is an example of Helm values that can be used to configure job-pod-reaper for OnDemand:

.. code-block:: yaml

  reapNamespaces: false
  namespaceLabels: app.kubernetes.io/name=open-ondemand
  objectLabels: app.kubernetes.io/managed-by=open-ondemand

You will need to tell OnDemand you are using `job-pod-reaper`_ and to bootstrap the necessary RoleBinding so that
job-pod-reaper can delete OnDemand pods. Update ``/etc/ood/config/hooks.env`` to include the following configuration:

.. code-block:: sh

  USE_JOB_POD_REAPER="true"

In order to cleanup unused namespaces the `k8-namespace-reaper`_ tool can be used.
This tool will delete a namespace based on several factors:

- The creation timestamp of the namespace
- ``openondemand.org/last-hook-execution`` annotation set by the OnDemand pre-PUN hook
- The last pod to run in that namespace based on Prometheus metrics

Below is an example of Helm values to deploy this tool for OnDemand where the OnDemand namespaces have ``user-`` prefix:

.. code-block:: yaml

  config:
    namespaceLabels: app.kubernetes.io/name=open-ondemand
    namespaceRegexp: user-.+
    namespaceLastUsedAnnotation: openondemand.org/last-hook-execution
    prometheusAddress: http://prometheus.prometheus:9090
    reapAfter: 8h
    lastUsedThreshold: 4h
    interval: 2h

Using a private image registry
******************************

OnDemand's Kubernetes integration can be setup to pull images from a private registry
like `Harbor <https://goharbor.io/>`_.

In order to pull images from a private registry that requires authentication,
OnDemand can be configured to setup `Image Pull Secrets <https://kubernetes.io/docs/tasks/configure-pod-container/pull-image-private-registry/>`_.
The OnDemand web node will need a JSON file setup that includes the username and password of a registry user authorized
to pull images used by OnDemand apps.

.. warning::

  Once the OnDemand user's namespace is given the registry auth secret, it will be readable by the user.
  It's recommended to use a read-only auth token that has limited to access just images used by OnDemand.

In the following example you can set the following values:

- ``$REGISTRY`` the registry address.
- ``$REGISTRY_USER`` the username of the user authorized to pull the images
- ``$REGISTRY_PASSWORD`` the password of the user authorized to pull the images

.. code-block:: sh

  AUTH=$(echo -n "${REGISTRY_USER}:${REGISTRY_PASSWORD}" | base64)
  cat > /etc/ood/config/image-registry.json <<EOF
  {
    "auths": {
      "${REGISTRY}": {
        "auth": "${AUTH}"
      }
    }
  }
  EOF
  chmod 0600 /etc/ood/config/image-registry.json

Once the registry JSON is created you must configure ``/etc/ood/config/hooks.env`` so OnDemand knows how to bootstrap
a user's namespaces with the ability to pull from this registry:

.. code-block:: sh

  IMAGE_PULL_SECRET="private-docker-registry"
  REGISTRY_DOCKER_CONFIG_JSON="/etc/ood/config/image-registry.json"

.. _kubernetes security context: https://kubernetes.io/docs/reference/kubernetes-api/workload-resources/pod-v1/#security-context
.. _open ondemand provided hooks: https://github.com/OSC/ondemand/tree/master/hooks
.. _open ondemand kubernetes resources: https://github.com/OSC/ondemand/blob/master/hooks/k8s-bootstrap/ondemand.yaml
.. _osc's prehook: https://github.com/OSC/osc-ood-config/blob/master/hooks/pre-hook.sh
.. _kyverno: https://kyverno.io
.. _kyverno baseline and restricted sescurity policies: https://github.com/kyverno/kyverno/tree/main/charts/kyverno-policies/templates
.. _example policies: https://github.com/OSC/osc-helm-charts/tree/main/charts/kyverno-policies/templates
.. _k8-ldap-configmap: https://github.com/OSC/k8-ldap-configmap
.. _job-pod-reaper: https://github.com/OSC/job-pod-reaper
.. _k8-namespace-reaper: https://github.com/OSC/k8-namespace-reaper
