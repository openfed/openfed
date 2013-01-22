<?php

/**
 * Return the form for menu set up
 * @return array 
 */
function openfed_menu_form() {
  drupal_set_title(st('Menu configuration'));
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select the menu areas which have to be foreseen:') . '</p>',
  );
  $form['menu_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Menu list'),
    '#options' => _openfed_return_menu_list(),
    '#description' => st('
      Note : by checking these options, the menus will automatically be created in the menus list of the website and located in the corresponding region (either the tools or the footer region).<br>
      If no menus are checked, they can still be created after the installation, but they will need to be created manually and located in the corresponding region.'),
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
    $ck_link = variable_get('ckeditor_link_autocomplete_menus');
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
          'theme' => openfed_return_default_front_theme_name(),
          'status' => 1,
          'weight' => 0,
          'region' => 'tools',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        );
        $blocks[] = $block_tools;
        $ck_link['menu-tools-menu'] = 'menu-tools-menu';
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
          'theme' => openfed_return_default_front_theme_name(),
          'status' => 1,
          'weight' => 0,
          'region' => 'footer',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        );
        $blocks[] = $block_footer;
        $ck_link['menu-footer-menu'] = 'menu-footer-menu';
    }
    menu_rebuild();
    if (!empty($blocks)) {
      $query = db_insert('block')->fields(array('module', 'delta', 'theme', 'status', 'weight', 'region', 'pages', 'title', 'cache'));
      foreach ($blocks as $record) {
        $query->values($record);
      }
      $query->execute();
      variable_set('ckeditor_link_autocomplete_menus', $ck_link);
    }

  }
}

?>