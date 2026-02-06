<?php

/**
 * @file
 * General helper functions for Openfed update hooks.
 */

/**
 * Log a message to the sandbox with severity level.
 *
 * This function categorizes messages as 'debug', 'success', 'warning' or 'error' and
 * only displays them based on the 'openfed_update_show_debug' setting.
 * Success messages, warnings and errors are always shown; debug messages are only shown when
 * the setting is TRUE.
 *
 * @param array $sandbox
 *   The sandbox array.
 * @param string $message
 *   The message to log.
 * @param string $severity
 *   The severity level: 'debug', 'success', 'warning' or 'error'.
 * @param int $indent
 *   The number of spaces to indent the message (default: 0).
 * @param bool $force
 *   The flag to force logging the message regardless of debug settings.
 *
 */
function _openfed_log_message(array &$sandbox, string $message, string $severity = 'debug', int $indent = 0, bool $force = false): void {
  // Get the debug setting from settings.php
  $settings = \Drupal::service('settings');
  $show_debug = $settings->get('openfed_update_show_debug', FALSE);

  // Always show success, warnings and errors, only show debug if enabled
  if ($severity === 'success' || $severity === 'warning' || $severity === 'error' || $show_debug || $force) {
    // Detect existing indentation in the message
    preg_match('/^(\s*)(.*)$/', $message, $matches);
    $existing_indent = $matches[1];
    $message_content = $matches[2];

    // Prefix the message with an indicator
    $prefix = match ($severity) {
      'error' => '❌ ERROR: ',
      'warning' => '⚠️  WARNING: ',
      'success' => '✅ ',
      'debug' => '🔍 ',
      '' => '',
    };

    // Apply additional indentation
    $additional_indent = str_repeat(' ', $indent);
    $sandbox['messages'][] = $additional_indent . $existing_indent . $prefix . $message_content;
  }

  // Track errors separately for summary
  if ($severity === 'error' && !isset($sandbox['errors'])) {
    $sandbox['errors'] = 0;
  }
  if ($severity === 'error') {
    $sandbox['errors']++;
  }
}
