<?php
/**
 * @file
 * ofed_feature_new.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_new_taxonomy_default_vocabularies() {
  return array(
    'ofed_news' => array(
      'name' => 'News',
      'machine_name' => 'ofed_news',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
