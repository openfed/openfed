<?php

/**
 * Return the form for complete set up
 * @return array 
 */
function openfed_complete() {
  $enable = array(
    'theme_default' => openfed_return_default_front_theme_name(),
    'admin_theme' => openfed_return_default_backend_theme_name(),
    'maintenance_theme' => openfed_return_default_maintenance_theme_name(),
  );
  theme_enable($enable);

  foreach ($enable as $var => $theme) {
    if (!is_numeric($var)) {
      variable_set($var, $theme);
    }
  }
  // Disable the default Bartik theme
  theme_disable(array('bartik', 'seven'));

  variable_set('node_admin_theme', '1');

  variable_set('admin_theme_admin_theme_batch', '0');
  variable_set( 'cron_safe_threshold', '0');
 
  $settings['maintenance_theme']  = "maintenance";
  drupal_rewrite_settings($settings);
  
  node_access_rebuild(FALSE);
}