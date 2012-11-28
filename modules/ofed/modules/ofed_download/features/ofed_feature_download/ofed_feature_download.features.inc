<?php
/**
 * @file
 * ofed_feature_download.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_download_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_download_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_download_node_info() {
  $items = array(
    'ofed_download' => array(
      'name' => t('Download'),
      'base' => 'node_content',
      'description' => t('Use <em>Download</em> to add many documents who can be downloaded by someone else.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
