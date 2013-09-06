<?php
/**
 * @file
 * ofed_feature_event.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ofed_feature_event_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ofed_event_page_meta|node|ofed_event|form';
  $field_group->group_name = 'group_ofed_event_page_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ofed_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Page metadata',
    'weight' => '2',
    'children' => array(
      0 => 'field_ofed_event_pubdate',
      1 => 'field_ofed_event_update',
      2 => 'field_ofed_event_update_force',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Page metadata',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_ofed_event_page_meta|node|ofed_event|form'] = $field_group;

  return $export;
}
