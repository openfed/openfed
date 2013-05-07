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
    'address' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
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
  );
  $export['node|ofed_address|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function ofed_feature_address_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'address';
  $ds_field->label = 'Address';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_address|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
$street = (!empty($entity->field_ofed_address_street[\'und\'][0][\'safe_value\'])) ? $entity->field_ofed_address_street[\'und\'][0][\'safe_value\'] : FALSE;
$number = (!empty($entity->field_ofed_address_number[\'und\'][0][\'safe_value\'])) ? $entity->field_ofed_address_number[\'und\'][0][\'safe_value\'] : FALSE;
$bus = (!empty($entity->field_ofed_address_bus[\'und\'][0][\'safe_value\'])) ? $entity->field_ofed_address_bus[\'und\'][0][\'safe_value\'] : FALSE;
$zip = (!empty($entity->field_ofed_address_zip[\'und\'][0][\'safe_value\'])) ? $entity->field_ofed_address_zip[\'und\'][0][\'safe_value\'] : FALSE;
$city = (!empty($entity->field_ofed_address_city[\'und\'][0][\'safe_value\'])) ? $entity->field_ofed_address_city[\'und\'][0][\'safe_value\'] : FALSE;
$country = (!empty($entity->field_ofed_address_country[\'und\'][0][\'iso2\'])) ? country_load($entity->field_ofed_address_country[\'und\'][0][\'iso2\']) : FALSE;
if($number) {
  if($bus) {
    $number = $number . \'/\' . $bus;
  }
}
$line = array();
$lines[0] = trim($street . \' \' . $number);
$lines[1] = trim($zip . \' \' . $city);
if($country) {
  $lines[2] = trim(countries_t($country));
}
foreach($lines as $key => $value) {
if(empty($value)) {
unset($lines[$key]);
}
}
print \'<address>\' . implode(\'<br>\', $lines)  . \'</address>\';
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['address'] = $ds_field;

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
        0 => 'address',
        1 => 'field_ofed_address_name',
        2 => 'field_ofed_address_email',
        3 => 'field_ofed_address_phone',
        4 => 'field_ofed_address_opening_hours',
        5 => 'field_ofed_address_map',
        6 => 'field_ofed_address_directions',
      ),
    ),
    'fields' => array(
      'address' => 'ds_content',
      'field_ofed_address_name' => 'ds_content',
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
  $export['node|ofed_address|default'] = $ds_layout;

  return $export;
}
