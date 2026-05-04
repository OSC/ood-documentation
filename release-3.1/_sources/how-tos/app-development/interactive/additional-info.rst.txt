.. _app-development-interactive-additional-info:

Adding Additional Information to the session cards
==================================================

.. _bc_info_html_md_erb:

info.{md,html}.erb
------------------

It's possible for you to add additional information to this session's card.

You can do so by creating a Markdown file ``info.md.erb`` or an html file
``info.html.erb`` in the applications folder.  Markdown files get generated
into html with # turning into an <h1> and ## turning into an <h2> and so on.

Again, they're `eRuby (Embedded Ruby)`_ files so you can add some dynamic behavior
to them. Along with any library you may choose to use you can also access these
variables directly.

id
  The session UUID of the job
cluster_id
  The cluster the job was submitted to
job_id
  The job id from the scheduler
created_at
  The time the session was created


.. _bc_completed_html_md_erb:

completed.{md,html}.erb
------------------------

:ref:`bc_info_html_md_erb` above will display on the session's card
regardless of the state of the job - it will always be displayed.

``completed.{md,html}.erb`` on the other hand, will only display
once the job has reached the ``completed`` state.

You may want to add this to the session's card to display information
to the user when the job is completed. Again, as it's `eRuby (Embedded Ruby)`_
files so you can add some dynamic behavior to them. 


.. _eruby (embedded ruby): https://en.wikipedia.org/wiki/ERuby
