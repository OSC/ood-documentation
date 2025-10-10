.. _support_ticket_guide:

Support Tickets
---------------

The Dashboard enables users to easily submit support requests directly to your institution's Help Desk system.
This feature provides a customizable form that collects user input and sends the information to the configured system.

To enable this feature, define the settings needed using the configuration property ``support_ticket``.
Once this configuration object is defined, the ``Submit Support Ticket`` link will be shown in the ``Help`` navigation menu
and in all interactive session cards.

Quick Start
...........

The simplest configuration to get started with email-based support tickets:

.. code-block:: yaml

   # /etc/ood/config/ondemand.d/support_ticket.yml
   support_ticket:
     email:
       to: "support@example.edu"

This minimal configuration will:

* Enable the support ticket feature
* Display the default form with all standard fields
* Send tickets via email to the specified address
* Use the default SMTP configuration from Rails

For production use, you'll likely want to customize the form, add SMTP settings, and possibly use a different delivery mechanism. See the sections below for detailed configuration options.

.. figure:: /images/support_ticket_menu.png
   :align: center

.. raw:: html

   <div style="margin-top: 1.5rem;"></div>

The support ticket page has a simple form to gather information that will be submitted to the support system.
The form can be pre-populated with contextual information in two ways:

1. **From Interactive Session Cards**: When triggered from a BatchConnect session card, the system automatically includes session details (session ID, title, status, creation time) to help troubleshoot the issue.
2. **From Job Information**: When triggered with job context, the system can include job details (job ID, cluster, status, submission time).

The support ticket URL accepts these optional query parameters:

* ``session_id``: UUID of a BatchConnect session to include in the ticket
* ``job_id``: Job ID to include in the ticket (requires ``cluster`` parameter)
* ``cluster``: Cluster name where the job is running
* ``queue``: Pre-select a specific queue for Request Tracker systems

Example URLs:

.. code-block:: bash

   # With session context
   https://ondemand.example.edu/support?session_id=abc-123-def

   # With job context
   https://ondemand.example.edu/support?job_id=12345&cluster=owens

   # With queue selection
   https://ondemand.example.edu/support?queue=General

.. figure:: /images/support_ticket_form.png
   :align: center

.. raw:: html

   <div style="margin-top: 1rem;"></div>

Supported Delivery Mechanisms
.............................

Open OnDemand supports the following delivery mechanisms for support tickets:

* **Email** - Uses SMTP to send tickets via email to your help desk system
* **Request Tracker API** - Creates tickets directly in Request Tracker systems
* **ServiceNow API** - Creates incidents directly in ServiceNow systems

Default Form Fields
...................

The support ticket form includes these default fields:

* **Username:** The logged-in username (read-only). Added to the ticket body for reference.
* **Email:** Required. Email address for communication about this ticket. A single email address is supported.
* **CC:** Optional. Additional email address to copy on ticket communications. A single email address is supported.
* **Subject:** Required. Brief description of the problem.
* **Attachments:** Optional. Upload files (e.g., screenshots) to help with debugging and troubleshooting. Default limits: 4 files, 6MB per file.
* **Description:** Required. Detailed description of the problem.
* **Session ID:** Hidden field. Automatically populated when launched from a session card.
* **Session Description:** Read-only field. Displays session information when a session ID is present.
* **Job ID:** Hidden field. Automatically populated when job context is provided.
* **Cluster:** Hidden field. Automatically populated when job context is provided.
* **Job Description:** Read-only field. Displays job information when job context is present.
* **Queue:** Hidden field. For Request Tracker systems to pre-select a queue.

Email
.....

The Email delivery mechanism uses SMTP to send support tickets to your help desk system. This was the first implementation and requires email configuration.

These are the configuration properties for email delivery:

* ``description``: Optional. Text to customize the support ticket header.
* ``ui_template``: Optional. Custom view template name. Defaults to ``email_service_template``.
* ``email``: Required section to configure how the email is sent to the support system.

  * ``to``: Required. The destination email address of your Help Desk.
  * ``from``: Optional. The address to set in the from field when sending the email. Defaults to the email submitted in the support ticket form. This is useful to prevent the incoming emails being considered spam.
  * ``delivery_method``: Optional. Rails setting to set the transport mechanism to use. This is usually ``smtp``. For more information see the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.
  * ``delivery_settings``: Optional. Rails settings object to set the transport configuration properties. See example below or the `Rails documentation on mailers <https://guides.rubyonrails.org/action_mailer_basics.html#action-mailer-configuration>`_.
  * ``success_message``: Optional. Custom message to display when ticket is successfully created. Defaults to a message showing the recipient address.

.. warning::

  Use caution when supplying username and password in delivery_settings. These files are readable by
  unprivileged users and as such this information can be found by a sophisticated user without privilege
  escalation.

Sample email configuration:

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
        My optional description Text for the support ticket feature

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

  The ``email`` field must be present in the form for the support ticket feature to be functional, as it is used for communication with the user.

Available field attributes:

* ``required``: Boolean. Mark field as required for validation.
* ``readonly``: Boolean. Display field value but prevent editing.
* ``disabled``: Boolean. Disable the field.
* ``hide_when_empty``: Boolean. Hide field when it has no value.
* ``widget``: String. Specify the field type (``email_field``, ``text_area``, ``hidden_field``, ``file_attachments``).
* ``value``: Set a default or fixed value for the field. Supports ERB templating (e.g., ``<%= CurrentUser.name %>``).
* ``fixed``: Boolean. When combined with ``value``, makes the value unchangeable.
* ``rows``: Integer. For text areas, specify the number of rows.

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
          required: true
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
        job_id:
          widget: hidden_field
        cluster:
          widget: hidden_field
        job_description:
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
        - job_id
        - cluster
        - job_description
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

Request Tracker API
...................

The Request Tracker API delivery mechanism creates tickets directly in Request Tracker systems.

These are the supported configuration options:

* ``description``: Optional. Text to customize the support ticket header.
* ``ui_template``: Optional. Custom view template name. Defaults to ``email_service_template``.
* ``rt_api``: Required section for Request Tracker configuration.

  * ``server``: Required. The URL of the Request Tracker server.
  * ``auth_token``: The value for the API authentication token. Required when ``Authorization: Token <value>`` is used.
  * ``user``: The user value when HTTP basic authentication is used.
  * ``pass``: The password value when HTTP basic authentication is used.
  * ``priority``: Required. The priority value for all tickets.
  * ``queues``: Required. Array of allowed queues to submit tickets. By default, the first queue in the array will be used.
  * ``template``: Optional. Custom ERB template for ticket content. Defaults to ``rt_ticket_content.text.erb``.
  * ``success_message``: Optional. Custom message to display when ticket is successfully created.
  * ``timeout``: Optional. The maximum time in seconds that the client should wait for responses from the server. Defaults to ``30``.
  * ``verify_ssl``: Optional. Whether to verify SSL certificates.

  .. code-block:: yaml

    support_ticket:
      rt_api:
        server: "http://rt:34000"
        auth_token: "auth_token"
        user: "root"
        pass: "password"
        priority: 4
        queues:
          - "General"
          - "Support"
        template: "custom_rt_template.text.erb"
        success_message: "Your ticket has been created successfully."
        timeout: 10
        verify_ssl: true

ServiceNow API
..............

The ServiceNow API delivery mechanism creates incidents directly in ServiceNow systems.

These are the supported configuration options:

* ``description``: Optional. Text to customize the support ticket header.
* ``ui_template``: Optional. Custom view template name. Defaults to ``email_service_template``.
* ``servicenow_api``: Required section for ServiceNow configuration.

  * ``server``: Required. The URL of the ServiceNow server.
  * ``auth_header``: Optional. The name for the API authentication header. Defaults to ``x-sn-apikey``.
  * ``auth_token``: The value for the API authentication key. Required when API key authentication is used.
  * ``auth_token_env``: Optional. Environment variable name containing the API authentication key. Takes precedence over ``auth_token`` if set.
  * ``user``: The user value when HTTP basic authentication is used.
  * ``pass``: The password value when HTTP basic authentication is used.
  * ``pass_env``: Optional. Environment variable name containing the password. Takes precedence over ``pass`` if set.
  * ``timeout``: Optional. The maximum time in seconds that the client should wait for responses from the server. Defaults to ``30``.
  * ``verify_ssl``: Optional. Whether to verify SSL certificates. Defaults to ``true``.
  * ``proxy``: Optional. Proxy server URL to use for the connection.
  * ``map``: Optional. Map of ServiceNow incident fields to support ticket form field names. The value can be a single field name or an array of field names (values will be concatenated with commas).
  * ``payload``: Optional. Map of ServiceNow incident fields to static values. Use ``nil`` as the value to dynamically pull from the form field with the same name.
  * ``template``: Optional. Custom ERB template for incident description. Defaults to ``servicenow_content.text.erb``.
  * ``success_message``: Optional. Custom message to display when ticket is successfully created.

.. note::

  For security, use ``auth_token_env`` and ``pass_env`` to store credentials in environment variables rather than directly in configuration files.

**ServiceNow Field Mapping**

The ServiceNow implementation builds the incident payload in three stages:

1. **Default mappings** (always included):

   * ``email`` → ``caller_id``
   * ``cc`` → ``watch_list``
   * ``subject`` → ``short_description``
   * ``description`` → ``description`` (formatted using template)

2. **Custom mappings via** ``map`` (adds to or overrides default mappings):

   Maps form field values to ServiceNow incident fields. The configuration key is the ServiceNow field name, and the value is either:

   * A single form field name (string)
   * An array of form field names (values will be joined with commas)

3. **Static/dynamic values via** ``payload`` (final stage, highest precedence):

   Sets ServiceNow incident fields to specific values. For each key-value pair:

   * If the value is NOT ``nil``: uses the static value provided
   * If the value IS ``nil``: dynamically pulls the value from the form field matching the key name

Example showing all three stages:

  .. code-block:: yaml

    support_ticket:
      servicenow_api:
        server: "https://servicenow.server.com"
        auth_header: "x-sn-apikey"
        auth_token_env: "SERVICENOW_API_KEY"

        # Stage 2: Map form fields to ServiceNow incident fields
        # These add to or override the default mappings
        map:
          # Override default caller_id mapping (normally uses 'email')
          caller_id: "username"
          # Map a single form field
          u_email_source: "email"
          # Map multiple form fields - values joined with commas
          u_affected_users: ["username", "email"]

        # Stage 3: Set static or dynamic values
        # These have the highest precedence
        payload:
          # Static values: always use these exact values
          u_category: "troubleshooting"
          contact_type: "External System"
          assignment_group: "IT Support Team"
          u_business_service: "Research Computing"

          # Dynamic values: use nil to pull from form field with same name
          # This would use support_ticket.priority if that field exists
          priority: nil

          # You can also override default mappings here with static values
          # This would ignore the user's email and always use this value
          # caller_id: "system@example.edu"

        template: "custom_servicenow_template.text.erb"
        success_message: "Your ServiceNow incident has been created."

The resulting ServiceNow incident would have:

* ``caller_id``: Value from ``username`` form field (overridden by ``map``)
* ``watch_list``: Value from ``cc`` form field (default mapping)
* ``short_description``: Value from ``subject`` form field (default mapping)
* ``description``: Formatted using template (default mapping)
* ``u_email_source``: Value from ``email`` form field (added by ``map``)
* ``u_affected_users``: "username,email" (added by ``map``)
* ``u_category``: "troubleshooting" (static value from ``payload``)
* ``contact_type``: "External System" (static value from ``payload``)
* ``assignment_group``: "IT Support Team" (static value from ``payload``)
* ``u_business_service``: "Research Computing" (static value from ``payload``)
* ``priority``: Value from ``priority`` form field if it exists (dynamic from ``payload``)

Profile-Based Configuration
...........................

Support tickets can be configured differently based on user profiles. This is useful for multi-tenant environments where different groups need tickets routed to different support teams.

.. code-block:: yaml

   # Global default configuration
   support_ticket:
     email:
       to: "general-support@example.edu"

   # Profile-specific configurations
   profiles:
     research_team:
       support_ticket:
         email:
           to: "research-support@example.edu"
         description: "Contact the Research Computing support team"

     teaching_team:
       support_ticket:
         servicenow_api:
           server: "https://teaching.service-now.com"
           auth_token_env: "TEACHING_SNOW_TOKEN"
           payload:
             assignment_group: "Teaching Support"

Users will use the profile-specific configuration if they have selected that profile or if hostname-based profile matching is enabled.

Custom Templates
................

All delivery mechanisms support custom ERB templates for formatting ticket content:

**Email Templates**

Override the default email template by creating:

.. code-block:: bash

   /etc/ood/config/apps/dashboard/views/support_ticket/email/_email.text.erb

**Request Tracker Templates**

Customize RT ticket content by creating:

.. code-block:: bash

   /etc/ood/config/apps/dashboard/views/support_ticket/rt/rt_ticket_content.text.erb

**ServiceNow Templates**

Customize ServiceNow incident description by creating:

.. code-block:: bash

   /etc/ood/config/apps/dashboard/views/support_ticket/servicenow/servicenow_content.text.erb

Templates have access to a ``context`` object containing:

* ``context.support_ticket``: The support ticket form data
* ``context.session``: BatchConnect session object (if applicable)
* ``context.job``: Job information object (if applicable)

Example custom template:

.. code-block:: erb

   Problem Report from <%= context.support_ticket.username %>

   Email: <%= context.support_ticket.email %>
   Subject: <%= context.support_ticket.subject %>

   Description:
   <%= context.support_ticket.description %>

   <% if context.session %>
   Session Information:
   - Title: <%= context.session.title %>
   - Job ID: <%= context.session.job_id %>
   - Status: <%= context.session.status %>
   <% end %>

   <% if context.job %>
   Job Information:
   - Job ID: <%= context.job.id %>
   - Cluster: <%= context.job.cluster %>
   - Status: <%= context.job.status %>
   <% end %>

Delivery Mechanism Precedence
.............................

When multiple delivery mechanisms are configured, Open OnDemand follows a specific precedence order:

1. **Email** (highest precedence)
2. **Request Tracker API**
3. **ServiceNow API** (lowest precedence)

The system will use the first available mechanism in this order. For example, if both Email and ServiceNow are configured, Email will be used.

.. warning::

   Only configure one delivery mechanism per profile to avoid confusion. The precedence order exists for backward compatibility but is not recommended for production use.

Security Considerations
.......................

When configuring support tickets, keep these security best practices in mind:

**Credential Management**

* **Use environment variables for secrets**: Always use ``auth_token_env`` and ``pass_env`` instead of storing credentials directly in configuration files.
* **File permissions**: Configuration files in ``/etc/ood/config`` are readable by all users. Never store sensitive credentials directly in these files.
* **Environment variables**: Set sensitive credentials in ``/etc/ood/profile`` or Apache configuration where they are not accessible to users.

Example secure configuration:

.. code-block:: yaml

   # /etc/ood/config/ondemand.d/support_ticket.yml
   support_ticket:
     servicenow_api:
       server: "https://servicenow.example.edu"
       auth_token_env: "SERVICENOW_API_TOKEN"  # Secure
       # auth_token: "secret123"                # INSECURE - Do not do this!

.. code-block:: bash

   # /etc/ood/profile
   export SERVICENOW_API_TOKEN="actual-secret-token-here"

**SSL/TLS Verification**

* Always use ``verify_ssl: true`` (the default) in production environments
* Only disable SSL verification for testing/development environments
* Use proper SSL certificates from trusted certificate authorities

**Input Validation**

* The system automatically validates email addresses using standard RFC patterns
* File upload sizes are limited by default (6MB per file, 4 files maximum)
* Adjust ``attachments.max_size`` and ``attachments.max_items`` based on your environment's needs

**Session Data Filtering**

* The system automatically filters sensitive session parameters (like ``ood_connection_info``)
* Custom templates should avoid exposing sensitive information
* Review custom templates to ensure they don't inadvertently include passwords or tokens

Community contributions for new delivery mechanisms are welcome!