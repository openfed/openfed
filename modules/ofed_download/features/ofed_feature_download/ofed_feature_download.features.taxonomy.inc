<?php
/**
 * @file
 * ofed_feature_download.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_download_taxonomy_default_vocabularies() {
  return array(
    'ofed_download' => array(
      'name' => 'Download',
      'machine_name' => 'ofed_download',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
