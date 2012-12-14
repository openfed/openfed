<?php
/**
 * @file
 * ofed_feature_download.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function ofed_feature_download_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'ofed_download';
  $path_breadcrumb->name = 'Downloads';
  $path_breadcrumb->path = 'downloads/%downloads';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Downloads',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'downloads',
      1 => '<none>',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'downloads' => array(
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
              'ofed_download' => 'ofed_download',
            ),
          ),
          'context' => 'downloads',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['ofed_download'] = $path_breadcrumb;

  return $export;
}
