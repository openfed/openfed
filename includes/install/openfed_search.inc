<?php


variable_set('search_active_modules', array( 'node' => 'node', 'ds_search' => 0, 'user' => 0 ));

variable_set('search_config', array(
  'forms' => array( 'toggle_forms' => 0, 'move_keyword_search' => 0, 'advanced_populate' => 0, 'remove_containing_wrapper' => 'default', 'advanced_expand' => 'default' ),
  'fields' => array(
    'containing_any' => array( 'remove' => 0, 'roles' => array( '1' => 0, '2' => 0, '3' => 0, '4' => 0, '5' => 0, '6' => 0, '7' => 0 ) ),
    'containing_phrase' => array( 'remove' => 1, 'roles' => array( '1' => 0, '2' => 0, '3' => 0, '4' => 0, '5' => 0, '6' => 0, '7' => 0 ) ),
    'containing_none' => array( 'remove' => 1, 'roles' => array( '1' => 0, '2' => 0, '3' => 0, '4' => 0, '5' => 0, '6' => 0, '7' => 0 ) ),
    'types' => array(
        'remove' => 1, 
        'roles' => array( '1' => 0, '2' => 0, '3' => 0, '4' => 0, '5' => 0, '6' => 0, '7' => 0 ), 
        'filter' => array( 'panel' => 0 ), 
        'groupings' => array()
    ),
    'category' => array( 'remove' => 0, 'roles' => array( '0' => 0, '1' => 0, '2' => 0, '3' => 0, '4' => 0, '5' => 0, '6' => 0, '7' => 0 ) )
  ),
  'restrictions' => array( 'admin_bypass' => 0 )
));


variable_set('search_config_string_overrides', array(
  'labels' => array(
    'basic' => '',
    'basic_with_keys' => '',
    'basic_submit' => '',
    'advanced_fieldset' => '',
    'advanced_fieldset_with_keys' => '',
    'advanced_any' => '',
    'advanced_phrase' => '',
    'advanced_none' => '',
    'advanced_type' => '',
    'advanced_language' => '',
    'advanced_submit' => ''
  ),
  'title_display' => array(
    'basic' => 'default',
    'advanced_any' => 'default',
    'advanced_phrase' => 'default',
    'advanced_none' => 'default',
    'advanced_type' => 'default',
    'advanced_language' => 'default'
  )
));

