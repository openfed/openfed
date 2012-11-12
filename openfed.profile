<?php
/**
 * Enables modules and site configuration for a openfed site installation.
 */

// Include all custom function.
require_once('includes/misc/openfed_function.inc');

// Function for the setup of menu.
//require_once('includes/form/openfed_regional_function.inc');

// Function for the setup of menu.
require_once('includes/form/openfed_menu_function.inc');

// Function for the setup of roles.
require_once('includes/form/openfed_role_function.inc');

// Function for the setup of taxonomy.
require_once('includes/form/openfed_taxonomy_function.inc');

// Function for the setup of Defaults user form.
require_once('includes/form/openfed_user_function.inc');

// Function for the setup of additional function.
require_once('includes/form/openfed_functionnalities_form.inc');
  
// Function for the setup of complete step.
require_once('includes/form/openfed_complete_function.inc');

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function openfed_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'OpenFED';
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
  $form['settings']['mysql']['advanced_options']['db_prefix']['#default_value'] = 'drupal_';
  // For SQLITE.
  $form['settings']['sqlite']['advanced_options']['db_prefix']['#default_value'] = 'drupal_';
}

/**
 * Implements hook_install_tasks().
 * task that can be accomplish within the installation process
 */
function openfed_install_tasks($install_state) {
  // load js
  drupal_add_js('profiles/openfed/assets/scripts/openfed.js');
  // load css
  drupal_add_css('profiles/openfed/assets/styles/openfed.css');
  
  //drupal_set_title('openFED7 : '.drupal_get_title());
  $menu_tools = !empty($install_state['parameters']['menu_list']) && $install_state['parameters']['menu_list'] = 'menu-tools-menu'; 
  $menu_footer = !empty($install_state['parameters']['menu_list']) && $install_state['parameters']['menu_list'] = 'menu-footer-menu'; 
  
  $tasks = array();
  
  // Step to choose which language to pre-install.
  // TODO DEBUG why it redirect to the public website
//  $tasks['openfed_regional_form'] = array(
//    'display_name' => st('Setup Regional'),
//    'display' => TRUE,
//    'type' => 'form',
//  );
  
  // Step to choose which menu to pre-install.
  $tasks['openfed_menu_form'] = array(
    'display_name' => st('Setup menu'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which role to pre-install.
  $tasks['openfed_role_form'] = array(
    'display_name' => st('Setup role'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which taxonomy vocabulary to pre-install.
  $tasks['openfed_taxonomy_form'] = array(
    'display_name' => st('Setup taxonomy'),
    'display' => TRUE,
    'type' => 'form',
  );

  // Step to create Default Builder user
  $tasks['openfed_user'] = array(
      'display_name' => st('Setup Builder User'),
  );
    
  // Step to choose which additional functionalities to add.
  $tasks['openfed_functionnalities_form'] = array(
    'display_name' => st('Setup functionnalities'),
    'display' => TRUE,
    'type' => 'form',
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