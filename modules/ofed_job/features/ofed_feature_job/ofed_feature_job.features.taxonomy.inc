<?php
/**
 * @file
 * ofed_feature_job.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ofed_feature_job_taxonomy_default_vocabularies() {
  return array(
    'ofed_job' => array(
      'name' => 'Job',
      'machine_name' => 'ofed_job',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
    'ofed_job_experience' => array(
      'name' => 'Job experience',
      'machine_name' => 'ofed_job_experience',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
    'ofed_job_occupation' => array(
      'name' => 'Job occupation',
      'machine_name' => 'ofed_job_occupation',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
    'ofed_job_study_level' => array(
      'name' => 'Job study level',
      'machine_name' => 'ofed_job_study_level',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'language' => 'und',
      'i18n_mode' => 4,
    ),
  );
}