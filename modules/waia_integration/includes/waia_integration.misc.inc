<?php

/**
 * @file WAIA miscellaneous functions.
 */

/**
 * Check if the URL is valid or not.
 */
function _waia_integration_check_script_url($url) {
  // Get the HTTP request and the file extenssion.
  $result = drupal_http_request($url);
  // Check if the respond code is allowed.
  if (!preg_match('#^(2|3)#', $result->code) || !preg_match('#\.js$#', basename($url))) {
    // Set the variable.
    variable_set('waia_script_url_validated', FALSE);
    // Return.
    return FALSE;
  }

  // Set the variable.
  variable_set('waia_script_url_validated', TRUE);
  // Return.    
  return TRUE;
}