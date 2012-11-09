<?php

// CREATE A DEFAULT ROLE FOR SITE ADMINISTRATORS, WITH ALL AVAILABLE PERMISSIONS ASSIGNED.
  $admin_role = new stdClass();
  $admin_role->name = 'Administrator';
  $admin_role->weight = 2;
  user_role_save($admin_role);
  user_role_grant_permissions($admin_role->rid, array_keys(module_invoke_all('permission')));
  
// Set this as the administrator role.
  variable_set('user_admin_role', $admin_role->rid);

// Assign user 1 the "administrator" role.
  db_insert('users_roles')->fields(array('uid' => 1, 'rid' => $admin_role->rid))->execute();