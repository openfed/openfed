<?php
/**
 * @file
 * ofed_feature_photo.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_photo_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/photos
  $menu_links['menu-cms-menu:cms/photos'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/photos',
    'router_path' => 'cms/photos',
    'link_title' => 'Photos',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Photos');


  return $menu_links;
}
