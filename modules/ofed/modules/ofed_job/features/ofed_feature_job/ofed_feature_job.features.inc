<?php
/**
 * @file
 * ofed_feature_job.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_job_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_job_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_job_node_info() {
  $items = array(
    'ofed_job' => array(
      'name' => t('Job'),
      'base' => 'node_content',
      'description' => t('Use <em>Job</em> to create an manage any jobs.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
