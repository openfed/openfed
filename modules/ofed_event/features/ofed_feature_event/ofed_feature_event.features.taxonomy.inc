<?php
/**
 * @file
 * ofed_feature_event.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_event_taxonomy_default_vocabularies() {
  return array(
    'ofed_event' => array(
      'name' => 'Event',
      'machine_name' => 'ofed_event',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
