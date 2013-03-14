<?php
/**
 * @file
 * administration configuration.
 */

/**
 * Configuration page of the WAIA Integration module.
 */
function waia_integration_admin() {
  $form = array();

  $form['waia_integration_url'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Url'),
    '#default_value'    => variable_get('waia_integration_url', ''),
    '#description'      => t('Url to generated WAIA javascript file.'),
    '#required'         => TRUE,
    '#maxlength'        => 255,
  );

  return system_settings_form($form);
}
