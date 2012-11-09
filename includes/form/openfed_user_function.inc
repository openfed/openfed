<?php

/**
 * Return the form for Defaults user set up.
 * 
 * @return array 
 */
function openfed_user() {
  // Setup the Default Builder account.
  $account = array(
    'name' => 'builder-user',
    'pass' => 'w8c4rFed', //user_password(),
    'mail' => 'f.schmit@blue4you.be',
    'status' => 1,
    'init' => 'f.schmit@blue4you.be',
  );
  $account = user_save(null, $account);
    
    
  // Assign the builder-user to the "Builder" role.
  $role = user_role_load_by_name( 'builder' );
  db_insert('users_roles')
    ->fields(array('uid' => $account->uid, 'rid' => $role->rid))
    ->execute();
    
  
  drupal_set_message('Default Builder user created.');
}