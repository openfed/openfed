<?php
/**
 * @file
 * ofed_feature_photogallery.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ofed_feature_photogallery_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_ofed_photogallery';
  $strongarm->value = 1;
  $export['addanother_button_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_ofed_photogallery';
  $strongarm->value = 1;
  $export['addanother_message_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_ofed_photogallery';
  $strongarm->value = 1;
  $export['addanother_tab_edit_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_ofed_photogallery';
  $strongarm->value = 0;
  $export['addanother_tab_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_ofed_photogallery';
  $strongarm->value = 'edit-scheduler';
  $export['additional_settings__active_tab_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__ofed_photogallery';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => TRUE,
      ),
      'search_index' => array(
        'custom_settings' => TRUE,
      ),
      'search_result' => array(
        'custom_settings' => TRUE,
      ),
      'print' => array(
        'custom_settings' => TRUE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'block_column' => array(
        'custom_settings' => TRUE,
      ),
      'block_element' => array(
        'custom_settings' => TRUE,
      ),
      'block_info' => array(
        'custom_settings' => TRUE,
      ),
      'block_list' => array(
        'custom_settings' => TRUE,
      ),
      'page_list' => array(
        'custom_settings' => TRUE,
      ),
      'references' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'language' => array(
          'weight' => '0',
        ),
        'metatags' => array(
          'weight' => '10',
        ),
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '9',
        ),
        'redirect' => array(
          'weight' => '8',
        ),
        'xmlsitemap' => array(
          'weight' => '7',
        ),
      ),
      'display' => array(
        'language' => array(
          'default' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'teaser' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'rss' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'search_index' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'search_result' => array(
            'weight' => '14',
            'visible' => FALSE,
          ),
          'print' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'block_column' => array(
            'weight' => '12',
            'visible' => FALSE,
          ),
          'block_element' => array(
            'weight' => '12',
            'visible' => FALSE,
          ),
          'block_info' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'block_list' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'page_list' => array(
            'weight' => '12',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_extended_ofed_photogallery';
  $strongarm->value = '4';
  $export['i18n_node_extended_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_options_ofed_photogallery';
  $strongarm->value = array(
    0 => 'current',
    1 => 'required',
  );
  $export['i18n_node_options_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_sync_node_type_ofed_photogallery';
  $strongarm->value = array();
  $export['i18n_sync_node_type_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ofed_photogallery';
  $strongarm->value = '2';
  $export['language_content_type_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_ofed_photogallery';
  $strongarm->value = array();
  $export['menu_options_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_ofed_photogallery';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ofed_photogallery';
  $strongarm->value = array();
  $export['node_options_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_ofed_photogallery';
  $strongarm->value = '1';
  $export['node_preview_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_ofed_photogallery';
  $strongarm->value = 1;
  $export['node_submitted_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_title_type_ofed_photogallery';
  $strongarm->value = '';
  $export['page_title_type_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_title_type_ofed_photogallery_showfield';
  $strongarm->value = 1;
  $export['page_title_type_ofed_photogallery_showfield'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_ofed_photogallery_en_pattern';
  $strongarm->value = 'photos-gallery/[node:title]';
  $export['pathauto_node_ofed_photogallery_en_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_ofed_photogallery_fr_pattern';
  $strongarm->value = 'galerie-photos/[node:title]';
  $export['pathauto_node_ofed_photogallery_fr_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_ofed_photogallery_nl_pattern';
  $strongarm->value = 'fotos-galerij/[node:title]';
  $export['pathauto_node_ofed_photogallery_nl_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_ofed_photogallery_pattern';
  $strongarm->value = 'photos-gallery/[node:title]';
  $export['pathauto_node_ofed_photogallery_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_ofed_photogallery_und_pattern';
  $strongarm->value = '';
  $export['pathauto_node_ofed_photogallery_und_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_display_comment_ofed_photogallery';
  $strongarm->value = 0;
  $export['print_display_comment_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_display_ofed_photogallery';
  $strongarm->value = 1;
  $export['print_display_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_display_urllist_ofed_photogallery';
  $strongarm->value = 1;
  $export['print_display_urllist_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_ofed_photogallery';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_ofed_photogallery';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_required_ofed_photogallery';
  $strongarm->value = 0;
  $export['scheduler_publish_required_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_revision_ofed_photogallery';
  $strongarm->value = 0;
  $export['scheduler_publish_revision_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_ofed_photogallery';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_ofed_photogallery';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_required_ofed_photogallery';
  $strongarm->value = 0;
  $export['scheduler_unpublish_required_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_revision_ofed_photogallery';
  $strongarm->value = 0;
  $export['scheduler_unpublish_revision_ofed_photogallery'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ofed_photogallery';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ofed_photogallery'] = $strongarm;

  return $export;
}
