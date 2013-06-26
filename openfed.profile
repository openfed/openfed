<?php
/**
 * Enables modules and site configuration for a openfed site installation.
 */

// Include all custom function.
require_once('includes/misc/openfed_function.inc');

// Function for the setup of menu.
require_once('includes/form/openfed_regional_function.inc');

// Function for the setup of menu.
require_once('includes/form/openfed_menu_function.inc');

// Function for the setup of roles.
require_once('includes/form/openfed_role_function.inc');

// Function for the setup of taxonomy.
require_once('includes/form/openfed_taxonomy_function.inc');

// Function for the setup of additional function.
require_once('includes/form/openfed_functionalities_form.inc');
  
// Function for the setup of complete step.
require_once('includes/form/openfed_complete_function.inc');

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
 * Allows the profile to alter the site database form.
 * 
 * @param type $form
 * @param type $form_state
 * @param type $install_state 
 */
function system_form_install_settings_form_alter(&$form, &$form_state, &$install_state){
  // Set the default value for the database settings.
  // For MYSQL
  if ( isset($form['settings']['mysql']) ) {
    $form['settings']['mysql']['advanced_options']['db_prefix']['#default_value'] = 'drupal_';
    $form['settings']['mysql']['label_advanced_options'] = array(
      '#markup' => '<label>'.st('By default, a prefix will be set for your tables. If you wish to adapt it, please edit the Advanced Options below.').'</label>',
      '#weight' => 5,
    );
  }
  
  // For SQLITE.
  if ( isset($form['settings']['sqlite']) ) {
    $form['settings']['sqlite']['advanced_options']['db_prefix']['#default_value'] = 'drupal_';
    $form['settings']['sqlite']['label_advanced_options'] = array(
      '#markup' => '<label>'.st('By default, a prefix will be set for your tables. If you wish to adapt it, please edit the Advanced Options below.').'</label>',
      '#weight' => 5,
    );
  }
  
// For PostgreSQL.
  if ( isset($form['settings']['pgsql']) ) {
    $form['settings']['pgsql']['advanced_options']['db_prefix']['#default_value'] = 'drupal_';
    $form['settings']['pgsql']['label_advanced_options'] = array(
      '#markup' => '<label>'.st('By default, a prefix will be set for your tables. If you wish to adapt it, please edit the Advanced Options below.').'</label>',
      '#weight' => 5,
    );
  }
}

/**
 * Implements hook_install_tasks().
 * task that can be accomplish within the installation process
 */
function openfed_install_tasks($install_state) {
  // Load js for custom layout.
  drupal_add_js(drupal_get_path('theme', 'maintenance') . '/assets/scripts/script.js');
  // Load css for custom layout.
  drupal_add_css(drupal_get_path('theme', 'maintenance') . '/assets/styles/design.css');
  
  drupal_set_title('OpenFed : '.  drupal_get_title());
  $menu_tools = !empty($install_state['parameters']['menu_list']) && $install_state['parameters']['menu_list'] = 'menu-tools-menu'; 
  $menu_footer = !empty($install_state['parameters']['menu_list']) && $install_state['parameters']['menu_list'] = 'menu-footer-menu'; 
  
  $tasks = array();
  
  $openfed_need_batch_internalization = variable_get('openfed_need_batch_internalization', FALSE);
  $openfed_need_batch_functionalities = variable_get('openfed_need_batch_functionalities', FALSE);
  
  // Step to choose which language to pre-install.
  $tasks['openfed_regional_form'] = array(
    'display_name' => st('Setup Regional'),
    'display' => TRUE,
    'type' => 'form',
  );
  // batch the process of language activation if a language must be pre-install
  $tasks['openfed_batch_internalization'] = array(
    'display_name' => st('Import internalization'),
    'display' => $openfed_need_batch_internalization,
    'type' => 'batch',
    'run' => $openfed_need_batch_internalization ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
  );
  
  // Step to choose which menu to pre-install.
  $tasks['openfed_menu_form'] = array(
    'display_name' => st('Setup Menu'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which taxonomy vocabulary to pre-install.
  $tasks['openfed_taxonomy_form'] = array(
    'display_name' => st('Setup Taxonomy'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which role to pre-install.
  $tasks['openfed_role_form'] = array(
    'display_name' => st('Setup Role'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which additional functionalities to add.
  $tasks['openfed_functionalities_form'] = array(
    'display_name' => st('Setup Functionalities'),
    'display' => TRUE,
    'type' => 'form',
  );
  $tasks['openfed_batch_functionalities'] = array(
    'display_name' => st('Import functionalities'),
    'display' => $openfed_need_batch_functionalities,
    'type' => 'batch',
    'run' => $openfed_need_batch_functionalities ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
  );
    
  // Step to rebuild permission.
  $tasks['openfed_complete'] = array(
      'display_name' => st('Setup complete'),
  );
    
  return $tasks;
}

/**
 * Implements hook_theme().
 */
function openfed_theme() {
  return array(
    'form_element_checkbox_list' => array(
      'render element' => 'element',
    ),
  );
}


