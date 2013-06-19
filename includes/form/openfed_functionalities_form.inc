<?php

/**
 * Return the form for functionalities set up.
 *
 * @return array
 */
function openfed_functionalities_form() {
  drupal_set_title(st('Functionalities configuration'));
  $form = array();

  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the specific functionalities that have to be available in the website.') . '</p><p>' . st('Note : each module can be enabled after the installation in the Modules list.') . '</p>',
  );

  $form['module_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Setup your module below.'),
    '#options' => _openfed_return_functionalities_list(),
    '#attributes' => array('class' => array('clearfix')),
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
function openfed_functionalities_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if (!empty($values['module_list'])) {
    $enable = array(
      'theme_default' => openfed_return_default_maintenance_theme_name(),
      'admin_theme' => openfed_return_default_maintenance_theme_name(),
      'maintenance_theme' => openfed_return_default_maintenance_theme_name(),
    );
    theme_enable($enable);

    foreach ($enable as $var => $theme) {
      if (!is_numeric($var)) {
        variable_set($var, $theme);
      }
    }

    $module_list = array();
    foreach ($values['module_list'] as $key => $name) {
      if ($key === $name) {
        $module_list[] = $name;
      }
    }

    variable_set('openfed_need_batch_functionalities', TRUE);
    variable_set('openfed_need_batch_functionalities_functions', $module_list);
  }

  _openfed_functionalities_grant_permissions();
}

/**
 * batch function to enable functionalities
 */
function openfed_batch_functionalities() {
  $values = variable_get('openfed_need_batch_functionalities_functions');

  if (!empty($values)) {
    $batch = array(
      'title' => st('Importing functionalities'),
      'operations' => array(
        array('_openfed_batch_enabling_functionalities', array($values, TRUE)),
      ),
      'finished' => '_openfed_batch_finished_functionalities',
      'init_message' => st('Starting import functionalities'),
      'error_message' => st('Error importing functionalities'),
    );
    batch_set($batch);
    batch_process('http://' . $_SERVER['HTTP_HOST'] . '/install.php?profile=openfed&locale=en');
  }
  else {
    variable_del('openfed_need_batch_functionalities');
    variable_del('openfed_need_batch_functionalities_functions');
  }
}

/**
 * declaration of batch operation to enable functionalities
 */
function _openfed_batch_enabling_functionalities($module_list, $enable_dependencies, &$context) {
  module_enable($module_list, $enable_dependencies);
}

/**
 * declaration of batch finished function
 */
function _openfed_batch_finished_functionalities($success, $results, $operations) {
  if ($success) {
    variable_del('openfed_need_batch_functionalities');
    variable_del('openfed_need_batch_functionalities_functions');
    drupal_set_message(t('Success importing functionalities'));
  }
  else {
    drupal_set_message(t('BatchError importing functionalities'));
  }

  $enable = array(
    'theme_default' => 'bartik',
    'admin_theme' => 'seven',
    'maintenance_theme' => 'seven',
  );
  theme_enable($enable);

  foreach ($enable as $var => $theme) {
    if (!is_numeric($var)) {
      variable_set($var, $theme);
    }
  }

  if (module_exists('ofed_federalheader')) {
    _openfed_set_block_into_region('ofed_federalheader', 'federalheader', 'tools');
  }
}

function _openfed_functionalities_grant_permissions() {
  // content related roles
  $roles = array(
    'Administrator',
    'Builder',
    'Configurator',
    'Content Manager',
  );
  // retreive node permissions
  $permissions = module_invoke('node', 'permission');
  $permissions = array_keys($permissions);
  $override_permissions = module_invoke('override_node_options', 'permission');
  $override_permissions = array_keys($override_permissions);
  $perms = array_merge($permissions, $override_permissions);
  $revoke = array();

  $revoke['Content Manager'] = array(
    'bypass node access',
    'administer content types',
    'administer nodes',
    'create ofed_banner content',
    'create ofed_slider content',
    'create ofed_slideshow content',
    'delete any webform content',
    'override webform authored by option',
  );
  $revoke['Builder'] = array(
    'bypass node access',
    'administer nodes',
    'delete revisions',
    'delete any webform content',
  );
  $revoke['Configurator'] = array(
    'delete revisions',
    'delete any webform content',
  );

  foreach ($roles as $role_name) {
    $role = user_role_load_by_name($role_name);

    if (!empty($role->rid)) {
      user_role_grant_permissions($role->rid, $perms);

      if (!empty($revoke[$role_name])) {
        user_role_revoke_permissions($role->rid, $revoke[$role_name]);
      }
    }
  }
}