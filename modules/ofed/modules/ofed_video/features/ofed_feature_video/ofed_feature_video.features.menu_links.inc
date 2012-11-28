<?php
/**
 * @file
 * ofed_feature_video.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_video_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/videos
  $menu_links['menu-cms-menu:cms/videos'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/videos',
    'router_path' => 'cms/videos',
    'link_title' => 'Videos',
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
  t('Videos');


  return $menu_links;
}
