.. _authentication-duo-2fa-with-keycloak:

Two Factor Auth using Duo with Keycloak
=======================================

These are the steps to setup two factor authentication with Duo using Keycloak.

Install Keycloak Duo SPI
--------------------------------------------------

#. Clone the Keycloak Duo SPI repo

   .. code::

      git clone https://github.com/OSC/keycloak-duo-spi.git
      cd keycloak-duo-spi
      git submodule update --init

#. Edit ``pom.xml`` and ensure ``keycloak.version`` matches the version of Keycloak you are running.

#. Build (with Docker) - produces ``target/keycloak-duo-spi-jar-with-dependencies.jar``

   .. code::

      docker run --rm -it -v $(pwd):/keycloak-duo-spi -w /keycloak-duo-spi \
        ohiosupercomputer/keycloak_duo_spi_buildbox:latest mvn clean test package

#. Build (without Docker) - produces ``target/keycloak-duo-spi-jar-with-dependencies.jar``

   .. code::

      yum -y install maven
      cd build/duo_java/DuoWeb
      mvn clean test install
      cd ../../..
      mvn clean test package

#. Copy the JAR file to Keycloak and instruct Keycloak to install the SPI

   .. code::

      sudo install -o keycloak -g keycloak -m 0644 target/keycloak-duo-spi-jar-with-dependencies.jar \
        /opt/keycloak-9.0.0/standalone/deployments/keycloak-duo-spi-jar-with-dependencies.jar
      sudo install -o keycloak -g keycloak -m 0644 /dev/null \
        /opt/keycloak-9.0.0/standalone/deployments/keycloak-duo-spi-jar-with-dependencies.jar.dodeploy

Configure Duo SPI
--------------------------------------------------

#. Log into your Keycloak instance
#. Choose the realm to configure in upper left corner, eg ``ondemand``
#. Choose ``Realm Settings`` in the left menu then ``Security Defenses`` tab
#. Add ``frame-src https://*.duosecurity.com/ 'self';`` to the beginning of the value for ``Content-Security-Policy``
#. Choose ``Authentication`` in the left menu
#. While on ``Flows`` tab ensure the dropdown for the flow name is ``Browser`` and click ``Copy``
#. Name the new flow ``browser-with-duo``
#. For all items below ``Username Password Form`` delete them by choosing ``Actions`` then ``Delete``
#. Choose ``Actions`` for ``Browser-with-duo Forms`` and choose ``Add Execution``
#. Select the ``Duo MFA`` provider and click ``Save``
#. Click ``Actions`` for ``Duo MFA`` and select ``Config``. Fill in all values as appropriate and select ``Save``.
#. Select ``Required`` for ``Duo MFA``
#. Choose the ``Bindings`` tab and set ``Browser Flow`` to ``browser-with-duo`` and choose ``Save``

Users logging into Keycloak will be required to verify their identity using Duo.
