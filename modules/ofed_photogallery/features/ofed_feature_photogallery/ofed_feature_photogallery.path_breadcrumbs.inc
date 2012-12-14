<?php
/**
 * @file
 * ofed_feature_photogallery.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function ofed_feature_photogallery_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'ofed_photogallery';
  $path_breadcrumb->name = 'Photos galleries';
  $path_breadcrumb->path = 'photos-galleries/%photos-galleries';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Photos galleries',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'photos-galleries',
      1 => '<none>',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'photos-galleries' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'ofed_photogallery' => 'ofed_photogallery',
            ),
          ),
          'context' => 'photos-galleries',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['ofed_photogallery'] = $path_breadcrumb;

  return $export;
}
