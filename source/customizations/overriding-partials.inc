.. _overriding-partials:


Overriding Pages
----------------

Open OnDemand is built with Ruby on Rails which uses ``partials``
to build the web pages that are ultimately served to the clients.

All partials are held within `dashboard's views folder`_.  These
are the default ``partials`` that get distributed when you install
the package.

Open OnDemand provides a facility to override any of these partial
pages by supplying new files in ``/etc/ood/config/apps/dashboard/views``.

Let's look at an example where a center can provide a different,
specialized, footer for the bottom of the page. Overriding the
``partial`` that has been distributed.

First, you would need to find the original ``partial`` that is being
distributed.  

We can find this file's location at ``layouts/_footer.html.erb``
(relative to the `dashboard's views folder`_).

To override it, we simply provide a new file of the same name
and path in the ``/etc/ood/config/apps/dashboard/views`` folder.

So, the full file path would be ``/etc/ood/config/apps/dashboard/views/layouts/_footer.html.erb``.
By providing a simple html file like the one below, placed in the location in the
previous sentence, your center has now provided a different footer than the one
distributed by the Open OnDemand package.

.. code-block:: html

  <div class="text-center p-4 my-3 fs-5" >
    My center's custom footer.
  <div>

The [utility classes](https://getbootstrap.com/docs/5.0/utilities/spacing/) for text alignment, padding, margin, and font size in the sample are from Bootstrap, the front-end framework used in Open OnDemand. Using Bootstrap classes in custom overrides, widgets, and pages streamlines development and maintains a consistent user experience. The current installed version is Bootstrap 5.3.

.. _dashboard's views folder: https://github.com/OSC/ondemand/tree/master/apps/dashboard/app/views
