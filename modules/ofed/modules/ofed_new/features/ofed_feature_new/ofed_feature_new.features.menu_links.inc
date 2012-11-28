<?php
/**
 * @file
 * ofed_feature_new.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_new_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/news
  $menu_links['menu-cms-menu:cms/news'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/news',
    'router_path' => 'cms/news',
    'link_title' => 'News',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('News');


  return $menu_links;
}
