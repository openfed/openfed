<?php
/**
 * @file
 * ofed_feature_video.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_video_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_video_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_video_node_info() {
  $items = array(
    'ofed_video' => array(
      'name' => t('Videos'),
      'base' => 'node_content',
      'description' => t('Use <em>Videos</em> to create an manage any videos galeries.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
