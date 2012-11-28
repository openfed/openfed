<?php
/**
 * @file
 * ofed_feature_job.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ofed_feature_job_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cms-menu:cms/jobs
  $menu_links['menu-cms-menu:cms/jobs'] = array(
    'menu_name' => 'menu-cms-menu',
    'link_path' => 'cms/jobs',
    'router_path' => 'cms/jobs',
    'link_title' => 'Jobs',
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
  t('Jobs');


  return $menu_links;
}
