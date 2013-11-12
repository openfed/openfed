<?php
/**
 * @file
 * ofed_slideshow.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_slideshow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_slideshow_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_slideshow_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_slideshow_images.
  $styles['ofed_slideshow_images'] = array(
    'name' => 'ofed_slideshow_images',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 438,
          'height' => 164,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_slideshow_images',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_slideshow_node_info() {
  $items = array(
    'ofed_slideshow' => array(
      'name' => t('Slideshow'),
      'base' => 'node_content',
      'description' => t('Use <em>Slideshow</em> to create mini slider gallery and add block on a region to show them.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}