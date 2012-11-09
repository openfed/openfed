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
    '#options' => openfed_getAllRoles(),
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
    
  if ( !empty($values['role_list']) ) {
    
    if ( $values['role_list']['configurator'] === 'configurator' ) {
      $web_role = new stdClass();
      $web_role->name = 'Configurator';
      $web_role->weight = 5;
      user_role_save($web_role);
      
      $web_role = user_role_load_by_name('Configurator');
      $web_role_rid = $web_role->rid;
      $web_role_permissions = array(
          'use text format full_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($web_role_rid, $web_role_permissions);
    }
    
    if ( $values['role_list']['editor'] === 'editor' ) {
      $web_role = new stdClass();
      $web_role->name = 'Editor';
      $web_role->weight = 6;
      user_role_save($web_role);
      
      $web_role = user_role_load_by_name('Editor');
      $web_role_rid = $web_role->rid;
      $web_role_permissions = array(
          'use text format full_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($web_role_rid, $web_role_permissions);
    }
    
    
    if ( $values['role_list']['user'] === 'user' ) {
      $user_role = new stdClass();
      $user_role->name = 'User';
      $user_role->weight = 7;
      user_role_save($user_role);
      
      $user_role = user_role_load_by_name('User');
      $user_role_rid = $user_role->rid;
      $user_role_permissions = array(
          'use text format filtered_html' => TRUE,
          'use add another' => TRUE,
      );
      user_role_change_permissions($user_role_rid, $user_role_permissions);
    }
  }
}

?>