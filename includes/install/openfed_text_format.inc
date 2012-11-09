<?php

$filtered_html_format = array(
  'format' => 'filtered_html',
  'name' => 'Filtered HTML',
  'status' => 1,
  'weight' => 0,
  'filters' => array(
    // URL filter.
    'filter_url' => array(
      'weight' => 0,
      'status' => 1,
    ),
    // HTML filter.
    'filter_html' => array(
      'weight' => 1,
      'status' => 1,
    ),
    // Line break filter.
    'filter_autop' => array(
      'weight' => 2,
      'status' => 1,
    ),
    // HTML corrector filter.
    'filter_htmlcorrector' => array(
      'weight' => 10,
      'status' => 1,
    ),
  ),
);
if (module_exists('ckeditor_link') ) {
  // HTML corrector filter.
  $full_html_format['filters']['ckeditor_link_filter'] = array(
    'weight' => 8,
    'status' => 1,
  );
}
if (module_exists('table_altrow') ) {
  // Add odd/even on table row
  $full_html_format['filters']['table_altrow'] = array(
    'weight' => 9,
    'status' => 1,
  );
}
$filtered_html_format = (object) $filtered_html_format;
filter_format_save($filtered_html_format);




$full_html_format = array(
  'format' => 'full_html',
  'name' => 'Full HTML',
  'status' => 1,
  'weight' => 1,
  'filters' => array(
    // URL filter.
    'filter_url' => array(
      'weight' => 0,
      'status' => 1,
    ),
    // Line break filter.
    'filter_autop' => array(
      'weight' => 1,
      'status' => 1,
    ),
    // HTML corrector filter.
    'filter_htmlcorrector' => array(
      'weight' => 10,
      'status' => 1,
    ),
  ),
);
if (module_exists('ckeditor_link') ) {
  // HTML corrector filter.
  $full_html_format['filters']['ckeditor_link_filter'] = array(
    'weight' => 8,
    'status' => 1,
  );
}
if (module_exists('table_altrow') ) {
  // Add odd/even on table row
  $full_html_format['filters']['table_altrow'] = array(
    'weight' => 9,
    'status' => 1,
  );
}
$full_html_format = (object) $full_html_format;
filter_format_save($full_html_format);