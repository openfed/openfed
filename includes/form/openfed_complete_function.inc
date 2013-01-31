<?php

/**
 * Return the form for complete set up
 * @return array 
 */
function openfed_complete() {
  // Set theme variable
  $enable = array(
    'theme_default'     => openfed_return_default_front_theme_name(),
    'admin_theme'       => openfed_return_default_backend_theme_name(),
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

  // set admin theme for node edit
  variable_set('node_admin_theme', '1');

  // desactive admin theme for batch action
  variable_set('admin_theme_admin_theme_batch', '0');

  // desactive cron on launch
  variable_set( 'cron_safe_threshold', '0');
 
  // set menu options for content type
  $menu_options_ofed_page = variable_get('menu_options_ofed_page', array());
  $menu_options_webform = variable_get('menu_options_webform', array());
  
  // add menu list where menu can be attach to content
  $menus     = menu_get_menus(FALSE);
  $menu_list = _openfed_return_menu_list();
  foreach( $menu_list as $key => $desc ) {
    if (array_key_exists($key, $menus) ) {
      if (!in_array($key, $menu_options_ofed_page) ) $menu_options_ofed_page[] = $key;
      if (!in_array($key, $menu_options_webform) ) $menu_options_webform[] = $key;
    }
  }
  foreach( language_list() as $lang ) {
    $name = strtolower('main-'.$lang->name.'-menu');
    if (array_key_exists( $name, $menus) ) {
      if (!in_array($key, $menu_options_ofed_page) ) $menu_options_ofed_page[] = $name;
      if (!in_array($key, $menu_options_webform) ) $menu_options_webform[] = $name;
    }
  }
  variable_set( 'menu_options_ofed_page', $menu_options_ofed_page );
  variable_set( 'menu_options_webform', $menu_options_webform );
  
  // rebuild access to node
  node_access_rebuild(FALSE);
}