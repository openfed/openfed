<?php
/**
 * @file
 * ofed_feature_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_page_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_page_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_page_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_page_thumb.
  $styles['ofed_page_thumb'] = array(
    'name' => 'ofed_page_thumb',
    'effects' => array(
      7 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '150',
          'height' => '150',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_page_node_info() {
  $items = array(
    'ofed_page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('Use <em>Page</em> to create an manage any page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
