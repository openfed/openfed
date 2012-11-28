<?php
/**
 * @file
 * ofed_feature_document.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_document_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/documents
  $menu_links['menu-cms-menu:cms/documents'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/documents',
    'router_path' => 'cms/documents',
    'link_title' => 'Documents',
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
  t('Documents');


  return $menu_links;
}
