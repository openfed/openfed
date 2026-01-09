<?php

/**
 * @file
 * CKEditor 4 to CKEditor 5 migration helper functions.
 */

/**
 * Post-migration fix: Convert anchor link to bookmarks.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Convert.
 */
function _openfed_migrate_anchor_link(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  // Check if Anchor button was enabled in CKEditor 4.
  if (!in_array('Anchor', $enabled_buttons)) {
    $sandbox['messages'][] = "    No Anchor button found in CKEditor 4 toolbar, skipping bookmark migration";
    return;
  }

  $sandbox['messages'][] = "    Found Anchor button in CKEditor 4 toolbar";

  // Ensure bookmark module is enabled.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_plugin_pack_bookmark')) {
    \Drupal::service('module_installer')->install(['ckeditor5_plugin_pack_bookmark']);
    $sandbox['messages'][] = "    Enabled ckeditor5_plugin_pack_bookmark module";
  }

  // Get toolbar items.
  $toolbar_items = $settings['toolbar']['items'] ?? [];
  $has_bookmark = in_array('bookmark', $toolbar_items);
  $has_anchor = in_array('anchor', $toolbar_items);

  // Remove old anchor button if present (CKEditor 4 button that won't work in CKEditor 5).
  if ($has_anchor) {
    $toolbar_items = array_values(array_filter($toolbar_items, function($item) {
      return $item !== 'anchor';
    }));
    $sandbox['messages'][] = "    Removed anchor button from toolbar";
  }

  // Add bookmark button if not already present.
  if (!$has_bookmark) {
    $toolbar_items[] = 'bookmark';
    $sandbox['messages'][] = "    Added bookmark button to toolbar";
  }
  else {
    $sandbox['messages'][] = "    bookmark button already in toolbar";
  }

  // Update toolbar items.
  $settings['toolbar']['items'] = $toolbar_items;

  // Remove 'id' attribute from <a> tag in source editing settings.
  if (isset($settings['plugins']['ckeditor5_sourceEditing']['allowed_tags'])) {
    $original_tags = $settings['plugins']['ckeditor5_sourceEditing']['allowed_tags'];
    $updated_tags = [];
    $modified = FALSE;

    foreach ($original_tags as $tag) {
      // Check if this is an <a> tag with attributes.
      if (preg_match('/^<a(\s+[^>]+)?>$/i', $tag, $matches)) {
        $attributes = isset($matches[1]) ? trim($matches[1]) : '';

        // Check if it has the 'id' attribute.
        if (preg_match('/\bid\b/', $attributes)) {
          // Remove the id attribute.
          $new_attributes = preg_replace('/\s*\bid\b\s*/', ' ', $attributes);
          $new_attributes = trim(preg_replace('/\s+/', ' ', $new_attributes));

          if (!empty($new_attributes)) {
            // Still has other attributes after removing id.
            $modified_tag = '<a ' . $new_attributes . '>';
          }
          else {
            // No attributes left after removing id.
            $modified_tag = '<a>';
          }

          $updated_tags[] = $modified_tag;
          $sandbox['messages'][] = "      Modified source editing: '" . htmlspecialchars($tag) . "' -> '" . htmlspecialchars($modified_tag) . "'";
          $modified = TRUE;
        }
        else {
          $updated_tags[] = $tag;
        }
      }
      else {
        $updated_tags[] = $tag;
      }
    }

    if ($modified) {
      $settings['plugins']['ckeditor5_sourceEditing']['allowed_tags'] = $updated_tags;
    }
  }

  $sandbox['messages'][] = "    SUCCESS: Anchor migrated to bookmark";
}

/**
 * Post-migration fix: Set CodeMirror options.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Sets specific CodeMirror options for the source editing plugin.
 */
function _openfed_migrate_codemirror(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  $sandbox['messages'][] = "    Setting CodeMirror options...";

  if (!isset($settings['plugins'])) {
    $settings['plugins'] = [];
  }

  if (!isset($settings['plugins']['ckeditor_codemirror_source_editing'])) {
    $settings['plugins']['ckeditor_codemirror_source_editing'] = [];
  }

  if (!isset($settings['plugins']['ckeditor_codemirror_source_editing']['options'])) {
    $settings['plugins']['ckeditor_codemirror_source_editing']['options'] = [];
  }

  // Merge the three specific settings into existing options.
  $settings['plugins']['ckeditor_codemirror_source_editing']['options']['matchTags'] = TRUE;
  $settings['plugins']['ckeditor_codemirror_source_editing']['options']['searchBottom'] = TRUE;
  $settings['plugins']['ckeditor_codemirror_source_editing']['options']['styleActiveLine'] = TRUE;

  $sandbox['messages'][] = "    SUCCESS: CodeMirror options set";
}


/**
 * Post-migration fix: Fix entity_embed filter and link toolbar.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Adds link button and sets default Linkit profile if entity_embed filter is enabled.
 */
function _openfed_migrate_entity_embed(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  $filters = $format->get('filters');

  if (isset($filters['entity_embed']) && !empty($filters['entity_embed']['status'])) {
    $sandbox['messages'][] = "    entity_embed filter enabled, checking link toolbar...";

    $toolbar = $settings['toolbar'] ?? [];
    $has_link = FALSE;

    foreach ($toolbar['items'] as $item) {
      if ($item === 'link') {
        $has_link = TRUE;
        break;
      }
    }

    if (!$has_link) {
      $sandbox['messages'][] = "    Adding link button to toolbar...";
      $toolbar['items'][] = 'link';
      $settings['toolbar'] = $toolbar;
      $sandbox['messages'][] = "    Added link button";
    }

    // Set default Linkit profile.
    if (!isset($settings['plugins']['linkit_extension']['linkit_profile']) || empty($settings['plugins']['linkit_extension']['linkit_profile'])) {
      if (!isset($settings['plugins']['linkit_extension'])) {
        $settings['plugins']['linkit_extension'] = [];
      }
      $settings['plugins']['linkit_extension']['linkit_profile'] = 'default';
      $sandbox['messages'][] = "    Set default Linkit profile";
    }

    $sandbox['messages'][] = "    SUCCESS: entity_embed configured";
  }
  else {
    $sandbox['messages'][] = "    entity_embed not enabled, skipping";
  }
}
/**
 * Post-migration fix: Fix Heading plugin - remove heading1 (H1).
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Removes heading1 (H1) from enabled headings.
 */
function _openfed_migrate_heading(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  if (isset($settings['plugins']['ckeditor5_heading']['enabled_headings'])) {
    $enabled_headings = $settings['plugins']['ckeditor5_heading']['enabled_headings'];

    if (in_array('heading1', $enabled_headings)) {
      $sandbox['messages'][] = "    Removing heading1 (H1)...";
      $enabled_headings = array_values(array_diff($enabled_headings, ['heading1']));
      $settings['plugins']['ckeditor5_heading']['enabled_headings'] = $enabled_headings;
      $sandbox['messages'][] = "    SUCCESS: Removed heading1";
    }
    else {
      $sandbox['messages'][] = "    heading1 not enabled";
    }
  }
  else {
    $sandbox['messages'][] = "    Heading plugin not found, skipping";
  }
}

/**
 * Post-migration fix: Fix Media plugin view mode configuration.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Ensures at least 2 view modes are available if allow_view_mode_override is enabled.
 */
function _openfed_migrate_media(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  if (isset($settings['plugins']['media_media'])) {
    $media_settings = $settings['plugins']['media_media'];

    if (!empty($media_settings['allow_view_mode_override'])) {
      $sandbox['messages'][] = "    Fixing Media plugin view mode configuration...";

      $filters = $format->get('filters');

      // Only proceed if media_embed filter is enabled.
      if (isset($filters['media_embed']) && !empty($filters['media_embed']['status'])) {
        $media_embed_settings = $filters['media_embed']['settings'] ?? [];
        $existing_modes = $media_embed_settings['allowed_view_modes'] ?? [];

        // Ensure at least 2 view modes are available.
        if (count($existing_modes) < 2) {
          $sandbox['messages'][] = "    Extending allowed_view_modes to ensure at least 2 modes...";

          // Start with existing modes or empty array.
          $new_modes = $existing_modes;

          // Add default if not present.
          if (!isset($new_modes['default'])) {
            $new_modes['default'] = 'default';
          }

          // Add full if not present and we still need more modes.
          if (count($new_modes) < 2 && !isset($new_modes['full'])) {
            $new_modes['full'] = 'full';
          }

          $media_embed_settings['allowed_view_modes'] = $new_modes;
          $filters['media_embed']['settings'] = $media_embed_settings;
          $format->set('filters', $filters);
          $format->save();

          $sandbox['messages'][] = "    SUCCESS: Media plugin configured with " . count($new_modes) . " view modes";
        }
        else {
          $sandbox['messages'][] = "    Media plugin already has " . count($existing_modes) . " view modes, no changes needed";
        }
      }
      else {
        $sandbox['messages'][] = "    media_embed filter not enabled, skipping";
      }
    }
  }
  else {
    $sandbox['messages'][] = "    Media plugin not found, skipping";
  }
}

/**
 * Post-migration fix: Remove unsupported img tags from ckeditor5_style styles.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Removes any styles that use <img> tags, which are not supported in CKEditor 5 styles.
 */
function _openfed_migrate_styles(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  $sandbox['messages'][] = "    Removing img tags from ckeditor5_style styles...";

  if (!isset($settings['plugins']['ckeditor5_style']['styles'])) {
    $sandbox['messages'][] = "    No ckeditor5_style styles found, skipping";
  }
  else {
    $styles = $settings['plugins']['ckeditor5_style']['styles'];
    $modified = FALSE;

    foreach ($styles as $index => $style) {
      if (isset($style['element']) && preg_match('/^<img\b/', $style['element'])) {
        $sandbox['messages'][] = "    Removing style: " . ($style['label'] ?? 'unlabeled') . " (img tag)";
        unset($styles[$index]);
        $modified = TRUE;
      }
    }

    if ($modified) {
      // Reindex array to prevent gaps in numeric keys.
      $styles = array_values($styles);
      $settings['plugins']['ckeditor5_style']['styles'] = $styles;
      $sandbox['messages'][] = "    SUCCESS: img tags removed from styles";
    }
    else {
      $sandbox['messages'][] = "    No img tags found in styles";
    }
  }
}

/**
 * Post-migration fix: Fix Source Editing plugin.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Removes redundant tags and attributes from source editing allowed_tags.
 */
function _openfed_migrate_source_editing(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  if (isset($settings['plugins']['ckeditor5_sourceEditing'])) {
    $source_editing = $settings['plugins']['ckeditor5_sourceEditing'];

    if (!empty($source_editing['allowed_tags'])) {
      $original_tags = $source_editing['allowed_tags'];
      $updated_tags = [];
      $removed_tags = [];
      $modified_tags = [];

      // Elements where we should remove the class attribute.
      $elements_with_class = ['abbr', 'em', 'strong', 'ul', 'ol', 'li', 'table', 'caption', 'tbody', 'thead', 'tfoot', 'th', 'td', 'tr', 'blockquote', 'a', 'img'];

      // Elements that are fully supported by CKEditor5 and should be removed entirely.
      $fully_supported_elements = ['abbr', 'em', 'strong', 'li'];

      foreach ($original_tags as $tag) {
        $should_remove = FALSE;
        $modified_tag = $tag;

        // Check if this is a fully supported element (no attributes needed).
        foreach ($fully_supported_elements as $element) {
          if (preg_match('/^<' . preg_quote($element, '/') . '(\s|>)/i', $tag)) {
            $should_remove = TRUE;
            $removed_tags[] = [
              'tag' => $tag,
              'reason' => 'fully supported by CKEditor5',
            ];
            break;
          }
        }

        if ($should_remove) {
          continue;
        }

        // Check if this element has a class attribute that should be removed.
        foreach ($elements_with_class as $element) {
          if (preg_match('/^<' . preg_quote($element, '/') . '(\s+[^>]+)?>$/i', $tag, $elem_matches)) {
            $element_name = $element;
            $full_attributes = isset($elem_matches[1]) ? trim($elem_matches[1]) : '';

            if (preg_match('/\bclass\b/', $full_attributes)) {
              // Remove the class attribute.
              $new_attributes = preg_replace('/\s*\bclass\b\s*/', ' ', $full_attributes);
              $new_attributes = trim(preg_replace('/\s+/', ' ', $new_attributes));

              if (!empty($new_attributes)) {
                // Still has other attributes after removing class.
                $modified_tag = '<' . $element_name . ' ' . $new_attributes . '>';
                $modified_tags[] = [
                  'from' => $tag,
                  'to' => $modified_tag,
                ];
              }
              else {
                // No attributes left after removing class.
                // If it's a fully supported element, remove it; otherwise keep as basic tag.
                if (in_array($element_name, $fully_supported_elements)) {
                  $should_remove = TRUE;
                  $removed_tags[] = [
                    'tag' => $tag,
                    'reason' => 'fully supported, no attrs needed',
                  ];
                }
                else {
                  $modified_tag = '<' . $element_name . '>';
                  $modified_tags[] = [
                    'from' => $tag,
                    'to' => $modified_tag,
                  ];
                }
              }
              break;
            }
          }
        }

        if (!$should_remove) {
          $updated_tags[] = $modified_tag;
        }
      }

      if (count($removed_tags) > 0 || count($modified_tags) > 0) {
        $sandbox['messages'][] = "    Fixing Source Editing plugin...";
        foreach ($removed_tags as $removed) {
          $sandbox['messages'][] = "      Removed source editing: '" . htmlspecialchars($removed['tag']) . "' (" . htmlspecialchars($removed['reason']) . ")";
        }
        foreach ($modified_tags as $modified) {
          $sandbox['messages'][] = "      Modified source editing: '" . htmlspecialchars($modified['from']) . "' -> '" . htmlspecialchars($modified['to']) . "'";
        }

        $settings['plugins']['ckeditor5_sourceEditing']['allowed_tags'] = $updated_tags;
        $sandbox['messages'][] = "    SUCCESS: Source Editing cleaned";
      }
      else {
        $sandbox['messages'][] = "    Source Editing already clean";
      }
    }
  }
  else {
    $sandbox['messages'][] = "    Source Editing plugin not found, skipping";
  }
}

/**
 * Post-migration fix: Extract CKEditor templates and create config entities.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the editor.
 * Extracts templates from ckeditor_templates.js files and creates config entities.
 */
function _openfed_migrate_templates(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  // Check if Templates button was in CKEditor 4.
  if (!in_array('Templates', $enabled_buttons)) {
    return;
  }

  $sandbox['messages'][] = "    Templates button was enabled in CKEditor 4";

  // Ensure ckeditor5_plugin_pack_templates module is enabled.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_plugin_pack_templates')) {
    \Drupal::service('module_installer')->install(['ckeditor5_plugin_pack_templates']);
    $sandbox['messages'][] = "    Enabled ckeditor5_plugin_pack_templates module";
  }

  // Initialize templates processing state in sandbox if not already done.
  if (!isset($sandbox['templates_processed'])) {
    $sandbox['templates_processed'] = FALSE;
    $sandbox['templates_file_searched'] = FALSE;
    $sandbox['templates_file'] = NULL;
    $sandbox['template_ids'] = [];
  }

  // Search for templates file only once.
  if (!$sandbox['templates_file_searched']) {
    $sandbox['templates_file'] = _openfed_migrate_templates_find_ckeditor_templates_file('ckeditor_templates.js');
    $sandbox['templates_file_searched'] = TRUE;

    if ($sandbox['templates_file']) {
      $sandbox['messages'][] = "    Found template file: " . $sandbox['templates_file'];
    }
  }

  $js_file = $sandbox['templates_file'];

  if (!$js_file) {
    if (!$sandbox['templates_processed']) {
      $sandbox['messages'][] = "    Warning: Could not find ckeditor_templates.js file. Skipping template extraction.";
      $sandbox['templates_processed'] = TRUE;
    }
    return;
  }

  // Extract templates from the JS file only once (first time).
  if (!$sandbox['templates_processed']) {
    $template_ids = _openfed_migrate_templates_extract_ckeditor_templates($js_file, $sandbox, $format);
    $sandbox['template_ids'] = $template_ids;
    $sandbox['templates_processed'] = TRUE;

    if (count($template_ids) > 0) {
      $sandbox['messages'][] = "    Created " . count($template_ids) . " template(s)";

      // Remove the JS files.
      if (file_exists($js_file)) {
        unlink($js_file);
        $sandbox['messages'][] = "    Removed: " . $js_file;
      }

      $min_js_file = _openfed_migrate_templates_find_ckeditor_templates_file('ckeditor_templates.min.js');
      if ($min_js_file && file_exists($min_js_file)) {
        unlink($min_js_file);
        $sandbox['messages'][] = "    Removed: " . $min_js_file;
      }
    }
  }
  else {
    // Templates already created, add this format to existing template configs.
    if (count($sandbox['template_ids']) > 0) {
      _openfed_migrate_templates_add_format_to_templates($sandbox['template_ids'], $format, $sandbox);
    }
  }

  // Add insertTemplate button to toolbar if not present.
  if (count($sandbox['template_ids']) > 0) {
    $toolbar_items = $settings['toolbar']['items'] ?? [];
    if (!in_array('insertTemplate', $toolbar_items)) {
      $toolbar_items[] = 'insertTemplate';
      $settings['toolbar']['items'] = $toolbar_items;
      $sandbox['messages'][] = "    Added insertTemplate button to toolbar";
    }
    else {
      $sandbox['messages'][] = "    insertTemplate button already in toolbar";
    }

    $sandbox['messages'][] = "    SUCCESS: Templates configured for format: " . $format->id();
  }
}

/**
 * Find ckeditor_templates.js file in custom themes.
 */
function _openfed_migrate_templates_find_ckeditor_templates_file($filename) {
  $app_root = \Drupal::root();
  $search_path = $app_root . '/themes/custom';

  if (!is_dir($search_path)) {
    return NULL;
  }

  // Recursively search for the file.
  $iterator = new \RecursiveIteratorIterator(
    new \RecursiveDirectoryIterator($search_path, \RecursiveDirectoryIterator::SKIP_DOTS)
  );

  foreach ($iterator as $file) {
    if ($file->isFile() && $file->getFilename() === $filename) {
      return $file->getPathname();
    }
  }

  return NULL;
}

/**
 * Extract CKEditor templates from JS file and create config entities.
 */
function _openfed_migrate_templates_extract_ckeditor_templates($js_file, array &$sandbox, $format) {
  $content = file_get_contents($js_file);
  if (!$content) {
    return [];
  }

  // Extract imagesPath.
  $images_path = '';
  if (preg_match('/imagesPath:\s*["\']([^"\']+)["\']/', $content, $matches)) {
    $images_path = $matches[1];
  }

  // Extract templates array.
  if (!preg_match('/templates:\s*\[([\s\S]*?)\]\s*,?\s*}\s*\)/', $content, $templates_match)) {
    $sandbox['messages'][] = "    No templates found in JS file";
    return [];
  }

  $templates_str = $templates_match[1];

  // Parse individual templates.
  $template_regex = '/\{\s*title:\s*Drupal\.t\(["\']([^"\']+)["\']\)\s*,\s*image:\s*["\']([^"\']+)["\']\s*,\s*description:\s*Drupal\.t\(["\']([^"\']+)["\']\)\s*,\s*html:\s*(.+?)\s*,?\s*\}/s';

  preg_match_all($template_regex, $templates_str, $matches, PREG_SET_ORDER);

  $config_storage = \Drupal::service('config.storage');
  $uuid_service = \Drupal::service('uuid');
  $language_manager = \Drupal::languageManager();
  $default_langcode = $language_manager->getDefaultLanguage()->getId();

  $index = 0;
  $app_root = \Drupal::root();
  $template_ids = [];
  $format_id = $format->id();

  foreach ($matches as $match) {
    $title = $match[1];
    $image = $match[2];
    $description = $match[3];
    $html_parts = $match[4];

    // Construct image path.
    $image_path = '';
    if ($images_path && $image) {
      $image_path = $app_root . $images_path . $image;
    }

    // Clean up HTML (remove quotes and concatenation).
    $html = preg_replace('/["\']\\s*\\+\\s*["\']/', '', $html_parts);
    $html = preg_replace('/^["\']\\s*|\\s*["\']$/', '', $html);
    $html = preg_replace('/,\\s*$/', '', $html);
    $html = trim($html);

    // Generate machine name from title.
    $id = strtolower($title);
    $id = preg_replace('/\s+/', '_', $id);
    $id = preg_replace('/[^a-z0-9_]/', '', $id);

    // Get SVG code for image.
    $svg_code = _openfed_migrate_templates_get_svg_for_image($image);

    if (!$svg_code && $image_path) {
      $sandbox['messages'][] = "      Warning: No SVG icon found for image \"$image\" in template \"$title\"";
      $sandbox['messages'][] = "      Please manually validate at /admin/config/ckeditor5-templates/content-templates and convert image \"{$images_path}\" to SVG";
    }

    // Create config entity.
    $config_data = [
      'uuid' => $uuid_service->generate(),
      'langcode' => $default_langcode,
      'status' => TRUE,
      'dependencies' => [],
      'id' => $id,
      'label' => $title,
      'description' => $description,
      'icon' => $svg_code,
      'data' => $html,
      'textFormats' => [
        $format_id => $format_id,
      ],
      'weight' => $index,
    ];

    $config_name = 'ckeditor5_plugin_pack_templates.ckeditor5_template.' . $id;
    $config_storage->write($config_name, $config_data);

    // Remove image file if it exists.
    if ($image_path && file_exists($image_path)) {
      unlink($image_path);
      $sandbox['messages'][] = "      Removed image: " . $image_path;
    }

    $template_ids[] = $id;
    $index++;
  }

  return $template_ids;
}

/**
 * Get SVG code for template image.
 */
function _openfed_migrate_templates_get_svg_for_image($image_name) {
  $svg_map = [
    'textblock-blue.png' => '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 70">
  <defs>
    <clipPath id="rounded">
      <rect x="0" y="0" width="100" height="70" rx="12" ry="12"/>
    </clipPath>
  </defs>

  <rect x="0" y="0" width="100" height="70" rx="12" ry="12" fill="#E3E9ED"/>

  <rect x="0" y="0" width="8" height="70" fill="#9EC6D3" clip-path="url(#rounded)"/>

  <circle cx="45" cy="35" r="3" fill="#000"/>
  <circle cx="55" cy="35" r="3" fill="#000"/>
  <circle cx="65" cy="35" r="3" fill="#000"/>
</svg>',

    'organigram.png' => '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 200 140">
  <rect x="80" y="0" width="40" height="30" fill="#4A4A4A"/>
  <line x1="100" y1="30" x2="100" y2="55" stroke="#4A4A4A" stroke-width="2"/>
  <line x1="30" y1="55" x2="170" y2="55" stroke="#4A4A4A" stroke-width="2"/>
  <line x1="50" y1="55" x2="50" y2="80" stroke="#4A4A4A" stroke-width="2"/>
  <line x1="100" y1="55" x2="100" y2="80" stroke="#4A4A4A" stroke-width="2"/>
  <line x1="150" y1="55" x2="150" y2="80" stroke="#4A4A4A" stroke-width="2"/>
  <rect x="20" y="80" width="60" height="40" fill="#4A4A4A"/>
  <rect x="70" y="80" width="60" height="40" fill="#2FA4B8"/>
  <rect x="120" y="80" width="60" height="40" fill="#4A4A4A"/>
</svg>',

    'template2.gif' => '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 200 140">
  <rect x="2" y="2" width="180" height="100" fill="#FFFFFF" stroke="#4A4A4A" stroke-width="2"/>
  <rect x="20" y="20" width="60" height="8" rx="3" fill="#BFC7CC"/>
  <rect x="100" y="20" width="60" height="8" rx="3" fill="#BFC7CC"/>
  <rect x="20" y="40" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="20" y="52" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="20" y="64" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="100" y="40" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="100" y="52" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="100" y="64" width="60" height="5" rx="2.5" fill="#BFC7CC"/>
  <rect x="20" y="76" width="140" height="5" rx="3" fill="#BFC7CC"/>
  <rect x="20" y="88" width="140" height="5" rx="3" fill="#BFC7CC"/>
</svg>',

    'ico-table.svg' => '<svg enable-background="new 0 0 480 480" version="1.1" viewBox="0 0 480 480" xml:space="preserve" xmlns="http://www.w3.org/2000/svg">
  <path d="m472 0h-464c-4.418 0-8 3.582-8 8v464c0 4.418 3.582 8 8 8h464c4.418 0 8-3.582 8-8v-464c0-4.418-3.582-8-8-8zm-8 464h-448v-384h448v384zm0-400h-448v-48h448v48z"/>
  <rect x="32" y="32" width="16" height="16"/>
  <rect x="64" y="32" width="16" height="16"/>
  <rect x="96" y="32" width="16" height="16"/>
  <path d="m200 392h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
  <path d="m200 232h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
  <path d="m328 392h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
  <path d="m328 232h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
  <path d="m72 392h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
  <path d="m72 232h80c4.418 0 8-3.582 8-8v-64c0-4.418-3.582-8-8-8h-80c-4.418 0-8 3.582-8 8v64c0 4.418 3.582 8 8 8zm8-64h64v48h-64v-48z"/>
</svg>',
  ];

  return $svg_map[$image_name] ?? '';
}

/**
 * Add a format to existing template config entities.
 *
 * @param array $template_ids
 *   Array of template IDs to update.
 * @param \Drupal\filter\FilterFormatInterface $format
 *   The text format to add.
 * @param array $sandbox
 *   The sandbox array for messages.
 */
function _openfed_migrate_templates_add_format_to_templates(array $template_ids, $format, array &$sandbox) {
  $config_storage = \Drupal::service('config.storage');
  $format_id = $format->id();
  $updated_count = 0;

  foreach ($template_ids as $template_id) {
    $config_name = 'ckeditor5_plugin_pack_templates.ckeditor5_template.' . $template_id;
    $config_data = $config_storage->read($config_name);

    if ($config_data) {
      // Add the format to textFormats if not already present.
      if (!isset($config_data['textFormats'][$format_id])) {
        $config_data['textFormats'][$format_id] = $format_id;
        $config_storage->write($config_name, $config_data);
        $updated_count++;
      }
    }
  }

  if ($updated_count > 0) {
    $sandbox['messages'][] = "    Added format '$format_id' to $updated_count template(s)";
  }
  else {
    $sandbox['messages'][] = "    Format '$format_id' already in all templates";
  }
}

/**
 * Refactor ckeditor_stylesheets to ckeditor5-stylesheets in theme.info.yml files.
 *
 * This function:
 * - Finds all theme.info.yml files in custom themes
 * - Replaces ckeditor_stylesheets with ckeditor5-stylesheets
 * - Updates SCSS files to use .ck-content instead of .cke_editable
 * - Removes CKEditor 4 specific styles like .cke_panel_listItem
 *
 * @param array $sandbox
 *   The sandbox array.
 */
function _openfed_refactor_ckeditor_stylesheets(array &$sandbox) {
  $sandbox['messages'][] = "Refactoring ckeditor_stylesheets in theme.info.yml files...";

  $app_root = \Drupal::root();
  $custom_themes_path = $app_root . '/themes/custom';

  // Check if custom themes directory exists.
  if (!is_dir($custom_themes_path)) {
    $sandbox['messages'][] = "  No custom themes directory found.";
    return;
  }

  // Find all .info.yml files in custom themes.
  $info_files = [];
  $iterator = new \RecursiveIteratorIterator(
    new \RecursiveDirectoryIterator($custom_themes_path, \RecursiveDirectoryIterator::SKIP_DOTS)
  );

  foreach ($iterator as $file) {
    if ($file->isFile() && preg_match('/\.info\.yml$/', $file->getFilename())) {
      $info_files[] = $file->getPathname();
    }
  }

  if (empty($info_files)) {
    $sandbox['messages'][] = "  No .info.yml files found in custom themes.";
    return;
  }

  $updated_count = 0;

  foreach ($info_files as $info_file) {
    $content = file_get_contents($info_file);

    // Check if the file contains ckeditor_stylesheets.
    if (strpos($content, 'ckeditor_stylesheets:') === FALSE) {
      continue;
    }

    $sandbox['messages'][] = "  Found ckeditor_stylesheets in: " . basename(dirname($info_file));

    // Extract CSS paths from ckeditor_stylesheets section.
    $css_paths = _openfed_extract_css_paths_from_info($content);
    $theme_dir = dirname($info_file);

    // Process each CSS path.
    foreach ($css_paths as $css_path) {
      $sandbox['messages'][] = "    CSS path: $css_path";

      // Try to find the SCSS source file.
      $scss_path = preg_replace('/\.css$/', '.scss', $css_path);
      $full_scss_path = $theme_dir . '/' . $scss_path;

      // Also check scss/ directory variant.
      $scss_alt_path = str_replace('css/', 'scss/', $scss_path);
      $full_scss_alt_path = $theme_dir . '/' . $scss_alt_path;

      $actual_scss_path = NULL;
      if (file_exists($full_scss_path)) {
        $actual_scss_path = $full_scss_path;
      }
      elseif (file_exists($full_scss_alt_path)) {
        $actual_scss_path = $full_scss_alt_path;
      }

      if ($actual_scss_path) {
        _openfed_update_scss_for_ckeditor5($sandbox, $actual_scss_path);

        // Remove compiled CSS file if it exists.
        $full_css_path = $theme_dir . '/' . $css_path;
        if (file_exists($full_css_path)) {
          unlink($full_css_path);
          $sandbox['messages'][] = "    Removed old CSS file (will be regenerated): $css_path";
        }
      }
      else {
        $sandbox['messages'][] = "    WARNING: SCSS file not found for: $css_path";
      }
    }

    // Replace ckeditor_stylesheets with ckeditor5-stylesheets.
    $updated_content = str_replace('ckeditor_stylesheets:', 'ckeditor5-stylesheets:', $content);
    file_put_contents($info_file, $updated_content);

    $sandbox['messages'][] = "  Updated ckeditor_stylesheets to ckeditor5-stylesheets in: " . basename($info_file);
    $updated_count++;
  }

  if ($updated_count > 0) {
    $sandbox['messages'][] = "Successfully updated $updated_count theme.info.yml file(s).";
    $sandbox['messages'][] = "";
    $sandbox['messages'][] = "⚠️  WARNING: Manual validation required!";
    $sandbox['messages'][] = "Please manually review heading styles (h1-h6) in updated SCSS files.";
    $sandbox['messages'][] = "After validation, recompile your theme's CSS to apply changes.";
  }
  else {
    $sandbox['messages'][] = "No ckeditor_stylesheets definitions found in theme.info.yml files.";
  }
}

/**
 * Extract CSS paths from ckeditor_stylesheets section in theme.info.yml content.
 *
 * @param string $content
 *   The content of the .info.yml file.
 *
 * @return array
 *   Array of CSS paths.
 */
function _openfed_extract_css_paths_from_info($content) {
  $css_paths = [];
  $lines = explode("\n", $content);
  $in_section = FALSE;

  foreach ($lines as $line) {
    // Check if we're entering the ckeditor_stylesheets section.
    if (preg_match('/^ckeditor_stylesheets:/', $line)) {
      $in_section = TRUE;
      continue;
    }

    if ($in_section) {
      // Check if we've left the section (new top-level key).
      if (preg_match('/^[a-zA-Z]/', $line) && !preg_match('/^\s/', $line)) {
        break;
      }

      // Extract CSS path from list item.
      if (preg_match('/^\s*-\s*["\']?([^"\']+)["\']?\s*$/', $line, $matches)) {
        $css_paths[] = trim($matches[1]);
      }
    }
  }

  return $css_paths;
}

/**
 * Update SCSS file to use CKEditor 5 class names.
 *
 * @param array $sandbox
 *   The sandbox array.
 * @param string $scss_file_path
 *   The path to the SCSS file.
 */
function _openfed_update_scss_for_ckeditor5(array &$sandbox, $scss_file_path) {
  $content = file_get_contents($scss_file_path);

  // Build updated content with header.
  $updated_content = "// CKEditor 5 content styles\n";
  $updated_content .= "// Original styles updated for CKEditor 5\n";
  $updated_content .= "// Updated: .cke_editable replaced with .ck-content\n";
  $updated_content .= "// Removed: Lines containing .cke_panel_listItem (CKEditor 4 specific)\n";
  $updated_content .= "// Source: https://www.drupal.org/node/3259165\n";
  $updated_content .= "\n";

  // Replace .cke_editable with .ck-content and remove lines with .cke_panel_listItem.
  $lines = explode("\n", $content);
  foreach ($lines as $line) {
    // Skip lines containing .cke_panel_listItem.
    if (strpos($line, '.cke_panel_listItem') !== FALSE) {
      continue;
    }
    // Replace .cke_editable with .ck-content.
    $line = str_replace('.cke_editable', '.ck-content', $line);
    $updated_content .= $line . "\n";
  }

  file_put_contents($scss_file_path, $updated_content);
  $sandbox['messages'][] = "    Updated SCSS with .ck-content replacement: " . basename($scss_file_path);
}

