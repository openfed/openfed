<?php
/**
 * @file
 * ofed_feature_page.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_page_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/pages
  $menu_links['menu-cms-menu:cms/pages'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/pages',
    'router_path' => 'cms/pages',
    'link_title' => 'Pages',
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
  t('Pages');


  return $menu_links;
}
