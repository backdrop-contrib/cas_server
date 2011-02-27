<?php

/**
 * @file
 * CAS module settings UI.
 */

/**
 * Provides settings pages.
 */
function cas_admin_settings() {

  // Only displays path settings if Libraries API is not installed.
  if (!module_exists('libraries')) {

    $form['library'] = array(
      '#type' => 'fieldset',
      '#title' => t('CAS library settings'),
      '#collapsible' => TRUE,
      '#after_build' => array('cas_library_version_check'),
    );

    $form['library']['cas_library_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Library directory'),
      '#default_value' => variable_get('cas_library_dir', 'CAS'),
      '#description' => t('Specify the path to the directory the CAS.php file resides in. Leave blank to load cas from your phpinclude path.'),
      '#element_validate' => array('cas_library_dir_validate'),
    );
  }

  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('CAS server settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['cas_version'] = array(
    '#type' => 'radios',
    '#title' => t('CAS version'),
    '#default_value' => variable_get('cas_version', '2.0'),
    '#options' => array(
      '1.0' => '1.0',
      '2.0' => t('2.0 or higher'),
      'S1' => t('SAML Version 1.1'),
    ),
  );

  $form['server']['cas_server'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS server'),
    '#default_value' => variable_get('cas_server', ''),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('Location of CAS authentication service.'),
  );

  $form['server']['cas_port'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS port'),
    '#default_value' => variable_get('cas_port', '443'),
    '#size' => 30,
    '#maxlength' => 8,
    '#description' => t('443 is the standard ssl port. 8443 is the standard non-root port for Tomcat.'),
  );

  $form['server']['cas_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS URI'),
    '#default_value' => variable_get('cas_uri', ''),
    '#size' => 30,
    '#description' => t('If CAS is not at the root of the host, include a URI (e.g., /cas).'),
  );

  $form['server']['cas_check_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check with the CAS server to see if the user is already logged in?'),
    '#default_value' => variable_get('cas_check_first', 0),
    '#description' => t('This implements the <a href="@cas-gateway">Gateway feature</a> of the CAS Protocol. The check is only performed the first time a user visits your site, so that the local drupal logout is still useful for site admins.', array('@cas-gateway' => 'https://wiki.jasig.org/display/CAS/gateway')),
  );

  $form['server']['cas_cert_verify'] = array(
    '#type' => 'radios',
    '#title' => t('CAS PEM certificate verification'),
    '#default_value' => variable_get('cas_cert_verify', CAS_NO_VERIFY),
    '#options' => array(
      CAS_NO_VERIFY => t('Do not verify the certificate'),
      CAS_CA_VERIFY => t('Verify the Certificate Authority using PEM certificate'),
    ),
  );

  $form['server']['cas_cert'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS PEM Certificate (phpCAS 0.6 or greater)'),
    '#default_value' => variable_get('cas_cert', ''),
    '#size' => 30,
    '#description' => t('With client version 0.6 or greater this is the certificate for validating cas or the cas CA as appropriate.'),
  );

  $form['server']['cas_proxy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Initialize CAS as proxy'),
    '#default_value' => variable_get('cas_proxy', 0),
    '#description' => t('When using a proxy it is required to set the option "Require CAS login for:" to "specific pages" with "node/*" as a specific page or "all pages except specific pages" on the "Redirection settings".')
  );

  $form['server']['cas_pgtformat'] = array(
    '#type' => 'radios',
    '#title' => t('CAS PGT storage file format'),
    '#default_value' => variable_get('cas_pgtformat', 'plain'),
    '#options' => array('plain' => t('Plain Text'), 'xml' => t('XML')),
  );

  $form['server']['cas_pgtpath'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS PGT storage path'),
    '#default_value' => variable_get('cas_pgtpath', ''),
    '#size' => 30,
    '#description' => t("Only needed if 'Use CAS proxy initializer' is configured. Leave empty for default."),
  );

  $form['server']['cas_signout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable CAS Single Sign Out (CAS server 3.1 or greater)'),
    '#default_value' => variable_get('cas_signout', FALSE),
    '#description' => t('For more details see <a href="http://www.ja-sig.org/wiki/display/CASUM/Single+Sign+Out">http://www.ja-sig.org/wiki/display/CASUM/Single+Sign+Out</a>.'),
  );

  $form['server']['cas_debugfile'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS debugging output filename'),
    '#default_value' => variable_get('cas_debugfile', ''),
    '#size' => 30,
    '#description' => t("Leave empty if you don't want debugging output."),
  );


  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('User account settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['account']['cas_user_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Should Drupal user accounts be automatically created?'),
    '#default_value' => variable_get('cas_user_register', 1),
    '#description' => t('If a CAS user logs in, his Drupal account will automatically be created. If you don\'t check this option, you will have to pre-create accounts for the users you want to allow.'),
  );

  $form['account']['cas_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Domain'),
    '#default_value' => variable_get('cas_domain', ''),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('Append this domain name to each new user in order generate his email address.'),
  );

  $form['account']['cas_hide_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change email address'),
    '#default_value' => variable_get('cas_hide_email', 0),
    '#description' => t('Hide email address field on the edit user form.'),
  );

  $form['account']['cas_hide_password'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change password'),
    '#default_value' => variable_get('cas_hide_password', 0),
    '#description' => t('Hide password field on the edit user form. This also removes the requirement to enter your current password before changing your e-mail address.'),
  );

  if (module_exists('persistent_login')) {
    $form['account']['cas_allow_rememberme'] = array(
      '#type' => 'checkbox',
      '#title' => t('Users can stay logged in between sessions'),
      '#default_value' => variable_get('cas_allow_rememberme', 0),
      '#description' => t('If Persistent Login is enabled, users can choose to stay logged in between browser sessions'),
      );
  }

  $form['account']['cas_auto_assigned_role'] = array(
    '#type' => 'select',
    '#title' => t('Auto-assign users to the role(s)'),
    '#default_value' => variable_get('cas_auto_assigned_role', array(DRUPAL_AUTHENTICATED_RID)),
    '#options' => user_roles(TRUE),
    '#multiple' => TRUE,
    '#description' => t('This value can be used to establish a role automatically for all CAS users.  As an example, if you are also using the simple_ldap module, you can use this role to establish a tie between CAS and LDAP-populated data.  i.e. Users with the role of \'cas:user\' should have their LDAP data updated automatically.'),
  );


  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirection settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pages']['cas_access'] = array(
    '#type' => 'radios',
    '#title' => t('Require CAS login for'),
    '#default_value' => variable_get('cas_access', 0),
    '#options' => array(t('specific pages'), t('all pages except specific pages')),
  );

  $form['pages']['cas_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific pages'),
    '#default_value' => variable_get('cas_pages', ''),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['pages']['cas_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#default_value' => variable_get('cas_exclude', CAS_EXCLUDE),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Indicates which pages will be ignored (no login checks). Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );


  // Settings for redirection upon first login
  $form['pages']['cas_first_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force redirection on initial login'),
    '#default_value' => variable_get('cas_first_login', 0),
    '#description' => t("Activate this option if you want a user to be directed to the following page after their first CAS login."),
  );

  $form['pages']['cas_first_login_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial login landing page'),
    '#default_value' => variable_get('cas_first_login_destination', ''),
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. An example path is '<em>blog</em>' for the blog page. '&lt;front&gt;' is the front page. An example URL is '<em>http://www.example.com</em>'."),
  );

  // Setting for message displayed to user upon successfull login
  $form['pages']['cas_login_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Successful login message'),
    '#default_value' => variable_get('cas_login_message', 'Logged in via CAS as %cas_username.'),
    '#description' => t('The message displayed to a user when he successfully logs in via CAS. You may specify \'%cas_username\', the username of the user.'),
  );

  // Setting for page to return to after a CAS logout
  $form['pages']['cas_logout_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect user on logout'),
    '#default_value' => variable_get('cas_logout_redirect', 0),
    '#description' => t("Activate this option if you want a user to be directed to the following page after logging out of CAS. The logout destination must be specified below."),
  );

  $form['pages']['cas_logout_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout destination'),
    '#default_value' => variable_get('cas_logout_destination', ''),
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t("URL. An example URL is '<em>http://www.example.com</em>'. You can also use '&lt;front&gt;' for the front page."),
  );


  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['misc']['cas_changePasswordURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Change password URL'),
    '#default_value' => variable_get('cas_changePasswordURL', ''),
    '#description' => t('The URL users should use for changing their password.  Leave blank to use the standard Drupal page.'),
  );

  $form['misc']['cas_registerURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration URL'),
    '#default_value' => variable_get('cas_registerURL', ''),
    '#description' => t('The URL users should use for changing registering.  Leave blank to use the standard Drupal page.'),
  );

  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login form settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login']['cas_login_form'] = array(
    '#type' => 'radios',
    '#title' => t('Add CAS link to login forms'),
    '#default_value' => variable_get('cas_login_form', CAS_NO_LINK),
    '#options' => array(
      CAS_NO_LINK => t('Do not add link to login forms'),
      CAS_ADD_LINK => t('Add link to login forms'),
      CAS_MAKE_DEFAULT => t('Make CAS login default on login forms')),
  );

  $form['login']['cas_login_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS Login invitation'),
    '#default_value' => variable_get('cas_login_invite', CAS_LOGIN_INVITE_DEFAULT),
    '#size' => 55,
    '#maxlength' => 80,
    '#description' => t('Message users will see to invite them to log in with cas credentials .'),
  );

  $form['login']['cas_login_drupal_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('Drupal login invitation'),
    '#default_value' => variable_get('cas_login_drupal_invite', CAS_LOGIN_DRUPAL_INVITE_DEFAULT),
    '#size' => 55,
    '#maxlength' => 80,
    '#description' => t('Message users will see to invite them to log in with drupal credentials.'),
  );

  $form['login']['cas_login_redir_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirection notification message'),
    '#default_value' => variable_get('cas_login_redit_message', CAS_LOGIN_REDIR_MESSAGE),
    '#size' => 55,
    '#maxlength' => 80,
    '#description' => t('Message users see at the top of the cas login form to warn them that they are being redirected.'),
  );

  return system_settings_form($form);
}

/**
 * Validates the cas_admin_settings form.
 */
function cas_admin_settings_validate(&$form, &$form_state) {
  if (!module_exists('libraries')) {
    form_set_value($form['library']['cas_library_dir'], rtrim($form_state['values']['cas_library_dir'], '/'), $form_state);
  }
}

/**
 * Returns the version of phpCAS installed on the server.
 *
 * @param $dir
 *   A string containing the directory the CAS.php file resides in.
 * @param &$error
 *   Returns a human readable message as to why the version could not be
 *   retrieved, empty string if there are no errors.
 *
 * @return
 *   A string containing the version, FALSE on errors.
 */
function cas_library_version_get($dir, &$error = NULL) {
  $error = '';

  // Gets path to library directory, path to the CAS.php file.
  if ($dir != '')
    $dir  = rtrim($dir, '/') . '/';
  $filename = $dir . 'CAS.php';

  // Make sure that the library exists.
  if (_cas_include_exists($filename)) {
    require_once($filename);
  }
  else {
    $error = t('The phpCAS library was not found at %path', array('%path' => $filename));
    return FALSE;
  }

  // Verify that the class exists
  if (!class_exists('phpCAS')) {
    $error = t('The <em>CAS.php</em> file was loaded, but the <em>phpCAS</em> class was not found.');
    return FALSE;
  }

  // Retrieve the version
  if (!defined('PHPCAS_VERSION')) {
    $error = t('The phpCAS library was loaded, but the version could not be determined.');
  }
  return PHPCAS_VERSION;
}

/**
 * Checks that the library is installed in the location specified by loading the
 * class and extracting the version.
 *
 * @param $form_element
 *   The form element containing the "library" fieldset.
 * @param $form_state
 *   An array containing the form's state information.
 *
 * @return
 *   The modified form element containing the "library" fieldset.
 */
function cas_library_version_check($form_element, $form_state) {
  if ($version = cas_library_version_get($form_state['values']['cas_library_dir'], $error)) {
    $form_element['library']['cas_library_version'] = array(
      '#type' => 'item',
      '#title' => t('Library version'),
      '#markup' => '<pre>' . check_plain($version) . '</pre>',
      '#description' => t('The phpCAS library was loaded and returned this version information.'),
    );
  }
  else {
    $form_element['library'] = array(
      '#value' => '<p class="error">' . $error . '</p>',
    );
  }
  $form_element['library']['cas_library_version']['#type'] = 'item';
  return $form_element;
}

/**
 * Validates the CAS library version.
 *
 * @param $element
 *   An array containing the element being validated.
 *
 * @return
 *   A boolean flagging whether or not the element is valid.
 */
function cas_library_dir_validate($element) {
  if ($version = cas_library_version_get($element['#value'])) {
    return TRUE;
  }
  else {
    form_set_error($element['#parents'][0], t('CAS library directory not valid.'));
    return FALSE;
  }
}
