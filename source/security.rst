.. _security:

Security
=================

Introduction
------------

This document provides an overview of the security framework implemented in Open OnDemand, focusing on practical security concerns administrators need to consider when installing and managing the platform.

Considerations
--------------

**The Good:**

- **PUN Architecture**: The Per-user Nginx (PUN) architecture underpins the security model where web servers, run by individual users rather than the root, handle user requests. This ensures that all actions, including file accesses, are executed under non-root user privileges, enhancing security by isolating user processes.

- **Apache Authentication**: Authentication is mandatory, with the type of scheme being adjustable per site. Open OnDemand discourages and does not document insecure basic authentication mechanisms such as Basic or LDAP to promote stronger security measures.

**The Bad:**

- **HTTP Traffic to Origin Servers**: Currently, traffic to origin servers (like compute nodes running applications such as Jupyter) is handled via HTTP. This presents a risk as it is not encrypted. Efforts are ongoing to shift this traffic to HTTPS to secure all data in transit.

Security Features
-----------------

- **Monitoring and Logging**: Extensive monitoring and logging are in place, providing crucial tools for security auditing and incident response. For more information, see :ref:`logging`.

- **Vulnerability Management**: Vulnerabilities within Open OnDemand are diligently identified, reported, and managed. For more details on this process, see :ref:`vulnerability-management`.

- **Security Audits**: Open OnDemand has undergone several security audits by Trusted CI, the NSF Cybersecurity Center of Excellence. The latest audit report is available `here <https://openondemand.org/sites/default/files/documents/Trusted%20CI%20Open%20OnDemand%20Engagement%20Final%20Report%20-%20REDACTED%20FOR%20PUBLIC%20RELEASE%20210712_0.pdf>`__.

Conclusion
----------

Maintaining robust security is pivotal for the operation of Open OnDemand. Ongoing efforts are dedicated to strengthening the security measures in place. Users and administrators are encouraged to adhere to the outlined best practices and security guidelines to ensure a secure operational environment.

Relevant References
-------------------

.. toctree::
   :maxdepth: 2
   :caption: Security Topics

   security/vulnerability-management
   authentication/overview
   how-tos/monitoring/logging
   customizations
