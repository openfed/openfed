<?php

/**
 * Return the form for role set up
 * @return array 
 */
function openfed_role_form() {
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the roles and the corresponding permission to foresee:') . '<br/>' . st('(By default "Admin" and "Builder" are automaticaly created.)') . '</p>',
  );
  $form['role_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Roles'),
    '#options' => _openfed_return_roles_list(),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  return $form;
}

/**
 * manage the submit of the form
 * @param array $form
 * @param array $form_state 
 */
function openfed_role_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if ( !empty($values['role_list']) ) {
    
    
    if ( $values['role_list']['configurator'] === 'configurator' ) {
      // Manage Configurator information 
        $conf_role = new stdClass();
        $conf_role->name = 'Configurator';
        $conf_role->weight = 5;
        user_role_save($conf_role);
      // Assign permission  
        $conf_role = user_role_load_by_name('Configurator');
        user_role_change_permissions($conf_role->rid, _openfed_return_permission_configurator() );
    }
    
    if ( $values['role_list']['content_manager'] === 'content_manager' ) {
      // Manage Content Manager information  
        $cm_role = new stdClass();
        $cm_role->name = 'Content Manager';
        $cm_role->weight = 6;
        user_role_save($cm_role);
      // Assign permission 
        $cm_role = user_role_load_by_name('Content Manager');
        user_role_change_permissions($cm_role->rid, _openfed_return_permission_content_manager() );
    }
    
    if ( $values['role_list']['user_manager'] === 'user_manager' ) {
      // Manage User Manager information
        $um_role = new stdClass();
        $um_role->name = 'User Manager';
        $um_role->weight = 7;
        user_role_save($um_role);
      // Assign permission
        $um_role = user_role_load_by_name('User Manager');
        user_role_change_permissions($um_role->rid, _openfed_return_permission_user_manager() );
    }
    
    if ( $values['role_list']['user_manager'] === 'authenticated_visitor' ) {
      // Manage Authenticated visitor information  
        $av_role = new stdClass();
        $av_role->name = 'Authenticated Visitor';
        $av_role->weight = 8;
        user_role_save($av_role);
      // Assign permission 
        $av_role = user_role_load_by_name('Authenticated Visitor');
        user_role_change_permissions($av_role->rid, _openfed_return_permission_authenticated_visitor() );
    }
  }
  
  // SET PERMISSION FOR ADMINISTRATOR
    $adm_role = user_role_load_by_name('Administrator');
    $adm_role_rid = $adm_role->rid;
    user_role_grant_permissions($adm_role_rid, array_keys(module_invoke_all('permission')));
  
  // Assign permission for role Builder
    $web_role = user_role_load_by_name('Builder');
    $web_role_rid = $web_role->rid;
    user_role_change_permissions($web_role_rid, _openfed_return_permission_builder());
    
    
  // SET PERMISSION FOR AUTHENTICATED USER
    $auth_role = user_role_load_by_name('authenticated user');
    $auth_role_rid = $auth_role->rid;
    user_role_change_permissions($auth_role_rid, _openfed_return_permission_authenticated_user());
  

  // SET PERMISSION FOR ANONYMOUS USER
    $ano_role = user_role_load_by_name('anonymous user');
    $ano_role_rid = $ano_role->rid;
    user_role_change_permissions($ano_role_rid, _openfed_return_permission_anonymous_user());
  
    
}

?>