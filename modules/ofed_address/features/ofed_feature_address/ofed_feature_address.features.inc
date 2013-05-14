<?php
/**
 * @file
 * ofed_feature_address.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_address_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
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
function ofed_feature_address_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_address_node_info() {
  $items = array(
    'ofed_address' => array(
      'name' => t('Address'),
      'base' => 'node_content',
      'description' => t('Use <em>Address</em> to add an address who might be added to a content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
