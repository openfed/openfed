<?php

/**
 * Return the form for contenttypes set up.
 *
 * @return array
 */
function openfed_contenttypes_form() {
  drupal_set_title(st('Enable content types'));
  $form = array();

  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the specific content types that have to be available in the website.') . '</p><p>' . st('Note : each content type can be enabled after the installation in the Features list.') . '</p>',
  );

  $form['types_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Content types:'),
    '#options' => _openfed_return_contenttypes_list(),
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
function openfed_contenttypes_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  if (!empty($values['types_list'])) {
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
    foreach ($values['types_list'] as $key => $name) {
      if ($key === $name) {
        $module_list[] = $name;
      }
    }

    variable_set('openfed_need_batch_contenttypes', TRUE);
    variable_set('openfed_need_batch_contenttypes_functions', $module_list);
  }

  _openfed_contenttypes_grant_permissions();
}

/**
 * batch function to enable contenttypes
 */
function openfed_batch_contenttypes() {
  $values = variable_get('openfed_need_batch_contenttypes_functions');

  if (!empty($values)) {
    $batch = array(
      'title' => st('Importing content types'),
      'operations' => array(
        array('_openfed_batch_enabling_contenttypes', array($values, TRUE)),
      ),
      'finished' => '_openfed_batch_finished_contenttypes',
      'init_message' => st('Starting import content types'),
      'error_message' => st('Error importing content types'),
    );
    batch_set($batch);
    batch_process('http://' . $_SERVER['HTTP_HOST'] . '/install.php?profile=openfed&locale=en');
  }
  else {
    variable_del('openfed_need_batch_contenttypes');
    variable_del('openfed_need_batch_contenttypes_functions');
  }
}

/**
 * declaration of batch operation to enable contenttypes
 */
function _openfed_batch_enabling_contenttypes($module_list, $enable_dependencies, &$context) {
  module_enable($module_list, $enable_dependencies);
}

/**
 * declaration of batch finished function
 */
function _openfed_batch_finished_contenttypes($success, $results, $operations) {
  if ($success) {
    variable_del('openfed_need_batch_contenttypes');
    variable_del('openfed_need_batch_contenttypes_functions');
    drupal_set_message(t('Success importing contenttypes'));
  }
  else {
    drupal_set_message(t('BatchError importing contenttypes'));
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

function _openfed_contenttypes_grant_permissions() {
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
