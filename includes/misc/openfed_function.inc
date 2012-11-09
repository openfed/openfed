<?php

/**
 * Return the array for the list of all roles.
 * 
 * @return string 
 */
function openfed_getAllRoles() {
  $role_list = array(
    //'builder' => 'Builder: gives access to the features activation once the website is set up (modules and content-types)',
    'configurator' => 'Configurator: gives access to the modules and content-types configuration',
    'editor' => 'Editor: if there will be a content editor, who will have access to the CMS and who will be able to manage full html format',
    'user' => 'User: if there will be authenticated users on the website, able to manage filtered html'
  );
  return $role_list;
}

/**
 * Return the array for the list of all functionalities.
 * 
 * @return string 
 */
function openfed_getAllFunctionalities() {
  $features = drupal_get_path('profile', 'openfed').'/assets/images/features.gif';
  $modules = drupal_get_path('profile', 'openfed').'/assets/images/modules.gif';
  
  $function_list = array(
    // Content types
    'ofed_page' => array(
      'title' => 'Pages',
      'picture' => $features,
      'description' => 'Enables the creation of content page.',
    ),
    'ofed_banner' => array(
      'title' => 'Banners',
      'picture' => $features,
      'description' => 'Enables the creation of banner.',
    ),
    'ofed_new' => array(
      'title' => 'News',
      'picture' => $features,
      'description' => 'Enables the creation of news.',
    ),
    'ofed_download' => array(
      'title' => 'Downloads',
      'picture' => $features,
      'description' => 'Enables the creation of download files.',
    ),
    'webform' => array(
      'title' => 'Webform',
      'picture' => $features,
      'description' => 'Enables the creation of forms and questionnaires.',
    ),
    'poll' => array(
      'title' => 'Poll',
      'picture' => $features,
      'description' => 'Enables the creation of poll.',
    ),
    'blog' => array(
      'title' => 'Blog',
      'picture' => $features,
      'description' => 'Enables the creation of blog.',
    ),
    
    // Modules
    'ofed_switcher' => array(
      'title' => 'Interface Switcher',
      'picture' => $modules,
      'description' => 'Add a block to switch between public website and administration.',
    ),
    'ofed' => array(
      'title' => 'Ofed',
      'picture' => $features,
      'description' => 'extend views with Helper for openFED suite',
    ),
    'ofed_federal_header' => array(
      'title' => 'Federal header',
      'picture' => $features,
      'description' => 'Provide the official Belgian Federal Authorities header.',
    ),
      
    'backup_migrate' => array(
      'title' => 'Backup Migrate',
      'picture' => $modules,
      'description' => 'Backup or migrate the Drupal Database quickly and without unnecessary data.',
    ),
    'beididp' => array(
      'title' => 'Belgian eID IDP Integration',
      'picture' => $modules,
      'description' => "Allows users to authenticate with their Belgian eID card, using Fedict's OpenID Identity provider.",
    ),
    'content_access' => array(
      'title' => 'Content Access',
      'picture' => $modules,
      'description' => 'Provides flexible content access control.',
    ),
    'countries' => array(
      'title' => 'Countries',
      'picture' => $modules,
      'description' => 'A module that provides a FAPI / Field country element and a simple wrapper module to store / update country data.',
    ),
    'diff' => array(
      'title' => 'Diff',
      'picture' => $modules,
      'description' => 'Show difference between node revisions.',
    ),
    'field_permission' => array(
      'title' => 'Field Permission',
      'picture' => $modules,
      'description' => 'Set field-level permissions to create, update or view fields.',
    ),
    'l10n_client' => array(
      'title' => 'Localization client',
      'picture' => $modules,
      'description' => 'Provides on-page localization',
    ),
    'module_filter' => array(
      'title' => 'Module filter',
      'picture' => $modules,
      'description' => 'Filter the modules list.',
    ),
    'multiple_node_menu' => array(
      'title' => 'Multiple node menu',
      'picture' => $modules,
      'description' => 'Replaces the node menu form with one that can handle multiple parents.',
    ),
    'performance' => array(
      'title' => 'Performance',
      'picture' => $modules,
      'description' => 'Logs detailed and/or summary page generation time and memory consumption for page requests.',
    ),
    'role_delegation' => array(
      'title' => 'Role delegation',
      'picture' => $modules,
      'description' => 'Allows site administrators to grant some roles the authority to assign selected roles to users.',
    ),
    'securelogin' => array(
      'title' => 'Secure login',
      'picture' => $modules,
      'description' => 'Enables secure login.',
    ),
      
      
      

  );
  return $function_list;
}

/**
 * Preprocess of the module list in functionalities install task
 * use this if you want to have a description and full description on checkboxes list.
 * 
 * @param array $element
 * @return array 
 */
function form_process_checkboxes_at_install($element) {
  $value = is_array($element['#value']) ? $element['#value'] : array();
  $element['#tree'] = TRUE;
  if(count($element['#options']) > 0) {
    if(!isset($element['#default_value']) || $element['#default_value'] == 0) {
      $element['#default_value'] = array();
    }
    $weight = 0;
    foreach($element['#options'] as $key => $choice) {
      // Integer 0 is not a valid #return_value, so use '0' instead.
      // @see form_type_checkbox_value().
      // @todo For Drupal 8, cast all integer keys to strings for consistency
      //   with form_process_radios().
      if($key === 0) {
        $key = '0';
      }
      // Maintain order of options as defined in #options, in case the element
      // defines custom option sub-elements, but does not define all option
      // sub-elements.
      $weight += 0.001;

      $element += array($key => array());
      $element[$key] += array(
        '#type' => 'checkbox',
        '#title' => $choice['title'],
        '#return_value' => $key,
        '#default_value' => isset($value[$key]) ? $key : NULL,
        '#attributes' => $element['#attributes'],
        '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
        '#weight' => $weight,
        '#description' => isset($choice['description']) ? $choice['description'] : NULL, // add a description to the element
        '#full_description' => isset($choice['full_description']) ? $choice['full_description'] : NULL, // add a new variable to the element
        '#picture' => isset($choice['picture']) ? $choice['picture'] : NULL, // add a new variable to the element
        '#process' => array('form_process_checkbox', 'ajax_process_form'), // override process for theming element
        '#theme_wrappers' => array('form_element_checkbox_list'), // override process for theming wrapper
      );
    }
  }
  return $element;
}

/**
 * Return the template for a checkbox item with description and full description possibilities.
 * 
 * @param array $variables
 * @return string 
 */
function theme_form_element_checkbox_list($variables) {
  $element = &$variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if(isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if(!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if(!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if(!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if(!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if(!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }
  // Manage the new variable
  if(!empty($element['#full_description'])) {
    $output .= '<div class="full-description">' . $element['#full_description'] . "</div>\n";
  }
  if(!empty($element['#picture'])) {
    $output .= '<div class="picture">' . theme('image', array( 'path' => $element['#picture'] )) . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

