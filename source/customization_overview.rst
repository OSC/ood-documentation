.. _customization_overview:

Customization Overview
======================

OnDemand's configuration is stored in the environment, which can be modified using a hierarchy of config files. Configuration files are rooted in ``/etc/ood``. Assets that should be publicly available (such as a favicon or logo image) are placed under ``/var/www/ood/public``.

   * **/etc/ood/profile**

     - If exists, this file is sourced instead of the default at ``/opt/ood/nginx_stage/etc/profile`` by ``/opt/ood/nginx_stage/sbin/nginx_stage`` script when running as root, prior to launching the PUN.
     - You should source ``/opt/ood/nginx_stage/etc/profile`` in your custom ``/etc/ood/profile`` if you add one to load the correct software collections.

   * **/etc/ood/config/nginx_stage.yml**

     - YAML file to override default configuration for the PUN. You can set environment variables via key-value pairs in the mapping ``pun_custom_env``. You can specify a list of environment variables set in ``/etc/ood/profile`` to pass through to the PUN by defining the sequence ``pun_custom_env_declarations``.
     - An example of both of these uses may be found in `nginx_stage_example.yml <https://github.com/OSC/ondemand/blob/d85a3982d69746144d12bb808d2419b42ccc97a1/nginx_stage/share/nginx_stage_example.yml#L26-L43>`__. Variables set here are set for all OnDemand applications.

   * **/etc/ood/config/apps/$APP/env**

     - Used to provide application specific config
     - ``env`` files do not override values set by prior methods.

   * **/etc/ood/config/apps/$APP/initializers/$SOMETHING.rb**

     - Modify Rails application behavior `using Ruby code <https://guides.rubyonrails.org/configuring.html#using-initializer-files>`__. Since this is application code environment variables can be set, removed.
     - This method is specific to Ruby on Rails applications: Activejobs,
       Dashboard, File Editor, and Job Composer.
