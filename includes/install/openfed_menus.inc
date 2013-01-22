<?php

$menus = menu_get_menus(FALSE);
if(!isset($menus['menu-cms-menu'])) {
  // Create a CMS Menu if not exist
  $menu = array();
  $menu['menu_name'] = "menu-cms-menu";
  $menu['title'] = "CMS Menu";
  $menu['description'] = "";
  menu_save($menu);
}

// Update the menu router information.
menu_rebuild();


// Set cms path to use admin theme
$admin_theme = variable_get('admin_theme_path', '');
if( empty($admin_theme) || strpos('cms' . PHP_EOL . 'cms/*', $admin_theme) === false) {
  variable_set('admin_theme_path', $admin_theme . PHP_EOL . 'cms' . PHP_EOL . 'cms/*');
}