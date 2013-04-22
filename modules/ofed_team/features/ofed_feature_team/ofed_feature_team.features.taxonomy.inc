<?php
/**
 * @file
 * ofed_feature_team.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_team_taxonomy_default_vocabularies() {
  return array(
    'ofed_team' => array(
      'name' => 'Team members',
      'machine_name' => 'ofed_team',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
    'ofed_team_civility' => array(
      'name' => 'Team members civility',
      'machine_name' => 'ofed_team_civility',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
    'ofed_team_gender' => array(
      'name' => 'Team members gender',
      'machine_name' => 'ofed_team_gender',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'language' => 'und',
      'i18n_mode' => '4',
    ),
  );
}
