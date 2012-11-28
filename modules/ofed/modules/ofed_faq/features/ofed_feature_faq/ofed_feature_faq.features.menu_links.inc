<?php
/**
 * @file
 * ofed_feature_faq.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_faq_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/faqs
  $menu_links['menu-cms-menu:cms/faqs'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/faqs',
    'router_path' => 'cms/faqs',
    'link_title' => 'FAQ\'s',
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
  t('FAQ\'s');


  return $menu_links;
}
