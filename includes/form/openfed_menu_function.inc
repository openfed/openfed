<?php

/**
 * Return the form for menu set up
 * @return array 
 */
function openfed_menu_form() {
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the menu areas which have to be foreseen:') . '</p>',
  );
  $form['menu_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Menu list'),
    '#options' => array( 
      'menu-tools-menu' => 'Tools Menu: placed at the very top of the screen', 
      'menu-footer-menu' => 'Footer Menu: placed at the very bottom of the screen'
    ),
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
function openfed_menu_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $blocks = array();
  if ( !empty($values['menu_list']) ) {
    if ( $values['menu_list']['menu-tools-menu'] === 'menu-tools-menu' ) {
      // Create a tools menu.
        $menu = array();
        $menu['menu_name'] = "menu-tools-menu";
        $menu['title'] = "Tools Menu";
        $menu['description'] = "";
        menu_save($menu);
        $block_tools = array(
          'module' => 'menu',
          'delta' => 'menu-tools-menu',
          'theme' => variable_get('theme_default', 'nerra'),
          'status' => 1,
          'weight' => 0,
          'region' => 'tools',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        );
        $blocks[] = $block_tools;
    }
    if ( $values['menu_list']['menu-footer-menu'] === 'menu-footer-menu' ) {
      // Create a footer menu.
        $menu = array();
        $menu['menu_name'] = "menu-footer-menu";
        $menu['title'] = "Footer Menu";
        $menu['description'] = "";
        menu_save($menu);
        $block_footer = array(
          'module' => 'menu',
          'delta' => 'menu-footer-menu',
          'theme' => variable_get('theme_default', 'nerra'),
          'status' => 1,
          'weight' => 0,
          'region' => 'footer',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        );
        $blocks[] = $block_footer;
    }
    menu_rebuild();
    if (!empty($blocks)) {
      $query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'pages', 'title', 'cache'));
      foreach ($blocks as $record) {
        $query->values($record);
      }
      $query->execute();
    }

  }
}

?>