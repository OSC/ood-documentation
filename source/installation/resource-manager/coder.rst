.. _resource-manager-coder:

Coder
==========

The Coder adapter enables launching virtual machines from Open OnDemand using Coder as a middleware solution. Coder is an open-source platform that allows users to create and manage developer workspaces by executing Terraform/OpenTofu code, serving as a bridge between Open OnDemand and cloud providers. Currently, OpenStack is the supported cloud provider.

A YAML cluster configuration file for a Coder is defined by:

.. code-block:: yaml

  # /etc/ood/config/clusters.d/my_coder.yml
  ---
  v2:
    metadata:
      title: "VMs from OOD"
    job:
      adapter: "coder"
      host: "https://my.coder.deployment.com"
      cluster: "my_coder"
      token: "my_coder_token"
      auth: 
        cloud: "openstack"
        url: "https://identity.openstack.my_instance.com/v3"
        region: "RegionOne"
      service_user: "service"
      credential_deletion_max_attempts: 5
      credential_deletion_timeout_interval: 10
    batch_connect:
      ssh_allow: false

``adapter``
  This is set to ``coder``.
``cluster``
  The cluster name. 
``token``
  The API token retrieved from Coder UI under ``/settings/tokens`` or by calling ``coder tokens create``.
``host``
  Path to your Coder instance. For testing, you can use default tunnel.
``auth``
  Defines the Coder authentication method. Currently only OpenStack is supported.
``service_user``
  Service user on your Coder instance. All workspaces are created in this user's namespace.  
``credential_deletion_max_attempts``
  Number of attempts to delete credentials after the VM is destroyed. Default is 5.
``credential_deletion_timeout_interval``
  Time in seconds between attempts to delete credentials after the VM is destroyed. Default is 10s.

Authentication (OpenStack)
--------------------------

Similar to Kubernetes, the Coder adapter relies on hooks to handle authentication. Currently, only OpenStack application credentials are supported. In this case, the hook is responsible for issuing an OpenStack token and then storing it in the user's home directory as a JSON file. This is later used by the adapter to create application credentials. These credentials are then destroyed when the instance is terminated. 
The mechanism relies on OIDC token exchange and the ability of the access token to create unrestricted application credentials. Consult with your OIDC expert regarding this requirement. 

openstack_hook.sh needs to be sourced from the main hook.

.. code-block:: bash
  
  source /etc/ood/config/openstack_hook.sh


OpenStack hook
**************

.. code-block:: bash
  
  # /etc/ood/config/openstack_hook.sh
  export OS_INTERFACE="public"
  export OS_IDENTITY_API_VERSION=3
  export OS_AUTH_TYPE="v3oidcaccesstoken"
  export OS_AUTH_URL=https://identity.brno.openstack.cloud.e-infra.cz/v3
  export OS_IDENTITY_PROVIDER="login.e-infra.cz"
  export OS_PROTOCOL="openid"
  export OS_PROJECT_DOMAIN_ID="3b5cb406d60249508d0ddab2a80502b5"
  export OS_ACCESS_TOKEN=$OOD_OIDC_ACCESS_TOKEN
  echo $OOD_OIDC_ACCESS_TOKEN 

  start_time=$(date +%s)
  OUTPUT=$(timeout 5s openstack token issue -f json)
  exit_code=$?
  end_time=$(date +%s)
  elapsed_time=$((end_time - start_time))

  if [ $exit_code -eq 0 ]; then
    echo "$OUTPUT" > /home/$USER/token.json
    chown $USER /home/$USER/token.json
    echo "$OUTPUT"
    echo "openstack token issued in $elapsed_time seconds"
  elif [ $exit_code -eq 124 ]; then
      echo "Command timed out - OpenStack might be unreachable"
  else
    echo "Token issuance failed with error code $exit_code in $elapsed_time seconds"
  fi

.. warning::
  In order to use different cloud provider, the hook needs to be modified accordingly and a credential class needs to be implemented. Use this [https://github.com/OSC/ood_core/pull/897](pull request) as a reference.

Example OpenStack VM
********************
An example interactive application that can be launched using this adapter can be found at this link: https://github.com/andrejcermak/bc_openstack_vm . Its Coder counterpart can be found here: https://github.com/andrejcermak/coder_template_os_vm .

How to setup coder server
*************************

- follow the official documentation https://coder.com/docs/install
- create a service user
- issue a token via UI or cli https://coder.com/docs/admin/users/sessions-tokens#long-lived-tokens-api-tokens

How to publish a new template in Coder
**************************************

#. have a coder server (standalone, docker ...)
#. have terraform.tfvars in ~/terraform.tfvars with

.. code-block:: bash
  application_credential_id     = "your-application-credential-id"
  application_credential_name   = "your-application-credential-name"
  application_credential_secret = "your-application-credential-secret"
  openstack_region             = "your-region-name"
  openstack_identity_provider  = "your-identity-provider"
  project_id                   = "your-project-id"


#. ``git clone _your_coder_template_``
#. ``cd _your_coder_template_``
#. ``terraform init``
#. ``coder template push os-vm --variables-file="~/terraform.tfvars" -y``
#. ``coder template list -c name -c "organization id" -c "active version id"``
#. fill in the organization and template version ids in submit.yml.erb 