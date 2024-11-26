.. _security:

Security
========

Introduction
------------
This document details the security framework for Open OnDemand, providing essential information that administrators need to know for secure deployment and operation.

.. note::
  If you're here to report a vulnerability, you may refer to :ref:`vulnerability-management`.

Considerations
--------------
This section outlines key security advantages and areas for vigilance within the Open OnDemand environment.

Advantages
^^^^^^^^^^

- **Per-user Nginx (PUN) Architecture**: By running individual Nginx instances per user, Open OnDemand ensures that actions such as file access are conducted under user-specific non-root privileges, which isolates processes and enhances security.

- **Robust Authentication**: Open OnDemand supports various authentication methods. It particularly emphasizes secure protocols over less secure options like Basic or LDAP authentication, reinforcing its commitment to high security standards.

Limitations
^^^^^^^^^^^

- **HTTP Traffic to Origin Servers**: Traffic to backend services, including computational resources like Jupyter servers, is currently over HTTP, which is unencrypted. Plans are underway to upgrade this to HTTPS to ensure encryption of data in transit, thereby bolstering security.

Controls
^^^^^^^^

These are things the the out of the box OnDemand installation will provide
that some centers may want to change or disable altogether.

- **File Access**: OnDemand lets users navigate the file system. While file permissions
  limit what a user can view and navigate to, some centers may want to limit this even further.
  One option is to :ref:`set-file-allowlist` to limit what directories users may navigate to.
  Additionally, you may want to disable or limit access to the application. You can do this
  through :ref:`disabling_applications`.

.. _vulnerability-management:

Vulnerability Management
------------------------

Vulnerability management is a critical component of the security strategy for Open OnDemand.
This document outlines the procedures for reporting and managing vulnerabilities.

Reporting a Vulnerability
^^^^^^^^^^^^^^^^^^^^^^^^^

If you have security concerns or think you have found a vulnerability, please submit a
private report by visiting the 'Security' section of our GitHub located at
`GitHub Open OnDemand Security <https://github.com/OSC/ondemand/security/>`_ and
clicking 'Report a vulnerability'.

For direct inquiries or issues in submitting a report, contact the core project team
via email at security@openondemand.org.

Disclosure Policy
^^^^^^^^^^^^^^^^^

- Upon reporting, you will receive a response within hours, acknowledging the receipt of the report.
- A primary handler from the team will be assigned to coordinate the fix and release process:
- Confirm the problem and determine the affected versions (1-2 days).
- Audit code to find any potential similar problems.
- Prepare fixes for all releases still under maintenance and release as soon as possible.

Comments on Policy
^^^^^^^^^^^^^^^^^^

Suggestions to improve this process can be made via submitting a ticket, opening a
Discourse topic, or a pull request.

Security Audits
^^^^^^^^^^^^^^^

Open OnDemand has been audited several times by Trusted CI, the NSF Cybersecurity
Center of Excellence. The latest engagement report is available
`here <https://openondemand.org/sites/default/files/documents/Trusted%20CI%20Open%20OnDemand%20Engagement%20Final%20Report%20-%20REDACTED%20FOR%20PUBLIC%20RELEASE%20210712_0.pdf>`__.
These audits have helped shape the security landscape of the platform and contribute
to its ongoing security enhancements.


Maintaining a secure and robust operational environment is critical for the success of
Open OnDemand. Administrators are encouraged to implement the security practices
recommended in this guide and to regularly review security settings and updates.


Relevant References
-------------------

- :ref:`Authentication Overview <authentication-overview>`
- :ref:`Logging <logging>`
- :ref:`Customizations <customizations>`
