<?php
/**
 * @file
 * ofed_feature_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_event_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ofed_feature_event_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_event_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_event_image.
  $styles['ofed_event_image'] = array(
    'name' => 'ofed_event_image',
    'effects' => array(
      6 => array(
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
        'weight' => '-10',
      ),
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
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
      8 => array(
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
          'path' => 'module://ofed/modules/ofed/modules/ofed_event/assets/images/transparent_150x150.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      9 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '150',
          'height' => '150',
          'anchor' => 'left-top',
        ),
        'weight' => '4',
      ),
    ),
  );

  // Exported image style: ofed_event_image_block_column.
  $styles['ofed_event_image_block_column'] = array(
    'name' => 'ofed_event_image_block_column',
    'effects' => array(
      6 => array(
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
        'weight' => '-10',
      ),
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
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
      8 => array(
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
          'path' => 'module://ofed/modules/assets/images/transparent_150x150.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      9 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '150',
          'height' => '150',
          'anchor' => 'left-top',
        ),
        'weight' => '4',
      ),
    ),
  );

  // Exported image style: ofed_event_image_block_info.
  $styles['ofed_event_image_block_info'] = array(
    'name' => 'ofed_event_image_block_info',
    'effects' => array(
      6 => array(
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
        'weight' => '-10',
      ),
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
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
      8 => array(
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
          'path' => 'module://ofed/modules/ofed_event/assets/images/transparent_150x150.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      9 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '150',
          'height' => '150',
          'anchor' => 'left-top',
        ),
        'weight' => '4',
      ),
    ),
  );

  // Exported image style: ofed_event_image_block_list.
  $styles['ofed_event_image_block_list'] = array(
    'name' => 'ofed_event_image_block_list',
    'effects' => array(
      6 => array(
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
        'weight' => '-10',
      ),
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
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
      8 => array(
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
          'path' => 'module://ofed/modules/ofed_event/assets/images/transparent_150x150.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      9 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '150',
          'height' => '150',
          'anchor' => 'left-top',
        ),
        'weight' => '4',
      ),
    ),
  );

  // Exported image style: ofed_event_image_page_list.
  $styles['ofed_event_image_page_list'] = array(
    'name' => 'ofed_event_image_page_list',
    'effects' => array(
      6 => array(
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
        'weight' => '-10',
      ),
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
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '-8',
      ),
      8 => array(
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
          'path' => 'module://ofed/modules/ofed_event/assets/images/transparent_150x150.png',
          'dimensions' => 'background',
        ),
        'weight' => '3',
      ),
      9 => array(
        'label' => 'Crop',
        'help' => 'Cropping will remove portions of an image to make it the specified dimensions.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => '150',
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
function ofed_feature_event_node_info() {
  $items = array(
    'ofed_event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Use <em>Event</em> to create an manage any event.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
