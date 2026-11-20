<?php

/**
 * @file
 * Configuration helpers for Media Entity File Replace 1.x.
 */

use Drupal\Component\Utility\SortArray;
use Drupal\file\Plugin\Field\FieldType\FileItem;
use Drupal\media\Plugin\media\Source\File;

/**
 * Enables replacement for supported media sources on default form displays.
 *
 * Other saved form displays are left unchanged and reported for manual review.
 *
 * @return string[]
 *   Placement results per form display and reasons for skipped media sources.
 */
function _openfed_configure_media_file_replace(): array {
  $manager = \Drupal::entityTypeManager();
  $field_manager = \Drupal::service('entity_field.manager');
  // The newly installed module adds an extra field to existing bundles.
  $field_manager->clearCachedFieldDefinitions();
  $display_storage = $manager->getStorage('entity_form_display');
  $messages = [];

  foreach ($manager->getStorage('media_type')->loadMultiple() as $media_type) {
    $messages[] = sprintf("\nMedia type: %s", $media_type->id());
    $source = $media_type->getSource();
    $source_field = $source->getSourceFieldDefinition($media_type);
    $source_name = $source_field ? $source_field->getName() : NULL;
    $supported = $source instanceof File && $source_field
      && is_a($source_field->getItemDefinition()->getClass(), FileItem::class, TRUE);
    // Contrib reads only the first item and its non-overwrite branch replaces
    // the entire field value. Do not enable that on multi-value source fields.
    $single_value = $source_field && $source_field->getFieldStorageDefinition()->getCardinality() === 1;

    if (!$supported) {
      if ($source instanceof File) {
        $message = sprintf('Skipped media.%s: the File-based source has a missing or incompatible source field.', $media_type->id());
        $messages[] = '  - ' . $message;
        \Drupal::logger('openfed')->warning($message);
      }
      else {
        $messages[] = sprintf('  - Skipped: source plugin "%s" is not File-based; replace_file is not supported.', $source->getPluginId());
      }
      continue;
    }
    if (!$single_value) {
      $message = sprintf('Skipped media.%s.%s: multi-value source fields are unsafe with Media Entity File Replace 1.3; only the first item is read and non-overwrite replacement discards the other items.', $media_type->id(), $source_name);
      $messages[] = '  - ' . $message;
      \Drupal::logger('openfed')->warning($message);
      continue;
    }

    $displays = $display_storage->loadByProperties([
      'targetEntityType' => 'media',
      'bundle' => $media_type->id(),
    ]);
    $has_default = FALSE;
    foreach ($displays as $display) {
      if ($display->getMode() !== 'default') {
        $messages[] = sprintf('  - %s: left unchanged; manual review required.', $display->id());
        continue;
      }
      $has_default = TRUE;
      $component = $display->getComponent($source_name);
      $replacement = $display->getComponent('replace_file');
      if ($component === NULL || ($component['region'] ?? 'content') === 'hidden') {
        if ($replacement !== NULL) {
          $display->removeComponent('replace_file')->save();
          $messages[] = sprintf('  - %s: disabled replace_file because source field "%s" is hidden.', $display->id(), $source_name);
        }
        else {
          $messages[] = sprintf('  - %s: skipped because source field "%s" is hidden; replace_file was not enabled.', $display->id(), $source_name);
        }
        continue;
      }

      $before = $display->toArray();
      $weight = ($component['weight'] ?? 0) + 1;
      $region = $component['region'] ?? 'content';
      $display->setComponent('replace_file', [
          'weight' => $weight,
          'region' => $region,
        ] + ($replacement ?? []));

      // Make room immediately after the source, preserving other field order.
      $components = $display->getComponents();
      unset($components['replace_file']);
      uasort($components, [SortArray::class, 'sortByWeightElement']);
      $after_source = FALSE;
      foreach ($components as $name => $options) {
        if ($name === $source_name) {
          $after_source = TRUE;
          continue;
        }
        if (!$after_source || ($options['region'] ?? 'content') !== $region) {
          continue;
        }
        $weight = max($weight + 1, $options['weight'] ?? 0);
        if ($weight !== ($options['weight'] ?? 0)) {
          $display->setComponent($name, ['weight' => $weight] + $options);
        }
      }
      if ($display->toArray() !== $before) {
        $display->save();
        $messages[] = sprintf('  - %s: positioned replace_file directly below source field "%s".', $display->id(), $source_name);
      }
      else {
        $messages[] = sprintf('  - %s: already configured; replace_file is directly below source field "%s".', $display->id(), $source_name);
      }
    }
    if (!$has_default) {
      $message = sprintf('Skipped media.%s: no saved default form display exists; no widgets were created.', $media_type->id());
      $messages[] = '  - ' . $message;
      \Drupal::logger('openfed')->warning($message);
    }
  }

  if ($messages) {
    array_unshift($messages,
      'Media file replacement: only the default form mode is configured automatically.',
      'Other form displays are left unchanged. Review their Manage form display settings and enable or position "Replace file" if appropriate.'
    );
  }

  return $messages ?: ['No media types found; no file replacement configuration was needed.'];
}
