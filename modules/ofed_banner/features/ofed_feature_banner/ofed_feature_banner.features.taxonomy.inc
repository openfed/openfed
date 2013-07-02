<?php
/**
 * @file
 * ofed_feature_banner.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_banner_taxonomy_default_vocabularies() {
  return array(
    'ofed_banner' => array(
      'name' => 'Banner',
      'machine_name' => 'ofed_banner',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
  );
}