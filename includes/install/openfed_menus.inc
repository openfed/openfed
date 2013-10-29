<?php

/**
 * @file
 * Sets up Menus during install.
 */

$menus = menu_get_menus(FALSE);
// Create a CMS Menu if it did not exist yet.
if (!isset($menus['menu-cms-menu'])) {
  menu_save(array(
    'menu_name' => 'menu-cms-menu',
    'title' => 'CMS Menu',
    'description' => '',
  ));
}

// Update the menu router information.
menu_rebuild();

// Set the CMS path to use the admin theme.
$admin_theme = variable_get('admin_theme_path', '');
if (empty($admin_theme) || strpos('cms' . PHP_EOL . 'cms/*', $admin_theme) === FALSE) {
  variable_set('admin_theme_path', $admin_theme . PHP_EOL . 'cms' . PHP_EOL . 'cms/*');
}
