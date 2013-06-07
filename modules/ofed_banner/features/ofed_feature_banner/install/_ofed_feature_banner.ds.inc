<?php
/**
 * @file
 * ofed_feature_banner.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ofed_feature_banner_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_banner|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_banner';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'banner_image' => array(
      'weight' => '0',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Image',
        ),
      ),
    ),
  );
  $export['node|ofed_banner|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function ofed_feature_banner_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'banner_image';
  $ds_field->label = 'Banner (image only)';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_banner|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
$type = $entity->field_ofed_banner_type[\'und\'][0][\'value\'];
switch($type) {
case \'leadboard\':
$path = $entity->field_ofed_banner_img_leadboard[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_leadboard[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_leadboard[\'und\'][0][\'title\'];
break;
case \'button\':
$path = $entity->field_ofed_banner_img_button[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_button[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_button[\'und\'][0][\'title\'];
break;
case \'full\':
$path = $entity->field_ofed_banner_img_full[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_full[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_full[\'und\'][0][\'title\'];
break;
case \'srectangle\':
$path = $entity->field_ofed_banner_img_srectangle[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_srectangle[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_srectangle[\'und\'][0][\'title\'];
break;
case \'mrectangle\':
$path = $entity->field_ofed_banner_img_mrectangle[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_mrectangle[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_mrectangle[\'und\'][0][\'title\'];
break;
case \'skyscraper\':
$path = $entity->field_ofed_banner_img_skyscraper[\'und\'][0][\'uri\'];
$alt = $entity->field_ofed_banner_img_skyscraper[\'und\'][0][\'alt\'];
$title = $entity->field_ofed_banner_img_skyscraper[\'und\'][0][\'title\'];
break;
}
if(!empty($path)) {
print theme(\'image\', array(
      \'path\' => $path,
      \'alt\' => $alt,
      \'title\' => $title,
    ));
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['banner_image'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_banner_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_banner|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_banner';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'banner_image',
        1 => 'field_ofed_banner_link',
      ),
    ),
    'fields' => array(
      'banner_image' => 'ds_content',
      'field_ofed_banner_link' => 'ds_content',
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
  $export['node|ofed_banner|default'] = $ds_layout;

  return $export;
}
