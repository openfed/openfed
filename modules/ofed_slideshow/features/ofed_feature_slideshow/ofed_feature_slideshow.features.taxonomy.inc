<?php
/**
 * @file
 * ofed_feature_slideshow.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_slideshow_taxonomy_default_vocabularies() {
  return array(
    'ofed_slideshow' => array(
      'name' => 'Slideshow',
      'machine_name' => 'ofed_slideshow',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
