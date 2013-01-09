<?php

/**
 * Return the form for regional set up
 * @return array 
 */
function openfed_regional_form() {
  drupal_set_title(st('Regional configuration'));
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the regional languages which have to be foreseen:') . '</p>',
  );
  $form['regional_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Regional languages list'),
    '#options' => _openfed_return_languages_list(),
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
  _openfed_create_panel_node_frontpage('en');
  if ( !empty($values['regional_list']) ) {
    $lang = array();
    foreach( $values['regional_list'] as $key => $value ) {
      if ( $key === $value ) {
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
  $values = variable_get( 'openfed_need_batch_internalization_lang' );
  
  if ( !empty($values) ) {
    include_once DRUPAL_ROOT . '/includes/iso.inc';
    $predefined = _locale_get_predefined_list();
    
    foreach( $values as $key => $value ) {
      locale_add_language($value);
      drupal_set_message(t('The language %language has been created and can now be used.', array('%language' => t($predefined[$value][0]))));
//      if ($batch = locale_batch_by_language($value, '_locale_batch_language_finished')) {
//        batch_set($batch);
//      }
      
      // create panel in each language
      _openfed_create_panel_node_frontpage($value);

    }
      variable_del('openfed_need_batch_internalization');
      variable_del('openfed_need_batch_internalization_lang');
      
      _openfed_set_block_into_region('local','language', 'tools');
      
      module_enable( array('translation_overview'), TRUE );
  }
}

/**
 * create a panel an set it to the frontpage
 * @param string $lang the language code
 */
function _openfed_create_panel_node_frontpage($lang) {
  
  // check if variable $lang is known in languages_list
  if ( array_key_exists($lang, _openfed_return_languages_list()) || $lang == 'en' ){
    
    
    switch($lang){
      case 'en':
        $title = st('Home');
        $alias = st('home');
        
        // store main link source variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', 'main-menu');
        
        _openfed_show_main_menu_for_language('system', 'main-menu', $lang);
        
        $query = db_update('languages')
              ->fields(array('prefix' => 'en'))
              ->condition('language', 'en', '=')
              ->execute();
      break;
    
      case 'fr':
        // set title & alias string
        $title = st('Accueil');
        $alias = st('accueil');
        
        // create the french menu
        $menu = array();
        $menu['menu_name'] = "main-french-menu";
        $menu['title'] = "Main French Menu";
        $menu['description'] = "";
        $menu['i18n_mode'] = "2";
        $menu['language'] = "fr";
        menu_save($menu);
        
        // create front link in menu
        _openfed_create_front_menu_link($menu['menu_name']);
        
        // store main link source variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', $menu['menu_name']);
        
        // set the menu in the navigation region for nerra
        _openfed_set_block_into_region('menu',$menu['menu_name'], 'navigation');
        
        _openfed_show_main_menu_for_language('menu', $menu['menu_name'], $lang);
      break;
      case 'nl':
        $title = st('Welkom');
        $alias = st('welcom');
        
        
        // create the Dutch menu
        $menu = array();
        $menu['menu_name'] = "main-dutch-menu";
        $menu['title'] = "Main Dutch Menu";
        $menu['description'] = "";
        $menu['i18n_mode'] = "2";
        $menu['language'] = "nl";
        menu_save($menu);
        
        // create front link
        _openfed_create_front_menu_link($menu['menu_name']);
        
        // store variable for a language
        variable_store_set('language', $lang, 'menu_main_links_source', $menu['menu_name']);
        
        // set the menu in the navigation region for nerra
        _openfed_set_block_into_region('menu',$menu['menu_name'], 'navigation');
        
        _openfed_show_main_menu_for_language('menu', $menu['menu_name'], $lang);
      break;
    }

    $pages = array(
        'name' => $alias,
        'task' => 'page',
        'admin_title' => $title,
        'path' => $alias,
        'access' => array(
          'plugins'=>array()
        ),
        'menu' => array(),
        'arguments' => array(),
        'conf' => array(
          'admin_paths'=>array()
        ),
    );
    drupal_write_record('page_manager_pages', $pages);
    $display = array(
        'layout' => 'onecol',
        'layout_settings' => array(),
        'panel_settings' => array(
          'style_settings' => array(
            'default' => '',
            'middle' => '',
          )
        ),
        'cache' => array(),
        'title' => '',
        'hide_title' => 1,
        'title_pane' => 0,
    );
    drupal_write_record('panels_display', $display);
    
    $handlers = array(
        'name' => 'page_'.$alias.'_panel_context',
        'task' => 'page',
        'subtask' => $alias,
        'handler' => 'panel_context',
        'weight' => 0,
        'conf' => array(
          'title' => $title,
          'no_blocks' => 0,
          'pipeline' => 'standard',
          'body_classes_to_remove' => '',
          'body_classes_to_add' => '',
          'css_id' => '',
          'css' => '',
          'contexts' => array(),
          'relationships' => array(),
          'did' => $display['did']
        )
    );
    drupal_write_record('page_manager_handlers', $handlers);
    
    
    // set panel to the front page
    if ( $lang == 'en' ) variable_set('site_frontpage', $alias);
    
    variable_store_set('language', $lang, 'site_frontpage', $alias);
  }
  
  
}


/**
 * Create menu entry for home
 * @param string $menu_name 
 */
function _openfed_create_front_menu_link($menu_name) {
  // Create a Home link
  $item = array(
    'link_title' => st('Home'),
    'link_path' => '<front>',
    'menu_name' => 'menu-'.$menu_name,
    'weight' => -50,
  );
  menu_link_save($item);
}


/**
 * Active menu block into navigation region
 * @param string $menu_name
 */
function _openfed_set_block_into_region($module_name, $delta_name, $region_name){
  $block = array(
    'module' => $module_name,
    'delta' => $delta_name,
    'theme' => openfed_return_default_front_theme_name(),
    'status' => 1,
    'weight' => 0,
    'region' => $region_name,
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
  );
  
  $exist = db_query(
        'SELECT * FROM {block} WHERE module = :module AND delta = :delta AND theme = :theme', 
        array(':module' => $block['module'], ':delta' => $block['delta'], ':theme' => $block['theme'])
      )
      ->fetchObject();
  if (empty($exist)) {
    $query = db_insert('block')
              ->fields($block);
  } else {
    $query = db_update('block')
              ->fields($block)
              ->condition('module', $block['module'], '=')
              ->condition('delta', $block['delta'], '=')
              ->condition('theme', $block['theme'], '=');
  }
  $query->execute();
}


/**
 * show a block for a language
 * @param string $module
 * @param string $delta
 * @param string $language 
 */
function _openfed_show_main_menu_for_language($module, $delta, $language) {
  $query = db_insert('i18n_block_language')->fields(array('language', 'module', 'delta'));
  $query->values(array('language' => $language,'module' => $module,'delta' => $delta,));
  $query->execute();
}