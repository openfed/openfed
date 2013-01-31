<?php

/**
 * Return the default front theme.
 * 
 */
function openfed_return_default_front_theme_name() {
  return 'nerra';
}

/**
 * Return the default backend theme.
 * 
 */
function openfed_return_default_backend_theme_name() {
  return 'cms_theme';
}

/**
 * Return the default maintenance theme.
 * 
 */
function openfed_return_default_maintenance_theme_name() {
  return 'maintenance';
}

/**
 * Create menu entry for home
 * @param string $menu_name 
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
 * Return the array for the list of potential languages.
 * 
 * @return array 
 */
function _openfed_return_languages_list() {
  $languages_list = array(
    'fr' => st('French (Français)'), 
    'nl' => st('Dutch (Nederlands)')
  );
  return $languages_list;
}

/**
 * Return the array for the list of potential menu.
 * 
 * @return array 
 */
function _openfed_return_menu_list() {
  $menu_list = array(
    'menu-tools-menu' => st('Tools Menu: placed at the very top of the screen'),
    'menu-footer-menu' => st('Footer Menu: placed at the very bottom of the screen')
  );
  return $menu_list;
}

/**
 * Return the array for the list of all roles.
 * 
 * @return array 
 */
function _openfed_return_roles_list() {
  $role_list = array(
    'configurator' => st('Configurator: user in the final client\'s team who has advanced knowledge in Drupal, who can configure modules.'),
    'content_manager' => st('Content Manager: has the permission to create and edit content items.'),
    'user_manager' => st('User Manager: has the permissions to create new users and to manage their permissions.'),
    'authenticated_visitor' => st('Authenticated Visitor: this role is required if there is possibility to log in into the website.'),
  );
  return $role_list;
}

/**
 * Return the array for the list of all taxonomy.
 * 
 * @return array 
 */
function _openfed_return_taxonomy_list() {
  $taxonomy_list = array(
    'categories' => st('Categories.'),
  );
  return $taxonomy_list;
}

/**
 * Return the array for the list of all functionalities.
 * 
 * @return array 
 */
function _openfed_return_functionalities_list() {
  $features = drupal_get_path('profile', 'openfed').'/assets/images/features.png';
  $modules = drupal_get_path('profile', 'openfed').'/assets/images/modules.png';
  
  $function_list = array(
    // Content types
    'ofed_faq' => array(
      'title' => st('FAQ'),
      'picture' => $features,
      'description' => st('Enables the creation of frequently asked questions.'),
    ),
    'ofed_new' => array(
      'title' => st('News'),
      'picture' => $features,
      'description' => st('Enables the creation of news.'),
    ),
    'ofed_press' => array(
      'title' => st('Press'),
      'picture' => $features,
      'description' => st('Enables the creation of press.'),
    ),
    'ofed_slideshow' => array(
      'title' => st('Slideshow'),
      'picture' => $features,
      'description' => st('Enables the creation of slideshow.'),
    ),
    'poll' => array(
      'title' => st('Poll'),
      'picture' => $features,
      'description' => st('Enables the creation of poll.'),
    ),
    'blog' => array(
      'title' => st('Blog'),
      'picture' => $features,
      'description' => st('Enables the creation of blog.'),
    ),
    
    // Modules
    'ofed_federalheader' => array(
      'title' => st('Federal header'),
      'picture' => $modules,
      'description' => st('Provide the official Belgian Federal Authorities header.'),
    ),
    'lexicon' => array(
      'title' => st('Lexicon'),
      'picture' => $modules,
      'description' => st('Maintain one or more lexicons on your site and optionally mark term from one or more lexicons in the content of the website.'),
    ),
    'beididp' => array(
      'title' => st('Belgian eID IDP Integration'),
      'picture' => $modules,
      'description' => st('Allows users to authenticate with their Belgian eID card, using Fedict\'s OpenID Identity provider.'),
    ),
    'content_access' => array(
      'title' => st('Content Access'),
      'picture' => $modules,
      'description' => st('Provides flexible content access control.'),
    ),
    'countries' => array(
      'title' => st('Countries'),
      'picture' => $modules,
      'description' => st('A module that provides a FAPI / Field country element and a simple wrapper module to store / update country data.'),
    ),
    'field_permission' => array(
      'title' => st('Field Permission'),
      'picture' => $modules,
      'description' => st('Set field-level permissions to create, update or view fields.'),
    ),
    'l10n_client' => array(
      'title' => st('Localization client'),
      'picture' => $modules,
      'description' => st('Provides on-page localization'),
    ),
    'module_filter' => array(
      'title' => st('Module filter'),
      'picture' => $modules,
      'description' => st('Filter the modules list.'),
    ),
    'multiple_node_menu' => array(
      'title' => st('Multiple node menu'),
      'picture' => $modules,
      'description' => st('Replaces the node menu form with one that can handle multiple parents.'),
    ),
    'performance' => array(
      'title' => st('Performance'),
      'picture' => $modules,
      'description' => st('Logs detailed and/or summary page generation time and memory consumption for page requests.'),
    ),
    'role_delegation' => array(
      'title' => st('Role delegation'),
      'picture' => $modules,
      'description' => st('Allows site administrators to grant some roles the authority to assign selected roles to users.'),
    ),
    'securelogin' => array(
      'title' => st('Secure login'),
      'picture' => $modules,
      'description' => st('Enables secure login.'),
    ),
  );
  return $function_list;
}

/**
 * Return the array for the list of builder permission
 * 
 * @return array 
 */
function _openfed_return_permission_builder() {
  $permission = array(
    // Add another
      'administer add another' => TRUE,
      'use add another' => TRUE,
    // Administration menu
      'access administration menu' => TRUE,
      'flush caches' => TRUE,
    // Administration theme
      'access admin theme' => TRUE,
    // Administrative pages
      'administer admin paths' => TRUE,
    // Aggregator
      'administer news feeds' => TRUE,
      'access news feeds' => TRUE,
    // Backup and Migrate
      'access backup and migrate' => TRUE,
      'perform backup' => TRUE,
      'access backup files' => TRUE,
      'delete backup files' => TRUE,
      'restore from backup' => TRUE,
      'administer backup and migrate' => TRUE,
    // Block
      'administer blocks' => TRUE,
    // CKEditor
      'administer ckeditor' => TRUE,
      'customize ckeditor' => TRUE,
    // CKEditor Link
      'access ckeditor link' => TRUE,
      'administer ckeditor link' => TRUE,
    // Content translation
      'translate content' => TRUE,
    // Contextual links
      'access contextual links' => TRUE,
    // Display Suite
      'admin_display_suite' => TRUE,
    // Display Suite Extras
      'ds_switch ofed_download' => TRUE,
      'ds_switch ofed_page' => TRUE,
      'ds_switch panel' => TRUE,
      'ds_switch webform' => TRUE,
    // Display Suite UI
      'admin_view_modes' => TRUE,
      'admin_fields' => TRUE,
      'admin_classes' => TRUE,
    // Features
      'administer features' => TRUE,
      'manage features' => TRUE,
    // Fieldgroup
      'administer fieldgroups' => TRUE,
    // Filter
      'administer filters' => TRUE,
      'use text format filtered_html' => TRUE,
      'use text format full_html' => TRUE,
    // Flag
      'administer flags' => TRUE,
      'use flag import' => TRUE,
    // IMCE
      'administer imce' => TRUE,
    // IMAGE
      'administer image styles' => TRUE,
    // Link Checker
      'access broken links report' => TRUE,
      'access own broken links report' => TRUE,
      'administer linkchecker' => TRUE,
      'edit link settings' => TRUE,
    // Locale
      'administer languages' => TRUE,
      'translate interface' => TRUE,
    // Media
      'administer media' => TRUE,
      'import media' => TRUE,
      'view media' => TRUE,
      'edit media' => TRUE,
    // Media Internet Sources
      'add media from remote sources' => TRUE,
    // Menu
      'administer menu' => TRUE,
    // Menu attributes
      'administer menu attributes' => TRUE,
    // Menu position
      'administer menu positions' => TRUE,
    // Meta tags
      'administer meta tags' => TRUE,
      'edit meta tags' => TRUE,
    // Mini panels
      'create mini panels' => TRUE,
      'administer mini panels' => TRUE,
    // Mollom
      'administer mollom' => TRUE,
      'access mollom statistics' => TRUE,
    // Multilingual content
      'administer content translations' => TRUE,
    // Node
      'access content overview' => TRUE,
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
      'view revisions' => TRUE,
      'revert revisions' => TRUE,
      // CT: Download
        'create ofed_download content' => TRUE,
        'edit own ofed_download content' => TRUE,
        'edit any ofed_download content' => TRUE,
        'delete own ofed_download content' => TRUE,
        'delete any ofed_download content' => TRUE,
      // CT: Page
        'create ofed_page content' => TRUE,
        'edit own ofed_page content' => TRUE,
        'edit any ofed_page content' => TRUE,
        'delete own ofed_page content' => TRUE,
        'delete any ofed_page content' => TRUE,
      // CT: Panel
        'create panel content' => TRUE,
        'edit own panel content' => TRUE,
        'edit any panel content' => TRUE,
        'delete own panel content' => TRUE,
      // CT: Webform
        'create webform content' => TRUE,
        'edit own webform content' => TRUE,
        'edit any webform content' => TRUE,
        'delete own webform content' => TRUE,
    // Override node options
      // CT: Download
        'override ofed_download published option' => TRUE,
        'override ofed_download promote to front page option' => TRUE,
        'override ofed_download sticky option' => TRUE,
        'override ofed_download revision option' => TRUE,
        'enter ofed_download revision log entry' => TRUE,
        'override ofed_download authored on option' => TRUE,
        'override ofed_download authored by option' => TRUE,
      // CT: Page
        'override ofed_page published option' => TRUE,
        'override ofed_page promote to front page option' => TRUE,
        'override ofed_page sticky option' => TRUE,
        'override ofed_page revision option' => TRUE,
        'enter ofed_page revision log entry' => TRUE,
        'override ofed_page authored on option' => TRUE,
        'override ofed_page authored by option' => TRUE,
      // CT: Panel
        'override panel published option' => TRUE,
        'override panel promote to front page option' => TRUE,
        'override panel sticky option' => TRUE,
        'override panel revision option' => TRUE,
        'enter panel revision log entry' => TRUE,
        'override panel authored on option' => TRUE,
        'override panel authored by option' => TRUE,
      // CT: Webform
        'override webform published option' => TRUE,
        'override webform promote to front page option' => TRUE,
        'override webform sticky option' => TRUE,
        'override webform revision option' => TRUE,
        'enter webform revision log entry' => TRUE,
        'override webform authored on option' => TRUE,
        'override webform authored by option' => TRUE,
    // Page Title
      'set page title' => TRUE,
      'administer page titles' => TRUE,
    // Page model
      'administer page model module' => TRUE,
      'use page model module' => TRUE,
    // Panel nodes
      'create panel-nodes' => TRUE,
      'edit any panel-nodes' => TRUE,
      'edit own panel-nodes' => TRUE,
      'administer panel-nodes' => TRUE,
      'delete any panel-nodes' => TRUE,
      'delete own panel-nodes' => TRUE,
    // Panels
      'use panels dashboard' => TRUE,
      'view pane admin links' => TRUE,
      'administer pane access' => TRUE,
      'administer advanced pane settings' => TRUE,
      'administer panels layouts' => TRUE,
      'administer panels styles' => TRUE,
    // Path
      'administer url aliases' => TRUE,
      'create url aliases' => TRUE,
    // Path breadcrubms UI
      'administer path breadcrumbs' => TRUE,
    // Pathauto
      'administer pathauto' => TRUE,
      'notify of path changes' => TRUE,
    // Printer-friendly pages
      'administer print' => TRUE,
      'node-specific print configuration' => TRUE,
      'access print' => TRUE,
    // Redirect
      'administer redirects' => TRUE,
    // Rules
      'administer rules' => TRUE,
      'bypass rules access' => TRUE,
      'access rules debug' => TRUE,
    // Scheduler
      'administer scheduler' => TRUE,
      'schedule (un)publishing of nodes' => TRUE,
    // Search
      'administer search' => TRUE,
    // Security Kit
      'administer seckit' => TRUE,
    // Security Review
      'access security review list' => TRUE,
      'run security checks' => TRUE,
    // Site map
      'access site map' => TRUE,
    // Statistics
      'administer statistics' => TRUE,
      'access statistics' => TRUE,
      'view post access counter' => TRUE,
    // String translation
      'translate user-defined strings' => TRUE,
      'translate admin strings' => TRUE,
    // Stylizer
      'administer stylizer' => TRUE,
    // Sweaver
      'configure sweaver' => TRUE,
      'use editor' => TRUE,
    // System
      'administer actions' => TRUE,
      'access administration pages' => TRUE,
      'access site in maintenance mode' => TRUE,
      'view the administration theme' => TRUE,
      'access site reports' => TRUE,
      'block IP addresses' => TRUE,
    // Taxonomy
      'administer taxonomy' => TRUE,
    // Translation overview
      'view translation overview assigments' => TRUE,
    // User
      'administer permissions' => TRUE,
      'administer users' => TRUE,
      'access user profiles' => TRUE,
    // View Unpublished
      'view any unpublished content' => TRUE,
    // Views
      'administer views' => TRUE,
      'access all views' => TRUE,
    // Webform
      'access all webform results' => TRUE,
      'access own webform results' => TRUE,
      'edit all webform submissions' => TRUE,
      'delete all webform submissions' => TRUE,
      'access own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'delete own webform submissions' => TRUE,
    // XML sitemap
      'administer xmlsitemap' => TRUE,
    // robots.txt
      'administer robots.txt' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of configurator permission
 * 
 * @return array 
 */
function _openfed_return_permission_configurator() {
  $permission = array(
    // Add another
      'administer add another' => TRUE,
      'use add another' => TRUE,
    // Administration menu
      'access administration menu' => TRUE,
      'flush caches' => TRUE,
    // Administration theme
      'access admin theme' => TRUE,
    // Administrative pages
      'administer admin paths' => TRUE,
    // Aggregator
      'administer news feeds' => TRUE,
      'access news feeds' => TRUE,
    // Block
      'administer blocks' => TRUE,
    // CKEditor
      'administer ckeditor' => TRUE,
      'customize ckeditor' => TRUE,
    // CKEditor Link
      'access ckeditor link' => TRUE,
      'administer ckeditor link' => TRUE,
    // Content translation
      'translate content' => TRUE,
    // Contextual links
      'access contextual links' => TRUE,
    // Display Suite
      'admin_display_suite' => TRUE,
    // Display Suite Extras
      'ds_switch ofed_download' => TRUE,
      'ds_switch ofed_page' => TRUE,
      'ds_switch panel' => TRUE,
      'ds_switch webform' => TRUE,
    // Display Suite UI
      'admin_view_modes' => TRUE,
      'admin_fields' => TRUE,
      'admin_classes' => TRUE,
    // Features
      'administer features' => TRUE,
      'manage features' => TRUE,
    // Fieldgroup
      'administer fieldgroups' => TRUE,
    // Filter
      'administer filters' => TRUE,
      'use text format filtered_html' => TRUE,
    // Flag
      'administer flags' => TRUE,
    // IMAGE
      'administer image styles' => TRUE,
    // Link Checker
      'access broken links report' => TRUE,
      'access own broken links report' => TRUE,
      'edit link settings' => TRUE,
    // Locale
      'administer languages' => TRUE,
    // Media
      'administer media' => TRUE,
      'import media' => TRUE,
      'view media' => TRUE,
      'edit media' => TRUE,
    // Media Internet Sources
      'add media from remote sources' => TRUE,
    // Menu
      'administer menu' => TRUE,
    // Menu attributes
      'administer menu attributes' => TRUE,
    // Menu position
      'administer menu positions' => TRUE,
    // Meta tags
      'administer meta tags' => TRUE,
      'edit meta tags' => TRUE,
    // Mini panels
      'create mini panels' => TRUE,
      'administer mini panels' => TRUE,
    // Mollom
      'access mollom statistics' => TRUE,
    // Multilingual content
      'administer content translations' => TRUE,
    // Node
      'bypass node access' => TRUE,
      'administer nodes' => TRUE,
      'access content overview' => TRUE,
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
      'view revisions' => TRUE,
      'revert revisions' => TRUE,
      // CT: Download
        'create ofed_download content' => TRUE,
        'edit own ofed_download content' => TRUE,
        'edit any ofed_download content' => TRUE,
        'delete own ofed_download content' => TRUE,
        'delete any ofed_download content' => TRUE,
      // CT: Page
        'create ofed_page content' => TRUE,
        'edit own ofed_page content' => TRUE,
        'edit any ofed_page content' => TRUE,
        'delete own ofed_page content' => TRUE,
        'delete any ofed_page content' => TRUE,
      // CT: Panel
        'create panel content' => TRUE,
        'edit own panel content' => TRUE,
        'edit any panel content' => TRUE,
        'delete own panel content' => TRUE,
      // CT: Webform
        'create webform content' => TRUE,
        'edit own webform content' => TRUE,
        'edit any webform content' => TRUE,
        'delete own webform content' => TRUE,
    // Override node options
      // CT: Download
        'override ofed_download published option' => TRUE,
        'override ofed_download promote to front page option' => TRUE,
        'override ofed_download sticky option' => TRUE,
        'override ofed_download revision option' => TRUE,
        'enter ofed_download revision log entry' => TRUE,
        'override ofed_download authored on option' => TRUE,
        'override ofed_download authored by option' => TRUE,
      // CT: Page
        'override ofed_page published option' => TRUE,
        'override ofed_page promote to front page option' => TRUE,
        'override ofed_page sticky option' => TRUE,
        'override ofed_page revision option' => TRUE,
        'enter ofed_page revision log entry' => TRUE,
        'override ofed_page authored on option' => TRUE,
        'override ofed_page authored by option' => TRUE,
      // CT: Panel
        'override panel published option' => TRUE,
        'override panel promote to front page option' => TRUE,
        'override panel sticky option' => TRUE,
        'override panel revision option' => TRUE,
        'enter panel revision log entry' => TRUE,
        'override panel authored on option' => TRUE,
        'override panel authored by option' => TRUE,
      // CT: Webform
        'override webform published option' => TRUE,
        'override webform promote to front page option' => TRUE,
        'override webform sticky option' => TRUE,
        'override webform revision option' => TRUE,
        'enter webform revision log entry' => TRUE,
        'override webform authored on option' => TRUE,
        'override webform authored by option' => TRUE,
    // Page Title
      'set page title' => TRUE,
      'administer page titles' => TRUE,
    // Page model
      'administer page model module' => TRUE,
      'use page model module' => TRUE,
    // Panel nodes
      'create panel-nodes' => TRUE,
      'edit any panel-nodes' => TRUE,
      'edit own panel-nodes' => TRUE,
      'administer panel-nodes' => TRUE,
      'delete any panel-nodes' => TRUE,
      'delete own panel-nodes' => TRUE,
    // Panels
      'use panels dashboard' => TRUE,
      'view pane admin links' => TRUE,
      'administer pane access' => TRUE,
      'administer advanced pane settings' => TRUE,
      'administer panels layouts' => TRUE,
      'administer panels styles' => TRUE,
      'use panels caching features' => TRUE,
      'use panels locks' => TRUE,
    // Path
      'administer url aliases' => TRUE,
      'create url aliases' => TRUE,
    // Path breadcrubms UI
      'administer path breadcrumbs' => TRUE,
    // Pathauto
      'administer pathauto' => TRUE,
      'notify of path changes' => TRUE,
    // Printer-friendly pages
      'administer print' => TRUE,
      'node-specific print configuration' => TRUE,
      'access print' => TRUE,
    // Redirect
      'administer redirects' => TRUE,
    // Rules
      'administer rules' => TRUE,
      'bypass rules access' => TRUE,
      'access rules debug' => TRUE,
    // Scheduler
      'administer scheduler' => TRUE,
      'schedule (un)publishing of nodes' => TRUE,
    // Search
      'administer search' => TRUE,
      'search content' => TRUE,
    // Security Kit
      'administer seckit' => TRUE,
    // Security Review
      'access security review list' => TRUE,
      'run security checks' => TRUE,
    // Site map
      'access site map' => TRUE,
    // Statistics
      'administer statistics' => TRUE,
      'access statistics' => TRUE,
      'view post access counter' => TRUE,
    // String translation
      'translate user-defined strings' => TRUE,
      'translate admin strings' => TRUE,
    // Stylizer
      'administer stylizer' => TRUE,
    // Sweaver
      'configure sweaver' => TRUE,
      'use editor' => TRUE,
    // System
      'administer actions' => TRUE,
      'access administration pages' => TRUE,
      'view the administration theme' => TRUE,
    // Taxonomy
      'administer taxonomy' => TRUE,
    // Translation overview
      'view translation overview assigments' => TRUE,
    // User
      'access user profiles' => TRUE,
    // View Unpublished
      'view any unpublished content' => TRUE,
    // Webform
      'access all webform results' => TRUE,
      'access own webform results' => TRUE,
      'edit all webform submissions' => TRUE,
      'delete all webform submissions' => TRUE,
      'access own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'delete own webform submissions' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of content manager permission
 * 
 * @return array 
 */
function _openfed_return_permission_content_manager() {
  $permission = array(
    // Add another
      'administer add another' => TRUE,
      'use add another' => TRUE,
    // Administration menu
      'access administration menu' => TRUE,
      'flush caches' => TRUE,
    // Administration theme
      'access admin theme' => TRUE,
    // Aggregator
      'access news feeds' => TRUE,
    // CKEditor Link
      'access ckeditor link' => TRUE,
    // Content translation
      'translate content' => TRUE,
    // Contextual links
      'access contextual links' => TRUE,
    // Filter
      'use text format filtered_html' => TRUE,
    // IMAGE
      'administer image styles' => TRUE,
    // Link Checker
      'access broken links report' => TRUE,
      'access own broken links report' => TRUE,
    // Media
      'administer media' => TRUE,
      'import media' => TRUE,
      'view media' => TRUE,
      'edit media' => TRUE,
    // Media Internet Sources
      'add media from remote sources' => TRUE,
    // Menu
      'administer menu' => TRUE,
    // Meta tags
      'edit meta tags' => TRUE,
    // Multilingual content
      'administer content translations' => TRUE,
    // Node
      'access content overview' => TRUE,
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
      'view revisions' => TRUE,
      'revert revisions' => TRUE,
      // CT: Download
        'create ofed_download content' => TRUE,
        'edit own ofed_download content' => TRUE,
        'edit any ofed_download content' => TRUE,
        'delete own ofed_download content' => TRUE,
        'delete any ofed_download content' => TRUE,
      // CT: Page
        'create ofed_page content' => TRUE,
        'edit own ofed_page content' => TRUE,
        'edit any ofed_page content' => TRUE,
        'delete own ofed_page content' => TRUE,
        'delete any ofed_page content' => TRUE,
      // CT: Webform
        'create webform content' => TRUE,
        'edit own webform content' => TRUE,
        'edit any webform content' => TRUE,
        'delete own webform content' => TRUE,
    // Override node options
      // CT: Download
        'override ofed_download published option' => TRUE,
        'override ofed_download promote to front page option' => TRUE,
        'override ofed_download sticky option' => TRUE,
        'override ofed_download revision option' => TRUE,
        'enter ofed_download revision log entry' => TRUE,
        'override ofed_download authored on option' => TRUE,
      // CT: Page
        'override ofed_page published option' => TRUE,
        'override ofed_page promote to front page option' => TRUE,
        'override ofed_page sticky option' => TRUE,
        'override ofed_page revision option' => TRUE,
        'enter ofed_page revision log entry' => TRUE,
        'override ofed_page authored on option' => TRUE,
      // CT: Webform
        'override webform published option' => TRUE,
        'override webform promote to front page option' => TRUE,
        'override webform sticky option' => TRUE,
        'override webform revision option' => TRUE,
        'enter webform revision log entry' => TRUE,
        'override webform authored on option' => TRUE,
    // Page Title
      'set page title' => TRUE,
      'administer page titles' => TRUE,
    // Page model
      'administer page model module' => TRUE,
      'use page model module' => TRUE,
    // Path
      'administer url aliases' => TRUE,
      'create url aliases' => TRUE,
    // Printer-friendly pages
      'access print' => TRUE,
    // Scheduler
      'schedule (un)publishing of nodes' => TRUE,
    // Site map
      'access site map' => TRUE,
    // Statistics
      'access statistics' => TRUE,
      'view post access counter' => TRUE,
    // System
      'access administration pages' => TRUE,
      'view the administration theme' => TRUE,
    // Taxonomy
      'administer taxonomy' => TRUE,
    // Translation overview
      'view translation overview assigments' => TRUE,
    // View Unpublished
      'view any unpublished content' => TRUE,
    // Webform
      'access all webform results' => TRUE,
      'access own webform results' => TRUE,
      'access own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'delete own webform submissions' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of user manager permission
 * 
 * @return array 
 */
function _openfed_return_permission_user_manager() {
  $permission = array(
    // Add another
      'use add another' => TRUE,
    // Administration menu
      'access administration menu' => TRUE,
    // Administration theme
      'access admin theme' => TRUE,
    // Aggregator
      'access news feeds' => TRUE,
    // Node
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
    // Printer-friendly pages
      'access print' => TRUE,
    // Site map
      'access site map' => TRUE,
    // User
      'administer permissions' => TRUE,
      'administer users' => TRUE,
      'access user profiles' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of authenticated visitor permission
 * 
 * @return array 
 */
function _openfed_return_permission_authenticated_visitor() {
  $permission = array(
    // Add another
      'use add another' => TRUE,
    // Aggregator
      'access news feeds' => TRUE,
    // Node
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
    // Printer-friendly pages
      'access print' => TRUE,
    // Site map
      'access site map' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of authenticated user permission
 * 
 * @return array 
 */
function _openfed_return_permission_authenticated_user() {
  $permission = array(
    // Add another
      'use add another' => TRUE,
    // Aggregator
      'access news feeds' => TRUE,
    // Display Suite Extras
      'view ds_flag_bookmarks on node' => TRUE,
      'view anchor on node' => TRUE,
      'view file_name on node' => TRUE,
//      'view file_reference on node' => TRUE,
      'view file_size on node' => TRUE,
      'view file_type on node' => TRUE,
      'view file_url_open on node' => TRUE,
      'view file_url_persistent on node' => TRUE,
      'view top_of_page on node' => TRUE,
      'view url_file_save on node' => TRUE,
      'view title on node' => TRUE,
      'view links on node' => TRUE,
      'view node_link on node' => TRUE,
      'view author on node' => TRUE,
      'view post_date on node' => TRUE,
      'view submitted_by on node' => TRUE,
      'view search_snippet on node' => TRUE,
      'view search_info on node' => TRUE,
      'view title on taxonomy_term' => TRUE,
      'view more_link on taxonomy_term' => TRUE,
      'view name on user' => TRUE,
      'view title on ds_views' => TRUE,
      'view header on ds_views' => TRUE,
      'view exposed on ds_views' => TRUE,
      'view attachment_before on ds_views' => TRUE,
      'view rows on ds_views' => TRUE,
      'view empty on ds_views' => TRUE,
      'view pager on ds_views' => TRUE,
      'view attachment_after on ds_views' => TRUE,
      'view more on ds_views' => TRUE,
      'view footer on ds_views' => TRUE,
      'view feed_icon on ds_views' => TRUE,
    // Node
      'access content' => TRUE,
      'view own unpublished content' => TRUE,
    // Printer-friendly pages
      'access print' => TRUE,
    // Site map
      'access site map' => TRUE,
  );
  return $permission;
}

/**
 * Return the array for the list of anonymous user permission
 * 
 * @return array 
 */
function _openfed_return_permission_anonymous_user() {
  $permission = array(
    // Aggregator
      'access news feeds' => TRUE,
    // Display Suite Extras
      'view ds_flag_bookmarks on node' => TRUE,
      'view anchor on node' => TRUE,
      'view file_name on node' => TRUE,
//      'view file_reference on node' => TRUE,
      'view file_size on node' => TRUE,
      'view file_type on node' => TRUE,
      'view file_url_open on node' => TRUE,
      'view file_url_persistent on node' => TRUE,
      'view top_of_page on node' => TRUE,
      'view url_file_save on node' => TRUE,
      'view title on node' => TRUE,
      'view links on node' => TRUE,
      'view node_link on node' => TRUE,
      'view author on node' => TRUE,
      'view post_date on node' => TRUE,
      'view submitted_by on node' => TRUE,
      'view search_snippet on node' => TRUE,
      'view search_info on node' => TRUE,
      'view title on taxonomy_term' => TRUE,
      'view more_link on taxonomy_term' => TRUE,
      'view name on user' => TRUE,
      'view title on ds_views' => TRUE,
      'view header on ds_views' => TRUE,
      'view exposed on ds_views' => TRUE,
      'view attachment_before on ds_views' => TRUE,
      'view rows on ds_views' => TRUE,
      'view empty on ds_views' => TRUE,
      'view pager on ds_views' => TRUE,
      'view attachment_after on ds_views' => TRUE,
      'view more on ds_views' => TRUE,
      'view footer on ds_views' => TRUE,
      'view feed_icon on ds_views' => TRUE,
    // Node
      'access content' => TRUE,
    // Printer-friendly pages
      'access print' => TRUE,
    // Site map
      'access site map' => TRUE,
  );
  return $permission;
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