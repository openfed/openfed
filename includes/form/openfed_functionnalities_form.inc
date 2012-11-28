<?php

/**
 * Return the form for functionalities set up
 * @return array 
 */
function openfed_functionnalities_form() {
  
  /*
  $module_available = array(
      //access control
        'content_access',
//        'content_access_rules',
      
      //Belgian eID
//        'beididp_block',
//        'beididp_button',
//        'beididp',
//        'beididp_migrate',
//        'beididp_pape',
//        'beididp_checkrole',
//        'beididp_fields',
      // Chaos tools
        'page_manager',
      // Date
        'calendar',
      // openFED
        'ofed_parent',
      // Fields
        'field_group',
      // Flags
        'flag',
      // Media
        'emfield',
      // Multilingual - i18n
        'forum',
        'i18n_forum',
      // Other
        'diff',
        'module_filter',
        'role_delegation',
      // Print
        'print_pdf',
      // Statistics
//        'google_analytics',
      // User Interface
        'extlink',
      // views
        'views_slideshow',
        'views_slideshow_cycle',
      // webform
        'webform',
  );
  
  
  $module_list = array();
  foreach( $module_available as $module) {
    $info = drupal_parse_info_file( drupal_get_path('module', $module) .'/'.$module.'.info');
    $module_list[$module] = $info['name'].'<br>'.$info['description'];
  }
  
  $form['module_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Setup your module below.'),
    '#options' => $module_list
  );
  */
  
  $form = array();
  
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the specific functionalities that have to be available in the website.') . '</p>',
  );
  
  
  $form['module_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Setup your module below.'),
    '#options' => openfed_getAllFunctionalities(),
    '#process' => array('form_process_checkboxes_at_install'), // override process for theming
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
function openfed_functionnalities_form_submit($form, &$form_state) {
//  $values = $form_state['values'];
  
//  if ( !empty($values['module_list']) ) {
//    $module_list = array();
//    foreach( $values['module_list'] as $key => $name ) {
//      if ( $key === $name ) {
//        $module_list[$key] = $name;
//      }
//    }
//    module_enable($module_list, TRUE);
//    node_access_rebuild(FALSE);
//  }
}
?>