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
require_once('includes/form/openfed_contenttypes_form.inc');
  
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
  $openfed_need_batch_contenttypes = variable_get('openfed_need_batch_contenttypes', FALSE);
  
  // Step to choose which language to pre-install.
  $tasks['openfed_regional_form'] = array(
    'display_name' => st('Enable languages'),
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
    'display_name' => st('Enable menus'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which taxonomy vocabulary to pre-install.
  $tasks['openfed_taxonomy_form'] = array(
    'display_name' => st('Enable taxonomy'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which role to pre-install.
  $tasks['openfed_role_form'] = array(
    'display_name' => st('Enable roles'),
    'display' => TRUE,
    'type' => 'form',
  );
    
  // Step to choose which additional contenttypes to add.
  $tasks['openfed_contenttypes_form'] = array(
    'display_name' => st('Enable content types'),
    'display' => TRUE,
    'type' => 'form',
  );
  $tasks['openfed_batch_contenttypes'] = array(
    'display_name' => st('Import content types'),
    'display' => $openfed_need_batch_contenttypes,
    'type' => 'batch',
    'run' => $openfed_need_batch_contenttypes ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
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
