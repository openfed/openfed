<?php

/**
 * @file Administration WAIA configuration.
 */

/**
 * Configuration page of the WAIA Integration module.
 */
function waia_integration_admin_form() {
  // Initialize.
  $form = array();

  // WAIA form.
  $form['waia_script_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('waia_script_url', ''),
    '#description' => t('URL to generated WAIA javascript file.'),
    '#required' => FALSE,
    '#maxlength' => 255,
  );

  // Return.
  return system_settings_form($form);
}

/**
 * Implementation of hook_validate.
 */
function waia_integration_admin_form_validate($form, &$form_state) {
  $url = $form_state['values']['waia_script_url'];
  if (!empty($url)) {
    // Validate the URL.
    $valid_url = _waia_integration_check_script_url($url);
    if (!$valid_url) {
      $message = check_plain(t('Unable to read the WAIA javascript file from the specified URL: !url', array('!url' => $url)));
      drupal_set_message($message, 'error');
      form_set_error('waia_script_url');
    }
  }
}