<?php

/**
 * Return the form for fedict user set up
 * @return array 
 */
function openfed_fedict() {
//  $form = array();
//  $form['intro'] = array(
//    '#markup' => '<p>' . st('Create the Fedict user for the website.') . '</p>',
//  );
//  $form['fedict_name'] = array(
//    '#type' => 'textfield',
//    '#title' => st('FEDICT Username'),
//    '#required' => TRUE,
//  );
//  $form['fedict_mail'] = array(
//    '#type' => 'textfield',
//    '#title' => st('FEDICT E-mail Address'),
//    '#required' => TRUE,
//  );
//  $form['fedict_pass'] = array(
//    '#type' => 'password',
//    '#title' => st('FEDICT Password'),
//    '#description' => st('if not set a password will be generated automatically'),
//  );
//  $form['fedict_role'] = array(
//    '#type' => 'select',
//    '#title' => st('FEDICT role.'),
//    '#options' => openfed_getAllRoles(),
//    '#required' => TRUE,
//  );
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => st('Continue'),
//  );
//  return $form;

//  $values = $form_state['values'];
//
//  if ( !empty($values['fedict_name']) && !empty($values['fedict_mail']) ) {
//    // Setup the user account array to programatically create a new user.
//    $account = array(
//      'name' => $values['fedict_name'],
//      'pass' => !empty($values['fedict_pass']) ? $values['fedict_pass'] : user_password(),
//      'mail' => $values['fedict_mail'],
//      'status' => 1,
//      'init' => $values['fedict_mail'],
//    );
//    $account = user_save(null, $account);
//    
//    if ( !empty($values['fedict_role']) ) {
//      // Assign the client to the "Builder" role.
//      $role = user_role_load_by_name( $values['fedict_role'] );
//      db_insert('users_roles')
//        ->fields(array('uid' => $account->uid, 'rid' => $role->rid))
//        ->execute();
//    }
//  }
  drupal_set_message('Fedict Set up done !');
}

?>