<?php

/**
 * @file
 * Needs to be documented.
 */

$menus = menu_get_menus(FALSE);
if (!isset($menus['menu-cms-menu'])) {
  // Create a CMS Menu if not exist.
  menu_save(array(
    'menu_name' => 'menu-cms-menu',
    'title' => 'CMS Menu',
    'description' => '',
  ));
}

// Update the menu router information.
menu_rebuild();

// Set cms path to use admin theme.
$admin_theme = variable_get('admin_theme_path', '');
if (empty($admin_theme) || strpos('cms' . PHP_EOL . 'cms/*', $admin_theme) === FALSE) {
  variable_set('admin_theme_path', $admin_theme . PHP_EOL . 'cms' . PHP_EOL . 'cms/*');
}
