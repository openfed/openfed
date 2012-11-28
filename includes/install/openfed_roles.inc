<?php

  /**
  * CREATE A DEFAULT ROLE FOR SITE ADMINISTRATORS, WITH ALL AVAILABLE PERMISSIONS ASSIGNED. 
  */
  $admin_role = new stdClass();
  $admin_role->name = 'Administrator';
  $admin_role->weight = 2;
  user_role_save($admin_role);
  user_role_grant_permissions($admin_role->rid, array_keys(module_invoke_all('permission')));
  
// Set this as the administrator role.
  variable_set('user_admin_role', $admin_role->rid);

// Assign user 1 the "administrator" role.
  db_insert('users_roles')->fields(array('uid' => 1, 'rid' => $admin_role->rid))->execute();
  
  
  
  /**
   * Create default role for Builder 
   */
  $web_role = new stdClass();
  $web_role->name = 'Builder';
  $web_role->weight = 4;
  user_role_save($web_role);

  $web_role = user_role_load_by_name('Builder');
  $web_role_rid = $web_role->rid;
  $web_role_permissions = array(
      'use text format full_html' => TRUE,
      'use add another' => TRUE,
  );
  user_role_change_permissions($web_role_rid, $web_role_permissions);
  
  
  
  /** 
   * SET PERMISSION FOR AUTHENTICATED USER
   */
  $auth_role = user_role_load_by_name('authenticated user');
  $auth_role_rid = $auth_role->rid;
  $auth_role_permissions = array(
      'access news feeds' => TRUE,
      'access content' => TRUE,
      'access print' => TRUE,
      'search content' => TRUE,
      'search panel content' => TRUE,
      'search webform content' => TRUE,
      'access site map' => TRUE,
      
      'use add another' => TRUE,
      'access ckeditor link' => TRUE,
      'use text format filtered_html' => TRUE,
      'view own unpublished content' => TRUE,
  );
  user_role_change_permissions($auth_role_rid, $auth_role_permissions);
  
  
  
  /**
   * SET PERMISSION FOR ANONYMOUS USER
   */
  $ano_role = user_role_load_by_name('anonymous user');
  $ano_role_rid = $ano_role->rid;
  $ano_role_permissions = array(
      'access news feeds' => TRUE,
      'access content' => TRUE,
      'access print' => TRUE,
      'search content' => TRUE,
      'search panel content' => TRUE,
      'search webform content' => TRUE,
      'access site map' => TRUE
  );
  user_role_change_permissions($ano_role_rid, $ano_role_permissions);