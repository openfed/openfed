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
 * Get the name of all roles availables or created by dafault.
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
 * Sort content types list callback function.
 * @param type $a
 * @param type $b
 * @return int
 */
//function _openfed_sort_content_types_list($a, $b){
//  if($a['title'] == $b['title']){
//    // Return.
//    return 0;
//  }
//  // Return.
//  return ($a['title'] < $b['title']) ? -1 : 1;
//}

/**
 * Get the permissions list for a specified role.
 * @param type $role_name
 *   The role name
 * @return array
 *   The permissions array.
 */
function _openfed_get_permissions_for_role($role_name) {
  // Initialize permissions.
  $permissions = array();
  // Switch on role.
  switch ($role_name) {
    // Builder.
    case 'Builder':
      $permissions = array(
        // Add another.
        'administer add another',
        'use add another',
        // Administration menu.
        'access administration menu',
        'flush caches',
        // Administration theme.
        'access admin theme',
        // Block.
        'administer blocks',
        // CKEditor.
        'administer ckeditor',
        'customize ckeditor',
        // CKEditor Link.
        'access ckeditor link',
        'administer ckeditor link',
        // Content translation.
        'translate content',
        // Contextual links.
        'access contextual links',
        // Display Suite.
        'admin_display_suite',
        // Display Suite Extras.
        'ds_switch ofed_download',
        'ds_switch ofed_page',
        'ds_switch webform',
        // Display Suite UI.
        'admin_view_modes',
        'admin_fields',
        'admin_classes',
        // Features.
        'administer features',
        'manage features',
        // Fieldgroup.
        'administer fieldgroups',
        // Filter.
        'administer filters',
        'use text format filtered_html',
        'use text format full_html',
        // Flag.
        'administer flags',
        'use flag import',
        // IMCE.
        'administer imce',
        // IMAGE.
        'administer image styles',
        // Interface switcher (ofed_switcher)
        'access ofed_switcher administration',
        'access ofed_switcher content',
        // Link Checker.
        'access broken links report',
        'access own broken links report',
        'administer linkchecker',
        'edit link settings',
        // Locale.
        'administer languages',
        'translate interface',
        // Media.
        'administer media',
        'import media',
        'view media',
        'edit media',
        // Media Internet Sources.
        'add media from remote sources',
        // Menu.
        'administer menu',
        // Menu attributes.
        'administer menu attributes',
        // Menu position.
        'administer menu positions',
        // Meta tags.
        'administer meta tags',
        'edit meta tags',
        // Mollom.
        'administer mollom',
        'access mollom statistics',
        // Multilingual content.
        'administer content translations',
        // Node.
        'administer content types',
        'access content overview',
        'access content',
        'view own unpublished content',
        'view revisions',
        'revert revisions',
        // CT: Webform.
        'create webform content',
        'edit own webform content',
        'edit any webform content',
        'delete own webform content',
        // Override node options.
        // CT: Webform.
        'override webform published option',
        'override webform promote to front page option',
        'override webform sticky option',
        'override webform revision option',
        'enter webform revision log entry',
        'override webform authored on option',
        'override webform authored by option',
        // Page Title.
        'set page title',
        'administer page titles',
        // Views multi-column display.
        'administer views multi-column display',
        'use views multi-column display',
        // Path.
        'administer url aliases',
        'create url aliases',
        // Path breadcrubms UI.
        'administer path breadcrumbs',
        // Pathauto.
        'administer pathauto',
        'notify of path changes',
        // Printer-friendly pages.
        'administer print',
        'node-specific print configuration',
        'access print',
        // Redirect.
        'administer redirects',
        // Rules.
        'administer rules',
        'bypass rules access',
        'access rules debug',
        // Scheduler.
        'administer scheduler',
        'schedule (un)publishing of nodes',
        // Search.
        'administer search',
        'search content',
        // Security Kit.
        'administer seckit',
        // Security Review.
        'access security review list',
        'run security checks',
        // Site map.
        'access site map',
        // String translation.
        'translate user-defined strings',
        'translate admin strings',
        // System.
        'administer actions',
        'access administration pages',
        'access site in maintenance mode',
        'view the administration theme',
        'access site reports',
        'block IP addresses',
        // Taxonomy.
        'administer taxonomy',
        // Translation overview.
        'view translation overview assigments',
        // User.
        'administer permissions',
        'administer users',
        'access user profiles',
        // View Unpublished.
        'view any unpublished content',
        // Views.
        'administer views',
        'access all views',
        // Webform.
        'access all webform results',
        'access own webform results',
        'edit all webform submissions',
        'delete all webform submissions',
        'access own webform submissions',
        'edit own webform submissions',
        'delete own webform submissions',
        // XML sitemap.
        'administer xmlsitemap',
      );
      break;

    // Configurator.
    case 'Configurator':
      $permissions = array(
        // Add another.
        'administer add another',
        'use add another',
        // Administration menu.
        'access administration menu',
        'flush caches',
        // Administration theme.
        'access admin theme',
        // Block.
        'administer blocks',
        // CKEditor.
        'administer ckeditor',
        'customize ckeditor',
        // CKEditor Link.
        'access ckeditor link',
        'administer ckeditor link',
        // Content translation.
        'translate content',
        // Contextual links.
        'access contextual links',
        // Display Suite.
        'admin_display_suite',
        // Display Suite Extras.
        'ds_switch ofed_download',
        'ds_switch ofed_page',
        'ds_switch webform',
        // Display Suite UI.
        'admin_view_modes',
        'admin_fields',
        'admin_classes',
        // Features.
        'administer features',
        'manage features',
        // Fieldgroup.
        'administer fieldgroups',
        // Filter.
        'administer filters',
        'use text format filtered_html',
        'use text format full_html',
        // Flag.
        'administer flags',
        // Image.
        'administer image styles',
        // Interface switcher (ofed_switcher)
        'access ofed_switcher administration',
        'access ofed_switcher content',
        // Link Checker.
        'access broken links report',
        'access own broken links report',
        'edit link settings',
        // Locale.
        'administer languages',
        // Media.
        'administer media',
        'import media',
        'view media',
        'edit media',
        // Media Internet Sources.
        'add media from remote sources',
        // Menu.
        'administer menu',
        // Menu attributes.
        'administer menu attributes',
        // Menu position.
        'administer menu positions',
        // Meta tags.
        'administer meta tags',
        'edit meta tags',
        // Mollom.
        'access mollom statistics',
        // Multilingual content.
        'administer content translations',
        // Node.
        'bypass node access',
        'administer nodes',
        'administer content types',
        'access content overview',
        'access content',
        'view own unpublished content',
        'view revisions',
        'revert revisions',
        // CT: Webform.
        'create webform content',
        'edit own webform content',
        'edit any webform content',
        'delete own webform content',
        // Override node options.
        // CT: Webform.
        'override webform published option',
        'override webform promote to front page option',
        'override webform sticky option',
        'override webform revision option',
        'enter webform revision log entry',
        'override webform authored on option',
        'override webform authored by option',
        // Page Title.
        'set page title',
        'administer page titles',
        // Views multi-column display.
        'administer views multi-column display',
        'use views multi-column display',
        // Path.
        'administer url aliases',
        'create url aliases',
        // Path breadcrubms UI.
        'administer path breadcrumbs',
        // Pathauto.
        'administer pathauto',
        'notify of path changes',
        // Printer-friendly pages.
        'administer print',
        'node-specific print configuration',
        'access print',
        // Redirect.
        'administer redirects',
        // Rules.
        'administer rules',
        'bypass rules access',
        'access rules debug',
        // Scheduler.
        'administer scheduler',
        'schedule (un)publishing of nodes',
        // Search.
        'administer search',
        'search content',
        // Security Kit.
        'administer seckit',
        // Security Review.
        'access security review list',
        'run security checks',
        // Site map.
        'access site map',
        // String translation.
        'translate user-defined strings',
        'translate admin strings',
        // System.
        'administer actions',
        'access administration pages',
        'view the administration theme',
        // Taxonomy.
        'administer taxonomy',
        // Translation overview.
        'view translation overview assigments',
        // User
        'access user profiles',
        // View Unpublished.
        'view any unpublished content',
        // Webform.
        'access all webform results',
        'access own webform results',
        'edit all webform submissions',
        'delete all webform submissions',
        'access own webform submissions',
        'edit own webform submissions',
        'delete own webform submissions',
      );
      break;

    // Content Manager.
    case 'Content Manager':
      $permissions = array(
        // Add another.
        'administer add another',
        'use add another',
        // Administration menu.
        'access administration menu',
        'flush caches',
        // Administration theme.
        'access admin theme',
        // CKEditor Link.
        'access ckeditor link',
        // Content translation.
        'translate content',
        // Contextual links.
        'access contextual links',
        // Filter.
        'use text format filtered_html',
        'use text format full_html',
        // Image.
        'administer image styles',
        // Interface switcher (ofed_switcher)
        'access ofed_switcher administration',
        'access ofed_switcher content',
        // Link Checker.
        'access broken links report',
        'access own broken links report',
        // Media.
        'administer media',
        'import media',
        'view media',
        'edit media',
        // Media Internet Sources.
        'add media from remote sources',
        // Menu.
        'administer menu',
        // Meta tags.
        'edit meta tags',
        // Multilingual content.
        'administer content translations',
        // Node.
        'access content overview',
        'access content',
        'view own unpublished content',
        'view revisions',
        'revert revisions',
        // CT: Webform.
        'create webform content',
        'edit own webform content',
        'edit any webform content',
        'delete own webform content',
        // Override node options.
        // CT: Webform.
        'override webform published option',
        'override webform promote to front page option',
        'override webform sticky option',
        'override webform revision option',
        'enter webform revision log entry',
        'override webform authored on option',
        // Page Title.
        'set page title',
        'administer page titles',
        // Page model.
        'use views multi-column display',
        // Path.
        'administer url aliases',
        'create url aliases',
        // Printer-friendly pages.
        'access print',
        // Scheduler
        'schedule (un)publishing of nodes',
        // Search.
        'search content',
        // Site map.
        'access site map',
        // System.
        'access administration pages',
        'view the administration theme',
        // Taxonomy.
        'administer taxonomy',
        // Translation overview.
        'view translation overview assigments',
        // View Unpublished.
        'view any unpublished content',
        // Webform.
        'access all webform results',
        'access own webform results',
        'access own webform submissions',
        'edit own webform submissions',
        'delete own webform submissions',
      );
      break;

    // User Manager.
    case 'User Manager':
      $permissions = array(
        // Add another.
        'use add another',
        // Administration menu.
        'access administration menu',
        // Administration theme.
        'access admin theme',
        // Contextual links.
        'access contextual links',
        // Node.
        'access content',
        'view own unpublished content',
        // Printer-friendly pages.
        'access print',
        // Search.
        'search content',
        // Site map.
        'access site map',
        // System.
        'access administration pages',
        'view the administration theme',
        // User.
        'administer permissions',
        'administer users',
        'access user profiles',
      );
      break;

    // Authenticated Visitor.
    case 'Authenticated Visitor':
      $permissions = array(
        // Add another.
        'use add another',
        // Node.
        'access content',
        'view own unpublished content',
        // Printer-friendly pages.
        'access print',
        // Search.
        'search content',
        // Site map.
        'access site map',
      );
      break;

    // Authenticated user.
    case 'authenticated user':
      $permissions = array(
        // Add another.
        'use add another',
        // Display Suite Extras.
        'view ds_flag_bookmarks on node',
        'view title on node',
        'view links on node',
        'view node_link on node',
        'view author on node',
        'view post_date on node',
        'view submitted_by on node',
        'view search_snippet on node',
        'view search_info on node',
        'view title on taxonomy_term',
        'view more_link on taxonomy_term',
        'view name on user',
        'view title on ds_views',
        'view header on ds_views',
        'view exposed on ds_views',
        'view attachment_before on ds_views',
        'view rows on ds_views',
        'view empty on ds_views',
        'view pager on ds_views',
        'view attachment_after on ds_views',
        'view more on ds_views',
        'view footer on ds_views',
        'view feed_icon on ds_views',
        // Node.
        'access content',
        'view own unpublished content',
        // Printer-friendly pages.
        'access print',
        // Search.
        'search content',
        // Site map.
        'access site map',
      );
      break;

    // Anonymous user.
    case 'anonymous user':
      $permissions = array(
        // Display Suite Extras.
        'view ds_flag_bookmarks on node',
        'view title on node',
        'view links on node',
        'view node_link on node',
        'view author on node',
        'view post_date on node',
        'view submitted_by on node',
        'view search_snippet on node',
        'view search_info on node',
        'view title on taxonomy_term',
        'view more_link on taxonomy_term',
        'view name on user',
        'view title on ds_views',
        'view header on ds_views',
        'view exposed on ds_views',
        'view attachment_before on ds_views',
        'view rows on ds_views',
        'view empty on ds_views',
        'view pager on ds_views',
        'view attachment_after on ds_views',
        'view more on ds_views',
        'view footer on ds_views',
        'view feed_icon on ds_views',
        // Node.
        'access content',
        // Printer-friendly pages.
        'access print',
        // Search.
        'search content',
        // Site map.
        'access site map',
      );
      break;
    default:
      $permissions = array();
      break;
  }

  // Transform array to associative array.
  if (!empty($permissions)) {
    $permissions = array_fill_keys($permissions, TRUE);
  }

  // Return.
  return $permissions;
}
