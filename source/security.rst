.. _security:

Security
========

Introduction
------------
This document details the security framework for Open OnDemand, providing essential information that administrators need to know for secure deployment and operation.

.. note::
  If you're here to report a vulerability, you may refer to :ref:`vulnerability-management`.

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

Conclusion
----------
Maintaining a secure and robust operational environment is critical for the success of Open OnDemand. Administrators are encouraged to implement the security practices recommended in this guide and to regularly review security settings and updates.


Relevant References
-------------------

.. toctree::
   :maxdepth: 2
   :caption: Security Topics

   security/vulnerability-management
   authentication/overview
   how-tos/monitoring/logging
   customizations
