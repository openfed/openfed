<?php
/**
 * @file
 * ofed_feature_photogallery.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_photogallery_taxonomy_default_vocabularies() {
  return array(
    'ofed_photogallery' => array(
      'name' => 'Photos gallery',
      'machine_name' => 'ofed_photogallery',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
