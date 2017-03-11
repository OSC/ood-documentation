Generate Apache Config
======================

#. Clone and check out the latest tag:

   .. code-block:: sh

      cd ~/ood/src
      scl enable git19 -- git clone https://github.com/OSC/ood-portal-generator.git
      cd ood-portal-generator/
      scl enable git19 -- git checkout v0.3.1

#. ``ood-portal-generator`` is a script that takes a ``config.yml`` (or uses
   defaults if not provided) and renders an Apache config from a template.
   Generate a default one now:

   .. code-block:: sh

      scl enable rh-ruby22 -- rake
      # => mkdir -p build
      # => rendering templates/ood-portal.conf.erb => build/ood-portal.conf

#. Copy this to the default installation location:

   .. code-block:: sh

      sudo scl enable rh-ruby22 -- rake install
      # => cp build/ood-portal.conf /opt/rh/httpd24/root/etc/httpd/conf.d/ood-portal.conf

#. For now, lets use basic auth with an ``.htpasswd`` file until we get the
   installation complete. Then we will add another authentication mechanism.
   Start by generating an ``.htpasswd`` file with a user that **exists** on
   your system (the password need not be the same as their current system
   password):

   .. code-block:: sh

      sudo scl enable httpd24 -- htpasswd -c /opt/rh/httpd24/root/etc/httpd/.htpasswd ${SUDO_USER}
      #=> New password:
      #=> Re-type new password:
      #=> Adding password for user ${SUDO_USER}

   .. warning::

      Replace ``${SUDO_USER}`` above with a user name that exists on the system
      if you want to test with another user other than current user.

.. note::

   The Apache config references the location of ``mod_ood_proxy``,
   ``nginx_stage``, and ``ood_auth_map``. Be sure to update these locations if
   you change the ``PREFIX`` for any installation of the corresponding package
   in the ``config.yml`` prior to generating the Apache config.
