<?php
/**
 * @file
 * ofed_feature_meeting.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_meeting_taxonomy_default_vocabularies() {
  return array(
    'ofed_meeting' => array(
      'name' => 'Meeting',
      'machine_name' => 'ofed_meeting',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
  );
}
