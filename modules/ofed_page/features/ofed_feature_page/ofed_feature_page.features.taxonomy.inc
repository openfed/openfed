<?php
/**
 * @file
 * ofed_feature_page.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_page_taxonomy_default_vocabularies() {
  return array(
    'ofed_page' => array(
      'name' => 'Page',
      'machine_name' => 'ofed_page',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
