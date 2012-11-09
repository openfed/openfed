<?php
/**
 * @file
 * ofed_feature_banner.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_banner_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_banner_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_banner_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_banner_images.
  $styles['ofed_banner_images'] = array(
    'name' => 'ofed_banner_images',
    'effects' => array(
      1 => array(
        'label' => 'Change file format',
        'help' => 'Choose to save the image as a different file type.',
        'effect callback' => 'coloractions_convert_image',
        'dimensions passthrough' => TRUE,
        'form callback' => 'coloractions_convert_form',
        'summary theme' => 'coloractions_convert_summary',
        'module' => 'imagecache_coloractions',
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/png',
          'quality' => '75',
        ),
        'weight' => '1',
      ),
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
          'width' => '400',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
      3 => array(
        'label' => 'Underlay (background)',
        'help' => 'Choose the file image you wish to use as an background, and position the processed image on it.',
        'effect callback' => 'canvasactions_canvas2file_image',
        'dimensions callback' => 'canvasactions_canvas2file_dimensions',
        'form callback' => 'canvasactions_canvas2file_form',
        'summary theme' => 'canvasactions_canvas2file_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_canvas2file',
        'data' => array(
          'xpos' => 0,
          'ypos' => 0,
          'alpha' => '100',
          'path' => 'module://ofed/modules/ofed_banner/assets/images/transparent_400x300.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      4 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '400',
          'height' => '150',
          'anchor' => 'left-top',
        ),
        'weight' => '4',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_banner_node_info() {
  $items = array(
    'ofed_banner' => array(
      'name' => t('Banner'),
      'base' => 'node_content',
      'description' => t('Use <em>Banner</em> to create mini slider gallery and add block on a region to show them.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
