<?php
/**
 * @file
 * ofed_feature_ad.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_ad_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/ads
  $menu_links['menu-cms-menu:cms/ads'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/ads',
    'router_path' => 'cms/ads',
    'link_title' => 'Ads',
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
  t('Ads');


  return $menu_links;
}
