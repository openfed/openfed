<?php

variable_set('linkchecker_action_status_code_301', FALSE);
variable_set('linkchecker_action_status_code_404', FALSE);
variable_set('linkchecker_check_links_interval', '2419200');
variable_set('linkchecker_check_links_types', FALSE);
variable_set('linkchecker_check_useragent', 'Drupal (+http://drupal.org/)');
variable_set('linkchecker_cleanup_links_last', '1353494078');

variable_set('linkchecker_disable_link_check_for_urls', "example.com
example.net
example.org");

variable_set('linkchecker_extract_from_a', TRUE);
variable_set('linkchecker_extract_from_audio', TRUE);
variable_set('linkchecker_extract_from_embed', TRUE);
variable_set('linkchecker_extract_from_iframe', TRUE);
variable_set('linkchecker_extract_from_img', TRUE);
variable_set('linkchecker_extract_from_object', TRUE);
variable_set('linkchecker_extract_from_video', TRUE);

variable_set('linkchecker_filter_blacklist', array(
  'ckeditor_link_filter' => 'ckeditor_link_filter',
  'filter_url' => 'filter_url',
  'filter_autop' => 'filter_autop',
  'filter_htmlcorrector' => 'filter_htmlcorrector',
  'table_altrow' => 0,
  'media_filter' => 0,
  'transliteration' => 0,
  'ds_code' => 0,
  'filter_html_escape' => 0,
  'filter_html' => 0,
));

variable_set('linkchecker_ignore_response_codes', "200
206
302
304
401
403");

variable_set('linkchecker_scan_blocks', TRUE);
variable_set('linkchecker_scan_comments', FALSE);
variable_set('linkchecker_scan_nodetypes', array());