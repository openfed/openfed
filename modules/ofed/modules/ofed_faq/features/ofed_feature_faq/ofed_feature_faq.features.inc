<?php
/**
 * @file
 * ofed_feature_faq.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_faq_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_faq_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_faq_node_info() {
  $items = array(
    'ofed_faq' => array(
      'name' => t('FAQ'),
      'base' => 'node_content',
      'description' => t('Use <em>FAQ</em> to create an manage any frequently asked questions.'),
      'has_title' => '1',
      'title_label' => t('Question'),
      'help' => '',
    ),
  );
  return $items;
}
