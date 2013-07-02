<?php
/**
 * @file
 * ofed_feature_job.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ofed_feature_job_ctools_plugin_api() {
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
function ofed_feature_job_views_api() {
  return array("api" => "3.0");
}


/**
 * Implements hook_image_default_styles().
 */
function ofed_feature_job_image_default_styles() {
  $styles = array();

  // Exported image style: ofed_job_thumb.
  $styles['ofed_job_thumb'] = array(
    'name' => 'ofed_job_thumb',
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
  );

  // Exported image style: ofed_job_thumb_block_column.
  $styles['ofed_job_thumb_block_column'] = array(
    'name' => 'ofed_job_thumb_block_column',
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
  );

  // Exported image style: ofed_job_thumb_block_element.
  $styles['ofed_job_thumb_block_element'] = array(
    'name' => 'ofed_job_thumb_block_element',
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
  );

  // Exported image style: ofed_job_thumb_block_list.
  $styles['ofed_job_thumb_block_list'] = array(
    'name' => 'ofed_job_thumb_block_list',
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
  );

  // Exported image style: ofed_job_thumb_block_teaser.
  $styles['ofed_job_thumb_block_teaser'] = array(
    'name' => 'ofed_job_thumb_block_teaser',
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
  );

  // Exported image style: ofed_job_thumb_page_list.
  $styles['ofed_job_thumb_page_list'] = array(
    'name' => 'ofed_job_thumb_page_list',
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
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ofed_feature_job_node_info() {
  $items = array(
    'ofed_job' => array(
      'name' => t('Job'),
      'base' => 'node_content',
      'description' => t('Use <em>Job</em> to create an manage any job.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}