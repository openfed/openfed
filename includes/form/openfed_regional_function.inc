<?php

/**
 * Return the form for regional set up
 * @return array
 */
function openfed_regional_form() {
  drupal_set_title(st('Regional configuration'));
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the regional languages which have to be foreseen.') . '</p>',
  );

  $form['regional_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Regional languages list'),
    '#options' => _openfed_return_languages_list(),
    '#description' => '<p>' . st('Note : when checking a language, a main menu will automatically be created in the menus list for that language, and the menu will be located in the corresponding Navigation area.<br>
      If no languages are checked, only the English language will be enabled. Consequently, the main menu will be created for the English language only and will be located in the Navigation area. <br>
      Additional languages can be enabled after the installation, but the main menu will then have to be created manually for each language and located in the corresponding area.'
    ) . '</p>'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  return $form;
}

/**
 * manage the submit of the form
 * @param array $form
 * @param array $form_state
 */
function openfed_regional_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if (!empty($values['regional_list'])) {
    $lang = array();
    foreach ($values['regional_list'] as $key => $value) {
      if ($key === $value) {
        $lang[] = $key;
      }
    }
    variable_set('openfed_need_batch_internalization', TRUE);
    variable_set('openfed_need_batch_internalization_lang', $lang);
  }
}

/**
 * batch function to activate language
 */
function openfed_batch_internalization() {
  $values = variable_get('openfed_need_batch_internalization_lang', array());
  $values[] = 'en';

  if (!empty($values)) {
    include_once DRUPAL_ROOT . '/includes/iso.inc';
    $predefined = _locale_get_predefined_list();

    foreach ($values as $key => $value) {
      if ($value != 'en') {
        locale_add_language($value);
        drupal_set_message(t('The language %language has been created and can now be used.', array('%language' => t($predefined[$value][0]))));
      }

      // create basic content in each language
      _openfed_create_content_type($value);
    }
    variable_del('openfed_need_batch_internalization');
    variable_del('openfed_need_batch_internalization_lang');

    _openfed_set_block_into_region('locale', 'language', 'tools');

    module_enable(array('translation_overview'), TRUE);
  }
}

/**
 * create a list of content type for a language
 * * panel for homepage
 * * webform for contact
 * @param string $lang the language code
 */
function _openfed_create_content_type($lang) {

  // check if variable $lang is known in languages_list
  if (array_key_exists($lang, _openfed_return_languages_list()) || $lang == 'en') {

    $ck_link = variable_get('ckeditor_link_autocomplete_menus');

    switch ($lang) {
      case 'en':
        // store main link source variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', 'main-menu');
        
        // show block for english language only
        _openfed_show_block_for_language('system', 'main-menu', $lang);

        // add date format
        $date_format = array();
        $date_format[] = array('format' => 'd/m/Y', 'type' => 'date_only', 'language' => 'en');
        $date_format[] = array('format' => 'c', 'type' => 'html5_tools_iso8601', 'language' => 'en');
        $date_format[] = array('format' => 'l, F j, Y - H:i', 'type' => 'long', 'language' => 'en');
        $date_format[] = array('format' => 'D, d/m/Y - H:i', 'type' => 'medium', 'language' => 'en');
        $date_format[] = array('format' => 'd/m/Y - H:i', 'type' => 'short', 'language' => 'en');
        _openfed_localize_date_format($date_format);

        // adda prefix for english language
        $query = db_update('languages')
          ->fields(array('prefix' => 'en'))
          ->condition('language', 'en', '=')
          ->execute();

        // create webform contact page
        _openfed_create_webform_contact($lang, 'main-menu');

        // create a menu block for submenu
        _openfed_create_submenu($lang, 'main-menu');
      break;

      case 'fr':
        $menu_name = 'main-french-menu';

        // create the french menu
        _openfed_create_custom_menu($menu_name, "Main French Menu", '', '2', 'fr');

        // add custom menu into ckeditor link for autocomplete menu
        $ck_link[$menu_name] = $menu_name;

        // store main link source variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', $menu_name);

        // show block for french language only
        _openfed_show_block_for_language('menu', $menu_name, $lang);

        // add date format
        $date_format = array();
        $date_format[] = array('format' => 'd/m/Y', 'type' => 'date_only', 'language' => 'fr');
        $date_format[] = array('format' => 'c', 'type' => 'html5_tools_iso8601', 'language' => 'fr');
        $date_format[] = array('format' => 'l, j. F Y - G:i', 'type' => 'long', 'language' => 'fr');
        $date_format[] = array('format' => 'D, d/m/Y - H:i', 'type' => 'medium', 'language' => 'fr');
        $date_format[] = array('format' => 'd/m/Y - H:i', 'type' => 'short', 'language' => 'fr');
        _openfed_localize_date_format($date_format);

        // create webform contact page
        _openfed_create_webform_contact($lang, $menu_name);

        // create a menu block for submenu
        _openfed_create_submenu($lang, $menu_name);

        // set the menu in the navigation region for nerra
        _openfed_set_block_into_region('menu', $menu_name, 'navigation');
      break;
    
      case 'nl':
        $menu_name = "main-dutch-menu";

        // create the Dutch menu
        _openfed_create_custom_menu($menu_name, "Main Dutch Menu", '', '2', 'nl');

        // add custom menu into ckeditor link for autocomplete menu
        $ck_link[$menu_name] = $menu_name;

        // store variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', $menu_name);

        // show block for dutch language only
        _openfed_show_block_for_language('menu', $menu_name, $lang);

        // add date format
        $date_format = array();
        $date_format[] = array('format' => 'd/m/Y', 'type' => 'date_only', 'language' => 'nl');
        $date_format[] = array('format' => 'c', 'type' => 'html5_tools_iso8601', 'language' => 'nl');
        $date_format[] = array('format' => 'l, j. F Y - G:i', 'type' => 'long', 'language' => 'nl');
        $date_format[] = array('format' => 'D, d/m/Y - H:i', 'type' => 'medium', 'language' => 'nl');
        $date_format[] = array('format' => 'd/m/Y - H:i', 'type' => 'short', 'language' => 'nl');
        _openfed_localize_date_format($date_format);

        // create webform contact page
        _openfed_create_webform_contact($lang, $menu_name);

        // create a menu block for submenu
        _openfed_create_submenu($lang, $menu_name);

        // set the menu in the navigation region for nerra
        _openfed_set_block_into_region('menu', $menu_name, 'navigation');
      break;
    }
    
    variable_set('ckeditor_link_autocomplete_menus', $ck_link);
  }
}

function _openfed_create_submenu($lang, $menu_name = 'main-menu') {

  switch ($lang) {
    case 'en':
      // EN
      variable_set("menu_block_1_title_link", FALSE);
      variable_set("menu_block_1_admin_title", 'Main menu(2+)');
      variable_set("menu_block_1_parent", 'main-menu:0');
      variable_set("menu_block_1_level", '2');
      variable_set("menu_block_1_follow", FALSE);
      variable_set("menu_block_1_depth", '0');
      variable_set("menu_block_1_expanded", FALSE);
      variable_set("menu_block_1_sort", FALSE);
      variable_set("menu_block_ids", array('1', '2', '3'));
      $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'region', 'status', 'weight', 'delta', 'cache'));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_front_theme_name(),
        'region' => 'sidebar_first',
        'status' => 1,
        'weight' => 0,
        'delta' => 1,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_backend_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 1,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_maintenance_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 1,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->execute();
      break;
    case 'fr':
      // FR
      variable_set("menu_block_2_title_link", FALSE);
      variable_set("menu_block_2_admin_title", 'Main french menu(2+)');
      variable_set("menu_block_2_parent", 'main-french-menu:0');
      variable_set("menu_block_2_level", '2');
      variable_set("menu_block_2_follow", FALSE);
      variable_set("menu_block_2_depth", '0');
      variable_set("menu_block_2_expanded", FALSE);
      variable_set("menu_block_2_sort", FALSE);
      variable_set("menu_block_ids", array('1', '2', '3'));
      $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'region', 'status', 'weight', 'delta', 'cache'));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_front_theme_name(),
        'region' => 'sidebar_first',
        'status' => 1,
        'weight' => 0,
        'delta' => 2,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_backend_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 2,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_maintenance_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 2,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->execute();
      break;
    case 'nl':
      // NL
      variable_set("menu_block_3_title_link", FALSE);
      variable_set("menu_block_3_admin_title", 'Main dutch menu(2+)');
      variable_set("menu_block_3_parent", 'main-dutch-menu:0');
      variable_set("menu_block_3_level", '2');
      variable_set("menu_block_3_follow", FALSE);
      variable_set("menu_block_3_depth", '0');
      variable_set("menu_block_3_expanded", FALSE);
      variable_set("menu_block_3_sort", FALSE);
      variable_set("menu_block_ids", array('1', '2', '3'));
      $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'region', 'status', 'weight', 'delta', 'cache'));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_front_theme_name(),
        'region' => 'sidebar_first',
        'status' => 1,
        'weight' => 0,
        'delta' => 3,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_backend_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 3,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->values(array(
        'visibility' => 0,
        'pages' => '<front>',
        'custom' => 0,
        'title' => '<none>',
        'module' => 'menu_block',
        'theme' => openfed_return_default_maintenance_theme_name(),
        'region' => '',
        'status' => 0,
        'weight' => 0,
        'delta' => 3,
        'cache' => DRUPAL_NO_CACHE,
      ));
      $query->execute();
      break;
  }
}

/**
 * Create a webform
 * @param string $lang
 */
function _openfed_create_webform_contact($lang, $menu_name = 'main-menu') {
  switch ($lang) {
    case 'fr':
      $name = st('Nom');
      $subject = st('Sujet');
      $email = st('Email');
      $message = st('Message');
      break;
    case 'en':
      $name = st('Name');
      $subject = st('Subject');
      $email = st('Email');
      $message = st('Message');
      break;
    case'nl':
      $name = st('Naam');
      $subject = st('Onderwerp');
      $email = st('Email');
      $message = st('Bericht');
      break;
  }

  // Creating webform node
  $node = new stdClass();
  $node->type = 'webform';
  $node->title = "Contact";
  $node->language = $lang;
  $node->status = 1;
  $node->tnid = 1;
  node_object_prepare($node);

  $node->menu = array(
    'enabled' => 1,
    'mlid' => 0,
    'module' => 'menu',
    'hidden' => 0,
    'has_children' => 0,
    'customized' => 0,
    'options' => array(),
    'expanded' => 0,
    'parent_depth_limit' => 8,
    'link_title' => $node->title,
    'description' => '',
    'parent' => $menu_name . ':0',
    'weight' => 10,
    'plid' => 0,
    'menu_name' => $menu_name
  );
  node_save($node);

  // assign components to webform
  $components = array(
    0 => array(
      'name' => $name,
      'form_key' => strtolower($name),
      'type' => 'textfield',
      'mandatory' => 1,
      'weight' => 0,
      'pid' => 0
    ),
    1 => array(
      'name' => $email,
      'form_key' => strtolower($email),
      'type' => 'email',
      'mandatory' => 1,
      'weight' => 1,
      'pid' => 0
    ),
    2 => array(
      'name' => $subject,
      'form_key' => strtolower($subject),
      'type' => 'textfield',
      'mandatory' => 1,
      'weight' => 2,
      'pid' => 0
    ),
    3 => array(
      'name' => $message,
      'form_key' => strtolower($message),
      'type' => 'textarea',
      'mandatory' => 1,
      'weight' => 3,
      'pid' => 0
    ),
  );

  foreach ($components as $component) {
    $component['nid'] = $node->nid;
    $component['extra']['title_display'] = 'inline';
    $node->webform['components'][] = $component;
    webform_component_insert($component);
  }
}

/**
 * add a date format in database
 * @param array $date_format
 */
function _openfed_localize_date_format($date_format) {
  foreach ($date_format as $key => $date_format_locale) {
    drupal_write_record('date_format_locale', $date_format_locale);
  }
}