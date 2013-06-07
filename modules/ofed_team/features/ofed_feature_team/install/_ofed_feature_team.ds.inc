<?php
/**
 * @file
 * ofed_feature_team.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ofed_feature_team_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|block_column';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'block_column';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_team|block_column'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|block_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'block_list';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Update date',
        ),
      ),
    ),
  );
  $export['node|ofed_team|block_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'social_button' => array(
      'weight' => '12',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Social medias',
        ),
      ),
    ),
    'field_ofed_team_body' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_contact' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_gender' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
    'field_ofed_team_phone' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_email' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
  );
  $export['node|ofed_team|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'social_button' => array(
      'weight' => '12',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Social medias',
        ),
      ),
    ),
    'field_ofed_team_body' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_contact' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_gender' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_phone' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_email' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
  );
  $export['node|ofed_team|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|page_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'page_list';
  $ds_fieldsetting->settings = array(
    'full_name_with_link' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'node_link' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_team_body' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
  );
  $export['node|ofed_team|page_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|print';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'print';
  $ds_fieldsetting->settings = array(
    'field_ofed_team_body' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_contact' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_gender' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Updated date',
        ),
      ),
    ),
    'field_ofed_team_phone' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_email' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
  );
  $export['node|ofed_team|print'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|rss';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'rss';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => '',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_team|rss'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|search_index';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'search_index';
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
    'field_ofed_team_body' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_contact' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_gender' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_picture' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
  );
  $export['node|ofed_team|search_index'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|search_result';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'search_result';
  $ds_fieldsetting->settings = array(
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Updated date',
        ),
      ),
    ),
  );
  $export['node|ofed_team|search_result'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_team|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_team';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'node_link' => array(
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_team_civility' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_first_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_function' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_team_last_name' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_team_pubdate' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Published date',
        ),
      ),
    ),
    'field_ofed_team_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
          'lb' => 'Update date',
        ),
      ),
    ),
  );
  $export['node|ofed_team|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_team_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|block_column';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'block_column';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_picture',
        3 => 'field_ofed_team_civility',
        4 => 'field_ofed_team_first_name',
        5 => 'field_ofed_team_last_name',
        6 => 'field_ofed_team_function',
        7 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
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
  $export['node|ofed_team|block_column'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|block_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'block_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_civility',
        3 => 'field_ofed_team_first_name',
        4 => 'field_ofed_team_last_name',
        5 => 'field_ofed_team_function',
        6 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
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
  $export['node|ofed_team|block_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_picture',
        3 => 'field_ofed_team_gender',
        4 => 'field_ofed_team_civility',
        5 => 'field_ofed_team_first_name',
        6 => 'field_ofed_team_last_name',
        7 => 'field_ofed_team_phone',
        8 => 'field_ofed_team_email',
        9 => 'field_ofed_team_function',
        10 => 'field_ofed_team_body',
        11 => 'field_ofed_team_contact',
        12 => 'social_button',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_gender' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_phone' => 'ds_content',
      'field_ofed_team_email' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
      'field_ofed_team_contact' => 'ds_content',
      'social_button' => 'ds_content',
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
  $export['node|ofed_team|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_update',
        1 => 'field_ofed_team_pubdate',
        2 => 'field_ofed_team_picture',
        3 => 'field_ofed_team_gender',
        4 => 'field_ofed_team_civility',
        5 => 'field_ofed_team_first_name',
        6 => 'field_ofed_team_last_name',
        7 => 'field_ofed_team_phone',
        8 => 'field_ofed_team_email',
        9 => 'field_ofed_team_function',
        10 => 'field_ofed_team_body',
        11 => 'field_ofed_team_contact',
        12 => 'social_button',
      ),
    ),
    'fields' => array(
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_gender' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_phone' => 'ds_content',
      'field_ofed_team_email' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
      'field_ofed_team_contact' => 'ds_content',
      'social_button' => 'ds_content',
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
  $export['node|ofed_team|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|page_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'page_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'full_name_with_link',
        1 => 'field_ofed_team_picture',
        2 => 'field_ofed_team_function',
        3 => 'field_ofed_team_body',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'full_name_with_link' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
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
  $export['node|ofed_team|page_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|print';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'print';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_picture',
        3 => 'field_ofed_team_civility',
        4 => 'field_ofed_team_first_name',
        5 => 'field_ofed_team_last_name',
        6 => 'field_ofed_team_phone',
        7 => 'field_ofed_team_email',
        8 => 'field_ofed_team_function',
        9 => 'field_ofed_team_gender',
        10 => 'field_ofed_team_body',
        11 => 'field_ofed_team_social',
        12 => 'field_ofed_team_contact',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_phone' => 'ds_content',
      'field_ofed_team_email' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_gender' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
      'field_ofed_team_social' => 'ds_content',
      'field_ofed_team_contact' => 'ds_content',
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
  $export['node|ofed_team|print'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|rss';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'rss';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_civility',
        3 => 'field_ofed_team_first_name',
        4 => 'field_ofed_team_last_name',
        5 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
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
  $export['node|ofed_team|rss'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|search_index';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'search_index';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_team_pubdate',
        2 => 'field_ofed_team_update',
        3 => 'field_ofed_team_picture',
        4 => 'field_ofed_team_civility',
        5 => 'field_ofed_team_first_name',
        6 => 'field_ofed_team_last_name',
        7 => 'field_ofed_team_phone',
        8 => 'field_ofed_team_email',
        9 => 'field_ofed_team_function',
        10 => 'field_ofed_team_gender',
        11 => 'field_ofed_team_body',
        12 => 'field_ofed_team_contact',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_phone' => 'ds_content',
      'field_ofed_team_email' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_gender' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
      'field_ofed_team_contact' => 'ds_content',
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
  $export['node|ofed_team|search_index'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|search_result';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'search_result';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_civility',
        3 => 'field_ofed_team_first_name',
        4 => 'field_ofed_team_last_name',
        5 => 'field_ofed_team_function',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
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
  $export['node|ofed_team|search_result'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_team|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_team';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_team_pubdate',
        1 => 'field_ofed_team_update',
        2 => 'field_ofed_team_picture',
        3 => 'field_ofed_team_civility',
        4 => 'field_ofed_team_first_name',
        5 => 'field_ofed_team_last_name',
        6 => 'field_ofed_team_function',
        7 => 'field_ofed_team_body',
        8 => 'node_link',
      ),
    ),
    'fields' => array(
      'field_ofed_team_pubdate' => 'ds_content',
      'field_ofed_team_update' => 'ds_content',
      'field_ofed_team_picture' => 'ds_content',
      'field_ofed_team_civility' => 'ds_content',
      'field_ofed_team_first_name' => 'ds_content',
      'field_ofed_team_last_name' => 'ds_content',
      'field_ofed_team_function' => 'ds_content',
      'field_ofed_team_body' => 'ds_content',
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
  $export['node|ofed_team|teaser'] = $ds_layout;

  return $export;
}
