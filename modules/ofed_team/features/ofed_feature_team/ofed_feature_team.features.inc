<?php
/**
 * @file
 * ofed_feature_team.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_team_ctools_plugin_api() {
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
function ofed_feature_team_views_api() {
  return array("version" => "3.0");
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
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '125',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: ofed_team_thumb_block_column.
  $styles['ofed_team_thumb_block_column'] = array(
    'name' => 'ofed_team_thumb_block_column',
    'effects' => array(
      4 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '125',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: ofed_team_thumb_block_list.
  $styles['ofed_team_thumb_block_list'] = array(
    'name' => 'ofed_team_thumb_block_list',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '125',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: ofed_team_thumb_block_teaser.
  $styles['ofed_team_thumb_block_teaser'] = array(
    'name' => 'ofed_team_thumb_block_teaser',
    'effects' => array(
      8 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '125',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
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
          'width' => '125',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
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
      'description' => t('Use <em>Team members</em> to create an manage any members of the team memebers.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
