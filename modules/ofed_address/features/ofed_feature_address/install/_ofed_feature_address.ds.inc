<?php
/**
 * @file
 * ofed_feature_address.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ofed_feature_address_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_address|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_address';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'field_ofed_address_phone' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fis' => TRUE,
          'fis-el' => 'div',
          'fis-cl' => 'field-name-field-ofed-address-phone',
          'fis-at' => '',
          'fis-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'field-phone-item',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => TRUE,
        ),
      ),
    ),
    'field_ofed_address_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_address|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_address|page_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_address';
  $ds_fieldsetting->view_mode = 'page_list';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_address_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_address|page_list'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_address_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_address|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_address';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_address_name',
        1 => 'field_ofed_address_street',
        2 => 'field_ofed_address_number',
        3 => 'field_ofed_address_bus',
        4 => 'field_ofed_address_zip',
        5 => 'field_ofed_address_city',
        6 => 'field_ofed_address_country',
        7 => 'field_ofed_address_email',
        8 => 'field_ofed_address_phone',
        9 => 'field_ofed_address_opening_hours',
        10 => 'field_ofed_address_map',
        11 => 'field_ofed_address_directions',
        12 => 'field_ofed_address_update',
      ),
    ),
    'fields' => array(
      'field_ofed_address_name' => 'ds_content',
      'field_ofed_address_street' => 'ds_content',
      'field_ofed_address_number' => 'ds_content',
      'field_ofed_address_bus' => 'ds_content',
      'field_ofed_address_zip' => 'ds_content',
      'field_ofed_address_city' => 'ds_content',
      'field_ofed_address_country' => 'ds_content',
      'field_ofed_address_email' => 'ds_content',
      'field_ofed_address_phone' => 'ds_content',
      'field_ofed_address_opening_hours' => 'ds_content',
      'field_ofed_address_map' => 'ds_content',
      'field_ofed_address_directions' => 'ds_content',
      'field_ofed_address_update' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_address|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_address|page_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_address';
  $ds_layout->view_mode = 'page_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_address_name',
        1 => 'field_ofed_address_street',
        2 => 'field_ofed_address_number',
        3 => 'field_ofed_address_bus',
        4 => 'field_ofed_address_zip',
        5 => 'field_ofed_address_city',
        6 => 'field_ofed_address_country',
        7 => 'field_ofed_address_update',
        8 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_ofed_address_name' => 'ds_content',
      'field_ofed_address_street' => 'ds_content',
      'field_ofed_address_number' => 'ds_content',
      'field_ofed_address_bus' => 'ds_content',
      'field_ofed_address_zip' => 'ds_content',
      'field_ofed_address_city' => 'ds_content',
      'field_ofed_address_country' => 'ds_content',
      'field_ofed_address_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_address|page_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_address|references';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_address';
  $ds_layout->view_mode = 'references';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_address_name',
        1 => 'field_ofed_address_street',
        2 => 'field_ofed_address_number',
        3 => 'field_ofed_address_bus',
        4 => 'field_ofed_address_zip',
        5 => 'field_ofed_address_city',
        6 => 'field_ofed_address_country',
        7 => 'field_ofed_address_email',
        8 => 'field_ofed_address_phone',
        9 => 'field_ofed_address_opening_hours',
        10 => 'field_ofed_address_map',
        11 => 'field_ofed_address_directions',
      ),
    ),
    'fields' => array(
      'field_ofed_address_name' => 'ds_content',
      'field_ofed_address_street' => 'ds_content',
      'field_ofed_address_number' => 'ds_content',
      'field_ofed_address_bus' => 'ds_content',
      'field_ofed_address_zip' => 'ds_content',
      'field_ofed_address_city' => 'ds_content',
      'field_ofed_address_country' => 'ds_content',
      'field_ofed_address_email' => 'ds_content',
      'field_ofed_address_phone' => 'ds_content',
      'field_ofed_address_opening_hours' => 'ds_content',
      'field_ofed_address_map' => 'ds_content',
      'field_ofed_address_directions' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_address|references'] = $ds_layout;

  return $export;
}
