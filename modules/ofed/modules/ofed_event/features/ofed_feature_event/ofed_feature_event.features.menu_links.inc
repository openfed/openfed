<?php
/**
 * @file
 * ofed_feature_event.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_event_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/events
  $menu_links['menu-cms-menu:cms/events'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/events',
    'router_path' => 'cms/events',
    'link_title' => 'Events',
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
  t('Events');


  return $menu_links;
}
