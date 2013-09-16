<?php
/**
 * @file
 * ofed_feature_video.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_video_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_video_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_video_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_video_thumb.
  $styles['ofed_video_thumb'] = array(
    'name' => 'ofed_video_thumb',
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
          'width' => 150,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
    'label' => 'ofed_video_thumb',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_video_node_info() {
  $items = array(
    'ofed_video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => t('Use <em>Video</em> to create an manage any video.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
