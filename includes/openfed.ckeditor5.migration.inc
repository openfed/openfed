<?php

/**
 * @file
 * CKEditor 4 to CKEditor 5 migration helper functions.
 */

use Drupal\ckeditor5\Plugin\CKEditor5PluginConfigurableInterface;
use Drupal\editor\EditorInterface;
use Drupal\filter\FilterFormatInterface;

/**
 * Post-migration fix: Convert anchor link to bookmarks.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Convert.
 */
function _openfed_migrate_anchor_link(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  // Check if Anchor button was enabled in CKEditor 4.
  if (!in_array('Anchor', $enabled_buttons)) {
    _openfed_log_message($sandbox, "No Anchor button found in CKEditor 4 toolbar, skipping bookmark migration", 'debug', 4);
    return;
  }

  _openfed_log_message($sandbox, "Found Anchor button in CKEditor 4 toolbar", 'debug', 4);

  // Ensure bookmark module is enabled.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_plugin_pack_bookmark')) {
    \Drupal::service('module_installer')->install(['ckeditor5_plugin_pack_bookmark']);
    _openfed_log_message($sandbox, "Enabled ckeditor5_plugin_pack_bookmark module", 'debug', 4);
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
    _openfed_log_message($sandbox, "Removed anchor button from toolbar", 'debug', 4);
  }

  // Add bookmark button if not already present.
  if (!$has_bookmark) {
    $toolbar_items[] = 'bookmark';
    _openfed_log_message($sandbox, "Added bookmark button to toolbar", 'debug', 4);
  }
  else {
    _openfed_log_message($sandbox, "bookmark button already in toolbar", 'debug', 4);
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
          _openfed_log_message($sandbox, "Modified source editing: '" . htmlspecialchars($tag) . "' -> '" . htmlspecialchars($modified_tag) . "'", 'debug', 6);
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

  _openfed_log_message($sandbox, "Anchor migrated to bookmark", 'debug', 4);
}

/**
 * Post-migration fix: Set CodeMirror options.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Sets specific CodeMirror options for the source editing plugin.
 */
function _openfed_migrate_codemirror(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  _openfed_log_message($sandbox, "Setting CodeMirror options...", 'debug', 4);

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

  _openfed_log_message($sandbox, "CodeMirror options set", 'debug', 4);
}


/**
 * Post-migration fix: Fix entity_embed filter and link toolbar.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Adds link button and sets default Linkit profile if entity_embed
 * filter is enabled.
 */
function _openfed_migrate_entity_embed(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  $filters = $format->get('filters');

  if (isset($filters['entity_embed']) && !empty($filters['entity_embed']['status'])) {
    _openfed_log_message($sandbox, "entity_embed filter enabled, checking link toolbar...", 'debug', 4);

    $toolbar = $settings['toolbar'] ?? [];
    $has_link = FALSE;

    foreach ($toolbar['items'] as $item) {
      if ($item === 'link') {
        $has_link = TRUE;
        break;
      }
    }

    if (!$has_link) {
      _openfed_log_message($sandbox, "Adding link button to toolbar...", 'debug', 4);
      $toolbar['items'][] = 'link';
      $settings['toolbar'] = $toolbar;
      _openfed_log_message($sandbox, "Added link button", 'debug', 4);
    }

    // Set default Linkit profile.
    if (!isset($settings['plugins']['linkit_extension']['linkit_profile']) || empty($settings['plugins']['linkit_extension']['linkit_profile'])) {
      if (!isset($settings['plugins']['linkit_extension'])) {
        $settings['plugins']['linkit_extension'] = [];
      }
      $settings['plugins']['linkit_extension']['linkit_profile'] = 'default';
      _openfed_log_message($sandbox, "Set default Linkit profile", 'debug', 4);
    }

    _openfed_log_message($sandbox, "entity_embed configured", 'debug', 4);
  }
  else {
    _openfed_log_message($sandbox, "entity_embed not enabled, skipping", 'debug', 4);
  }
}
/**
 * Post-migration fix: Fix Heading plugin - remove heading1 (H1).
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Removes heading1 (H1) from enabled headings.
 */
function _openfed_migrate_heading(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  if (isset($settings['plugins']['ckeditor5_heading']['enabled_headings'])) {
    $enabled_headings = $settings['plugins']['ckeditor5_heading']['enabled_headings'];

    if (in_array('heading1', $enabled_headings)) {
      _openfed_log_message($sandbox, "Removing heading1 (H1)...", 'debug', 4);
      $enabled_headings = array_values(array_diff($enabled_headings, ['heading1']));
      $settings['plugins']['ckeditor5_heading']['enabled_headings'] = $enabled_headings;
      _openfed_log_message($sandbox, "Removed heading1", 'debug', 4);
    }
    else {
      _openfed_log_message($sandbox, "heading1 not enabled", 'debug', 4);
    }
  }
  else {
    _openfed_log_message($sandbox, "Heading plugin not found, skipping", 'debug', 4);
  }
}

/**
 * Post-migration fix: Fix Media plugin view mode configuration.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Ensures at least 2 view modes are available if
 * allow_view_mode_override is enabled.
 */
function _openfed_migrate_media(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  if (isset($settings['plugins']['media_media'])) {
    $media_settings = $settings['plugins']['media_media'];

    if (!empty($media_settings['allow_view_mode_override'])) {
      _openfed_log_message($sandbox, "Fixing Media plugin view mode configuration...", 'debug', 4);

      $filters = $format->get('filters');

      // Only proceed if media_embed filter is enabled.
      if (isset($filters['media_embed']) && !empty($filters['media_embed']['status'])) {
        $media_embed_settings = $filters['media_embed']['settings'] ?? [];
        $existing_modes = $media_embed_settings['allowed_view_modes'] ?? [];

        // Ensure at least 2 view modes are available.
        if (count($existing_modes) < 2) {
          _openfed_log_message($sandbox, "Extending allowed_view_modes to ensure at least 2 modes...", 'debug', 4);

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

          _openfed_log_message($sandbox, "Media plugin configured with " . count($new_modes) . " view modes", 'debug', 4);
        }
        else {
          _openfed_log_message($sandbox, "Media plugin already has " . count($existing_modes) . " view modes, no changes needed", 'debug', 4);
        }
      }
      else {
        _openfed_log_message($sandbox, "media_embed filter not enabled, skipping", 'debug', 4);
      }
    }
  }
  else {
    _openfed_log_message($sandbox, "Media plugin not found, skipping", 'debug', 4);
  }
}

/**
 * Post-migration fix: Remove unsupported img tags from ckeditor5_style styles.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Removes any styles that use <img> tags, which are not supported in
 * CKEditor 5 styles. If no styles remain after cleanup (or were empty to begin
 * with), removes the style button from toolbar.
 */
function _openfed_migrate_styles(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  _openfed_log_message($sandbox, "Removing img tags from ckeditor5_style styles...", 'debug', 4);

  // Check if styles configuration exists and is not empty.
  if (!isset($settings['plugins']['ckeditor5_style']['styles'])) {
    _openfed_log_message($sandbox, "No ckeditor5_style styles found, skipping", 'debug', 4);
    return;
  }

  $styles = $settings['plugins']['ckeditor5_style']['styles'];

  // Check if styles array is empty (CKEditor 4 had Styles button but no actual styles configured).
  if (empty($styles)) {
    _openfed_log_message($sandbox, "Styles array was already empty (no styles configured in CKEditor 4)", 'debug', 4);
    _openfed_migrate_styles_remove_empty_config($settings, $sandbox);
    return;
  }

  $modified = FALSE;

  foreach ($styles as $index => $style) {
    if (isset($style['element']) && preg_match('/^<img\b/', $style['element'])) {
      _openfed_log_message($sandbox, "Removing style: " . ($style['label'] ?? 'unlabeled') . " (img tag)", 'debug', 4);
      unset($styles[$index]);
      $modified = TRUE;
    }
  }

  if ($modified) {
    // Reindex array to prevent gaps in numeric keys.
    $styles = array_values($styles);
    $settings['plugins']['ckeditor5_style']['styles'] = $styles;
    _openfed_log_message($sandbox, "img tags removed from styles", 'debug', 4);
  }
  else {
    _openfed_log_message($sandbox, "No img tags found in styles", 'debug', 4);
  }

  // Check if styles array is now empty after removing img tags.
  if (empty($styles)) {
    _openfed_log_message($sandbox, "Styles array is empty after cleanup", 'debug', 4);
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
    _openfed_log_message($sandbox, "Removed 'style' button from toolbar", 'debug', 4);
  }

  // Remove the empty styles configuration.
  unset($settings['plugins']['ckeditor5_style']);
  _openfed_log_message($sandbox, "Removed empty ckeditor5_style plugin configuration", 'debug', 4);
}

/**
 * Post-migration fix: Fix Source Editing plugin.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Removes redundant tags and attributes from source editing
 * allowed_tags.
 */
function _openfed_migrate_source_editing(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
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
      $fully_supported_elements = ['abbr', 'em', 'strong', 'li', 'p', 'br'];

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
        _openfed_log_message($sandbox, "Fixing Source Editing plugin...", 'debug', 4);
        foreach ($removed_tags as $removed) {
          _openfed_log_message($sandbox, "Removed source editing: '" . htmlspecialchars($removed['tag']) . "' (" . htmlspecialchars($removed['reason']) . ")", 'debug', 6);
        }
        foreach ($modified_tags as $modified) {
          _openfed_log_message($sandbox, "Modified source editing: '" . htmlspecialchars($modified['from']) . "' -> '" . htmlspecialchars($modified['to']) . "'", 'debug', 6);
        }

        $settings['plugins']['ckeditor5_sourceEditing']['allowed_tags'] = $updated_tags;
        _openfed_log_message($sandbox, "Source Editing cleaned", 'debug', 4);
      }
      else {
        _openfed_log_message($sandbox, "Source Editing already clean", 'debug', 4);
      }
    }
  }
  else {
    _openfed_log_message($sandbox, "Source Editing plugin not found, skipping", 'debug', 4);
  }
}

/**
 * Post-migration fix: Extract CKEditor templates and create config entities.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Extracts templates from ckeditor_templates.js files and creates
 * config entities.
 */
function _openfed_migrate_templates(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  // Check if Templates button was in CKEditor 4.
  if (!in_array('Templates', $enabled_buttons)) {
    return;
  }

  _openfed_log_message($sandbox, "Templates button was enabled in CKEditor 4", 'debug', 4);

  // Ensure ckeditor5_plugin_pack_templates module is enabled.
  if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_plugin_pack_templates')) {
    \Drupal::service('module_installer')->install(['ckeditor5_plugin_pack_templates']);
    _openfed_log_message($sandbox, "Enabled ckeditor5_plugin_pack_templates module", 'debug', 4);
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
      _openfed_log_message($sandbox, "Templates already extracted, adding format to existing templates", 'debug', 4);
      _openfed_migrate_templates_add_format_to_templates($sandbox['template_ids'], $format, $sandbox);
    }
    else {
      _openfed_log_message($sandbox, "No templates were previously extracted", 'debug', 4);
    }
  }
  else {
    // First format with Templates button enabled - search for and process the file.
    $js_file = _openfed_migrate_templates_find_ckeditor_templates_file('ckeditor_templates.js');

    if (!$js_file) {
      _openfed_log_message($sandbox, "Could not find ckeditor_templates.js file. Skipping template extraction.", 'debug', 5);
      // Mark as processed even though no file found, to prevent repeated searches.
      $sandbox['templates_processed'] = TRUE;
      $sandbox['template_ids'] = [];
      return;
    }

    _openfed_log_message($sandbox, "Found template file: " . $js_file, 'debug', 4);

    // Extract templates from the JS file.
    $template_ids = _openfed_migrate_templates_extract_ckeditor_templates($js_file, $sandbox, $format, $settings);

    // Mark as processed and save template IDs.
    $sandbox['templates_processed'] = TRUE;
    $sandbox['template_ids'] = $template_ids;

    if (count($template_ids) > 0) {
      _openfed_log_message($sandbox, "Created " . count($template_ids) . " template(s)", 'debug', 4);

      // Remove the JS files.
      if (file_exists($js_file)) {
        unlink($js_file);
        _openfed_log_message($sandbox, "Removed: " . $js_file, 'debug', 4);
      }

      $min_js_file = _openfed_migrate_templates_find_ckeditor_templates_file('ckeditor_templates.min.js');
      if ($min_js_file && file_exists($min_js_file)) {
        unlink($min_js_file);
        _openfed_log_message($sandbox, "Removed: " . $min_js_file, 'debug', 4);
      }
    }
    else {
      _openfed_log_message($sandbox, "No templates were extracted from the file", 'debug', 4);
      return;
    }
  }

  // Add insertTemplate button to toolbar if templates exist.
  if (!empty($sandbox['template_ids'])) {
    $toolbar_items = $settings['toolbar']['items'] ?? [];
    if (!in_array('insertTemplate', $toolbar_items)) {
      $toolbar_items[] = 'insertTemplate';
      $settings['toolbar']['items'] = $toolbar_items;
      _openfed_log_message($sandbox, "Added insertTemplate button to toolbar", 'debug', 4);
    }
    else {
      _openfed_log_message($sandbox, "insertTemplate button already in toolbar", 'debug', 4);
    }

    _openfed_log_message($sandbox, "Templates configured for format: " . $format->id(), 'debug', 4);
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
function _openfed_migrate_templates_extract_ckeditor_templates($js_file, array &$sandbox, FilterFormatInterface $format, array &$settings) {
  $content = file_get_contents($js_file);
  if (!$content) {
    _openfed_log_message($sandbox, "Could not read template file", 'error', 4);
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
    _openfed_log_message($sandbox, "No templates array found in JS file", 'warning', 4);
    _openfed_log_message($sandbox, "- The file may have an unexpected format. Please check the template file structure.", '', 4, TRUE);
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

  _openfed_log_message($sandbox, "Split into " . count($template_objects) . " template object(s), parsing...", 'debug', 4);

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
      _openfed_log_message($sandbox, "Template #" . ($idx + 1) . ": Could not extract title", 'warning', 6);
      continue;
    }
    $title = $title_match[1];

    // Extract image
    if (!preg_match('/image:\s*["\']([^"\']+)["\']/', $template_obj, $image_match)) {
      _openfed_log_message($sandbox, "Template #" . ($idx + 1) . " ('$title'): Could not extract image", 'warning', 6);
      continue;
    }
    $image = $image_match[1];

    // Extract description
    if (!preg_match('/description:\s*(?:Drupal\.t\()?\s*["\']([^"\']+)["\']\s*\)?/', $template_obj, $desc_match)) {
      _openfed_log_message($sandbox, "Template #" . ($idx + 1) . " ('$title'): Could not extract description", 'warning', 6);
      continue;
    }
    $description = $desc_match[1];

    // Extract html - everything after 'html:' until the end
    if (!preg_match('/html:\s*([\s\S]+?)(?:\s*\}?\s*$)/', $template_obj, $html_match)) {
      _openfed_log_message($sandbox, "Template #" . ($idx + 1) . " ('$title'): Could not extract html", 'warning', 6);
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
    _openfed_log_message($sandbox, "No templates matched the expected format in JS file", 'warning', 4);
    _openfed_log_message($sandbox, "- Expected format: { title: 'Title' or Drupal.t('Title'), image: 'image.png', description: 'Description' or Drupal.t('Description'), html: '...' }", '', 4, TRUE);
    return [];
  }

  _openfed_log_message($sandbox, "Found " . count($parsed_templates) . " template(s) in JS file, creating config entities...", 'debug', 4);

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
      _openfed_log_message($sandbox, "No SVG icon created for image \"$image\" in template \"$title\"", 'warning', 6);
      _openfed_log_message($sandbox, "- Please manually validate at /admin/config/ckeditor5-templates/content-templates and convert image \"{$images_path}\" to SVG", '', 6, TRUE);
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
    _openfed_log_message($sandbox, "Created template config: $id (\"$title\")", 'debug', 6);

    // Remove image file if it exists.
    if ($image_path && file_exists($image_path)) {
      unlink($image_path);
      _openfed_log_message($sandbox, "Removed image: " . $image_path, 'debug', 6);
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
        _openfed_log_message($sandbox, "Added style: $tag.$class", 'debug', 6);
      }
    }
  }

  // Update settings if new styles were added.
  if (!empty($added_styles)) {
    $settings['plugins']['ckeditor5_style']['styles'] = $existing_styles;
    _openfed_log_message($sandbox, "Added " . count($added_styles) . " missing style(s) from templates", 'debug', 4);
    _openfed_log_message($sandbox, "Manual validation required!", 'debug', 4);
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
    _openfed_log_message($sandbox, "Could not get image info for: " . basename($image_path), 'error', 6);
    return '';
  }

  $width = $image_info[0];
  $height = $image_info[1];
  $mime_type = $image_info['mime'];

  // Read the image file and encode as base64.
  $image_data = file_get_contents($image_path);
  if (!$image_data) {
    _openfed_log_message($sandbox, "Could not read image file: " . basename($image_path), 'error', 6);
    return '';
  }

  $base64 = base64_encode($image_data);

  // Create SVG with embedded image.
  $svg = '<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 ' . $width . ' ' . $height . '">';
  $svg .= '<image width="' . $width . '" height="' . $height . '" xlink:href="data:' . $mime_type . ';base64,' . $base64 . '"/>';
  $svg .= '</svg>';

  _openfed_log_message($sandbox, "Created SVG from image: " . basename($image_path) . " ({$width}x{$height})", 'debug', 6);

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
function _openfed_migrate_templates_add_format_to_templates(array $template_ids, FilterFormatInterface $format, array &$sandbox) {
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
    _openfed_log_message($sandbox, "Added format '$format_id' to $updated_count template(s)", 'debug', 4);
  }
  else {
    _openfed_log_message($sandbox, "Format '$format_id' already in all templates", 'debug', 4);
  }
}

/**
 * Post-migration fix: Activate the ckeditor5_paste_filter.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Enables the ckeditor5_paste_filter module if any paste-related
 * buttons
 * (Cut, Copy, Paste, PasteText, PasteFromWord) were enabled in CKEditor 4.
 */
function _openfed_migrate_copy_paste(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  // Define paste-related buttons to check for.
  $paste_buttons = ['Cut', 'Copy', 'Paste', 'PasteText', 'PasteFromWord'];

  // Find which paste buttons were enabled.
  $found_buttons = array_intersect($paste_buttons, $enabled_buttons);

  if (empty($found_buttons)) {
    _openfed_log_message($sandbox, "No paste-related buttons found in CKEditor 4 toolbar, skipping paste filter migration", 'debug', 4);
    return;
  }

  _openfed_log_message($sandbox, "Found paste-related buttons in CKEditor 4: " . implode(', ', $found_buttons), 'debug', 4);

  // Install the ckeditor5_paste_filter module.
  try {
    if (!\Drupal::moduleHandler()->moduleExists('ckeditor5_paste_filter')) {
      \Drupal::service('module_installer')->install(['ckeditor5_paste_filter']);
      _openfed_log_message($sandbox, "Successfully enabled ckeditor5_paste_filter module", 'debug', 4);
    }

    if (!isset($settings['plugins'])) {
      $settings['plugins'] = [];
    }

    if (!isset($settings['plugins']['ckeditor5_paste_filter_pasteFilter'])) {
      $settings['plugins']['ckeditor5_paste_filter_pasteFilter'] = [];
    }

    // Enable the paste filter plugin.
    $cke5_plugin_manager = \Drupal::service('plugin.manager.ckeditor5.plugin');
    /** @var CKEditor5PluginConfigurableInterface $plugin */
    $plugin = $cke5_plugin_manager->getPlugin('ckeditor5_paste_filter_pasteFilter', $editor);
    $settings['plugins']['ckeditor5_paste_filter_pasteFilter'] = $plugin->getConfiguration();
    $settings['plugins']['ckeditor5_paste_filter_pasteFilter']['enabled'] = TRUE;
  }
  catch (\Exception $e) {
    _openfed_log_message($sandbox, "Failed to enable ckeditor5_paste_filter module: " . $e->getMessage(), 'error', 4) ;
  }
}

/**
 * Post-migration fix: Migrate media embed resize configuration.
 *
 * This runs AFTER computeSmartDefaultSettings() has already migrated the
 * editor. Enable the ckeditor_media_resize module if Media Embed button was
 * enabled in CKEditor 4.
 */
function _openfed_migrate_media_embed_resize(array &$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  $toolbar_items = $settings['toolbar']['items'] ?? [];
  if (!in_array('drupalMedia', $toolbar_items)) {
    _openfed_log_message($sandbox, "No drupalMedia buttons found in CKEditor 5 toolbar, skipping media embed resize migration", 'debug', 4);
    return;
  }

  // Install the ckeditor_media_resize module.
  try {
    if (!\Drupal::moduleHandler()->moduleExists('ckeditor_media_resize')) {
      \Drupal::service('module_installer')->install(['ckeditor_media_resize']);

      // Reload the format to ensure the new filter is available.
      $format = \Drupal::entityTypeManager()->getStorage('filter_format')->load($format->id());
      _openfed_log_message($sandbox, "Successfully enabled ckeditor_media_resize module", 'debug', 4);
    }

    if (!isset($settings['plugins'])) {
      $settings['plugins'] = [];
    }

    if (!isset($settings['plugins']['ckeditor_media_resize_mediaResize'])) {
      $settings['plugins']['ckeditor_media_resize_mediaResize'] = [];
    }

    $filters = $format->get('filters');

    // Enable the media resize plugin.
    $cke5_plugin_manager = \Drupal::service('plugin.manager.ckeditor5.plugin');
    /** @var CKEditor5PluginConfigurableInterface $plugin */
    $plugin = $cke5_plugin_manager->getPlugin('ckeditor_media_resize_mediaResize', $editor);
    $settings['plugins']['ckeditor_media_resize_mediaResize'] = $plugin->getConfiguration();

    /** @var \Drupal\filter\FilterPluginManager $filter_manager */
    $filter_manager = \Drupal::service('plugin.manager.filter');

    // Check if required filters are enabled.
    $filter_html_enabled = isset($filters['filter_html']) && !empty($filters['filter_html']['status']);

    if (!$filter_html_enabled) {
      _openfed_log_message($sandbox, "Warning: filter_resize_media requires 'Limit allowed HTML tags' filter to be active", 'warning', 4);
    }

    // Only proceed with adjusting filter settings if the filter_resize_media filter is not enabled.
    if (!isset($filters['filter_resize_media']) || !$filters['filter_resize_media']['status']) {
      // Calculate the weight: should run before media_embed filter.
      $media_embed_weight = isset($filters['media_embed']['weight']) ? $filters['media_embed']['weight'] : 0;
      // Set weight to be 2 less than media_embed (more negative = earlier execution).
      $resize_filter_weight = $media_embed_weight - 2;

      $filter_resize_media = $filter_manager->createInstance('filter_resize_media');
      $filter_resize_media_config = $filter_resize_media->getConfiguration();
      $filter_resize_media_config['status'] = TRUE;
      $filter_resize_media_config['weight'] = $resize_filter_weight;
      $format->setFilterConfig('filter_resize_media', $filter_resize_media_config);
      $format->save();
      $editor->set('filterFormat', $format);
      _openfed_log_message($sandbox, "Enabled filter_resize_media with weight $resize_filter_weight (media_embed weight: $media_embed_weight)", 'debug', 4);
    }
    else {
      _openfed_log_message($sandbox, "filter_resize_media already enabled", 'debug', 4);
    }
  }
  catch (\Exception $e) {
    _openfed_log_message($sandbox, "Failed to enable ckeditor_media_resize module: " . $e->getMessage(), 'error', 4);
  }
}

/**
 * Refactor ckeditor_stylesheets to ckeditor5-stylesheets in theme.info.yml
 * files.
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
  _openfed_log_message($sandbox, "Refactoring ckeditor_stylesheets in theme.info.yml files...", 'debug');

  $app_root = \Drupal::root();
  $custom_themes_path = $app_root . '/themes/custom';

  // Check if custom themes directory exists.
  if (!is_dir($custom_themes_path)) {
    _openfed_log_message($sandbox, "No custom themes directory found.", 'debug', 2);
    return;
  }

  // Find all .info.yml files in custom themes.
  /** @var \Drupal\Core\File\FileSystemInterface $file_system */
  $file_system = \Drupal::service('file_system');

  $files = $file_system->scanDirectory($custom_themes_path, '/\.info\.yml$/');
  $info_files = array_column($files, 'uri');

  if (empty($info_files)) {
    _openfed_log_message($sandbox, "No .info.yml files found in custom themes.", 'debug', 2);
    return;
  }

  $updated_count = 0;

  foreach ($info_files as $info_file) {
    $content = file_get_contents($info_file);

    // Check if the file contains ckeditor_stylesheets.
    if (!str_contains($content, 'ckeditor_stylesheets:')) {
      continue;
    }

    _openfed_log_message($sandbox, "Found ckeditor_stylesheets in: " . basename(dirname($info_file)), 'debug', 2);

    // Extract CSS paths from ckeditor_stylesheets section.
    $css_paths = _openfed_extract_css_paths_from_info($content);
    $theme_dir = dirname($info_file);

    // Process each CSS path.
    foreach ($css_paths as $css_path) {
      _openfed_log_message($sandbox, "CSS path: $css_path", 'debug', 4);

      // Try to find the SCSS source file by scanning the theme directory.
      $scss_filename = basename(preg_replace('/\.css$/', '.scss', $css_path));
      $actual_scss_path = _openfed_find_file_in_directory($theme_dir, $scss_filename);

      if ($actual_scss_path) {
        _openfed_update_scss_for_ckeditor5($sandbox, $actual_scss_path);

        // Remove compiled CSS file if it exists.
        $full_css_path = $theme_dir . '/' . $css_path;
        if (file_exists($full_css_path)) {
          unlink($full_css_path);
          _openfed_log_message($sandbox, "Removed old CSS file (will be regenerated): $css_path", 'debug', 4);
        }
      }
      else {
        _openfed_log_message($sandbox, "SCSS file not found for: $css_path", 'warning', 4);
      }
    }

    // Replace ckeditor_stylesheets with ckeditor5-stylesheets.
    $updated_content = str_replace('ckeditor_stylesheets:', 'ckeditor5-stylesheets:', $content);
    file_put_contents($info_file, $updated_content);

    _openfed_log_message($sandbox, "Updated ckeditor_stylesheets to ckeditor5-stylesheets in: " . basename($info_file), 'debug', 2);
    $updated_count++;
  }

  if ($updated_count > 0) {
    _openfed_log_message($sandbox, "Successfully updated $updated_count theme.info.yml file(s).", 'debug');
    _openfed_log_message($sandbox, "Manual validation required for ckeditor stylesheet!", 'warning');
    _openfed_log_message($sandbox, "- Please manually review heading styles (h1-h6) in updated SCSS files.", '', 2, TRUE);
    _openfed_log_message($sandbox, "- After validation, recompile your theme's CSS to apply changes.", '', 2, TRUE);
  }
  else {
    _openfed_log_message($sandbox, "No ckeditor_stylesheets definitions found in theme.info.yml files.", 'debug');
  }
}

/**
 * Extract CSS paths from ckeditor_stylesheets section in theme.info.yml
 * content.
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

  _openfed_log_message($sandbox, "CKEditor ckeditor_stylesheets", 'debug', 4);
  _openfed_log_message($sandbox, "- Original styles updated for CKEditor 5", 'debug', 6);
  _openfed_log_message($sandbox, "- All content wrapped in .ck-content", 'debug', 6);
  _openfed_log_message($sandbox, "- Removed: Lines containing .cke_panel_listItem (CKEditor 4 specific)", 'debug', 6);
  _openfed_log_message($sandbox, "- Source: https://www.drupal.org/node/3259165", 'debug', 6);

  file_put_contents($scss_file_path, $updated_content);
  _openfed_log_message($sandbox, "Updated SCSS with .ck-content: " . basename($scss_file_path), 'debug', 4);
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
