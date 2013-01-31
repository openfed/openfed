<?php
/**
 * @file
 * ofed_feature_download.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ofed_feature_download_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|block_column';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'block_column';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'ft' => array(
          'classes' => 'clear-block more',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|block_column'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|block_element';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'block_element';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'node_link' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block more',
        ),
      ),
    ),
  );
  $export['node|ofed_download|block_element'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|block_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'block_list';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
  );
  $export['node|ofed_download|block_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_open' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_persistent' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'url_file_save' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'links' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_download_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block headline',
        ),
      ),
    ),
    'field_ofed_download_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_open' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_persistent' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'url_file_save' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'links' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_download_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block headline',
        ),
      ),
    ),
    'field_ofed_download_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|page_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'page_list';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'node_link' => array(
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => '',
        'ft' => array(
          'classes' => 'more',
        ),
      ),
    ),
    'field_ofed_download_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|page_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|print';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'print';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_open' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_url_persistent' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'url_file_save' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h2',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_download_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|print'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|references';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'references';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'url_file_save' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => '',
        'class' => '',
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
  );
  $export['node|ofed_download|references'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|rss';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'rss';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h2',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'ft' => array(
          'classes' => 'more',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|rss'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|search_index';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'search_index';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_url_open' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_url_persistent' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'url_file_save' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h2',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|search_index'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|search_result';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'search_result';
  $ds_fieldsetting->settings = array(
    'file_size' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h2',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'node_link' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'ft' => array(
          'classes' => 'clear-block more',
        ),
      ),
    ),
    'field_ofed_download_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_download_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_download|search_result'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_download|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_download';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'node_link' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'ft' => array(
          'classes' => 'clear-block more',
        ),
      ),
    ),
  );
  $export['node|ofed_download|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function ofed_feature_download_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_name';
  $ds_field->label = 'File Name';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
  foreach($entity->field_ofed_download_file as $file) {
    $pathinfo = pathinfo($file["0"]["filename"]);
    echo "<span class=\\"file-name\\">".$pathinfo["filename"]."</span>";
  }
  ?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['file_name'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_size';
  $ds_field->label = 'File Size';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
  foreach($entity->field_ofed_download_file as $file) {
    echo "<span class=\\"file-size\\">".format_size($file["0"]["filesize"])."</span>";
  }
  ?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['file_size'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_type';
  $ds_field->label = 'File Type';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
  foreach($entity->field_ofed_download_file as $file) {
    $pathinfo = pathinfo($file["0"]["filename"]);
    echo "<span class=\\"file-type-".strip_tags($pathinfo["extension"])."\\">".strip_tags($pathinfo["extension"])."</span>";
  }
  ?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['file_type'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_url_open';
  $ds_field->label = 'File url open';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("View file"), file_create_url($file["0"]["uri"]), array("attributes" => array("class" => "file-url-open", "target" => "_blank", "title" => t("View file"))) );
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['file_url_open'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'file_url_persistent';
  $ds_field->label = 'File url persistent';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("Share file"), "download-file/".$entity->nid, array("attributes" => array("target" => "_blank", "title" => t("Share file"))) );
  echo "<span class=\\"url-file-persistent\\">".url("download-file/".$entity->nid, array("absolute" => TRUE))."</span>";
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['file_url_persistent'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'url_file_save';
  $ds_field->label = 'File url save';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'ofed_download|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("Save file"), "download-file/".$entity->nid, array("attributes" => array("class" => "file-url-save", "title" => t("Save file"))) );
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => FALSE,
  );
  $export['url_file_save'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_download_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|block_column';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'block_column';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_summary',
        6 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
  $export['node|ofed_download|block_column'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|block_element';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'block_element';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_download|block_element'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|block_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'block_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
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
  $export['node|ofed_download|block_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'file_type',
        1 => 'file_size',
        2 => 'field_ofed_download_author',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_summary',
        6 => 'field_ofed_download_thumb',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
        12 => 'links',
      ),
    ),
    'fields' => array(
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_body' => 'ds_content',
      'field_ofed_download_file' => 'ds_content',
      'file_url_open' => 'ds_content',
      'url_file_save' => 'ds_content',
      'file_url_persistent' => 'ds_content',
      'links' => 'ds_content',
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
  $export['node|ofed_download|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'file_type',
        1 => 'file_size',
        2 => 'field_ofed_download_author',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_summary',
        6 => 'field_ofed_download_thumb',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
        12 => 'links',
      ),
    ),
    'fields' => array(
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_body' => 'ds_content',
      'field_ofed_download_file' => 'ds_content',
      'file_url_open' => 'ds_content',
      'url_file_save' => 'ds_content',
      'file_url_persistent' => 'ds_content',
      'links' => 'ds_content',
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
  $export['node|ofed_download|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|page_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'page_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_author',
        6 => 'field_ofed_download_thumb',
        7 => 'field_ofed_download_summary',
        8 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
  $export['node|ofed_download|page_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|print';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'print';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_author',
        4 => 'field_ofed_download_pubdate',
        5 => 'field_ofed_download_update',
        6 => 'field_ofed_download_thumb',
        7 => 'field_ofed_download_summary',
        8 => 'field_ofed_download_body',
        9 => 'field_ofed_download_file',
        10 => 'file_url_open',
        11 => 'url_file_save',
        12 => 'file_url_persistent',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'field_ofed_download_body' => 'ds_content',
      'field_ofed_download_file' => 'ds_content',
      'file_url_open' => 'ds_content',
      'url_file_save' => 'ds_content',
      'file_url_persistent' => 'ds_content',
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
  $export['node|ofed_download|print'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|references';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'references';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'url_file_save',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'url_file_save' => 'ds_content',
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
  $export['node|ofed_download|references'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|rss';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'rss';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
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
  $export['node|ofed_download|rss'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|search_index';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'search_index';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_author',
        4 => 'field_ofed_download_pubdate',
        5 => 'field_ofed_download_update',
        6 => 'field_ofed_download_thumb',
        7 => 'field_ofed_download_summary',
        8 => 'field_ofed_download_body',
        9 => 'field_ofed_download_file',
        10 => 'file_url_open',
        11 => 'url_file_save',
        12 => 'file_url_persistent',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'field_ofed_download_body' => 'ds_content',
      'field_ofed_download_file' => 'ds_content',
      'file_url_open' => 'ds_content',
      'url_file_save' => 'ds_content',
      'file_url_persistent' => 'ds_content',
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
  $export['node|ofed_download|search_index'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|search_result';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'search_result';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_pubdate',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_summary',
        6 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_pubdate' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
  $export['node|ofed_download|search_result'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_download|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_download';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_download_summary',
        2 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
  $export['node|ofed_download|teaser'] = $ds_layout;

  return $export;
}
