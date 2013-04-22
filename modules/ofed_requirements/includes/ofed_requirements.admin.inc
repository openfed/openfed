<?php

function ofed_requirements_check_page() {
  $output = '';
  // Check the permissions and the roles
  $permission_status = _ofed_requirements_check_permissions();

  if ($count = count($permission_status['roles'])) {
    // @TODO: prepare variables to build a form
    $output .= format_plural($count, 'The following role has been changed/added', '@count roles have been changed/added');

    foreach($permission_status['roles'] as $changed_role) {
      $output .=  $changed_role;
    }
    dsm($permission_status, 'permission_status', 'permission_status');
  }

  return $output;
}


function ofed_requirements_check_form($form) {

}


function _ofed_requirements_check_permissions() {
  // Retrieve default roles/permissions
  $path_to_files = __DIR__ . '/../assets/files/';
  // File containing serialize(user_roles());
  $default_roles = _ofed_requirements_file_get_unserialized_contents($path_to_files, 'roles');
  // File containing serialize(user_role_permissions($role_names)); $role_names beeing user_roles() returned value
  $default_permissions = _ofed_requirements_file_get_unserialized_contents($path_to_files, 'permissions');
  // File containing serialize(array_keys($permissions)); $permissions beeing module_invoke_all('permission') returned value
  $default_role_permissions = _ofed_requirements_file_get_unserialized_contents($path_to_files, 'role_permissions');

  // Retrieve current configuration
  // Retrieve permissions
  $permissions_array = module_invoke_all('permission');

  // Retrieve role names
  $role_names = user_roles();
  //check differences in roles definition
  $diff_roles = array_diff($role_names, $default_roles);

  // Fetch permissions for all roles or the one selected role.
  $role_permissions = user_role_permissions($role_names);
  //check differences in role permissions
  $diff_role_permissions = array();

  foreach ($role_permissions as $role_id => $role_defined_permissions) {
    // If the role is new, then it's not necessary to check wheter or not it corresponds with the predefined permissions
    if (!in_array($role_id, array_keys($diff_roles))) {
      $diff = array_diff($role_defined_permissions, $default_role_permissions[$role_id]);
      array_walk($diff, '_ofed_requirements_map_permissions_titles', $permissions_array); // Replace TRUE by the permission's title
      $diff_role_permissions[] = array(
        'role_id' => $role_id,
        'role_name' => $role_names[$role_id],
        'diff' => $diff,
       );
    }
  }
  $differences = array(
    'roles' => $diff_roles,
    'permissions' => $diff_role_permissions,
  );

  return $differences;
}


/**
 * Read a file containing a serialized PHP array/object and returns its content as an array/object
 * @param string $path
 * @param string $filename
 * @return array/object
 */
function _ofed_requirements_file_get_unserialized_contents($path, $filename) {
  // make use of @ so no warning is raised
  $file_content = @file_get_contents($path . $filename);
  $unserialized_value = @unserialize($file_content);

  if ($file_content === FALSE || empty($file_content)) {
    drupal_set_message(t('Missing %file config file. The test cannot run properly!', array('%file' => $filename)), 'error');
  }
  else if ($unserialized_value === FALSE) {
    drupal_set_message(t('Error while reading %file config files. The test cannot run properly!', array('%file' => $filename)), 'error');
  }
  return $unserialized_value;
}


function _ofed_requirements_map_permissions_titles(&$elt, $key, $permissions) {
  $elt = $permissions[$key]['title'];
}