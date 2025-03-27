.. _authentication-adfs-with-auth-mellon:

SAML Authentication with Active Directory Federated Services (ADFS) and mod_auth_mellon
========================================================================================

The following details how to use ADFS infrastructure via SAML authentication to authenticate to an OpenOnDemand deployment.

Prepare the Host
--------------------------------------------------
Before beginning, retrieve the following information from the ADFS administrator:
 
#. The SAML 2.0 service URL (e.g., https://adfs.organization.com/ADFS/ls)
#. The IdP metadata URL (e.g., https://adfs.organization.com/ADFS/metadata.xml)
#. Ensure SSL is properly configured and any organizational certificate authorities are properly integrated into the host's trust store, see :ref:`add-ssl`

Install mod_auth_mellon
--------------------------------------------------

#. Ensure Software Collections is enabled on the system
#. Install the mod_auth_mellon module:

.. tabs::

  .. tab:: EL7

    .. code-block:: shell

      yum install httpd24-mod_auth_mellon httpd24-mod_ssl

  .. tab:: EL8+

    .. code-block:: shell

      yum install mod_auth_mellon mod_ssl

  .. tab:: Ubuntu
    
    .. code-block:: shell

      apt install libapache2-mod-auth-mellon

Configure mod_auth_mellon
--------------------------------------------------

Note that this configuration assumes that SAML has been configured such that the returned NameID directly maps to a Unix
user on the OOD host. For more information, see https://jdennis.fedorapeople.org/doc/mellon-user-guide/mellon_user_guide.html

#. Change to apache's etc directory

    .. tabs::

       .. tab:: EL7/EL8+

         .. code-block:: shell

            mkdir -p /etc/httpd/mellon/
            cd /etc/httpd/mellon/

       .. tab:: Ubuntu

         .. code-block:: shell

            mkdir -p /etc/apache2/mellon/
            cd /etc/apache2/mellon/
       		     

#. Download the IDP metadata file

   .. code-block:: shell
		   
        wget https://adfs.organization.com/ADFS/metadata.xml -O idpmetadata.xml

#. Generate the mellon metadata

    .. tabs::
        .. tab:: EL7/EL8+
           .. code-block:: shell

              export mellon_endpoint="https://$(hostname)/mellon"
              /usr/libexec/mod_auth_mellon/mellon_create_metadata.sh "${mellon_endpoint}/metadata" "${mellon_endpoint}"
              mv *.cert ./mellon.cert
              mv *.key ./mellon.key
              mv *.xml ./mellon_metadata.xml

        .. tab:: Ubuntu

            There is a known problem on mellon_create_metadata in Ubuntu. If the xml generation fails silently try to apply the solution described at https://bugs.launchpad.net/ubuntu/+source/ssl-cert/+bug/1945774/comments/8

            .. code-block:: shell

                export mellon_endpoint="https://$(hostname)/mellon"
                /usr/sbin/mellon_create_metadata "${mellon_endpoint}/metadata" "${mellon_endpoint}"
                mv *.cert ./mellon.cert
                mv *.key ./mellon.key
                mv *.xml ./mellon_metadata.xml

#. Create a mellon configuration file
    .. tabs::
        .. tab:: EL7/EL8+
            .. code-block:: shell

                vi /etc/httpd/conf.d/00-mellon.conf

        .. tab:: Ubuntu
            .. code-block:: shell

                vi /etc/apache2/conf-available/mellon.conf

#. Add the following to the apache mellon's configuration file
    .. tabs::

        .. tab:: EL7/EL8+

           .. code-block:: xml

              <Location />
                MellonSPPrivateKeyFile /etc/httpd/mellon/mellon.key
                MellonSPCertFile /etc/httpd/mellon/mellon.cert
                MellonSPMetadataFile /etc/httpd/mellon/mellon_metadata.xml
                MellonIdPMetadataFile /etc/httpd/mellon/idpmetadata.xml

                MellonEndpointPath /mellon
                MellonEnable "auth"
              </Location>

        .. tab:: Ubuntu

            .. code-block:: xml

              <Location />
                MellonSPPrivateKeyFile /etc/apache2/mellon/mellon.key
                MellonSPCertFile /etc/apache2/mellon/mellon.cert
                MellonSPMetadataFile /etc/apache2/mellon/mellon_metadata.xml
                MellonIdPMetadataFile /etc/apache2/mellon/idpmetadata.xml

                MellonEndpointPath /mellon
                MellonEnable "auth"
              </Location>

#. Convert the key and cert files into PFX format
    .. tabs::
        .. tab:: EL7/EL8+
           .. code-block:: shell

              openssl pkcs12 -export -inkey /etc/httpd/mellon/mellon.key -in /etc/httpd/mellon/mellon.cert -out /etc/httpd/mellon/mellon.pfx

        .. tab:: Ubuntu
           .. code-block:: shell

              openssl pkcs12 -export -inkey /etc/apache2/mellon/mellon.key -in /etc/apache2/mellon/mellon.cert -out /etc/apache2/mellon/mellon.pfx

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
    .. tabs::
        .. tab:: EL7/EL8+
           .. code-block:: shell

                systemctl restart httpd

        .. tab:: Ubuntu
           .. code-block:: shell

                systemctl restart apache2
