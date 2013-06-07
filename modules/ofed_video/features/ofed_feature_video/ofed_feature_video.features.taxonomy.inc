<?php
/**
 * @file
 * ofed_feature_video.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_video_taxonomy_default_vocabularies() {
  return array(
    'ofed_video' => array(
      'name' => 'Video',
      'machine_name' => 'ofed_video',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
  );
}
