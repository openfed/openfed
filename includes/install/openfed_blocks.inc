<?php
// Enable some standard blocks.
  
// PUBLIC THEME
  $default_values = array(
    // TOOLS
      array( // Print
        'module' => 'print',
        'delta' => 'print-links',
        'theme' => openfed_return_default_front_theme_name(),
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
        'theme' => openfed_return_default_front_theme_name(),
        'status' => 1,
        'weight' => 0,
        'region' => 'tools',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
      
    // HEADER
    // NAVIGATION
      array( // Main Menu
        'module' => 'system',
        'delta' => 'main-menu',
        'theme' => openfed_return_default_front_theme_name(),
        'status' => 1,
        'weight' => 0,
        'region' => 'navigation',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
    // TOP
    // BREADCRUMB
      array( // Breadcrumb
        'module' => 'easy_breadcrumb',
        'delta' => 'easy_breadcrumb',
        'theme' => openfed_return_default_front_theme_name(),
        'status' => 1,
        'weight' => 0,
        'region' => 'breadcrumb',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
    // SIDEBAR FIRST
    // CONTENT TOP
    // CONTENT
      array( // System help 
        'module' => 'system',
        'delta' => 'help',
        'theme' => openfed_return_default_front_theme_name(),
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
        'theme' => openfed_return_default_front_theme_name(),
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
        'theme' => openfed_return_default_front_theme_name(),
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


// CMS THEME
  $admin_values = array(
      // TOOLS
      // HEADER
      // NAVIGATION
        array( // Main Menu
          'module' => 'menu',
          'delta' => 'menu-cms-menu',
          'theme' => openfed_return_default_backend_theme_name(),
          'status' => 1,
          'weight' => 0,
          'region' => 'navigation',
          'pages' => '',
          'title' => '<none>',
          'cache' => -1,
        ),
      // TOP
      // BREADCRUMB
      array( // Breadcrumb
        'module' => 'easy_breadcrumb',
        'delta' => 'easy_breadcrumb',
        'theme' => openfed_return_default_backend_theme_name(),
        'status' => 1,
        'weight' => 0,
        'region' => 'breadcrumb',
        'pages' => '',
        'title' => '<none>',
        'cache' => -1,
      ),
      // SIDEBAR FIRST
      // CONTENT TOP
      // CONTENT
        array( // System help 
          'module' => 'system',
          'delta' => 'help',
          'theme' => openfed_return_default_backend_theme_name(),
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
          'theme' => openfed_return_default_backend_theme_name(),
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
