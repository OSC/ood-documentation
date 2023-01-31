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

* ``description``: Text to customize the support ticket header. It supports HTML.
* ``from``: The email address to set the email from field when sending the email. It defaults to the email field set in the form.
  This is useful to prevent the incoming emails being considered spam.
* ``to``: The destination email address of your Help Desk. 
* ``delivery_method``: Rails setting to set the transport mechanism to use. This is usually ``smtp``.
  For more information see the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.
* ``delivery_settings``: Rails settings object to set the transport configuration properties.
  See example below or the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.

Sample configuration:

  .. code-block:: yaml

    support_ticket:
      email:
        # Optional.
        # Text/HTML added to the page under the support ticket header
        description: |
          <strong>My Description Text</strong><br />
          This is a description text for the frontend with HTML support
        # Optional.
        # To set the email from field. Defaults to the email set in the form.
        from: "config@example.com" 
        # Required.
        # Your support system email address. The email will be sent to this address
        to: "support@support.system.com"
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
  
  Please note that an ``email`` field must be present in the form for the support ticket feature to be functional.

Custom fields can be added, but they will require a custom email template to make use of the provided values in the email body.
Override the default email template with your own by dropping a file named ``_email.text.erb`` into the folder
``/etc/ood/config/apps/dashboard/views/support_ticket/email/``

The example below shows a custom form configuration with 3 fields and how to use them in the template to generate the email body.

  .. code-block:: yaml

    support_ticket:
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
