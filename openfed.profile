<?php

/**
 * @file
 * Profile file of Openfed that modifies the install form.
 */

use Drupal\Core\Extension\Extension;
use Drupal\Core\Extension\ExtensionLifecycle;
use Drupal\openfed\Form\SetupLanguagesForm;
use Drupal\openfed\Form\SetupMenusForm;
use Drupal\openfed\Form\SetupRolesForm;
use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_install_tasks().
 */
function openfed_install_tasks(array &$install_state) {
  return [
    'openfed_setup_languages' => [
      'display_name' => t('Set up languages'),
      'display' => TRUE,
      'type' => 'form',
      'function' => SetupLanguagesForm::class,
    ],

    // Step to choose which menus to pre-install.
    'openfed_install_menu_form' => [
      'display_name' => t('Set up menus'),
      'display' => TRUE,
      'type' => 'form',
      'function' => SetupMenusForm::class,
    ],

    // Step to choose which roles to pre-install.
    'openfed_install_role_form' => [
      'display_name' => t('Set up roles'),
      'display' => TRUE,
      'type' => 'form',
      'function' => SetupRolesForm::class,
    ],
  ];
}

/**
 * Implements hook_install_tasks_alter().
 */
function openfed_install_tasks_alter(array &$tasks, array $install_state) {
  // We'll ignore the language selection task since English will be our default.
  $tasks['install_select_language'] = [
    'function' => 'openfed_install_select_language',
    'display' => FALSE,
    'run' => INSTALL_TASK_SKIP,
  ];

  // Run post-installation tasks.
  $tasks['install_finished']['function'] = 'openfed_post_install';
}

/**
 * Implements hook_form_FORM_ID_alter() for the install_configure_form() form.
 *
 * @param array $form
 * @param \Drupal\Core\Form\FormStateInterface $form_state
 * @param string $form_id
 */
function openfed_form_install_configure_form_alter(array &$form, FormStateInterface $form_state, $form_id) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'OpenFed';
  $form['regional_settings']['site_default_country']['#default_value'] = 'BE';
  $form['regional_settings']['date_default_timezone']['#default_value'] = 'Europe/Brussels';

  // Add an option to enable openfed_federalheader module.
  $form['regional_settings']['extra_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Extra settings'),
    '#weight' => 10,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  ];
  $form['regional_settings']['extra_settings']['enable_federalheader'] = [
    '#type' => 'checkbox',
    '#title' => t('Enable Openfed federal header module'),
    '#default_value' => 1
  ];

  // No check for updates, no need for email notifications
  $form['update_notifications']['enable_update_status_module']['#default_value'] = 0;
  $form['update_notifications']['enable_update_status_emails']['#default_value'] = 0;

  $form['#submit'][] = 'openfed_form_install_optional_settings';

}

/**
 * Submit hook to set up HTTPS.
 */
function openfed_form_install_optional_settings(array &$form, FormStateInterface $form_state) {
  if ($form_state->getValue('enable_federalheader') == 1) {
    \Drupal::service('module_installer')->install(['openfed_federalheader']);
  }
}

/**
 * Defines things to do after installation.
 */
function openfed_post_install() {
  // Get rid of "The content access permissions need to be rebuilt" message.
  node_access_rebuild();
}

/**
 * Implements hook_system_info_alter().
 */
function openfed_system_info_alter(array &$info, Extension $file, $type): void {
  // Only act on modules.
  if ($type !== 'module') {
    return;
  }

  // List of deprecated modules in Openfed.
  $deprecated_modules = [
    'ckeditor_templates',
    'ckeditor4_codemirror',
    'anchor_link',
    'fakeobjects',
    'ckeditor_config',
    'ckeditor',
  ];

  // Check if the module is deprecated.
  if (!in_array($file->getName(), $deprecated_modules)) {
    return;
  }

  // Skip if lifecycle info is already set.
  if (isset($info[ExtensionLifecycle::LIFECYCLE_IDENTIFIER]) && $info[ExtensionLifecycle::LIFECYCLE_IDENTIFIER] === ExtensionLifecycle::DEPRECATED) {
    return;
  }

  // Mark the module as deprecated.
  $info[ExtensionLifecycle::LIFECYCLE_IDENTIFIER] = ExtensionLifecycle::DEPRECATED;
  $info[ExtensionLifecycle::LIFECYCLE_LINK_IDENTIFIER] = "https://github.com/openfed/openfed?tab=readme-ov-file#installation";
}
