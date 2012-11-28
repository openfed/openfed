<?php
/**
 * @file
 * ofed_feature_banner.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_banner_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/banners
  $menu_links['menu-cms-menu:cms/banners'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/banners',
    'router_path' => 'cms/banners',
    'link_title' => 'Banners',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Banners');


  return $menu_links;
}
