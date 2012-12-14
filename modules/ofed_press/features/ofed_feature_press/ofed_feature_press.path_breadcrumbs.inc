<?php
/**
 * @file
 * ofed_feature_press.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function ofed_feature_press_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'ofed_press';
  $path_breadcrumb->name = 'Press';
  $path_breadcrumb->path = 'press/%press';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Press',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'press',
      1 => '<none>',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'press' => array(
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
              'ofed_press' => 'ofed_press',
            ),
          ),
          'context' => 'press',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['ofed_press'] = $path_breadcrumb;

  return $export;
}
