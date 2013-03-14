<?php

/**
 * @file
 * Administrative page callbacks for the Administrative pages module.
 */

/**
 * Return the admin form to allow to configure the module.
 * @return void
 */
function ofed_pagemodel_admin_settings_form() {
  // Initialize.
  $form = array();
  
  // Fieldset for the number of column.
  $form['ofed_pagemodel_allowed_choices_columns'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Allowed choices of columns'),
  );
  
  $form['ofed_pagemodel_allowed_choices_columns']['ofed_pagemodel_allowed_choices_columns'] = array(
    '#title' => '',
    '#description' => t('Define the allowed choices of columns, separated by a comma. eg: 2, 5 (for two and five columns but not for 1, 3, 4)'), 
    '#type' => 'textfield',
    '#default_value' => variable_get('ofed_pagemodel_allowed_choices_columns', '1, 2, 3'),
  );
  
  // Fieldset for the associated views displays.
  $form['ofed_pagemodel_associed_displays'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Associated views displays'),
  );
  
  // Generate the options list.
  $options = array();
  // Get all views.
  $views = views_get_all_views();
  // For each views.
  foreach ($views as $view) {
    // If the view is active.
    if (!$view->disabled) {
      // If displays exist.
      if (!empty($view->display)) {
        // For each displays.
        foreach ($view->display as $display) {
          // If the display is not the default display.
          if ($display->id != 'default' && $display->id != $view->name . '_cms') {
            $human_name = (!empty($view->human_name)) ? $view->human_name : $view->name;
            $options[$view->name . '_' . $display->id] = $human_name . ' - ' . $display->display_title;
          }
        }
      }
    }
  }
  
  if (!empty($options)) {
    $form['ofed_pagemodel_associed_displays']['ofed_pagemodel_associed_displays'] = array(
      '#title' => '',
      '#description' => t('Select the displays where it\'s allowed to select the render of the output.'), 
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => variable_get('ofed_pagemodel_associed_displays', array()),
    );
  }
  else {
    $form['ofed_pagemodel_settings']['#description'] = t('No views with specific(s) display(s) are enabled.');
  }
  
  // Return.
  return system_settings_form($form);
}
