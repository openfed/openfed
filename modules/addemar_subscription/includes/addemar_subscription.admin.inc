<?php
/**
 * @file
 * administration configuration
 */

/**
 * Configuration page of the Addemar subscription module.
 */
function addemar_subscription_admin($form, &$form_state) {
  $form = array();

  if (!extension_loaded('soap')) {
    drupal_set_message(t('SOAP has to be enabled to use this module.'), 'error');
    $form['error'] = array(
      '#markup' => t('Please enable SOAP in order to configure this module.'),
    );
  }
  else {
    drupal_add_css(drupal_get_path('module', 'addemar_subscription') . '/assets/styles/addemar_subscription.css');

    $form['addemar_subscription'] = array(
      '#type' => 'vertical_tabs',
    );

    $form['addemar_subscription_soap'] = array(
      '#type'         => 'fieldset',
      '#title'        => t('SOAP settings'),
      '#collapsible'  => TRUE,
      '#collapsed'    => FALSE,
      '#group'        => 'addemar_subscription',
    );
    $form['addemar_subscription_soap']['addemar_subscription_soap_wsdl'] = array(
      '#type'             => 'textfield',
      '#title'            => t('URL for SOAP wsdl'),
      '#default_value'    => variable_get('addemar_subscription_soap_wsdl', ADDEMAR_SUBSCRIPTION_SOAP_WSDL),
      '#description'      => t('Put url to Addemar SOAP wsdl (e.g: https://ws-mailing.presscenter.org/soap/wsdl/?token=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx&version=1.3)'),
      '#required'         => TRUE,
      '#maxlength'        => 255,
    );
  //   $form['addemar_subscription_soap']['addemar_subscription_soap_message'] = array(
  //     '#type'             => 'textfield',
  //     '#title'            => t('SOAP Message'),
  //     '#default_value'    => variable_get('addemar_subscription_soap_message', ADDEMAR_SUBSCRIPTION_SOAP_MESSAGE),
  //     '#description'      => t('A log message, for tracking the origin of the contact.'),
  //     '#required'         => TRUE,
  //   );

    $form['addemar_subscription_settings'] = array(
      '#type'         => 'fieldset',
      '#title'        => t('General Settings'),
      '#collapsible'  => TRUE,
      '#collapsed'    => FALSE,
      '#group'        => 'addemar_subscription',
    );


    // Add a wrapper for the groups and add more button.
    $form['addemar_subscription_settings']['groups_wrapper'] = array(
      '#tree' => FALSE,
      '#weight' => -4,
      '#prefix' => '<div class="clearfix" id="addemar-group-wrapper">',
      '#suffix' => '</div>',
    );

    // Container for just the groups and their descriptions.
    $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'] = array(
      '#prefix' => '<div id="addemar-groups">',
      '#suffix' => '</div>',
    );

    $groups = variable_get('addemar_subscription_groups', array());

    if (empty($form_state['group_count'])) {
      $form_state['group_count'] = count($groups);
    }
    $group_count = $form_state['group_count'];

    $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_settings_group_count'] = array(
      '#type' => 'hidden',
      '#value' => $group_count,
    );

    $delta = $group_count - count($groups);
    $weight = 0;
    $i = 1;

    // display existing groups
    foreach ($groups as $group) {
      $key = 'addemar_subscription_group:' . $i;
      $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'][$key] = _addemar_subscription_add_more_newsletter_form($key, $i, $group['group_id'], $group['description']);
      $i++;
    }

    // display initial group (empty) or add a new one (delta)
    if (empty($groups) || $delta) {

      for ($delta; $delta > 0 || $i == 1; $delta--) {
        $key = 'addemar_subscription_group:' . $i;
        $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'][$key] = _addemar_subscription_add_more_newsletter_form($key, $i);
        $i++;
      }
    }

    $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_add_more'] = array(
      '#type' => 'submit',
      '#value' => t('Add more'),
      '#attributes' => array(
        'title' => t("If the amount of boxes above isn't enough, click here to add more choices."),
      ),
      '#weight' => 1,
      '#limit_validation_errors' => array(array('addemar_subscription_groups')),
      '#submit' => array('addemar_subscription_add_more_submit'),
      '#ajax' => array(
        'callback' => '_addemar_subscription_add_more_newsletter',
        'wrapper' => 'addemar-groups',
        'effect' => 'fade',
      ),
    );


    $form['addemar_subscription_settings']['addemar_subscription_source_message'] = array(
      '#type'             => 'textfield',
      '#title'            => t('Source'),
      '#default_value'    => variable_get('addemar_subscription_source_message', ADDEMAR_SUBSCRIPTION_SOURCE_MESSAGE),
      '#description'      => t('Insert the source you want to mention with all contacts as a value.<br/> This source will be visible in the history of every contact subscribed via this form.'),
      '#required'         => FALSE,
    );
    $form['addemar_subscription_settings']['addemar_subscription_subscription_type'] = array(
      '#type'             => 'radios',
      '#title'            => t('Type of subscription'),
      '#options'          => array(
        0 => 'Simple',
        1 => 'Confirmed',
      ),
      '#default_value'    => variable_get('addemar_subscription_subscription_type', ADDEMAR_SUBSCRIPTION_SUBSCRIPTION_TYPE),
      '#description'      => t('Insert the type of subscription scenario you want.<br/>
        You can set the value to: <br/>
        Simple No e-mail will be sent. Only the confirmation page you set in "ret" will be shown.<br/>
        Confirmed The subscriber will receive a message confirming he has subscribed.'),
      '#required'         => TRUE,
    );
    $form['addemar_subscription_form'] = array(
      '#type'         => 'fieldset',
      '#title'        => t('Form Settings'),
      '#collapsible'  => TRUE,
      '#collapsed'    => FALSE,
      '#group'        => 'addemar_subscription',
    );

    $soap_wsdl = variable_get('addemar_subscription_soap_wsdl', ADDEMAR_SUBSCRIPTION_SOAP_WSDL);
    $options = variable_get('addemar_subscription_addemar_fields', '');

    if (!empty($soap_wsdl) && empty($options)) {
      $sClient = new SoapClient($soap_wsdl);
      $fields = $sClient->getContactStructure();

      foreach ($fields->fields as $field) {
        $options .= $field->name . '|' . ucfirst($field->name) . "\n";
      }
    }

    $form['addemar_subscription_form']['addemar_subscription_addemar_fields'] = array(
      '#type'             => 'textarea',
      '#title'            => t('addemar Fields'),
      '#default_value'    => $options,
      '#description'      => t('List all fields declared in addemar here. If no field is declared and if we the SOAP wsdl is known, it will be automatically loaded from Addemar. Enter one value per line, in the format <em>key|label|mandatory</em>.<br/> The <strong>key</strong> is the field code defined in addemar without <code>&lt;? ?&gt;</code>.<br/> The <strong>label</strong> will be displayed in front of the field.<br/> The <strong>mandatory</strong> is optional and will be used to set required to form field.<br/> e.g: <em>email|Email|required</em> or <em>name|Name</em>'),
      '#required'         => FALSE,
    );
    $form['addemar_subscription_form']['addemar_subscription_page_url'] = array(
      '#type'             => 'textfield',
      '#title'            => t('Page url'),
      '#default_value'    => variable_get('addemar_subscription_page_url', ADDEMAR_SUBSCRIPTION_PAGE_URL),
      '#description'      => t('Url of the page where the form must be displayed'),
      '#required'         => TRUE,
    );
    $form['addemar_subscription_form']['addemar_subscription_submit_button'] = array(
      '#type'             => 'textfield',
      '#title'            => t('Submit value'),
      '#default_value'    => variable_get('addemar_subscription_submit_button', ADDEMAR_SUBSCRIPTION_SUBMIT_BUTTON),
      '#description'      => t('Change the text value on the submit button'),
      '#required'         => TRUE,
    );

    $form['addemar_subscription_message'] = array(
      '#type'         => 'fieldset',
      '#title'        => t('Message Settings'),
      '#collapsible'  => TRUE,
      '#collapsed'    => FALSE,
      '#group'        => 'addemar_subscription',
    );
    $form['addemar_subscription_message']['addemar_subscription_message_success'] = array(
      '#type'             => 'textfield',
      '#title'            => t('Success'),
      '#default_value'    => variable_get('addemar_subscription_message_success', ADDEMAR_SUBSCRIPTION_MESSAGE_SUCCESS),
      '#description'      => t('The message that will be displayed if everything gone well.'),
      '#required'         => TRUE,
    );
    $form['addemar_subscription_message']['addemar_subscription_message_error'] = array(
      '#type'             => 'textfield',
      '#title'            => t('Error'),
      '#default_value'    => variable_get('addemar_subscription_message_error', ADDEMAR_SUBSCRIPTION_MESSAGE_ERROR),
      '#description'      => t('The message that will be displayed if an error is return by addemar.'),
      '#required'         => TRUE,
    );

    $form['#validate'][] = 'addemar_subscription_admin_validate';
    $form['#submit'][] = 'addemar_subscription_admin_submit';

    return system_settings_form($form);
  }

  return $form;
}

function addemar_subscription_admin_validate($form, &$form_state) {
  $soap_wsdl = $form_state['values']['addemar_subscription_soap_wsdl'];

  if (!_addemar_subscription_get_soap_client($soap_wsdl)) {
    form_set_error('addemar_subscription_soap_wsdl', '');// the message is already set by _addemar_subscription_get_soap_client
  }
}

function addemar_subscription_admin_submit($form, &$form_state) {

  // Do not submit empty group id
  foreach ($form_state['values']['addemar_subscription_groups'] as $key => $values) {

    if (empty($values['group_id']) || empty($values['description'])) {
      unset($form_state['values']['addemar_subscription_groups'][$key]);
    }
  }

  // flush menu cache if the path has been changed
  if (variable_get('addemar_subscription_page_url', '') != $form_state['values']['addemar_subscription_page_url']) {
    // set the variable prior to flushing the cache otherwise, the path is still unknown
    variable_set('addemar_subscription_page_url', $form_state['values']['addemar_subscription_page_url']);
    menu_rebuild();
  }
}

function addemar_subscription_add_more_submit($form, &$form_state) {
  $form_state['group_count']++;
  $form_state['rebuild'] = TRUE;
}