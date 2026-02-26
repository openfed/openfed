<?php

/**
 * @file
 * Helper functions for openfed_update_cke - CKEditor 4 to 5 migration.
 */

use Drupal\ckeditor5\HTMLRestrictions;
use Drupal\ckeditor5\Plugin\Editor\CKEditor5;
use Drupal\editor\EditorInterface;
use Drupal\filter\Entity\FilterFormat;
use Drupal\filter\FilterFormatInterface;

/**
 * Initialize the CKEditor 5 migration batch process.
 *
 * @param array $sandbox
 *   The sandbox array for batch processing.
 */
function _openfed_update_cke_initialize(array &$sandbox) {
  $sandbox['messages'] = [];
  $sandbox['errors'] = 0;
  $sandbox['current'] = 0;

  try {
    // Enable CKEditor 5 module if not already enabled.
    $module_handler = \Drupal::moduleHandler();
    if (!$module_handler->moduleExists('ckeditor5')) {
      \Drupal::service('module_installer')->install(['ckeditor5']);
      _openfed_log_message($sandbox, 'Enabled CKEditor 5 module.', 'debug');
    }

    // Enable CKEditor 5 Find and Replace plugin if CKEditor Find module is present.
    if ($module_handler->moduleExists('ckeditor_find')) {
      \Drupal::service('module_installer')->install(['ckeditor5_plugin_pack_find_and_replace']);
      _openfed_log_message($sandbox, 'Enabled CKEditor 5 Find and Replace plugin module.', 'debug');
    }

    // Get all CKEditor 4 editors.
    $editor_ids = _openfed_update_cke_get_ckeditor4_editors();

    $sandbox['editor_ids'] = $editor_ids;
    $sandbox['total'] = count($editor_ids);

    if ($sandbox['total'] === 0) {
      _openfed_log_message($sandbox, 'No CKEditor 4 formats found to migrate.', 'debug');
      $sandbox['#finished'] = 1;
      return;
    }

    _openfed_log_message($sandbox, "Found {$sandbox['total']} format(s) to migrate.", 'debug');

    // Mark that stylesheets haven't been refactored yet.
    $sandbox['stylesheets_refactored'] = FALSE;
  }
  catch (\Exception $e) {
    _openfed_log_message($sandbox, 'Error during initialization: ' . $e->getMessage(), 'error');
    $sandbox['#finished'] = 1;
  }
}

/**
 * Get all CKEditor 4 editor IDs.
 *
 * @return array
 *   Array of editor IDs using CKEditor 4.
 */
function _openfed_update_cke_get_ckeditor4_editors() {
  $entity_type_manager = \Drupal::entityTypeManager();
  $editor_storage = $entity_type_manager->getStorage('editor');
  $editors = $editor_storage->loadMultiple();

  $ckeditor4_editors = [];
  foreach ($editors as $editor_id => $editor) {
    if ($editor->getEditor() === 'ckeditor') {
      $ckeditor4_editors[] = $editor_id;
    }
  }

  return $ckeditor4_editors;
}

/**
 * Process a single editor migration.
 *
 * @param array $sandbox
 *   The sandbox array for batch processing.
 */
function _openfed_update_cke_process_editor(array &$sandbox) {
  $editor_id = $sandbox['editor_ids'][$sandbox['current']];

  try {
    $entity_type_manager = \Drupal::entityTypeManager();
    $editor_storage = $entity_type_manager->getStorage('editor');
    /** @var EditorInterface $editor */
    $editor = $editor_storage->load($editor_id);

    if (!$editor) {
      _openfed_log_message($sandbox, "Editor {$editor_id} not found. Skipping.", 'warning');
      _openfed_update_cke_update_progress($sandbox);
      return;
    }

    _openfed_log_message($sandbox, "Migrating format: {$editor_id}", '', 0, TRUE);

    // Get the text format.
    $text_format = FilterFormat::load($editor->id());
    if (!$text_format) {
      throw new \RuntimeException("Text format not found for {$editor_id}");
    }

    // Get enabled buttons from original settings.
    $enabled_buttons = _openfed_update_cke_get_enabled_buttons($editor);

    // Perform base migration using Drupal core's service.
    $smart_defaults = \Drupal::service('ckeditor5.smart_default_settings');
    $result = $smart_defaults->computeSmartDefaultSettings($editor, $text_format);
    /** @var \Drupal\editor\Entity\Editor $updated_editor */
    $updated_editor = $result[0];
    $migration_messages = $result[1];

    // Log migration messages.
    _openfed_update_cke_log_messages($sandbox, $migration_messages);

    // Apply custom Openfed migrations.
    $new_settings = $updated_editor->getSettings();
    _openfed_update_cke_apply_custom_migrations($sandbox, $updated_editor, $text_format, $new_settings, $enabled_buttons);

    // Post-process settings to avoid duplicate toolbar items.
    _openfed_update_cke_dedupe_toolbar_items($sandbox, $new_settings);

    // Save the updated editor.
    $updated_editor->setSettings($new_settings);
    $updated_editor->save();

    // Update filter_html settings based on CKEditor 5 configuration.
    $has_html_restrictions = $updated_editor->getFilterFormat()->filters('filter_html')->status;
    if ($has_html_restrictions) {
      $ckeditor5PluginManager = \Drupal::service('plugin.manager.ckeditor5.plugin');
      $enabled_plugins = $ckeditor5PluginManager->getEnabledDefinitions($updated_editor);
      // Compute elements provided by the current CKEditor 5 settings.
      $restrictions = new HTMLRestrictions($ckeditor5PluginManager->getProvidedElements(array_keys($enabled_plugins), $updated_editor));

      // Compute eventual filter_html setting. Eventual as in: this is the list
      // of eventually allowed HTML tags.
      // @see \Drupal\filter\FilterFormatFormBase::submitForm()
      // @see ckeditor5_form_filter_format_form_alter()
      $filter_html_config = $updated_editor->getFilterFormat()->filters('filter_html')->getConfiguration();
      $filter_html_config['settings']['allowed_html'] = $restrictions->toFilterHtmlAllowedTagsString();
      // Ensure that the result of ::computeSmartDefaultSettings() always complies
      // with the config schema.
      // TRICKY: because we're validating using `editor.editor.*` as the config
      // name, TextEditorObjectDependentValidatorTrait will load the stored filter
      // format. That has not yet been updated at this point, so in order for
      // validation to pass, it must first be saved.
      // @see \Drupal\ckeditor5\Plugin\Validation\Constraint\TextEditorObjectDependentValidatorTrait::createTextEditorObjectFromContext()
      // @todo Remove this work-around in https://www.drupal.org/project/drupal/issues/3231354
      $updated_editor->getFilterFormat()->setFilterConfig('filter_html', $filter_html_config)->save();
    }

    // Reload the updated editor to ensure we have the latest data for validation.
    $updated_text_format = $updated_editor->getFilterFormat();

    // Check for extra validation violations after save.
    $violations = CKEditor5::validatePair($updated_editor, $updated_text_format, FALSE);
    if ($violations->count() > 0) {
      _openfed_log_message($sandbox, "Text format validation errors found:", 'warning');
      foreach ($violations as $violation) {
        _openfed_log_message($sandbox, "- " . $violation->getMessage(), '', 2, TRUE);
      }
    }

    _openfed_log_message($sandbox, "Successfully migrated format: {$editor_id}", 'success');
  }
  catch (\Exception $e) {
    _openfed_log_message($sandbox, "Error migrating format {$editor_id}: " . $e->getMessage(), 'error');
    \Drupal::logger('openfed')->error('CKEditor migration error for @editor_id: @message', [
      '@editor_id' => $editor_id,
      '@message' => $e->getMessage(),
    ]);
  }

  _openfed_update_cke_update_progress($sandbox);
}

/**
 * Get enabled buttons from CKEditor 4 toolbar configuration.
 *
 * @param \Drupal\editor\EditorInterface $editor
 *   The editor entity.
 *
 * @return array
 *   Array of enabled button names.
 */
function _openfed_update_cke_get_enabled_buttons(EditorInterface $editor) {
  $original_settings = $editor->getSettings();
  $original_toolbar = $original_settings['toolbar']['rows'] ?? [];

  $enabled_buttons = [];
  foreach ($original_toolbar as $row) {
    foreach ($row as $group) {
      if (isset($group['items']) && is_array($group['items'])) {
        $enabled_buttons = array_merge($enabled_buttons, $group['items']);
      }
    }
  }

  return $enabled_buttons;
}

/**
 * Log migration messages to sandbox.
 *
 * @param array $sandbox
 *   The sandbox array.
 * @param array $migration_messages
 *   Messages from the core migration service.
 */
function _openfed_update_cke_log_messages(array &$sandbox, array $migration_messages) {
  foreach ($migration_messages as $type => $type_messages) {
    foreach ($type_messages as $message) {
      $clean_message = strip_tags($message);
      _openfed_log_message($sandbox, "- " . $clean_message, "debug", 2);
    }
  }
}

/**
 * Apply custom Openfed migrations.
 *
 * @param array $sandbox
 *   The sandbox array.
 * @param \Drupal\editor\EditorInterface $editor
 *   The editor entity.
 * @param \Drupal\filter\FilterFormatInterface $format
 *   The text format.
 * @param array $settings
 *   The editor settings (passed by reference).
 * @param array $enabled_buttons
 *   Array of enabled button names from CKEditor 4.
 */
function _openfed_update_cke_apply_custom_migrations(&$sandbox, EditorInterface $editor, FilterFormatInterface $format, array &$settings, array $enabled_buttons) {
  _openfed_log_message($sandbox, "Starting custom migrations for format: {$format->id()}", 'debug');

  # Load CKEditor migration helper functions.
  include_once __DIR__ . '/openfed.ckeditor5.migration.inc';

  $migrations = [
    '_openfed_migrate_anchor_link',
    '_openfed_migrate_codemirror',
    '_openfed_migrate_entity_embed',
    '_openfed_migrate_heading',
    '_openfed_migrate_media',
    '_openfed_migrate_styles',
    '_openfed_migrate_source_editing',
    '_openfed_migrate_templates',
    '_openfed_migrate_copy_paste',
    '_openfed_migrate_media_embed_resize',
  ];

  _openfed_log_message($sandbox, "Checking " . count($migrations) . " migration functions", 'debug');

  foreach ($migrations as $migration_function) {
    if (function_exists($migration_function)) {
      _openfed_log_message($sandbox, "Executing: {$migration_function}", 'debug', 2);
      try {
        $migration_function($sandbox, $editor, $format, $settings, $enabled_buttons);
        _openfed_log_message($sandbox, "✓ {$migration_function} completed", 'debug', 2);
      }
      catch (\Exception $e) {
        _openfed_log_message($sandbox, "ERROR in {$migration_function}: " . $e->getMessage(), 'error');
      }
    }
    else {
      _openfed_log_message($sandbox, "Function {$migration_function} does not exist", 'warning');
    }
  }

  _openfed_log_message($sandbox, "Custom migrations completed for format: {$format->id()}", 'debug');
}

/**
 * Remove duplicate items from the CKEditor5 toolbar while preserving order.
 *
 * Duplicates can creep in when CKEditor4 toolbars contain repeated buttons
 * across groups (e.g. "Source" appearing multiple times). Core migration and
 * subsequent custom migrations can both add buttons too.
 *
 * @param array $sandbox
 *   The batch sandbox.
 * @param array $settings
 *   The editor settings array (passed by reference).
 */
function _openfed_update_cke_dedupe_toolbar_items(array &$sandbox, array &$settings): void {
  if (empty($settings['toolbar']['items']) || !is_array($settings['toolbar']['items'])) {
    return;
  }

  $original = $settings['toolbar']['items'];
  $seen = [];
  $deduped = [];
  $removed_counts = [];

  foreach ($original as $item) {
    // CKEditor5 toolbars can contain separators or group markers.
    // Keep them, but avoid collapsing multiple separators into one.
    if ($item === '|' || $item === '-') {
      $last = end($deduped);
      if ($last === $item) {
        continue;
      }
      $deduped[] = $item;
      continue;
    }

    // For button names: keep the first occurrence, drop subsequent ones.
    $key = is_string($item) ? $item : json_encode($item);
    if (isset($seen[$key])) {
      $label = is_string($item) ? $item : 'non-string-item';
      $removed_counts[$label] = ($removed_counts[$label] ?? 0) + 1;
      continue;
    }
    $seen[$key] = TRUE;
    $deduped[] = $item;
  }

  // Trim leading/trailing separators that might have become orphaned.
  while (!empty($deduped) && (reset($deduped) === '|' || reset($deduped) === '-')) {
    array_shift($deduped);
  }
  while (!empty($deduped) && (end($deduped) === '|' || end($deduped) === '-')) {
    array_pop($deduped);
  }

  if ($deduped !== $original) {
    $settings['toolbar']['items'] = array_values($deduped);

    // Build a readable message of removed duplicates.
    // Example: Source (x2), blockQuote (x1)
    $details = '';
    if (!empty($removed_counts)) {
      ksort($removed_counts);
      $parts = [];
      foreach ($removed_counts as $label => $count) {
        $parts[] = "{$label} (x{$count})";
      }
      $details = ' Removed duplicates: ' . implode(', ', $parts) . '.';
    }

    _openfed_log_message($sandbox, '  Cleaned up toolbar: removed duplicate buttons.' . $details, 'debug');
  }
}

/**
 * Update batch progress.
 *
 * @param array $sandbox
 *   The sandbox array.
 */
function _openfed_update_cke_update_progress(array &$sandbox) {
  $sandbox['current']++;
  $sandbox['#finished'] = $sandbox['current'] / $sandbox['total'];
}

/**
 * Finalize the CKEditor 5 migration.
 *
 * @param array $sandbox
 *   The sandbox array.
 *
 * @return string
 *   Final migration summary message.
 */
function _openfed_update_cke_finalize(array &$sandbox) {
  try {
    // Check if any CKEditor 4 editors remain.
    $remaining_editors = _openfed_update_cke_get_ckeditor4_editors();

    if (empty($remaining_editors)) {
      _openfed_update_cke_cleanup_modules($sandbox);
    }

    // Enable Openfed CKEditor module if not already enabled.
    $module_handler = \Drupal::moduleHandler();
    if (!$module_handler->moduleExists('openfed_ckeditor')) {
      \Drupal::service('module_installer')->install(['openfed_ckeditor']);
      _openfed_log_message($sandbox, 'Enabled Openfed CKEditor module.', 'debug');
    }

    // Add summary.
    _openfed_update_cke_build_summary($sandbox);
  }
  catch (\Exception $e) {
    _openfed_log_message($sandbox, 'Error during finalization: ' . $e->getMessage(), 'error');
  }

  return "Summary CKEditor4 > CKEditor5\n" . implode("\n", $sandbox['messages']);
}

/**
 * Cleanup deprecated CKEditor 4 modules.
 *
 * @param array $sandbox
 *   The sandbox array.
 */
function _openfed_update_cke_cleanup_modules(array &$sandbox) {
  $modules_to_uninstall = [
    'ckeditor_templates' => 'CKEditor templates',
    'ckeditor4_codemirror' => 'CKEditor4 codemirror',
    'anchor_link' => 'Anchor link',
    'fakeobjects' => 'Fake Objects (dependency for anchor_link)',
    'ckeditor_config' => 'CKEditor custom config',
    'ckeditor_uploadimage' => 'CKEditor upload image',
    'ckeditor' => 'CKEditor 4',
  ];
  $module_handler = \Drupal::moduleHandler();
  $module_installer = \Drupal::service('module_installer');

  foreach ($modules_to_uninstall as $module => $label) {
    // Only attempt to uninstall if the module is actually installed.
    if (!$module_handler->moduleExists($module)) {
      continue;
    }

    try {
      $module_installer->uninstall([$module]);
      _openfed_log_message($sandbox, "Disabled {$label} module. Deprecated and will be removed in future Openfed versions.", 'debug');
    }
    catch (\Exception $e) {
      _openfed_log_message($sandbox, "Could not uninstall {$label} module: " . $e->getMessage(), 'warning');
    }
  }
}

/**
 * Build migration summary message.
 *
 * @param array $sandbox
 *   The sandbox array.
 *
 * @return string
 *   Summary message.
 */
function _openfed_update_cke_build_summary(array &$sandbox) {
  $total = $sandbox['total'];
  $errors = $sandbox['errors'];
  $successful = $total - $errors;

  if ($errors > 0) {
    _openfed_log_message($sandbox, "Migration completed: {$successful}/{$total} format(s) migrated successfully, {$errors} error(s).", 'error');
  }
  else {
    _openfed_log_message($sandbox, "Migration completed successfully! All {$total} format(s) migrated.", 'success');
  }

}

/**
 * Don't allow list styling in media embed previews, as it can cause unwanted
 * spacing and bullets in the editor.
 *
 * @return string|void
 */
function _openfed_update_cke_media_embed_list_item() {
  $app_root = \Drupal::root();
  $custom_themes_path = $app_root . '/themes/custom';

  // Check if custom themes directory exists.
  if (!is_dir($custom_themes_path)) {
    return;
  }

  // Find all .info.yml files in custom themes.
  /** @var \Drupal\Core\File\FileSystemInterface $file_system */
  $file_system = \Drupal::service('file_system');

  $files = $file_system->scanDirectory($custom_themes_path, '/\.info\.yml$/');
  $info_files = array_column($files, 'uri');

  if (empty($info_files)) {
    return;
  }

  # Load CKEditor migration helper functions.
  include_once __DIR__ . '/openfed.ckeditor5.migration.inc';

  $updated_count = 0;
  foreach ($info_files as $info_file) {
    $content = file_get_contents($info_file);

    // Check if the file contains ckeditor_stylesheets.
    if (!str_contains($content, 'ckeditor5-stylesheets:')) {
      continue;
    }

    // Extract CSS paths from ckeditor_stylesheets section.
    $css_paths = _openfed_extract_css_paths_from_info($content, '/^ckeditor5-stylesheets:/');
    $theme_dir = dirname($info_file);

    // Process each CSS path.
    foreach ($css_paths as $css_path) {
      // Try to find the SCSS source file by scanning the theme directory.
      $scss_filename = basename(preg_replace('/\.css$/', '.scss', $css_path));
      $actual_scss_path = _openfed_find_file_in_directory($theme_dir, $scss_filename);

      if ($actual_scss_path) {
        $content = file_get_contents($actual_scss_path);

        // Check if the content already contains this rule to avoid duplicates.
        if (str_contains($content, '[data-drupal-media-preview] ul')) {
          continue;
        }

        // Prepare the new CSS content to insert within .ck-content.
        $new_css_content = <<<'SCSS'
  /* Remove list styling ONLY for media preview wrapper */
  [data-drupal-media-preview] ul {
    margin: 0;
    padding: 0;
    list-style: none;
  }

  [data-drupal-media-preview] li {
    margin: 0;
    padding: 0;
  }

SCSS;

        // Find the .ck-content section and insert before its closing brace.
        if (preg_match('/\.ck-content\s*\{/s', $content, $matches, PREG_OFFSET_CAPTURE)) {
          $opening_brace_pos = $matches[0][1] + strlen($matches[0][0]);

          // Count braces to find the matching closing brace for .ck-content.
          $brace_count = 1;
          $pos = $opening_brace_pos;
          $closing_brace_pos = FALSE;

          while ($pos < strlen($content) && $brace_count > 0) {
            $char = $content[$pos];
            if ($char === '{') {
              $brace_count++;
            }
            elseif ($char === '}') {
              $brace_count--;
              if ($brace_count === 0) {
                $closing_brace_pos = $pos;
                break;
              }
            }
            $pos++;
          }

          if ($closing_brace_pos !== FALSE) {
            // Insert the new content before the closing brace.
            $updated_content = substr($content, 0, $closing_brace_pos) . $new_css_content . substr($content, $closing_brace_pos);
            file_put_contents($actual_scss_path, $updated_content);

            // Remove compiled CSS file if it exists.
            $full_css_path = $theme_dir . '/' . $css_path;
            if (file_exists($full_css_path)) {
              unlink($full_css_path);
            }
          }
        }
      }
    }
    $updated_count++;
  }

  return 'Updated CKE5 media embed list item styles in ' . $updated_count . ' theme(s).';
}
