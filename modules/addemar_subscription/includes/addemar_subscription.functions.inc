<?php
/**
 * @file
 * custom method to return list of fields form a serialized variable.
 */

/**
 * Clean the variable and return an array of fields.
 */
function _addemar_subscription_addemar_fields() {
  $fields = variable_get('addemar_subscription_addemar_fields', ADDEMAR_SUBSCRIPTION_ADDEMAR_FIELDS);

  if (!empty($fields)) {
    $fields = explode("\n", $fields);
    $fields = array_map('trim', $fields);
  }

  return $fields;
}

function _addemar_subscription_add_more_newsletter($form, $form_state) {
  return $form['addemar_subscription_settings']['groups_wrapper']['addemar_subscription_groups'];
}

function _addemar_subscription_add_more_newsletter_form($key, $weight, $group = 0, $description = '') {
  $form = array();

  $form = array(
    '#tree' => TRUE,
    '#weight' => $weight,
  );


  $form['group_id'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Group ID'),
    '#default_value'    => $group,
    '#description'      => t("Insert the id's of the contact groups to which you want to subscribe via this form as a value, separated by comma's.<br/> If you leave the value empty, the contact will just be added to the contacts list.<br/> If you fill in the contact group id’s, the contact will be added to the general contacts list but also to the corresponding contact groups."),
    '#required'         => TRUE,
    '#element_validate' => array('element_validate_integer'),
    '#weight' => $weight++,
    '#parents' => array('addemar_subscription_groups', $key, 'group_id'),
  );

  $form['description'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Newsletter description'),
    '#default_value'    => $description,
    '#required'         => TRUE,
    '#weight' => $weight++,
    '#parents' => array('addemar_subscription_groups', $key, 'description'),
  );

  return $form;
}