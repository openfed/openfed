<?php
/**
 * @file
 * ofed_feature_faq.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function ofed_feature_faq_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'ofed_faq';
  $path_breadcrumb->name = 'FAQ\'s';
  $path_breadcrumb->path = 'faqs/%faqs';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'FAQ\'s',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'faqs',
      1 => '<none>',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'faqs' => array(
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
              'ofed_faq' => 'ofed_faq',
            ),
          ),
          'context' => 'faqs',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['ofed_faq'] = $path_breadcrumb;

  return $export;
}
