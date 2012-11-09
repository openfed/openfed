<?php
// Enable some standard blocks.

// PUBLIC THEME
  $default_theme = variable_get('theme_default', 'nerra');
  $default_values = array(
    // TOOLS
      array( // Print
        'module' => 'print',
        'delta' => 'print-links',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 0,
        'region' => 'tools',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
      array( // Resize
        'module' => 'text_resize',
        'delta' => '0',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 0,
        'region' => 'tools',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
      array( // Search
        'module' => 'search',
        'delta' => 'form',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 2,
        'region' => 'tools',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
      
    // TODO: change to form functionnalities
      array( // Switcher
        'module' => 'ofed_switcher',
        'delta' => 'ofed_switcher',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 2,
        'region' => 'tools',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
    //END TODO
    //
    // HEADER
    // NAVIGATION
      array( // Main Menu
        'module' => 'system',
        'delta' => 'main-menu',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 0,
        'region' => 'navigation',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
    // TOP
    // SIDEBAR FIRST
    // CONTENT TOP
    // CONTENT
      array( // System help 
        'module' => 'system',
        'delta' => 'help',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 0,
        'region' => 'content',
        'pages' => '',
        'title' => '',
        'cache' => -1,
      ),
      array( // Main page content
        'module' => 'system',
        'delta' => 'main',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 1,
        'region' => 'content',
        'pages' => '',
        'title' => '',
        'cache' => -1,
      ),
    // CONTENT BOTTOM
    // ASIDE RIGHT
      array( // User login
        'module' => 'user',
        'delta' => 'login',
        'theme' => $default_theme,
        'status' => 1,
        'weight' => 0,
        'region' => 'sidebar_second',
        'pages' => '',
        'title' => '',
        'cache' => -1,
      ),
    // BOTTOM
    // FOOTER
  );
  foreach ($default_values as $block) {
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


// CMS THEME
  $admin_theme = variable_get('admin_theme', 'cms_theme');
  
  $admin_values = array(
      
      // TODO: switch to functionalities
      // TOOLS
        array( // Switcher
          'module' => 'ofed_switcher',
          'delta' => 'ofed_switcher',
          'theme' => $admin_theme,
          'status' => 1,
          'weight' => 0,
          'region' => 'tools',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        ),
      // END TODO
      
      // HEADER
      // NAVIGATION
        array( // Main Menu
          'module' => 'menu',
          'delta' => 'menu-cms-menu',
          'theme' => $admin_theme,
          'status' => 1,
          'weight' => 0,
          'region' => 'navigation',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        ),
      // TOP
      // SIDEBAR FIRST
      // CONTENT TOP
      // CONTENT
        array( // System help 
          'module' => 'system',
          'delta' => 'help',
          'theme' => $admin_theme,
          'status' => 1,
          'weight' => 0,
          'region' => 'content',
          'pages' => '',
          'title' => '',
          'cache' => -1,
        ),
        array( // Main page content
          'module' => 'system',
          'delta' => 'main',
          'theme' => $admin_theme,
          'status' => 1,
          'weight' => 1,
          'region' => 'content',
          'pages' => '',
          'title' => '',
          'cache' => -1,
        ),
      // CONTENT BOTTOM
      // ASIDE RIGHT
      // BOTTOM
      // FOOTER

  );
  foreach ($admin_values as $block) {
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
