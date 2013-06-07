<?php
/**
 * @file
 * custom method to return list of fields form a serialized variable.
 */

/**
 * Clean the variable and return an array of fields.
 */
function _addemar_subscription_addemar_fields() {
  $fields = variable_get('addemar_subscription_addemar_fields', '');

  if (!empty($fields)) {
    $fields = explode("\n", $fields);
    $fields = array_map('trim', $fields);
  }

  return $fields;
}

function _addemar_subscription_add_more_newsletter($form, $form_state) {
  return $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'];
}

function _addemar_subscription_add_more_newsletter_form($key, $weight, $group = 0, $description = '') {
  $form = array();
  $pos = $weight;

  $form = array(
    '#tree' => TRUE,
    '#weight' => $weight++,
  );

  $form['open_newsletter_wrapper'] = array(
    '#markup' => '<div class="newsletter_wrapper"><h2>' . t('Newsletter ') . $pos . '</h2>',
    '#weight' => $weight++,
  );

  $form['group_id'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Group ID'),
    '#default_value'    => $group,
    '#description'      => t("Insert the id's of the contact groups to which you want to subscribe via this form as a value, separated by comma's.<br/> If you leave the value empty, the contact will just be added to the contacts list.<br/> If you fill in the contact group id’s, the contact will be added to the general contacts list but also to the corresponding contact groups."),
    '#required'         => $pos == 1,
    '#element_validate' => array('element_validate_integer'),
    '#weight' => $weight++,
    '#parents' => array('addemar_subscription_groups', $key, 'group_id'),
  );

  $form['description'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Newsletter description'),
    '#default_value'    => $description,
    '#required'         => $pos == 1,
    '#weight' => $weight++,
    '#parents' => array('addemar_subscription_groups', $key, 'description'),
  );

  $form['close_newsletter_wrapper'] = array(
    '#markup' => '</div>',
    '#weight' => $weight++,
  );

  return $form;
}

function _addemar_subscription_get_soap_client($wsdl) {
  $sClient = FALSE;

  if (extension_loaded('soap')) {
    // If the wsdl is wrong or unreachable, there is an uncatchable Fatal Error.
    // So we will use a custom error handler to catch any issue related to the wsdl
    // and throw a SoapFault.
    $old_error_handler = set_error_handler('_addemar_subscription_error_handler');

    try{
      // Make use of @ to avoid the display of the fatal error
      $sClient = @new SoapClient($wsdl, array('exceptions' => 1));
    }
    catch(SoapFault $E) {
      $msg = t('The Addemar subscription WSDL is not properly configured. If you are using https, check that php_openssl is enabled.');
      drupal_set_message($msg, 'error');
      watchdog('error', $msg);
      $sClient = FALSE;
    }
    set_error_handler($old_error_handler);
  }

  return $sClient;
}

function _addemar_subscription_error_handler($errno, $errstr, $errfile, $errline) {
  // If we enter here, there is something wrong with the wsdl,
  // it can be a notice or a warning or anything else. It all ends up in
  // a fatal error, so we throw a SoapFault
  throw new SoapFault($errstr, null);
}