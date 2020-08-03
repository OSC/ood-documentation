.. _authentication-adfs-with-auth-mellon:

SAML Authentication with Active Directory Federated Services (ADFS) and mod_auth_mellon
========================================================================================

The following details how to use ADFS infrastructure via SAML authentication to authenticate to an OpenOnDemand deployment. 

Prepare the Host
--------------------------------------------------
Before beginning, retrieve the following information from the ADFS administrator:
 
#. The SAML 2.0 service URL (e.g., https://adfs.organization.com/ADFS/ls)
#. The IdP metadata URL (e.g., https://adfs.organization.com/ADFS/metadata.xml)
#. Ensure SSL is properly configured and any organizationl certificate authorities are properly integrated into the host's trust store, see :ref:`add-ssl`

Install mod_auth_mellon
--------------------------------------------------

#. Ensure Software Collections is enabled on the system
#. Install the mod_auth_mellon module:

   .. code-block:: shell

      yum install httpd24-mod_auth_mellon httpd24-mod_ssl

Configure mod_auth_mellon
--------------------------------------------------

Note that this configuration assumes that SAML has been configured such that the returned NameID directly maps to a Unix user on the OOD host. For more information, see https://jdennis.fedorapeople.org/doc/mellon-user-guide/mellon_user_guide.html

#. Download the IDP metadata file

   .. code-block:: shell

      cd /etc/httpd/mellon/
      wget https://adfs.organization.com/ADFS/metadata.xml -O idpmetadata.xml

#. Generate the mellon metadata

   .. code-block:: shell

      export mellon_endpoint="https://$(hostname)/mellon"
      /usr/libexec/mod_auth_mellon/mellon_create_metadata.sh "${mellon_endpoint}" "${mellon_endpoint}/metadata"
      mv *.cert ./mellon.cert
      mv *.key ./mellon.key
      mv *.xml ./mellon_metadata.xml

#. Create a mellon configuration file

   .. code-block:: shell

      vi /etc/httpd/conf.d/00-mellon.conf

#. Add the following to the ``00-mellon.conf`` file

   .. code-block:: xml

      <Location />
        MellonSPPrivateKeyFile /etc/httpd/mellon/mellon.key
        MellonSPCertFile /etc/httpd/mellon/mellon.cert
        MellonSPMetadataFile /etc/httpd/mellon/mellon_metadata.xml
        MellonIdPMetadataFile /etc/httpd/mellon/idpmetadata.xml

        MellonEndpointPath /mellon
        MellonEnable "auth"
      </Location>

#. Convert the key and cert files into pfx format

   .. code-block:: shell

      openssl pkcs12 -export -inkey /etc/httpd/mellon/mellon.key -in /etc/httpd/mellon/mellon.cert -out /etc/httpd/mellon/mellon.pfx

#. Provide the ``mellon.pfx`` and ``mellon_metadata.xml`` files to your ADFS administrator. The files can then be imported into the ADFS system. 

Configure OOD
--------------------------------------------------

#. Edit the ``ood_portal.yml`` file to include the following:

   .. code-block:: yaml

      # /etc/ood/config/ood_portal.yml
      ---
      # ...
      # Your other custom configuration options...
      # ...

      auth:
        - 'AuthType Mellon'
        - 'Require valid-user'

#. Restart the HTTPD

   .. code-block:: shell

      systemctl restart httpd
