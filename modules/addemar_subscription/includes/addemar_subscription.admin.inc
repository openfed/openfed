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

  drupal_add_css(drupal_get_path('module', 'addemar_subscription') . '/assets/styles/addemar_subscription.css');

  $form['addemar_subscription'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['addemar_subscription_rest'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('REST settings'),
    '#collapsible'  => TRUE,
    '#collapsed'    => FALSE,
    '#group'        => 'addemar_subscription',
  );
  $form['addemar_subscription_rest']['addemar_subscription_rest_url'] = array(
    '#type'             => 'textfield',
    '#title'            => t('REST Url'),
    '#default_value'    => variable_get('addemar_subscription_rest_url', ADDEMAR_SUBSCRIPTION_REST_URL),
    '#description'      => t('Put the basic url to Addemar REST without url attributes and trailing slash. (e.g: http://ws.mailing.presscenter.org/rest)'),
    '#required'         => TRUE,
    '#maxlength'        => 255,
  );
  $form['addemar_subscription_rest']['addemar_subscription_rest_token'] = array(
    '#type'             => 'textfield',
    '#title'            => t('REST Token'),
    '#default_value'    => variable_get('addemar_subscription_rest_token', ''),
    '#description'      => t('Token of your REST web service user'),
    '#required'         => TRUE,
  );
  $form['addemar_subscription_rest']['addemar_subscription_rest_profile'] = array(
    '#type'             => 'textfield',
    '#title'            => t('REST Profile'),
    '#default_value'    => variable_get('addemar_subscription_rest_profile', ADDEMAR_SUBSCRIPTION_REST_PROFILE),
    '#description'      => t('Profile used, in this case "FormWS".'),
    '#required'         => TRUE,
  );
  $form['addemar_subscription_rest']['addemar_subscription_rest_method'] = array(
    '#type'             => 'textfield',
    '#title'            => t('REST Method'),
    '#default_value'    => variable_get('addemar_subscription_rest_method', ADDEMAR_SUBSCRIPTION_REST_METHOD),
    '#description'      => t('Method used, in this case "formOptin".'),
    '#required'         => TRUE,
  );
  $form['addemar_subscription_rest']['addemar_subscription_rest_message'] = array(
    '#type'             => 'textfield',
    '#title'            => t('REST Message'),
    '#default_value'    => variable_get('addemar_subscription_rest_message', ADDEMAR_SUBSCRIPTION_REST_MESSAGE),
    '#description'      => t('A log message, for tracking the origin of the contact.'),
    '#required'         => TRUE,
  );

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
    $key = 'addemar_subscription_group:' . $i;
    $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'][$key] = _addemar_subscription_add_more_newsletter_form($key, $i);
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
  $form['addemar_subscription_form']['addemar_subscription_addemar_fields'] = array(
    '#type'             => 'textarea',
    '#title'            => t('addemar Fields'),
    '#default_value'    => variable_get('addemar_subscription_addemar_fields', ADDEMAR_SUBSCRIPTION_ADDEMAR_FIELDS),
    '#description'      => t('List all fields declared in addemar here. If no field is declared, an "email" field will automatically be created in the form. Enter one value per line, in the format <em>key|label|mandatory</em>.<br/> The <strong>key</strong> is the field code defined in addemar without <code>&lt;? ?&gt;</code>.<br/> The <strong>label</strong> will be displayed in front of the field.<br/> The <strong>mandatory</strong> is optional and will be used to set required to form field.<br/> e.g: <em>email|Email|required</em> or <em>name|Name</em>'),
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

  return system_settings_form($form);
}

function addemar_subscription_add_more_submit($form, &$form_state) {
  $form_state['group_count']++;
  $form_state['rebuild'] = TRUE;
}