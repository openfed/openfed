<?php
/**
 * @file
 * ofed_banner.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_banner_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ofed_banner_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_banner_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_banner_button.
  $styles['ofed_banner_button'] = array(
    'name' => 'ofed_banner_button',
    'label' => 'ofed_banner_button',
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
          'width' => 180,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: ofed_banner_full.
  $styles['ofed_banner_full'] = array(
    'name' => 'ofed_banner_full',
    'label' => 'ofed_banner_full',
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
          'width' => 420,
          'height' => 60,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: ofed_banner_leaderboard.
  $styles['ofed_banner_leaderboard'] = array(
    'name' => 'ofed_banner_leaderboard',
    'label' => 'ofed_banner_leaderboard',
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
          'width' => 728,
          'height' => 90,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: ofed_banner_medium_rectangle.
  $styles['ofed_banner_medium_rectangle'] = array(
    'name' => 'ofed_banner_medium_rectangle',
    'label' => 'ofed_banner_medium_rectangle',
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
          'width' => 300,
          'height' => 250,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: ofed_banner_square_rectangle.
  $styles['ofed_banner_square_rectangle'] = array(
    'name' => 'ofed_banner_square_rectangle',
    'label' => 'ofed_banner_square_rectangle',
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
          'width' => 250,
          'height' => 250,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: ofed_banner_wide_skyscraper.
  $styles['ofed_banner_wide_skyscraper'] = array(
    'name' => 'ofed_banner_wide_skyscraper',
    'label' => 'ofed_banner_wide_skyscraper',
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
          'width' => 160,
          'height' => 600,
          'upscale' => 0,
        ),
        'weight' => -8,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_banner_node_info() {
  $items = array(
    'ofed_banner' => array(
      'name' => t('Banner'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
