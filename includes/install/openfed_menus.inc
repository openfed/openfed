<?php

// Create a Home link in the main menu.
$item = array(
  'link_title' => st('Home'),
  'link_path' => '<front>',
  'menu_name' => 'main-menu',
);
menu_link_save($item);

// Create a CMS Menu
$menu = array();
$menu['menu_name'] = "menu-cms-menu";
$menu['title'] = "CMS Menu";
$menu['description'] = "";
menu_save($menu);

// Update the menu router information.
menu_rebuild();


// Set cms path to use admin theme
if( empty($admin_theme) || strpos('cms' . PHP_EOL . 'cms/*', $admin_theme) === false) {
  variable_set('admin_theme_path', $admin_theme . PHP_EOL . 'cms' . PHP_EOL . 'cms/*');
}