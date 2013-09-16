<?php
/**
 * @file
 * ofed_feature_banner.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_banner_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_banner_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_banner_node_info() {
  $items = array(
    'ofed_banner' => array(
      'name' => t('Banner'),
      'base' => 'node_content',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
