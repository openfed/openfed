<?php

/**
 * @file
 * Administrative page callbacks for the Administrative pages module.
 */

/**
 * Return the admin form to allow to display check the requirement.
 * @return void
 */
function ofed_requirements_admin_requirements_form() {
  // Initialize.
  $form = array();

  // Fieldset for the roles list.
  $errors = _ofed_requirements_check_roles();
  $remark = variable_get('ofed_requirements_remarks_roles', '');
  $form['checks']['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check the defined users roles'),
    '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
    '#collapsible' => TRUE,
    '#attributes' => array(
      'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
    ),
    '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
  );
  $form['checks']['roles']['ofed_requirements_remarks_roles'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a remark / justification about this check:'),
    '#default_value' => variable_get('ofed_requirements_remarks_roles', ''),
    '#rows' => 10,
    '#required' => (empty($errors)) ? FALSE : TRUE,
  );

  // Fieldset for the permissions list.
  $errors = _ofed_requirements_check_perms();
  $remark = variable_get('ofed_requirements_remarks_perms', '');
  $form['checks']['permissions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check the permissions assigned to roles'),
    '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
    '#collapsible' => TRUE,
    '#attributes' => array(
      'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
    ),
    '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
  );
  $form['checks']['permissions']['ofed_requirements_remarks_perms'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a remark / justification about this check:'),
    '#default_value' => variable_get('ofed_requirements_remarks_perms', ''),
    '#rows' => 10,
    '#required' => (empty($errors)) ? FALSE : TRUE,
  );

  // Fieldset for modules enabled list.
  $errors = _ofed_requirements_check_modules_enabled();
  $remark = variable_get('ofed_requirements_remarks_modules_enabled', '');
  $form['checks']['modules_enabled'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check the enabled modules'),
    '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
    '#collapsible' => TRUE,
    '#attributes' => array(
      'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
    ),
    '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
  );
  $form['checks']['modules_enabled']['ofed_requirements_remarks_modules_enabled'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a remark / justification about this check:'),
    '#default_value' => variable_get('ofed_requirements_remarks_modules_enabled', ''),
    '#rows' => 10,
    '#required' => (empty($errors)) ? FALSE : TRUE,
  );

  // Fieldset for modules version list.
  $errors = _ofed_requirements_check_modules_version();
  $remark = variable_get('ofed_requirements_remarks_modules_version', '');
  $form['checks']['modules_version'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check the modules version'),
    '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
    '#collapsible' => TRUE,
    '#attributes' => array(
      'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
    ),
    '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
  );
  $form['checks']['modules_version']['ofed_requirements_remarks_modules_version'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a remark / justification about this check:'),
    '#default_value' => variable_get('ofed_requirements_remarks_modules_version', ''),
    '#rows' => 10,
    '#required' => (empty($errors)) ? FALSE : TRUE,
  );

  // Fieldset for modules / variables list.
  $errors = _ofed_requirements_check_variables();
  $remark = variable_get('ofed_requirements_remarks_variables', '');
  $form['checks']['variables'] = array(
    '#type' => 'fieldset',
    '#title' => t('Check the settings variables'),
    '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
    '#collapsible' => TRUE,
    '#attributes' => array(
      'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
    ),
    '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
  );
  $form['checks']['variables']['ofed_requirements_remarks_variables'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a remark / justification about this check:'),
    '#default_value' => variable_get('ofed_requirements_remarks_variables', ''),
    '#rows' => 10,
    '#required' => (empty($errors)) ? FALSE : TRUE,
  );

  // Fieldsets for each OpenFed features.
  $features = array(
    'ofed_feature_address' => 'OpenFed "Address" feature',
    'ofed_feature_banner' => 'OpenFed "Banners" feature',
    'ofed_feature_download' => 'OpenFed "Downloads" feature',
    'ofed_feature_event' => 'OpenFed "Events" feature',
    'ofed_feature_faq' => 'OpenFed "FAQ\'s" feature',
    'ofed_feature_job' => 'OpenFed "Jobs" feature',
    'ofed_feature_meeting' => 'OpenFed "Meeting" feature',
    'ofed_feature_news' => 'OpenFed "News" feature',
    'ofed_feature_page' => 'OpenFed "Pages" feature',
    'ofed_feature_photogallery' => 'OpenFed "Photos galeries" feature',
    'ofed_feature_press' => 'OpenFed "Press" feature',
    'ofed_feature_slider' => 'OpenFed "Slider" feature',
    'ofed_feature_slideshow' => 'OpenFed "Slideshows" feature',
    'ofed_feature_team' => 'OpenFed "Team members" feature',
    'ofed_feature_video' => 'OpenFed "Videos" feature',
  );
  foreach ($features as $feature_key => $feature_name) {
    $errors = _ofed_requirements_check_feature($feature_key, $feature_name);
    $remark = variable_get('ofed_requirements_remarks_feature_' . $feature_key, '');
    $form['checks']['features' . $feature_key] = array(
      '#type' => 'fieldset',
      '#title' => t('Check the !feature', array('!feature' => $feature_name)),
      '#collapsed' => (empty($errors) && empty($remark)) ? TRUE : FALSE,
      '#collapsible' => TRUE,
      '#attributes' => array(
        'class' => (empty($errors)) ? array('check-succeed') : array('check-failed'),
      ),
      '#description' => (!empty($errors)) ? '<ul class="check-errors"><li>' . implode($errors, '</li><li>') . '</u></li>' : '',
    );
    $form['checks']['features' . $feature_key]['ofed_requirements_remarks_feature_' . $feature_key] = array(
      '#type' => 'textarea',
      '#title' => t('Add a remark / justification about this check:'),
      '#default_value' => variable_get('ofed_requirements_remarks_feature_' . $feature_key, ''),
      '#rows' => 10,
      '#required' => (empty($errors)) ? FALSE : TRUE,
    );
  }

  // Add the button to clear notes.
  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Clear notes'),
    '#weight' => 1,
    '#limit_validation_errors' => array(),
    '#submit' => array('ofed_requirements_admin_requirements_notes_reset_redirect'),
  );

  // Add the button to export notes.
  $form['actions']['export'] = array(
    '#type' => 'submit',
    '#value' => t('Export notes'),
    '#weight' => 2,
    '#submit' => array('ofed_requirements_admin_requirements_notes_export'),
  );

  // Return.
  return system_settings_form($form);
}

/**
 * Implements hook_form_alter().
 * @param type $form
 * @param type $form_state
 * @param type $form_id
 */
function ofed_requirements_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'ofed_requirements_admin_requirements_form') {
    $form['actions']['submit']['#value'] = t('Save notes');
    $form['actions']['submit']['#weight'] = 0;
  }
}

/**
 * Reditect to the confirm form.
 */
function ofed_requirements_admin_requirements_notes_reset_redirect() {
  drupal_goto('admin/openfed/requirements/reset');
}

/**
 * Form confirm for the reset button.
 */
function ofed_requirements_admin_requirements_notes_reset_confirm() {
  return confirm_form(
    array(), t('Are you sure you want to remove all notes ?'), 'admin/openfed/requirements', t('This action cannot be undone.'), t('Remove notes'), t('Cancel')
  );
}

/**
 * Form submit for the reset confirm.
 * @param type $form
 * @param type $form_state
 */
function ofed_requirements_admin_requirements_notes_reset_confirm_submit($form, &$form_state) {
  // Get all variables used for remarks and erase it.
  $result = db_query("SELECT name FROM {variable} WHERE name LIKE 'ofed_requirements_remarks_%'");
  foreach ($result as $record) {
    variable_set($record->name, '');
  }
  drupal_set_message('All notes has been deleted.');
  drupal_goto('admin/openfed/requirements');
}

/**
 * Build and return the report text for a specific test.
 * @param string $title  The title of the test.
 * @param array $errors The errors.
 * @param string $remark The remark.
 * @return string
 */
function ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark) {
  // Initialize.
  $output = '';

  $output .= '--------------------------------------------------------------------------------------------------------------' . "\n";

  // Build text.
  $status = (empty($errors)) ? 'Success' : 'Failed';
  $output .= 'TEST: ' . $title . ' (' . $status . ').' . "\n\n";

  $status = (empty($errors)) ? 'None' : '';
  $output .= 'Error(s): ' . $status . "\n";
  if (!empty($errors)) {
    $output .= '---------' . "\n";
    foreach ($errors as $error) {
      $output .= $error . "\n";
    }
  }

  $status = (empty($remark)) ? 'None' : '';
  $output .= 'Remark(s): ' . $status . "\n";
  if (!empty($remark)) {
    $output .= '----------' . "\n";
    $output .= $remark . "\n";
  }
  else {
    $output .= "\n";
  }

  // Return.
  return $output;
}

/**
 * Export file.
 */
function ofed_requirements_admin_requirements_notes_export() {
  // Initialize.
  $output = '';

  // Build the file content.
  $output .= 'FEDICT REQUIREMENT FILE REPORT.' . "\n";
  $output .= '-------------------------------' . "\n";
  $output .= 'Report date: ' . date('d/m/Y H:i:s') . "\n\n";

  // Add roles infos.
  $title = 'Check the defined users roles';
  $errors = _ofed_requirements_check_roles();
  $remark = variable_get('ofed_requirements_remarks_roles', '');
  $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);

  // Add permissions infos.
  $title = 'Check the permissions assigned to roles';
  $errors = _ofed_requirements_check_perms();
  $remark = variable_get('ofed_requirements_remarks_perms', '');
  $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);

  // Add modules enabled list infos.
  $title = 'Check the enabled modules';
  $errors = _ofed_requirements_check_modules_enabled();
  $remark = variable_get('ofed_requirements_remarks_modules_enabled', '');
  $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);

  // Add modules versions list infos.
  $title = 'Check the modules version';
  $errors = _ofed_requirements_check_modules_version();
  $remark = variable_get('ofed_requirements_remarks_modules_version', '');
  $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);

  // Add variables infos.
  $title = 'Check the settings variables';
  $errors = _ofed_requirements_check_variables();
  $remark = variable_get('ofed_requirements_remarks_variables', '');
  $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);

  // Add feature infos.
  // Fieldsets for each OpenFed features.
  $features = array(
    'ofed_feature_address' => 'OpenFed "Address" feature',
    'ofed_feature_banner' => 'OpenFed "Banners" feature',
    'ofed_feature_download' => 'OpenFed "Downloads" feature',
    'ofed_feature_event' => 'OpenFed "Events" feature',
    'ofed_feature_faq' => 'OpenFed "FAQ\'s" feature',
    'ofed_feature_job' => 'OpenFed "Jobs" feature',
    'ofed_feature_meeting' => 'OpenFed "Meeting" feature',
    'ofed_feature_news' => 'OpenFed "News" feature',
    'ofed_feature_page' => 'OpenFed "Pages" feature',
    'ofed_feature_photogallery' => 'OpenFed "Photos galeries" feature',
    'ofed_feature_press' => 'OpenFed "Press" feature',
    'ofed_feature_slider' => 'OpenFed "Slider" feature',
    'ofed_feature_slideshow' => 'OpenFed "Slideshows" feature',
    'ofed_feature_team' => 'OpenFed "Team members" feature',
    'ofed_feature_video' => 'OpenFed "Videos" feature',
  );
  foreach ($features as $feature_key => $feature_name) {
    $title = t('Check the !feature', array('!feature' => $feature_name));
    $errors = _ofed_requirements_check_feature($feature_key, $feature_name);
    $remark = variable_get('ofed_requirements_remarks_feature_' . $feature_key, '');
    $output .= ofed_requirements_admin_requirements_build_report_text_for_test($title, $errors, $remark);
  }

  // Set the file path.
  $filpath = drupal_realpath('private://') . '/fedict-requirement-report.log';

  // Save the temporary file content.
  file_unmanaged_save_data($output, $filpath, FILE_EXISTS_REPLACE);

  // Force the download of the file.
  if (file_exists($filpath)) {
    header('Content-Description: File Transfer');
    header('Content-Type: application/octet-stream');
    header('Content-Disposition: attachment; filename=' . basename($filpath));
    header('Content-Transfer-Encoding: binary');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . filesize($filpath));
    ob_clean();
    flush();
    readfile($filpath);
    exit;
  }
}

/**
 * Check the permissions.
 * @param none
 * @return $array
 */
function _ofed_requirements_check_perms() {
  // Initialize.
  $errors = array();

  // Load OpenFed function file.
  module_load_include('inc', 'openfed', 'openfed_function');

  // Get the default roles names.
  $roles_default = _openfed_return_roles_list_available_by_default();
  // Get the actual role names.
  $roles_actuals = user_roles();

  // Check only for used roles included by default in the distribution.
  foreach ($roles_actuals as $role_actual_id => $role_actual_name) {
    if (in_array($role_actual_name, $roles_default)) {
      // Get the default perms for the current role.
      switch ($role_actual_name) {
        case 'anonymous user':
          $perms_default = _openfed_return_permission_anonymous_user();
          break;

        case 'authenticated user':
          $perms_default = _openfed_return_permission_authenticated_user();
          break;

        case 'Builder':
          $perms_default = _openfed_return_permission_builder();
          break;

        case 'Configurator':
          $perms_default = _openfed_return_permission_configurator();
          break;

        case 'Content Manager':
          $perms_default = _openfed_return_permission_content_manager();
          break;

        case 'User Manager':
          $perms_default = _openfed_return_permission_user_manager();
          break;

        case 'Authenticated Visitor':
          $perms_default = _openfed_return_permission_authenticated_visitor();
          break;

        default:
          // Do nothing...
          break;
      }

      // Get actuals perms.
      $perms_actuals = user_role_permissions(array($role_actual_id => $role_actual_name));
      $perms_actuals = $perms_actuals[$role_actual_id];

      // Compare the both perms list.
      if ($role_actual_name != 'Administrator') {
        // Get the removed perms.
        foreach ($perms_default as $perm_default_key => $perm_default_value) {
          // Check if the perms is in the array.
          if (!in_array($perm_default_key, $perms_actuals)) {
            $errors[] = t('The permission "!perm_name" was removed for the user role "!user_role".', array('!user_role' => strtolower($role_actual_name), '!perm_name' => $perm_default_key));
          }

          // Get the difference by deliting exiting.
          if (isset($perms_actuals[$perm_default_key])) {
            unset($perms_actuals[$perm_default_key]);
          }
        }
        // Get the added perms.
        foreach ($perms_actuals as $perm_actual_key => $perm_actual_value) {
          $errors[] = t('The permission "!perm_name" was added to the user role "!user_role".', array('!user_role' => strtolower($role_actual_name), '!perm_name' => $perm_actual_key));
        }
      }
    }
  }

  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}

/**
 * Check the roles.
 * @param none
 * @return $array
 */
function _ofed_requirements_check_roles() {
  // Initialize.
  $errors = array();

  // Load OpenFed function file.
  module_load_include('inc', 'openfed', 'openfed_function');

  // Get the default roles names.
  $roles_default = _openfed_return_roles_list_available_by_default();
  // Get the actual role names.
  $roles_actuals = user_roles();

  // Check which roles are not included by default in the distribution.
  foreach ($roles_actuals as $role_actual) {
    if (!in_array($role_actual, $roles_default)) {
      $errors[] = t('The user role "!user_role" is not include by default.', array('!user_role' => $role_actual));
    }
  }

  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}

/**
 * Check the modules.
 * @param none
 * @return $array
 */
function _ofed_requirements_check_modules_enabled() {
  // Initialize.
  $errors = array();

  // Test to check if the php_filter is enabled.
  if (module_exists('php')) {
    $errors[] = t('The "PHP filter" module is enabled.');
  }

  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}

/**
 * Check the modules version.
 * @param none
 * @return $array
 */
function _ofed_requirements_check_modules_version() {
  // Initialize.
  $errors = array();

  // Get the drupal.org.make file to fecth the default module versions.
  $infos = drupal_parse_info_file('profiles/openfed/drupal-org.make');
  foreach ($infos['projects'] as $project_name => $project_infos) {
    // Check only enabled module.
    if (module_exists($project_name)) {
      // Get inforamtion from the database.
      $result = db_select('system', 's')->fields('s', array('name', 'info'))->condition('name', $project_name)->execute();
      $result = $result->fetchAssoc();
      $info_base = unserialize($result['info']);

      // Get module versions.
      $info_version_base = $info_base['version'];
      $info_version_file = '7.x-' . $project_infos['version'];

      // Check module versions.
      if ($info_version_base != $info_version_file) {
        $errors[] = t('The actual version (!version_database) of module "!module_name" is not the same than the default version (!version_file) of this module.', array('!module_name' => $project_name, '!version_database' => $info_version_base, '!version_file' => $info_version_file));
      }
    }
  }

  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}

/**
 * Check the variables.
 * @param none
 * @return $array
 */
function _ofed_requirements_check_variables() {
  // Initialize.
  $errors = array();

  // Nothing for the moment because nothing to test :) but already ready to work... so be happy !
  // Smile :)
  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}

/**
 * Check the feature.
 * @param string $feature_key  The technical name of the feature.
 * @param string $feature_name The human name of the feature.
 * @return $array
 */
function _ofed_requirements_check_feature($feature_key, $feature_name) {
  // Initialize.
  $errors = array();

  module_load_include('inc', 'features', 'features.export');
  $feature_status = features_get_storage($feature_key);
  // Switch on status.
  switch ($feature_status) {
    case FEATURES_NEEDS_REVIEW:
      // Actual code state != Database content != File content (see api.txt in feature module.)
      $errors[] = t('The !feature needs review. The feature does match with the feature file content.', array('!feature' => $feature_name));
      break;

    case FEATURES_OVERRIDDEN:
      // Actual code state = Database content != File content (see api.txt in feature module.)
      $errors[] = t('The !feature is overrided. The feature does match with the feature file content.', array('!feature' => $feature_name));
      break;

    default:
    case FEATURES_DEFAULT:
      // Do nothing :)
      break;
  }

  // If the feature needs review or is overrided;
  if ($feature_status == FEATURES_NEEDS_REVIEW || $feature_status == FEATURES_OVERRIDDEN) {
    // Define component names (used for message).
    $component_names = array(
      'ctools' => 'CTools API',
      'features_api' => 'Features API',
      'field' => 'Fields',
      'image' => 'Image styles',
      'metatag' => 'Meta tags',
      'node' => 'Content types',
      'rules_config' => 'Rules configuration',
      'taxonomy' => 'Taxonomy',
      'variable' => 'Strongarm',
      'views_view' => 'Views',
    );

    // Load feature.
    $feature = features_load_feature($feature_key);
    // Get component state.
    $states = features_get_component_states(array($feature->name), FALSE);
    foreach ($feature->info['features'] as $component => $items) {
      // Get the component status.
      $component_status = FEATURES_DEFAULT;
      if (array_key_exists($component, $states[$feature->name])) {
        $component_status = $states[$feature->name][$component];
      }

      // Get the component name.
      $component_name = t('Unknown component name');
      if (array_key_exists($component, $component_names)) {
        $component_name = $component_names[$component];
      }

      // Switch on status.
      switch ($component_status) {
        case FEATURES_NEEDS_REVIEW:
          // Actual code state != Database content != File content (see api.txt in feature module.)
          $errors[] = t('The component "!component" needs review.', array('!component' => $component_name));
          break;

        case FEATURES_OVERRIDDEN:
          // Actual code state = Database content != File content (see api.txt in feature module.)
          $errors[] = t('The component "!component" is overrided.', array('!component' => $component_name));
          break;

        default:
        case FEATURES_DEFAULT:
          // Do nothing :)
          break;
      }
    }
  }

  // Count errors.
  if (!empty($errors)) {
    array_unshift($errors, t('!count error(s) found !', array('!count' => count($errors))));
  }

  // Return.
  return $errors;
}