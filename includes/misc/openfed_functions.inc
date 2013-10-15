<?php

/**
 * @file
 * Needs to be documented.
 */

/**
 * Get the name of the theme frontend.
 */
function _openfed_get_theme_frontend() {
  return 'nerra';
}
/**
 * Get the name of the theme backend.
 */
function _openfed_get_theme_backend() {
  return 'cms_theme';
}
/**
 * Get the name of the theme maintenance.
 */
function _openfed_get_theme_maintenance() {
  return 'maintenance';
}

/**
 * Show a block for a language.
 * @param string $module
 * @param string $delta
 * @param string $language
 */
function _openfed_show_block_for_language($module, $delta, $language) {
  $query = db_insert('i18n_block_language')->fields(array('language', 'module', 'delta'));
  $query->values(array('language' => $language, 'module' => $module, 'delta' => $delta));
  $query->execute();
}

/**
 * Create menu entry for home.
 */
function _openfed_create_front_menu_link($menu_name, $title) {
  // Create a Home link
  $item = array(
    'link_title' => $title,
    'link_path' => '<front>',
    'menu_name' => $menu_name,
    'weight' => -50,
  );
  menu_link_save($item);
}

/**
 * Create a custom menu.
 */
function _openfed_create_custom_menu($menu_name, $title, $description = '', $i18n_mode = '2', $language = 'en') {
  $menu = array();
  $menu['menu_name'] = $menu_name;
  $menu['title'] = $title;
  $menu['description'] = $description;
  $menu['i18n_mode'] = $i18n_mode;
  $menu['language'] = $language;
  menu_save($menu);
}

/**
 * Active menu block into navigation region.
 */
function _openfed_set_block_into_region($module_name, $delta_name, $region_name) {
  $block = array(
    'module' => $module_name,
    'delta' => $delta_name,
    'theme' => _openfed_get_theme_frontend(),
    'status' => 1,
    'weight' => 0,
    'region' => $region_name,
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
  );

  $exist = db_select('block', 'b')
    ->fields('b')
    ->condition('module', $block['module'])
    ->condition('delta', $block['delta'])
    ->condition('theme', $block['theme'])
    ->execute()
    ->fetchObject();

  if (empty($exist)) {
    $query = db_insert('block')
      ->fields($block);
  }
  else {
    $query = db_update('block')
      ->fields($block)
      ->condition('module', $block['module'], '=')
      ->condition('delta', $block['delta'], '=')
      ->condition('theme', $block['theme'], '=');
  }
  $query->execute();
}

/**
 * Get the list of potential languages.
 *
 * @return array
 *  The language list.
 */
function _openfed_get_languages_list() {
  // Set the language list.
  $languages_list = array(
    'fr' => st('French (Français)'),
    'nl' => st('Dutch (Nederlands)'),
    'de' => st('German (Deutsch)'),
  );

  // Return.
  return $languages_list;
}

/**
 * Get the list of potential menu.
 *
 * @return array
 *   The menus list.
 */
function _openfed_get_menus_list() {
  $menu_list = array(
    'menu-tools-menu' => st('Tools Menu: placed at the very top of the screen.'),
    'menu-footer-menu' => st('Footer Menu: placed at the very bottom of the screen.')
  );
  return $menu_list;
}

/**
 * Get the list of all roles.
 *
 * @return array
 *   The roles list.
 */
function _openfed_get_roles_list() {
  $role_list = array(
    'configurator' => st('Configurator: Experienced Drupal user, can configure modules.'),
    'content_manager' => st('Content Manager: Can create and edit content items.'),
    'user_manager' => st('User Manager: Can create new users and manage their permissions.'),
    'authenticated_visitor' => st('Authenticated Visitor.'),
  );
  return $role_list;
}

/**
 * Get the name of all roles availables or created by default.
 * Used to be called after install and bypass the error with the st() function,
 * not recognized after install.
 */
function _openfed_get_roles_list_default() {
  // Set roles.
  $role_key = array(
    'Administrator',
    'Builder',
    'Configurator',
    'Content Manager',
    'User Manager',
    'Authenticated Visitor',
    'authenticated user',
    'anonymous user',
  );

  // Return.
  return $role_key;
}

/**
 * Get the list of all taxonomy.
 *
 * @return array
 *  The taxonomy list.
 */
function _openfed_get_taxonomy_list() {
  $taxonomy_list = array(
    'categories' => st('Categories.'),
  );
  return $taxonomy_list;
}

/**
 * Get the list of all content types.
 *
 * @return array
 *  The content types list.
 */
function _openfed_get_functionnalities_list() {
  $functionalities = array(
    'ofed_address' => get_t('Address'),
    'ofed_banner' => get_t('Banner'),
    'blog' => get_t('Blog'),
    'ofed_event' => get_t('Event'),
    'ofed_faq' => get_t('FAQ'),
    'forum' => get_t('Forum'),
    'ofed_job' => get_t('Job'),
    'lexicon' => get_t('Lexicon'),
    'ofed_meeting' => get_t('Meeting'),
    'ofed_news' => get_t('News'),
    'ofed_photogallery' => get_t('Photo galleries'),
    'poll' => get_t('Poll'),
    'ofed_press' => get_t('Press'),
    'ofed_slider' => get_t('Slider'),
    'ofed_slideshow' => get_t('Slideshow'),
    'ofed_team' => get_t('Team member'),
    'ofed_video' => get_t('Video'),
  );

  // Sort by 'title' sub key alphabeticaly and preserve array keys.
  //uasort($functionalities, '_openfed_sort_content_types_list');
  natsort($functionalities);

  // Return.
  return $functionalities;
}

/**
 * Returns default permissions.
 *
 * @return array
 *  Associative array with as key the permission and as value the array of
 *  roles this permission applies to.
 */
function _openfed_get_default_permissions() {
  $permissions = array(
    // addanother
    'administer add another' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'use add another' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
    ),

    // admin_menu'
    'access administration menu' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
    ),
    'flush caches' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // admin_theme
    'access admin theme' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
    ),

    // block
    'administer blocks' => array(
      'Builder',
      'Configurator',
    ),

    // ckeditor
    'administer ckeditor' => array(
      'Builder',
      'Configurator',
    ),
    'customize ckeditor' => array(
      'Builder',
      'Configurator',
    ),

    // ckeditor_link
    'access ckeditor link' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'administer ckeditor link' => array(
      'Builder',
      'Configurator',
    ),

    // contextual
    'access contextual links' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
    ),

    // ds
    'admin_display_suite' => array(
      'Builder',
      'Configurator',
    ),

    // ds_extras
    'ds_switch ofed_download' => array(
      'Builder',
      'Configurator',
    ),
    'ds_switch ofed_page' => array(
      'Builder',
      'Configurator',
    ),
    'ds_switch webform' => array(
      'Builder',
      'Configurator',
    ),
    'view ds_flag_bookmarks on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view title on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view links on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view node_link on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view author on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view post_date on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view submitted_by on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view search_snippet on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view search_info on node' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view title on taxonomy_term' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view more_link on taxonomy_term' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view name on user' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view title on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view header on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view exposed on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view attachment_before on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view rows on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view empty on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view pager on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view attachment_after on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view more on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view footer on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),
    'view feed_icon on ds_views' => array(
      'authenticated user',
      'anonymous user',
    ),

    // ds_ui
    'admin_view_modes' => array(
      'Builder',
      'Configurator',
    ),
    'admin_fields' => array(
      'Builder',
      'Configurator',
    ),
    'admin_classes' => array(
      'Builder',
      'Configurator',
    ),

    // features
    'administer features' => array(
      'Builder',
      'Configurator',
    ),
    'manage features' => array(
      'Builder',
      'Configurator',
    ),

    // field_group
    'administer fieldgroups' => array(
      'Builder',
      'Configurator',
    ),

    // filter
    'administer filters' => array(
      'Builder',
      'Configurator',
    ),
    'use text format filtered_html' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'use text format full_html' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // flag
    'administer flags' => array(
      'Builder',
      'Configurator',
    ),
    'use flag import' => array(
      'Builder',
    ),

    // i18n_node
    'administer content translations' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // i18n_string
    'translate user-defined strings' => array(
      'Builder',
      'Configurator',
    ),
    'translate admin strings' => array(
      'Builder',
      'Configurator',
    ),

    // image
    'administer image styles' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // imce
    'administer imce' => array(
      'Builder',
    ),

    // linkchecker
    'access broken links report' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'access own broken links report' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'administer linkchecker' => array(
      'Builder',
    ),
    'edit link settings' => array(
      'Builder',
      'Configurator',
    ),

    // locale
    'administer languages' => array(
      'Builder',
      'Configurator',
    ),
    'translate interface' => array(
      'Builder',
    ),

    // media
    'administer media' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'import media' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'view media' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'edit media' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // media_internet
    'add media from remote sources' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // menu
    'administer menu' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // menu_attributes
    'administer menu attributes' => array(
      'Builder',
      'Configurator',
    ),

    // menu_position
    'administer menu positions' => array(
      'Builder',
      'Configurator',
    ),

    // metatag
    'administer meta tags' => array(
      'Builder',
      'Configurator',
    ),
    'edit meta tags' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // mollom
    'administer mollom' => array(
      'Builder',
    ),
    'access mollom statistics' => array(
      'Builder',
      'Configurator',
    ),

    // node
    'administer content types' => array(
      'Builder',
      'Configurator',
    ),
    'access content overview' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'access content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
      'anonymous user',
    ),
    'view own unpublished content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
    ),
    'view revisions' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'revert revisions' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'create webform content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'edit own webform content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'edit any webform content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'delete own webform content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'bypass node access' => array(
      'Configurator',
    ),
    'administer nodes' => array(
      'Configurator',
    ),

    // ofed_switcher
    'access ofed_switcher administration' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'access ofed_switcher content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // ofed_vmcd
    'administer views multi-column display' => array(
      'Builder',
      'Configurator',
    ),
    'use views multi-column display' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // override_node_options
    'override webform published option' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'override webform promote to front page option' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'override webform sticky option' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'override webform revision option' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'enter webform revision log entry' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'override webform authored on option' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'override webform authored by option' => array(
      'Builder',
      'Configurator',
    ),

    // page_title
    'set page title' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'administer page titles' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // path
    'administer url aliases' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'create url aliases' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // path_breadcrumbs_ui
    'administer path breadcrumbs' => array(
      'Builder',
      'Configurator',
    ),

    // pathauto
    'administer pathauto' => array(
      'Builder',
      'Configurator',
    ),
    'notify of path changes' => array(
      'Builder',
      'Configurator',
    ),

    // print
    'administer print' => array(
      'Builder',
      'Configurator',
    ),
    'node-specific print configuration' => array(
      'Builder',
      'Configurator',
    ),
    'access print' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
      'anonymous user',
    ),

    // redirect
    'administer redirects' => array(
      'Builder',
      'Configurator',
    ),

    // rules
    'administer rules' => array(
      'Builder',
      'Configurator',
    ),
    'bypass rules access' => array(
      'Builder',
      'Configurator',
    ),
    'access rules debug' => array(
      'Builder',
      'Configurator',
    ),

    // scheduler
    'administer scheduler' => array(
      'Builder',
      'Configurator',
    ),
    'schedule (un)publishing of nodes' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // search
    'administer search' => array(
      'Builder',
      'Configurator',
    ),
    'search content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
      'anonymous user',
    ),

    // seckit
    'administer seckit' => array(
      'Builder',
      'Configurator',
    ),

    // security_review
    'access security review list' => array(
      'Builder',
      'Configurator',
    ),
    'run security checks' => array(
      'Builder',
      'Configurator',
    ),

    // site_map
    'access site map' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
      'Authenticated Visitor',
      'authenticated user',
      'anonymous user',
    ),

    // system
    'administer actions' => array(
      'Builder',
      'Configurator',
    ),
    'access administration pages' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
    ),
    'access site in maintenance mode' => array(
      'Builder',
    ),
    'view the administration theme' => array(
      'Builder',
      'Configurator',
      'Content Manager',
      'User Manager',
    ),
    'access site reports' => array(
      'Builder',
    ),
    'block IP addresses' => array(
      'Builder',
    ),

    // taxonomy
    'administer taxonomy' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // translation
    'translate content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // translation_overview
    'view translation overview assigments' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // user
    'administer permissions' => array(
      'Builder',
      'User Manager',
    ),
    'administer users' => array(
      'Builder',
      'User Manager',
    ),
    'access user profiles' => array(
      'Builder',
      'Configurator',
      'User Manager',
    ),

    // view_unpublished
    'view any unpublished content' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // views
    'administer views' => array(
      'Builder',
    ),
    'access all views' => array(
      'Builder',
    ),

    // webform
    'access all webform results' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'access own webform results' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'edit all webform submissions' => array(
      'Builder',
      'Configurator',
    ),
    'delete all webform submissions' => array(
      'Builder',
      'Configurator',
    ),
    'access own webform submissions' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'edit own webform submissions' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),
    'delete own webform submissions' => array(
      'Builder',
      'Configurator',
      'Content Manager',
    ),

    // xmlsitemap
    'administer xmlsitemap' => array(
      'Builder',
    ),
  );
  return $permissions;
}

/**
 * Get the permissions list for a specified role.
 * @param type $role_name
 *   The role name
 * @return array
 *   Associative array with key the permission name and value TRUE if the role
 *   name has this permission.
 */
function _openfed_get_permissions_for_role($role_name) {
  // Initialize permissions.
  $permissions = _openfed_get_default_permissions();

  // Return the permissions that apply to this role.
  $permissions_for_role = array();
  foreach ($permissions as $permission_name => $roles) {
    if (in_array($role_name, $permissions[$permission_name])) {
      $permissions_for_role[$permission_name] = TRUE;
    }
  }

  return $permissions_for_role;
}
