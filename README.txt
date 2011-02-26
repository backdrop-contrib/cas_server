Requirements
============
PHP 5 with the following modules:
  curl, openssl, dom, zlib, and xml
phpCAS version 1.0.0 or later.

Installation
============

* Place the cas folder in your Drupal modules directory.

* Download phpCAS from http://www.ja-sig.org/wiki/display/CASC/phpCAS  You will
  need version 1.0.0 or later.

* There are several locations you can install the phpCAS library.

  1. Module directory installation. This means installing the library folder
     under the moduels directory, so that the file
     sites/<site>/modules/cas/CAS/CAS.php exists.

  2. System wide installation. See the phpCAS installation guide, currently at
     https://wiki.jasig.org/display/CASC/phpCAS+installation+guide

  3. Libraries API installation. Install and enable the Libraries API module,
     available at http://drupal.org/project/libraries. Then extract phpCAS so
     that sites/<site>/libraries/CAS/CAS.php exists.

* Go to Administer > Modules and enable this module.

* Go to Administer > Configuration > People > CAS to configure the CAS module.
  Depending on where and how you installed the phpCAS library, you may need
  to configure the path to CAS.php. The current library version will be
  displayed if the library is found.


API Changes Since 6.x-2.x
=========================
The hooks hook_auth_name() and hook_auth_filter() were combined and renamed
to hook_cas_user_alter(). See cas.api.php.
