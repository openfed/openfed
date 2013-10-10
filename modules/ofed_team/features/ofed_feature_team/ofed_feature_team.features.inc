<?php
/**
 * @file
 * ofed_feature_team.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_team_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ofed_feature_team_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_team_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_team_thumb.
  $styles['ofed_team_thumb'] = array(
    'name' => 'ofed_team_thumb',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 125,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_team_thumb',
  );

  // Exported image style: ofed_team_thumb_block_column.
  $styles['ofed_team_thumb_block_column'] = array(
    'name' => 'ofed_team_thumb_block_column',
    'effects' => array(
      12 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 125,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_team_thumb_block_column',
  );

  // Exported image style: ofed_team_thumb_block_list.
  $styles['ofed_team_thumb_block_list'] = array(
    'name' => 'ofed_team_thumb_block_list',
    'effects' => array(
      11 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 125,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_team_thumb_block_list',
  );

  // Exported image style: ofed_team_thumb_block_teaser.
  $styles['ofed_team_thumb_block_teaser'] = array(
    'name' => 'ofed_team_thumb_block_teaser',
    'effects' => array(
      9 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 125,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_team_thumb_block_teaser',
  );

  // Exported image style: ofed_team_thumb_page_list.
  $styles['ofed_team_thumb_page_list'] = array(
    'name' => 'ofed_team_thumb_page_list',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 125,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_team_thumb_page_list',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_team_node_info() {
  $items = array(
    'ofed_team' => array(
      'name' => t('Team members'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
