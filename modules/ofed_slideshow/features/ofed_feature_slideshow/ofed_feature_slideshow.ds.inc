<?php
/**
 * @file
 * ofed_feature_slideshow.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_slideshow_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_slideshow|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_slideshow';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_slide_menu',
        1 => 'field_ofed_slide_images',
        2 => 'field_ofed_slide_link',
      ),
    ),
    'fields' => array(
      'field_ofed_slide_menu' => 'ds_content',
      'field_ofed_slide_images' => 'ds_content',
      'field_ofed_slide_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-slideshow ds-wrapper-slideshow-default default ',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_slideshow|default'] = $ds_layout;

  return $export;
}
