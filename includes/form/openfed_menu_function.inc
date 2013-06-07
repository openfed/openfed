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
    '#description' => st('Note : by checking these options, the menus will automatically be created in the menus list of the website and located in the corresponding region (either the tools or the footer region).<br>
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
  if (!empty($values['menu_list'])) {
    $ck_link = variable_get('ckeditor_link_autocomplete_menus');
    foreach ($values['menu_list'] as $menu_key => $menu_identity) {

      if ($menu_key === $menu_identity) {
        foreach (language_list() as $lang) {
          $menu_name = substr($menu_identity, 0, strlen($menu_identity) - 4);
          $menu_name .= $lang->name;

          $menu_title = str_replace('-', ' ', $menu_name);

          $menu_name .= '-menu';
          $menu_name = strtolower($menu_name);

          // create the tools menu
          _openfed_create_custom_menu($menu_name, ucwords($menu_title), '', '2', $lang->language);

          // set block in region
          switch ($menu_identity) {
            case 'menu-tools-menu':
            case 'menu-tools-' . $lang->name . '-menu':
              _openfed_set_block_into_region('menu', $menu_name, 'tools');
              break;
            case 'menu-footer-menu':
            case 'menu-footer-' . $lang->name . '-menu':
              _openfed_set_block_into_region('menu', $menu_name, 'footer');
              break;
          }

          // show block for language only
          _openfed_show_block_for_language('menu', $menu_name, $lang->language);

          // add custom menu into ckeditor link for autocomplete menu
          $ck_link[$menu_name] = $menu_name;
        }
      }
    }

    variable_set('ckeditor_link_autocomplete_menus', $ck_link);
    menu_rebuild();
  }
}
?>