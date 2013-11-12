<?php
/**
 * @file
 * ofed_download.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_download_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
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
function ofed_download_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function ofed_download_flag_default_flags() {
  $flags = array();
  // Exported flag: "Download: Hide item from lists and blocks".
  $flags['download_hide'] = array(
    'content_type' => 'node',
    'title' => 'Download: Hide item from lists and blocks',
    'global' => 0,
    'types' => array(
      0 => 'ofed_download',
    ),
    'flag_short' => 'Hide item from lists and blocks.',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Show item in lists and blocks.',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
        1 => 3,
        2 => 4,
        3 => 5,
        4 => 6,
      ),
      'unflag' => array(
        0 => 2,
        1 => 3,
        2 => 4,
        3 => 5,
        4 => 6,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'ofed_download',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function ofed_download_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_download_thumb.
  $styles['ofed_download_thumb'] = array(
    'name' => 'ofed_download_thumb',
    'label' => 'ofed_download_thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 150,
          'height' => 150,
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
function ofed_download_node_info() {
  $items = array(
    'ofed_download' => array(
      'name' => t('Download'),
      'base' => 'node_content',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}