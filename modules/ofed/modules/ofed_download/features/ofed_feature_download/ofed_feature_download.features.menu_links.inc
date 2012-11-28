<?php
/**
 * @file
 * ofed_feature_download.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_download_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/downloads
  $menu_links['menu-cms-menu:cms/downloads'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/downloads',
    'router_path' => 'cms/downloads',
    'link_title' => 'Downloads',
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
  t('Downloads');


  return $menu_links;
}
