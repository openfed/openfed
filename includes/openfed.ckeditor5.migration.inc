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
 * If no styles remain after cleanup (or were empty to begin with), removes the style button from toolbar.
 */
function _openfed_migrate_styles(array &$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  $sandbox['messages'][] = "    Removing img tags from ckeditor5_style styles...";

  // Check if styles configuration exists and is not empty.
  if (!isset($settings['plugins']['ckeditor5_style']['styles'])) {
    $sandbox['messages'][] = "    No ckeditor5_style styles found, skipping";
    return;
  }

  $styles = $settings['plugins']['ckeditor5_style']['styles'];

  // Check if styles array is empty (CKEditor 4 had Styles button but no actual styles configured).
  if (empty($styles)) {
    $sandbox['messages'][] = "    Styles array was already empty (no styles configured in CKEditor 4)";
    _openfed_migrate_styles_remove_empty_config($settings, $sandbox);
    return;
  }

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

  // Check if styles array is now empty after removing img tags.
  if (empty($styles)) {
    $sandbox['messages'][] = "    Styles array is empty after cleanup";
    _openfed_migrate_styles_remove_empty_config($settings, $sandbox);
  }
}

/**
 * Helper function to remove empty style configuration and button.
 *
 * @param array $settings
 *   The editor settings array.
 * @param array $sandbox
 *   The sandbox array for messages.
 */
function _openfed_migrate_styles_remove_empty_config(array &$settings, array &$sandbox) {
  // Remove style button from toolbar.
  $toolbar_items = $settings['toolbar']['items'] ?? [];
  $original_count = count($toolbar_items);

  $toolbar_items = array_values(array_filter($toolbar_items, function($item) {
    return $item !== 'style';
  }));

  if (count($toolbar_items) < $original_count) {
    $settings['toolbar']['items'] = $toolbar_items;
    $sandbox['messages'][] = "    Removed 'style' button from toolbar";
  }

  // Remove the empty styles configuration.
  unset($settings['plugins']['ckeditor5_style']);
  $sandbox['messages'][] = "    Removed empty ckeditor5_style plugin configuration";
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
      $elements_with_class = ['abbr', 'em', 'strong', 'ul', 'ol', 'li', 'table', 'caption', 'tbody', 'thead', 'tfoot', 'th', 'td', 'tr', 'blockquote', 'a', 'img', 'h2', 'h3', 'h4', 'h5', 'h6'];

      // Elements that are fully supported by CKEditor5 and should be removed entirely.
      $fully_supported_elements = ['abbr', 'em', 'strong', 'li', 'p'];

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

  // Initialize templates tracking in sandbox if not already done.
  if (!isset($sandbox['templates_processed'])) {
    $sandbox['templates_processed'] = FALSE;
    $sandbox['template_ids'] = [];
  }

  // Check if templates have already been processed.
  if ($sandbox['templates_processed']) {
    // Templates already created, add this format to existing template configs.
    if (!empty($sandbox['template_ids'])) {
      $sandbox['messages'][] = "    Templates already extracted, adding format to existing templates";
      _openfed_migrate_templates_add_format_to_templates($sandbox['template_ids'], $format, $sandbox);
    }
    else {
      $sandbox['messages'][] = "    No templates were previously extracted";
    }
  }
  else {
    // First format with Templates button enabled - search for and process the file.
    $js_file = _openfed_migrate_templates_find_ckeditor_templates_file('ckeditor_templates.js');

    if (!$js_file) {
      $sandbox['messages'][] = "    ⚠️  Warning: Could not find ckeditor_templates.js file. Skipping template extraction.";
      // Mark as processed even though no file found, to prevent repeated searches.
      $sandbox['templates_processed'] = TRUE;
      $sandbox['template_ids'] = [];
      return;
    }

    $sandbox['messages'][] = "    Found template file: " . $js_file;

    // Extract templates from the JS file.
    $template_ids = _openfed_migrate_templates_extract_ckeditor_templates($js_file, $sandbox, $format, $settings);

    // Mark as processed and save template IDs.
    $sandbox['templates_processed'] = TRUE;
    $sandbox['template_ids'] = $template_ids;

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
    else {
      $sandbox['messages'][] = "    No templates were extracted from the file";
      return;
    }
  }

  // Add insertTemplate button to toolbar if templates exist.
  if (!empty($sandbox['template_ids'])) {
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
function _openfed_migrate_templates_extract_ckeditor_templates($js_file, array &$sandbox, $format, array &$settings) {
  $content = file_get_contents($js_file);
  if (!$content) {
    $sandbox['messages'][] = "    ERROR: Could not read template file";
    return [];
  }

  // Extract imagesPath - handle both simple strings and ternary expressions.
  $images_path = '';
  if (preg_match('/imagesPath:\s*["\']([^"\']+)["\']/', $content, $matches)) {
    // Simple string format.
    $images_path = $matches[1];
  }
  elseif (preg_match('/imagesPath:\s*[\s\S]*?\+\s*["\']([^"\']+)["\']/', $content, $matches)) {
    // Ternary expression with concatenation - extract the path suffix.
    $images_path = '/' . ltrim($matches[1], '/');
  }

  // Extract templates array.
  if (!preg_match('/templates:\s*\[([\s\S]*?)\]\s*,?\s*}\s*\)/', $content, $templates_match)) {
    $sandbox['messages'][] = "    ⚠️  WARNING: No templates array found in JS file";
    $sandbox['messages'][] = "    The file may have an unexpected format. Please check the template file structure.";
    return [];
  }

  $templates_str = $templates_match[1];

  // Split templates by },\s* pattern to separate individual template objects
  // This is more reliable than trying to match the entire template with one regex
  $template_objects = preg_split('/\}\s*,\s*(?=\{|$)/', $templates_str);

  // Filter out empty entries
  $template_objects = array_filter($template_objects, function($obj) {
    return !empty(trim($obj));
  });

  $sandbox['messages'][] = "    Split into " . count($template_objects) . " template object(s), parsing...";

  $parsed_templates = [];
  foreach ($template_objects as $idx => $template_obj) {
    // Clean up the template string
    $template_obj = trim($template_obj);
    if (empty($template_obj)) {
      continue;
    }

    // Add back closing brace if it was removed by split
    if (!preg_match('/\}\s*$/', $template_obj)) {
      $template_obj .= '}';
    }

    // Extract title
    if (!preg_match('/title:\s*(?:Drupal\.t\()?\s*["\']([^"\']+)["\']\s*\)?/', $template_obj, $title_match)) {
      $sandbox['messages'][] = "      ⚠️  Template #" . ($idx + 1) . ": Could not extract title";
      continue;
    }
    $title = $title_match[1];

    // Extract image
    if (!preg_match('/image:\s*["\']([^"\']+)["\']/', $template_obj, $image_match)) {
      $sandbox['messages'][] = "      ⚠️  Template #" . ($idx + 1) . " ('$title'): Could not extract image";
      continue;
    }
    $image = $image_match[1];

    // Extract description
    if (!preg_match('/description:\s*(?:Drupal\.t\()?\s*["\']([^"\']+)["\']\s*\)?/', $template_obj, $desc_match)) {
      $sandbox['messages'][] = "      ⚠️  Template #" . ($idx + 1) . " ('$title'): Could not extract description";
      continue;
    }
    $description = $desc_match[1];

    // Extract html - everything after 'html:' until the end
    if (!preg_match('/html:\s*([\s\S]+?)(?:\s*\}?\s*$)/', $template_obj, $html_match)) {
      $sandbox['messages'][] = "      ⚠️  Template #" . ($idx + 1) . " ('$title'): Could not extract html";
      continue;
    }
    $html_parts = $html_match[1];

    $parsed_templates[] = [
      'title' => $title,
      'image' => $image,
      'description' => $description,
      'html_parts' => $html_parts,
    ];
  }

  if (empty($parsed_templates)) {
    $sandbox['messages'][] = "    ⚠️  WARNING: No templates matched the expected format in JS file";
    $sandbox['messages'][] = "    Expected format: { title: 'Title' or Drupal.t('Title'), image: 'image.png', description: 'Description' or Drupal.t('Description'), html: '...' }";
    return [];
  }

  $sandbox['messages'][] = "    Found " . count($parsed_templates) . " template(s) in JS file, creating config entities...";

  $config_storage = \Drupal::service('config.storage');
  $uuid_service = \Drupal::service('uuid');
  $language_manager = \Drupal::languageManager();
  $default_langcode = $language_manager->getDefaultLanguage()->getId();

  $index = 0;
  $app_root = \Drupal::root();
  $template_ids = [];
  $format_id = $format->id();

  // Collect all classes from templates for validation.
  $classes_to_validate = ['ul' => [], 'a' => []];

  foreach ($parsed_templates as $template) {
    $title = $template['title'];
    $image = $template['image'];
    $description = $template['description'];
    $html_parts = $template['html_parts'];

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

    // Extract classes from ul and a tags in the template HTML.
    _openfed_migrate_templates_extract_classes_from_html($html, $classes_to_validate);

    // Generate machine name from title.
    $id = strtolower($title);
    $id = preg_replace('/\s+/', '_', $id);
    $id = preg_replace('/[^a-z0-9_]/', '', $id);

    // Create SVG icon from image.
    $svg_code = _openfed_migrate_templates_create_svg_from_image($image_path, $sandbox);

    if (!$svg_code && $image_path) {
      $sandbox['messages'][] = "      ⚠️  Warning: No SVG icon created for image \"$image\" in template \"$title\"";
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
    $sandbox['messages'][] = "      Created template config: $id (\"$title\")";

    // Remove image file if it exists.
    if ($image_path && file_exists($image_path)) {
      unlink($image_path);
      $sandbox['messages'][] = "      Removed image: " . $image_path;
    }

    $template_ids[] = $id;
    $index++;
  }

  // Validate and add missing styles for ul and a tags with classes.
  _openfed_migrate_templates_validate_and_add_styles($classes_to_validate, $settings, $sandbox);

  return $template_ids;
}

/**
 * Extract classes from ul and a tags in template HTML.
 *
 * @param string $html
 *   The HTML content to parse.
 * @param array $classes_to_validate
 *   Array to collect classes, keyed by tag name (ul, a).
 */
function _openfed_migrate_templates_extract_classes_from_html($html, array &$classes_to_validate) {
  // Extract classes from <ul> tags.
  if (preg_match_all('/<ul\s+[^>]*class=["\']([^"\']+)["\'][^>]*>/i', $html, $ul_matches)) {
    foreach ($ul_matches[1] as $class_attr) {
      // Split by spaces to get individual classes.
      $classes = preg_split('/\s+/', trim($class_attr));
      foreach ($classes as $class) {
        if (!empty($class)) {
          $classes_to_validate['ul'][$class] = $class;
        }
      }
    }
  }

  // Extract classes from <a> tags.
  if (preg_match_all('/<a\s+[^>]*class=["\']([^"\']+)["\'][^>]*>/i', $html, $a_matches)) {
    foreach ($a_matches[1] as $class_attr) {
      // Split by spaces to get individual classes.
      $classes = preg_split('/\s+/', trim($class_attr));
      foreach ($classes as $class) {
        if (!empty($class)) {
          $classes_to_validate['a'][$class] = $class;
        }
      }
    }
  }
}

/**
 * Validate classes against existing styles and add missing ones.
 *
 * @param array $classes_to_validate
 *   Array of classes to validate, keyed by tag name (ul, a).
 * @param array $settings
 *   The editor settings array.
 * @param array $sandbox
 *   The sandbox array for messages.
 */
function _openfed_migrate_templates_validate_and_add_styles(array $classes_to_validate, array &$settings, array &$sandbox) {
  // Check if there are any classes to validate.
  $has_classes = FALSE;
  foreach ($classes_to_validate as $tag => $classes) {
    if (!empty($classes)) {
      $has_classes = TRUE;
      break;
    }
  }

  if (!$has_classes) {
    return;
  }

  // Get existing styles.
  $existing_styles = $settings['plugins']['ckeditor5_style']['styles'] ?? [];

  // Build a map of existing styles by element and class.
  $existing_style_map = [];
  foreach ($existing_styles as $style) {
    if (isset($style['element'])) {
      // Parse element like "<ul class='check-list'>"
      if (preg_match('/<(\w+)\s+[^>]*class=["\']([^"\']+)["\']/', $style['element'], $matches)) {
        $tag = $matches[1];
        $class_attr = $matches[2];
        $classes = preg_split('/\s+/', trim($class_attr));
        foreach ($classes as $class) {
          if (!empty($class)) {
            $existing_style_map[$tag][$class] = true;
          }
        }
      }
    }
  }

  // Check and add missing styles.
  $added_styles = [];
  foreach ($classes_to_validate as $tag => $classes) {
    foreach ($classes as $class) {
      if (!isset($existing_style_map[$tag][$class])) {
        // Create a new style entry.
        $new_style = [
          'label' => ucfirst(str_replace(['-', '_'], ' ', $class)),
          'element' => "<$tag class=\"$class\">",
        ];
        $existing_styles[] = $new_style;
        $added_styles[] = "$tag.$class";
        $sandbox['messages'][] = "      Added style: $tag.$class";
      }
    }
  }

  // Update settings if new styles were added.
  if (!empty($added_styles)) {
    $settings['plugins']['ckeditor5_style']['styles'] = $existing_styles;
    $sandbox['messages'][] = "    Added " . count($added_styles) . " missing style(s) from templates";
    $sandbox['messages'][] = "    ⚠️  WARNING: Manual validation required!";
  }
}

/**
 * Create an SVG from an image file by embedding it as base64.
 *
 * @param string $image_path
 *   The full path to the image file.
 * @param array $sandbox
 *   The sandbox array for messages.
 *
 * @return string
 *   The SVG code with embedded image, or empty string if conversion failed.
 */
function _openfed_migrate_templates_create_svg_from_image($image_path, array &$sandbox): string {
  if (!file_exists($image_path)) {
    return '';
  }

  $image_info = @getimagesize($image_path);
  if (!$image_info) {
    $sandbox['messages'][] = "      Could not get image info for: " . basename($image_path);
    return '';
  }

  $width = $image_info[0];
  $height = $image_info[1];
  $mime_type = $image_info['mime'];

  // Read the image file and encode as base64.
  $image_data = file_get_contents($image_path);
  if (!$image_data) {
    $sandbox['messages'][] = "      Could not read image file: " . basename($image_path);
    return '';
  }

  $base64 = base64_encode($image_data);

  // Create SVG with embedded image.
  $svg = '<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 ' . $width . ' ' . $height . '">';
  $svg .= '<image width="' . $width . '" height="' . $height . '" xlink:href="data:' . $mime_type . ';base64,' . $base64 . '"/>';
  $svg .= '</svg>';

  $sandbox['messages'][] = "      Created SVG from image: " . basename($image_path) . " ({$width}x{$height})";

  return $svg;
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
  /** @var \Drupal\Core\File\FileSystemInterface $file_system */
  $file_system = \Drupal::service('file_system');

  $files = $file_system->scanDirectory($custom_themes_path, '/\.info\.yml$/');
  $info_files = array_column($files, 'uri');

  if (empty($info_files)) {
    $sandbox['messages'][] = "  No .info.yml files found in custom themes.";
    return;
  }

  $updated_count = 0;

  foreach ($info_files as $info_file) {
    $content = file_get_contents($info_file);

    // Check if the file contains ckeditor_stylesheets.
    if (!str_contains($content, 'ckeditor_stylesheets:')) {
      continue;
    }

    $sandbox['messages'][] = "  Found ckeditor_stylesheets in: " . basename(dirname($info_file));

    // Extract CSS paths from ckeditor_stylesheets section.
    $css_paths = _openfed_extract_css_paths_from_info($content);
    $theme_dir = dirname($info_file);

    // Process each CSS path.
    foreach ($css_paths as $css_path) {
      $sandbox['messages'][] = "    CSS path: $css_path";

      // Try to find the SCSS source file by scanning the theme directory.
      $scss_filename = basename(preg_replace('/\.css$/', '.scss', $css_path));
      $actual_scss_path = _openfed_find_file_in_directory($theme_dir, $scss_filename);

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
        $sandbox['messages'][] = "    ⚠️  WARNING: SCSS file not found for: $css_path";
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
 * Find a file by name within a directory, scanning recursively.
 *
 * @param string $directory
 *   The directory to search in.
 * @param string $filename
 *   The filename to search for.
 *
 * @return string|null
 *   The full path to the file if found, or NULL if not found.
 */
function _openfed_find_file_in_directory($directory, $filename) {
  // First check the root of the directory.
  $root_path = $directory . '/' . $filename;
  if (file_exists($root_path)) {
    return $root_path;
  }

  // Common subdirectories where SCSS files might live.
  $common_paths = [
    'src/scss',
    'scss',
    'assets/scss',
    'styles/scss',
    'css',
    'src/css',
    'assets/css',
    'styles',
  ];

  // Check common paths first for performance.
  foreach ($common_paths as $subdir) {
    $path = $directory . '/' . $subdir . '/' . $filename;
    if (file_exists($path)) {
      return $path;
    }
  }

  // If not found in common paths, scan the entire directory recursively
  // using Drupal's file system service.
  /** @var \Drupal\Core\File\FileSystemInterface $file_system */
  $file_system = \Drupal::service('file_system');

  // Escape special regex characters in the filename and create a pattern.
  $pattern = '/^' . preg_quote($filename, '/') . '$/';

  $files = $file_system->scanDirectory($directory, $pattern);
  if (!empty($files)) {
    // Return the first match found.
    $file = reset($files);
    return $file->uri;
  }

  return NULL;
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

  // Remove lines containing .cke_panel_listItem (CKEditor 4 specific).
  $lines = explode("\n", $content);
  $filtered_lines = [];
  foreach ($lines as $line) {
    if (!str_contains($line, '.cke_panel_listItem')) {
      $filtered_lines[] = $line;
    }
  }
  $content = implode("\n", $filtered_lines);

  // Check if the content contains .cke_editable section.
  if (preg_match('/\.cke_editable\s*\{([\s\S]*)\}/s', $content, $matches, PREG_OFFSET_CAPTURE)) {
    // Extract the inner content of .cke_editable.
    $inner_content = $matches[1][0];

    // Get the content before .cke_editable.
    $before_content = trim(substr($content, 0, $matches[0][1]));

    // Get the content after .cke_editable (after the closing brace).
    $after_start = $matches[0][1] + strlen($matches[0][0]);
    $after_content = trim(substr($content, $after_start));

    // Combine all content parts, indented for .ck-content wrapper.
    $combined_content = '';
    if (!empty($before_content)) {
      $combined_content .= _openfed_indent_scss_content($before_content, 2) . "\n\n";
    }
    // Inner content already has indentation from original file, just use it as-is.
    $combined_content .= $inner_content;
    if (!empty($after_content)) {
      $combined_content .= "\n\n" . _openfed_indent_scss_content($after_content, 2);
    }

    // Build updated content: wrap everything in .ck-content.
    $updated_content = ".ck-content {\n";
    $updated_content .= $combined_content . "\n";
    $updated_content .= "}\n";
  }
  else {
    // No .cke_editable found, wrap the full content in .ck-content.
    $indented_content = _openfed_indent_scss_content(trim($content), 2);

    $updated_content = ".ck-content {\n";
    $updated_content .= $indented_content . "\n";
    $updated_content .= "}\n";
  }

  $sandbox['messages'][] = "    CKEditor 5 content styles";
  $sandbox['messages'][] = "    Original styles updated for CKEditor 5";
  $sandbox['messages'][] = "    All content wrapped in .ck-content";
  $sandbox['messages'][] = "    Removed: Lines containing .cke_panel_listItem (CKEditor 4 specific)";
  $sandbox['messages'][] = "    Source: https://www.drupal.org/node/3259165";

  file_put_contents($scss_file_path, $updated_content);
  $sandbox['messages'][] = "    Updated SCSS with .ck-content: " . basename($scss_file_path);
}

/**
 * Indent SCSS content by a specified number of spaces.
 *
 * @param string $content
 *   The SCSS content to indent.
 * @param int $spaces
 *   The number of spaces to indent.
 *
 * @return string
 *   The indented content.
 */
function _openfed_indent_scss_content($content, $spaces) {
  $indent = str_repeat(' ', $spaces);
  $lines = explode("\n", $content);
  $indented_lines = [];

  foreach ($lines as $line) {
    // Only indent non-empty lines.
    if (trim($line) !== '') {
      $indented_lines[] = $indent . $line;
    }
    else {
      $indented_lines[] = $line;
    }
  }

  return implode("\n", $indented_lines);
}

