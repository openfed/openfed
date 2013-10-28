<?php

/**
 * @file
 * Needs to be documented.
 */

/**
 * Includes.
 */
// Include all custom functions.
require_once('includes/misc/openfed_functions.inc');
require_once('includes/steps/openfed_install_files_and_folders.inc');
require_once('includes/steps/openfed_install_regional.inc');
require_once('includes/steps/openfed_install_menus.inc');
require_once('includes/steps/openfed_install_roles.inc');
require_once('includes/steps/openfed_install_taxonomy.inc');
require_once('includes/steps/openfed_install_functionalities.inc');
require_once('includes/steps/openfed_install_complete.inc');

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function openfed_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'OpenFed';
  $form['server_settings']['site_default_country']['#default_value'] = 'BE';

  // Only check for updates, no need for email notifications
  $form['update_notifications']['update_status_module']['#default_value'] = array(0, 0);
}

/**
 * Implements hook_install_tasks().
 * Task that can be accomplish within the installation process.
 */
function openfed_install_tasks_alter(&$tasks, $install_state) {
  // Insert js and css to be able to change the layout.
  // Load js for custom layout.
  $file_js = drupal_get_path('theme', 'maintenance') . '/assets/scripts/script.js';
  if (is_file($file_js)){
    drupal_add_js($file_js);
  }
  // Load css for custom layout.
  $file_css = drupal_get_path('theme', 'maintenance') . '/assets/styles/design.css';
  if (is_file($file_css)){
    drupal_add_css($file_css);
  }

  // Set the title.
  drupal_set_title('OpenFed : ' .  drupal_get_title());

  // Rewrite completly the tasks array.
  // It's the only way to reorder all steps.
  $task_temp = array();

  if (isset($tasks['install_select_profile'])) {
    $task_temp['install_select_profile'] = $tasks['install_select_profile'];
  }

  if (isset($tasks['install_select_locale'])) {
    $task_temp['install_select_locale'] = $tasks['install_select_locale'];
  }

  if (isset($tasks['install_load_profile'])) {
    $task_temp['install_load_profile'] = $tasks['install_load_profile'];
  }

  if (isset($tasks['install_verify_requirements'])) {
    $task_temp['install_verify_requirements'] = $tasks['install_verify_requirements'];
  }

  if (isset($tasks['install_settings_form'])) {
    $task_temp['install_settings_form'] = $tasks['install_settings_form'];
  }

  if (isset($tasks['install_system_module'])) {
    $task_temp['install_system_module'] = $tasks['install_system_module'];
  }

  if (isset($tasks['install_bootstrap_full'])) {
    $task_temp['install_bootstrap_full'] = $tasks['install_bootstrap_full'];
  }

  // Install files and folders.
  $task_temp['openfed_install_files_and_folders'] = array(
    'run' => variable_get('openfed_install_files_and_folders_done', FALSE) ? INSTALL_TASK_SKIP : INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  );

  if (isset($tasks['install_profile_modules'])) {
    $task_temp['install_profile_modules'] = $tasks['install_profile_modules'];
  }

  if (isset($tasks['install_import_locales'])) {
    $task_temp['install_import_locales'] = $tasks['install_import_locales'];
  }

  // Openfed task place here.
  // Step to choose which language to pre-install.
  $task_temp['openfed_install_regional_form'] = array(
    'display_name' => st('Set up regional'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Batch the process of language activation if a language must be pre-install.
  $task_temp['openfed_install_regional_batch'] = array(
    'display_name' => st('Import internalization'),
    'display' => variable_get('openfed_regional_batch_run', FALSE),
    'type' => 'batch',
    'run' => variable_get('openfed_regional_batch_run', FALSE) ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
  );

  // Step to choose which menu to pre-install.
  $task_temp['openfed_install_menu_form'] = array(
    'display_name' => st('Set up menus'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Step to choose which taxonomy vocabulary to pre-install.
  $task_temp['openfed_install_taxonomy_form'] = array(
    'display_name' => st('Set up taxonomy'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Step to choose which role to pre-install.
  $task_temp['openfed_install_role_form'] = array(
    'display_name' => st('Set up roles'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Step to choose which additional functionalities to add.
  $task_temp['openfed_install_functionalities_form'] = array(
    'display_name' => st('Enable content types'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Batch the process of functionnalities activation if a fonctionnalities
  // must be pre-install.
  $task_temp['openfed_install_functionalities_batch'] = array(
    'display_name' => st('Import content types'),
    'display' => variable_get('openfed_content_types_batch_run', FALSE),
    'type' => 'batch',
    'run' => variable_get('openfed_content_types_batch_run', FALSE) ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
  );

  // Step to rebuild permission.
  $task_temp['openfed_install_complete'] = array(
    'display_name' => st('Setup complete'),
    'display' => FALSE,
  );

  if (isset($tasks['install_configure_form'])) {
    $task_temp['install_configure_form'] = $tasks['install_configure_form'];
  }

  if (isset($tasks['install_import_locales_remaining'])) {
    $task_temp['install_import_locales_remaining'] = $tasks['install_import_locales_remaining'];
  }

  if (isset($tasks['install_finished'])) {
    $task_temp['install_finished'] = $tasks['install_finished'];
  }

  // Reset tasks with the newest.
  $tasks = $task_temp;
}
