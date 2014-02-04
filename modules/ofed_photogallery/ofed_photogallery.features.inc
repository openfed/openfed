<?php
/**
 * @file
 * ofed_photogallery.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_photogallery_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ofed_photogallery_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_photogallery_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_photogallery_images.
  $styles['ofed_photogallery_images'] = array(
    'name' => 'ofed_photogallery_images',
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
          'width' => 150,
          'height' => 150,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images',
  );

  // Exported image style: ofed_photogallery_images_gallery_large.
  $styles['ofed_photogallery_images_gallery_large'] = array(
    'name' => 'ofed_photogallery_images_gallery_large',
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
          'width' => 800,
          'height' => 600,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_gallery_large',
  );

  // Exported image style: ofed_photogallery_images_gallery_medium.
  $styles['ofed_photogallery_images_gallery_medium'] = array(
    'name' => 'ofed_photogallery_images_gallery_medium',
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
          'width' => 400,
          'height' => 300,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_gallery_medium',
  );

  // Exported image style: ofed_photogallery_images_slideshow_small.
  $styles['ofed_photogallery_images_slideshow_small'] = array(
    'name' => 'ofed_photogallery_images_slideshow_small',
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
          'width' => 92,
          'height' => 69,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_slideshow_small',
  );

  // Exported image style: ofed_photogallery_images_slideshow_medium.
  $styles['ofed_photogallery_images_slideshow_medium'] = array(
    'name' => 'ofed_photogallery_images_slideshow_medium',
    'effects' => array(
      6 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 400,
          'height' => 300,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_slideshow_medium',
  );

  // Exported image style: ofed_photogallery_images_slideshow_thumb_block_column.
  $styles['ofed_photogallery_images_slideshow_thumb_block_column'] = array(
    'name' => 'ofed_photogallery_images_slideshow_thumb_block_column',
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
          'width' => 284,
          'height' => 213,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_slideshow_thumb_block_column',
  );

  // Exported image style: ofed_photogallery_images_slideshow_thumb_block_element.
  $styles['ofed_photogallery_images_slideshow_thumb_block_element'] = array(
    'name' => 'ofed_photogallery_images_slideshow_thumb_block_element',
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
          'width' => 192,
          'height' => 147,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_slideshow_thumb_block_element',
  );

  // Exported image style: ofed_photogallery_images_slideshow_thumb_page_list.
  $styles['ofed_photogallery_images_slideshow_thumb_page_list'] = array(
    'name' => 'ofed_photogallery_images_slideshow_thumb_page_list',
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
          'width' => 400,
          'height' => 300,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
    'label' => 'ofed_photogallery_images_slideshow_thumb_page_list',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_photogallery_node_info() {
  $items = array(
    'ofed_photogallery' => array(
      'name' => t('Photo gallery'),
      'base' => 'node_content',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
