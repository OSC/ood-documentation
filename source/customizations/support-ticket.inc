.. _support_ticket_guide:

Support Tickets
---------------

The Dashboard now supports sending a support ticket to your institution Help Desk system.
The feature uses email as the delivery mechanism, but it could be extended to support others.

To enable this feature, define the settings needed using the the configuration property ``support_ticket``.
Once this configuration object is defined, the ``Submit Support Ticket`` link will be shown in the ``Help`` navigation menu
and in all interactive session cards.

.. figure:: /images/support_ticket_menu.png
   :align: center

The support ticket page has a simple form to gather information that will be submitted to the support system via email.
If triggered from a session card, the system will automatically add information about the selected
session to the body of the email to help troubleshoot the issue.

.. figure:: /images/support_ticket_form.png
   :align: center

A brief description of the default form fields used in the support ticket form:

* **Username:** Logged in user. Username will be added to the support ticket body for reference.
* **Email:** Email address to communicate regarding this support ticket. A single email address is supported.
* **CC:** Additional email address to communicate regardig this ticket. A single email address is supported.
* **Subject:** Brief description of the problem.
* **Attachments:** Add screeshots of the problem to help with debugging and troubleshooting.
* **Description:** Detail description of the problem.

Configuration
.............

These are the most common configuration properties needed to enable and setup the support ticket feature:

* ``description``: Text to customize the support ticket header.
* ``email``: Section to configure how the email is sent to the support system.
* ``to``: The destination email address of your Help Desk.
* ``from``: The address to set in the from field when sending the email. It defaults to the email submitted in the support ticket form.
  This is useful to prevent the incoming emails being considered spam.
* ``delivery_method``: Rails setting to set the transport mechanism to use. This is usually ``smtp``.
  For more information see the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.
* ``delivery_settings``: Rails settings object to set the transport configuration properties.
  See example below or the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.

.. warning::

  Use caution when supplying username and password in delivery_settings.  These files are readable by
  unprivileged users and as such this information can be found by a sophsticated user without privilege
  escelation.

Sample configuration:

  .. code-block:: yaml

    support_ticket:
      # Optional.
      # Validation configuration for attachments.
      attachments:
        # Maximum number of attachments. Defaults to 4
        max_items: 1
        # Maximum size for a single attachment in bytes. Defaults to 6MB
        # Common file sizes:
        #  2MB = 2097152
        #  5MB = 5242880
        #  6MB = 6291456
        #  10MB = 10485760
        max_size: 2097152
      # Optional.
      # Text added to the page under the support ticket header
      description: |
        My optional description Text for the support ticket feture
      
      # email section is required and should always be present.
      # It configures how the support ticket email is sent
      email:
        # Required.
        # Your support system email address. The email will be sent to this address
        to: "support@support.system.com"
        # Optional.
        # To set the email from field. Defaults to the email set in the form.
        # The email set in the form will always be added to the reply-to email field
        from: "config@example.com"

        # delivery_method and delivery_settings are Rails configuration items
        # that can be set in this file to simplify configuration.
        # If you prefer, you can configure Rails in the usual way.
        delivery_method: "smtp"
        delivery_settings:
          address: 'smtp.gmail.com'
          port: 587
          domain: 'example.com'
          user_name: '<username>'
          password: '<password>'
          authentication: 'plain'
          enable_starttls_auto: true
          open_timeout: 15
          read_timeout: 15

Customizations
..............

The support ticket form can be customized using the ``form`` and ``attributes`` configuration properties.
In the same way that you can configure the :ref:`form for interactive applications <enable-desktops-modify-form-attributes>`,
the support ticket form fields can be arranged or changed as required.

.. note::
  
  Please note that the ``email`` field must be present in the form for the support ticket feature to be functional.

Custom fields can be added, but they will require a custom email template to make use of the provided values in the email body.
Override the default email template with your own by dropping a file named ``_email.text.erb`` into the folder
``/etc/ood/config/apps/dashboard/views/support_ticket/email/``

This is the default form for submitting support tickets. You can use this YAML as a starting
place for removing and/or adding fields.

  .. code-block:: yaml

    support_ticket:
      email: must supplied by you

      attributes:
        username:
          value: "<%= CurrentUser.name %>"
          readonly: true
        email:
          widget: email_field
          required: true
        cc:
          widget: email_field
        subject:
          required: true
        session_id:
          widget: hidden_field
        session_description:
          hide_when_empty: true
          disabled: true
        attachments:
          widget: file_attachments
        description:
          widget: text_area
          required: true
          rows: 10
        queue:
          widget: hidden_field

      form:
        - username
        - email
        - cc
        - subject
        - session_id
        - session_description
        - attachments
        - description
        - queue

The example below shows a custom form configuration with 3 fields and how to use them in the template to generate the email body.

  .. code-block:: yaml

    support_ticket:
      # email section is required and should always be present.
      # It configures how the support ticket email is sent
      email:
        to: "support@support.system.com"

      attributes:
        email:
          required: true
        subject:
          value: "OnDemand Problem: "
      form:
        - email
        - subject
        - department

  .. code-block::

    # /etc/ood/config/apps/dashboard/views/support_ticket/email/_email.text.erb
    Email Intro
    Department: <%= @context.support_ticket.department %>
    Subject Copy: <%= @context.support_ticket.subject %>

    Other static data.

.. figure:: /images/support_ticket_custom_form.png
   :align: center
