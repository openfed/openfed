<?php
/**
 * @file
 * ofed_feature_new.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ofed_feature_new_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|block_column';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'block_column';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => 'more',
        'ft' => array(),
      ),
    ),
  );
  $export['node|ofed_new|block_column'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|block_info';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'block_info';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_new_update' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|ofed_new|block_info'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|block_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'block_list';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|ofed_new|block_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_new_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'headline',
        ),
      ),
    ),
  );
  $export['node|ofed_new|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'field_ofed_new_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_new_source' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_new_summary' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'headline',
        ),
      ),
    ),
    'field_ofed_new_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_new_update' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
  );
  $export['node|ofed_new|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|page_list';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'page_list';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'node_link' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => 'more',
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_new_author' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
    'field_ofed_new_source' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'clear-block',
        ),
      ),
    ),
    'field_ofed_new_summary' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
    'field_ofed_new_thumb' => array(
      'formatter_settings' => array(
        'ft' => array(
          'classes' => 'float-left',
        ),
      ),
    ),
  );
  $export['node|ofed_new|page_list'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|print';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'print';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|ofed_new|print'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|rss';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'rss';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'node_link' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|ofed_new|rss'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|search_index';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'search_index';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_ofed_new_docs' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|ofed_new|search_index'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|search_result';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
  $ds_fieldsetting->view_mode = 'search_result';
  $ds_fieldsetting->settings = array(
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
  $export['node|ofed_new|search_result'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ofed_new|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ofed_new';
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
        'ft' => array(),
      ),
    ),
    'node_link' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link text' => 'Read more',
        'wrapper' => '',
        'class' => 'more',
        'ft' => array(),
      ),
    ),
  );
  $export['node|ofed_new|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ofed_feature_new_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|block_column';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'block_column';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_summary',
        3 => 'field_ofed_new_thumb',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-block-column block-column',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|block_column'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|block_info';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'block_info';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_thumb',
        2 => 'field_ofed_new_pubdate',
        3 => 'field_ofed_new_body',
        4 => 'field_ofed_new_docs',
        5 => 'field_ofed_new_links',
        6 => 'field_ofed_new_source',
        7 => 'field_ofed_new_author',
        8 => 'field_ofed_new_update',
        9 => 'field_ofed_new_update_force',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'field_ofed_new_pubdate' => 'ds_content',
      'field_ofed_new_body' => 'ds_content',
      'field_ofed_new_docs' => 'ds_content',
      'field_ofed_new_links' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_author' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_update_force' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-block-info block-info',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|block_info'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|block_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'block_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-block-list block-list',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|block_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_author',
        3 => 'field_ofed_new_source',
        4 => 'field_ofed_new_summary',
        5 => 'field_ofed_new_thumb',
        6 => 'field_ofed_new_body',
        7 => 'field_ofed_new_docs',
        8 => 'field_ofed_new_links',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_author' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'field_ofed_new_body' => 'ds_content',
      'field_ofed_new_docs' => 'ds_content',
      'field_ofed_new_links' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-default default',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_ofed_new_update',
        1 => 'field_ofed_new_author',
        2 => 'field_ofed_new_source',
        3 => 'field_ofed_new_summary',
        4 => 'field_ofed_new_thumb',
        5 => 'field_ofed_new_body',
        6 => 'field_ofed_new_docs',
        7 => 'field_ofed_new_links',
      ),
    ),
    'fields' => array(
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_author' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'field_ofed_new_body' => 'ds_content',
      'field_ofed_new_docs' => 'ds_content',
      'field_ofed_new_links' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-full full',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|page_list';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'page_list';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_author',
        3 => 'field_ofed_new_source',
        4 => 'field_ofed_new_thumb',
        5 => 'field_ofed_new_summary',
        6 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_author' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-page-list page-list',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|page_list'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|print';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'print';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_author',
        3 => 'field_ofed_new_source',
        4 => 'field_ofed_new_summary',
        5 => 'field_ofed_new_thumb',
        6 => 'field_ofed_new_body',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_author' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'field_ofed_new_body' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-print print',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|print'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|rss';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'rss';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-rss rss',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|rss'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|search_index';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'search_index';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_source',
        3 => 'field_ofed_new_summary',
        4 => 'field_ofed_new_body',
        5 => 'field_ofed_new_docs',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_source' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_body' => 'ds_content',
      'field_ofed_new_docs' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-search-index search-index',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|search_index'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|search_result';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'search_result';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_summary',
        3 => 'field_ofed_new_thumb',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-search-result search-result',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|search_result'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ofed_new|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ofed_new';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_ofed_new_update',
        2 => 'field_ofed_new_summary',
        3 => 'field_ofed_new_thumb',
        4 => 'node_link',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_ofed_new_update' => 'ds_content',
      'field_ofed_new_summary' => 'ds_content',
      'field_ofed_new_thumb' => 'ds_content',
      'node_link' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => 'ds-wrapper-new ds-wrapper-new-teaser teaser',
    'layout_attributes_merge' => 1,
    'hide_page_title' => '0',
    'page_option_title' => '',
    'hide_sidebars' => 0,
  );
  $export['node|ofed_new|teaser'] = $ds_layout;

  return $export;
}
