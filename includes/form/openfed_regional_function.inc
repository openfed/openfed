<?php

/**
 * Return the form for regional set up
 * @return array 
 */
function openfed_regional_form() {
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the regional languages which have to be foreseen:') . '</p>',
  );
  $form['regional_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Regional languages list'),
    '#options' => array( 
      'fr' => 'French', 
      'nl' => 'Dutch (Nederlands)'
    ),
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
function openfed_regional_form_submit($form, &$form_state) {
  
  /**
   * 
   *  !!! TO FIX !!!
   *  LOOSE INSTALLATION PROCESS 
   *  
   */
  $values = $form_state['values'];
  if ( !empty($values['regional_list']) ) {
    include_once DRUPAL_ROOT . '/includes/iso.inc';
    $predefined = _locale_get_predefined_list();
    
    foreach( $values['regional_list'] as $key => $value ) {
      if ( $key === $value ) {
        locale_add_language($value);
        drupal_set_message(t('The language %language has been created and can now be used. More information is available on the <a href="@locale-help">help screen</a>.', array('%language' => t($predefined[$value][0]), '@locale-help' => url('admin/help/locale'))));

        if ($batch = locale_batch_by_language($value, '_locale_batch_language_finished')) {
          batch_set($batch);
        }
      }
    }


  }
}

?>