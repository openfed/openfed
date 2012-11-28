<?php
/**
 * @file
 * ofed_feature_blog.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_blog_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/blogs
  $menu_links['menu-cms-menu:cms/blogs'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/blogs',
    'router_path' => 'cms/blogs',
    'link_title' => 'Blogs',
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
  t('Blogs');


  return $menu_links;
}
