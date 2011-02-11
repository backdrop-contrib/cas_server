phpCAS is available directly from http://www.ja-sig.org/wiki/display/CASC/phpCAS. phpCAS is distributed under the LGPL license.

You must download and install phpCAS library in order for this CAS module to work.

Your PHP must have the following modules enabled:
  --with-curl
  --with-openssl
  --with-dom
  --with-zlib

Drupal modifications
---------------------
1) Enable the CAS module in admin/modules
2) Set the CAS server parameters in admin/config/people/cas
3) Enable the CAS login block to provide authentication.
4) Test authentication
6) If the user database is not external, remove the ability for users to edit own user names
their accounts.
