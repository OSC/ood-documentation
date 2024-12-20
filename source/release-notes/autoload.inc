This comes from the Ruby on Rails framework that Open OnDemand utilizes.
It affects initializers you may have written, for example to :ref:`add-shortcuts-to-files-menu`.

To resolve this, wrap your code in a  ``Rails.application.config.after_initialize`` block.

For example, if you have:

.. code-block:: ruby

  # /etc/ood/config/apps/dashboard/initializers/ood.rb

    OodFilesApp.candidate_favorite_paths.tap do |paths|
      # add User project space directory
      paths << FavoritePath.new("/fs/project/#{User.new.name}")
    end

You will need to modify that file like so:

.. code-block:: ruby

  # /etc/ood/config/apps/dashboard/initializers/ood.rb

    Rails.application.config.after_initialize do
      OodFilesApp.candidate_favorite_paths.tap do |paths|
        # add User project space directory
        paths << FavoritePath.new("/fs/project/#{User.new.name}")
      end
    end