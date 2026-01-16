<?php

/**
 * @file
 * Helper functions for openfed_update_cke - CKEditor 4 to 5 migration.
 */

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
      $sandbox['messages'][] = 'Enabled CKEditor 5 module.';
    }

    // Get all CKEditor 4 editors.
    $editor_ids = _openfed_update_cke_get_ckeditor4_editors();

    $sandbox['editor_ids'] = $editor_ids;
    $sandbox['total'] = count($editor_ids);

    if ($sandbox['total'] === 0) {
      $sandbox['messages'][] = 'No CKEditor 4 formats found to migrate.';
      $sandbox['#finished'] = 1;
      return;
    }

    $sandbox['messages'][] = "Found {$sandbox['total']} format(s) to migrate.";

    // Mark that stylesheets haven't been refactored yet.
    $sandbox['stylesheets_refactored'] = FALSE;
  }
  catch (\Exception $e) {
    $sandbox['messages'][] = 'Error during initialization: ' . $e->getMessage();
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
    $editor = $editor_storage->load($editor_id);

    if (!$editor) {
      $sandbox['messages'][] = "⚠️  Warning: Editor {$editor_id} not found. Skipping.";
      _openfed_update_cke_update_progress($sandbox);
      return;
    }

    $sandbox['messages'][] = "Migrating format: {$editor_id}";

    // Get the text format.
    $text_format = $editor->getFilterFormat();
    if (!$text_format) {
      throw new \RuntimeException("Text format not found for {$editor_id}");
    }

    // Get enabled buttons from original settings.
    $enabled_buttons = _openfed_update_cke_get_enabled_buttons($editor);

    // Perform base migration using Drupal core's service.
    $smart_defaults = \Drupal::service('ckeditor5.smart_default_settings');
    $result = $smart_defaults->computeSmartDefaultSettings($editor, $text_format);
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

    $sandbox['messages'][] = "Successfully migrated format: {$editor_id}";
  }
  catch (\Exception $e) {
    $sandbox['messages'][] = "Error migrating format {$editor_id}: " . $e->getMessage();
    $sandbox['errors']++;
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
function _openfed_update_cke_get_enabled_buttons($editor) {
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
      $sandbox['messages'][] = "  [{$type}] {$clean_message}";
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
function _openfed_update_cke_apply_custom_migrations(&$sandbox, $editor, $format, array &$settings, array $enabled_buttons) {
  $sandbox['messages'][] = "Starting custom migrations for format: {$format->id()}";

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
  ];

  $sandbox['messages'][] = "Checking " . count($migrations) . " migration functions";

  foreach ($migrations as $migration_function) {
    if (function_exists($migration_function)) {
      $sandbox['messages'][] = "  Executing: {$migration_function}";
      try {
        $migration_function($sandbox, $editor, $format, $settings, $enabled_buttons);
        $sandbox['messages'][] = "  ✓ {$migration_function} completed";
      }
      catch (\Exception $e) {
        $sandbox['messages'][] = "  ERROR in {$migration_function}: " . $e->getMessage();
        $sandbox['errors']++;
      }
    }
    else {
      $sandbox['messages'][] = "  ⚠️  WARNING: Function {$migration_function} does not exist";
    }
  }

  $sandbox['messages'][] = "Custom migrations completed for format: {$format->id()}";
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

    $sandbox['messages'][] = '  Cleaned up toolbar: removed duplicate buttons.' . $details;
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
      $sandbox['messages'][] = 'Enabled Openfed CKEditor module.';
    }

    // Clear all caches.
    drupal_flush_all_caches();
    $sandbox['messages'][] = 'Cleared all caches.';

    // Add summary.
    $summary = _openfed_update_cke_build_summary($sandbox);
    $sandbox['messages'][] = $summary;
  }
  catch (\Exception $e) {
    $sandbox['messages'][] = 'Error during finalization: ' . $e->getMessage();
    $sandbox['errors']++;
  }

  return implode("\n", $sandbox['messages']);
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
      $sandbox['messages'][] = "Disabled {$label} module. Deprecated and will be removed in future Openfed versions.";
    }
    catch (\Exception $e) {
      $sandbox['messages'][] = "⚠️  Warning: Could not uninstall {$label} module: " . $e->getMessage();
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
    return "\nMigration completed: {$successful}/{$total} format(s) migrated successfully, {$errors} error(s).";
  }

  return "\nMigration completed successfully! All {$total} format(s) migrated.";
}

