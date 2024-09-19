CAS Server
==========

The CAS Server module lets Backdrop act as a central authentication system. It makes your user database the primary location for other systems to use for authentication in an SSO environment using the CAS 2.0 protocol.

There is also a CAS client module available for Backdrop (https://github.com/backdrop-contrib/cas) and Drupal (https://www.drupal.org/project/cas).

Do NOT simultaneously enable the CAS and CAS Server modules. Unpredictable
errors may occur.

Requirements
------------
 * SSL:
     The CAS protocol requires the CAS server to run over HTTPS (not HTTP).
     Your Backdrop site will need to be configured for HTTPS separately. The site
     should also have a valid SSL certificate signed by a trusted Certificate
     Authority. The certificate should be made available to your CAS clients
     for additional security.

Installation
------------
- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.
	
Configuration
-------------
Configuration can be found at /admin/config/people/cas_server, but the module
will start working right away without any configuration.

If your Backdrop site is https://site.example.com/, other CAS enabled
applications should be configured to use https://site.example.com/cas as the
CAS server.

Current Maintainers
-------------------
- [Alex Höbart](https://github.com/AlexHoebart-ICPDR)

Seeking additional maintainers.

Credits
-------
Ported to Backdrop CMS by [Alex Höbart](https://github.com/AlexHoebart-ICPDR).

Originally maintained for Drupal by:
- [bkosborne](https://www.drupal.org/u/bkosborne)
- [claudiucristea](https://www.drupal.org/u/claudiucristea)
- [metzlerd](https://www.drupal.org/u/metzlerd)


License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
