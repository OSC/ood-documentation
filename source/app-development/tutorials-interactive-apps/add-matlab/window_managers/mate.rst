.. _app-development-tutorials-interactive-apps-add-matlab-wm-mate:

Mate
====

.. note::

    `According to the developers`_ the correct pronunciation of Mate is "may-tah" like the drink, and not matey like pirates, or mate like friends.

The code for starting Mate in the background looks like this:

    .. code-block:: shell

        # Launch Mate Window Manager and Panel
        marco --no-composite --no-force-fullscreen --sm-disable &
        # mate-panel blocks, but does not work reliably when launched in the same subshell as marco
        mate-panel &

.. _according to the developers: https://ubuntu-mate.org/blog/how-to-pronounce-mate/