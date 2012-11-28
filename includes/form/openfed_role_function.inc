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
      $conf_role = new stdClass();
      $conf_role->name = 'Configurator';
      $conf_role->weight = 5;
      user_role_save($conf_role);
      
      $conf_role = user_role_load_by_name('Configurator');
      $conf_role_rid = $conf_role->rid;
      $conf_role_permissions = array(
          'use text format full_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($conf_role_rid, $conf_role_permissions);
    }
    
    if ( $values['role_list']['content_manager'] === 'content_manager' ) {
      $cm_role = new stdClass();
      $cm_role->name = 'Content Manager';
      $cm_role->weight = 6;
      user_role_save($cm_role);
      
      $cm_role = user_role_load_by_name('Content Manager');
      $cm_role_rid = $cm_role->rid;
      $cm_role_permissions = array(
          'use text format full_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($cm_role_rid, $cm_role_permissions);
    }
    
    
    if ( $values['role_list']['user_manager'] === 'user_manager' ) {
      $um_role = new stdClass();
      $um_role->name = 'User Manager';
      $um_role->weight = 7;
      user_role_save($um_role);
      
      $um_role = user_role_load_by_name('User Manager');
      $um_role_rid = $um_role->rid;
      $um_role_permissions = array(
          'use text format filtered_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($um_role_rid, $um_role_permissions);
    }
  }
}

?>