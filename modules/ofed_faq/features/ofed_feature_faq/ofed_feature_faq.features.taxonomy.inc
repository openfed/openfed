<?php
/**
 * @file
 * ofed_feature_faq.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_faq_taxonomy_default_vocabularies() {
  return array(
    'ofed_faq' => array(
      'name' => 'FAQ',
      'machine_name' => 'ofed_faq',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
  );
}
