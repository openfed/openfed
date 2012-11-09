<?php

/**
 * Return the form for functionalities set up.
 * 
 * @return array 
 */
function openfed_functionnalities_form() {
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
 * Manage the submit of the form.
 * 
 * @param array $form
 * @param array $form_state 
 */
function openfed_functionnalities_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if(!empty($values['module_list'])) {
    $module_list = array();
    foreach($values['module_list'] as $key => $name) {
      if($key === $name) {
        $module_list[$key] = $name;
      }
    }
    module_enable($module_list, TRUE);
  }
}