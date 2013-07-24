<?php
/**
 * @file
 * ofed_feature_apache_solr.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function ofed_feature_apache_solr_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'solr';
  $environment->name = 'Main server';
  $environment->url = 'http://hostname:port/solr/corename';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_index_last' => array(),
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'ofed_address',
      1 => 'ofed_banner',
      2 => 'ofed_download',
      3 => 'ofed_event',
      4 => 'ofed_faq',
      5 => 'ofed_job',
      6 => 'ofed_meeting',
      7 => 'ofed_news',
      8 => 'ofed_page',
      9 => 'ofed_photogallery',
      10 => 'ofed_press',
      11 => 'ofed_slider',
      12 => 'ofed_slideshow',
      13 => 'ofed_team',
      14 => 'ofed_video',
      15 => 'webform',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
