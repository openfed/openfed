<?php
/**
 * @file
 * ofed_team.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ofed_team_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ofed_team_page_meta|node|ofed_team|form';
  $field_group->group_name = 'group_ofed_team_page_meta';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ofed_team';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Page metadata',
    'weight' => '13',
    'children' => array(
      0 => 'field_ofed_team_pubdate',
      1 => 'field_ofed_team_update',
      2 => 'field_ofed_team_update_force',
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
  $export['group_ofed_team_page_meta|node|ofed_team|form'] = $field_group;

  return $export;
}