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
    ),
    'node_link' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|ofed_download|block_column'] = $ds_fieldsetting;

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
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
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
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
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
          'classes' => 'float-left',
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
    ),
    'links' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_download_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'headline',
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
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
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
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'links' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_download_file' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_download_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'headline',
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
    ),
    'node_link' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
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
    ),
    'file_type' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_url_open' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_url_persistent' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'url_file_save' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
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
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(),
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
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
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
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'file_url_persistent' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'url_file_save' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
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
    ),
    'node_link' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
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
    ),
    'node_link' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|ofed_download|teaser'] = $ds_fieldsetting;

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
        3 => 'field_ofed_download_update',
        4 => 'field_ofed_download_summary',
        5 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-block-column block-column',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_download|block_column'] = $ds_layout;

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
        3 => 'field_ofed_download_update',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-block-list block-list',
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
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_author',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_thumb',
        6 => 'field_ofed_download_summary',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
        12 => 'links',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-default default',
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
        0 => 'title',
        1 => 'file_type',
        2 => 'file_size',
        3 => 'field_ofed_download_author',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_thumb',
        6 => 'field_ofed_download_summary',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
        12 => 'links',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
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
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-full block-full',
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
        3 => 'field_ofed_download_author',
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_thumb',
        6 => 'field_ofed_download_summary',
        7 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_thumb' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-page-list page-list',
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
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_thumb',
        6 => 'field_ofed_download_summary',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
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
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-print print',
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
        3 => 'field_ofed_download_update',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-refereces refereces',
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
        3 => 'field_ofed_download_update',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-rss rss',
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
        4 => 'field_ofed_download_update',
        5 => 'field_ofed_download_thumb',
        6 => 'field_ofed_download_summary',
        7 => 'field_ofed_download_body',
        8 => 'field_ofed_download_file',
        9 => 'file_url_open',
        10 => 'url_file_save',
        11 => 'file_url_persistent',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_author' => 'ds_content',
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
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-search-index search-index',
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
        3 => 'field_ofed_download_update',
        4 => 'field_ofed_download_summary',
        5 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'file_type' => 'ds_content',
      'file_size' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-search-result search-result',
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
        1 => 'field_ofed_download_update',
        2 => 'field_ofed_download_summary',
        3 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_download_update' => 'ds_content',
      'field_ofed_download_summary' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-download ds-wrapper-download-teaser teaser',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_download|teaser'] = $ds_layout;

  return $export;
}
