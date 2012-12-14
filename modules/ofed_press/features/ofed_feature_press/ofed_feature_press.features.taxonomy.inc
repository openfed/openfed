<?php
/**
 * @file
 * ofed_feature_press.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_press_taxonomy_default_vocabularies() {
  return array(
    'ofed_press' => array(
      'name' => 'Press',
      'machine_name' => 'ofed_press',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
