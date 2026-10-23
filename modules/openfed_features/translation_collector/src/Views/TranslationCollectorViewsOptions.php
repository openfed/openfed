<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Views;

/**
 * Provides dynamic filter options for translation collector Views handlers.
 */
final class TranslationCollectorViewsOptions {

  /**
   * Returns distinct values for select-based Views filters.
   */
  public static function getDistinctOptions(string $column): array {
    $allowed_columns = ['langcode', 'string_type'];
    if (!in_array($column, $allowed_columns, TRUE)) {
      return [];
    }

    $query = \Drupal::database()
      ->select('translation_collector_strings', 't')
      ->fields('t', [$column])
      ->distinct()
      ->orderBy($column, 'ASC');

    $values = $query->execute()->fetchCol();
    $options = [];
    foreach ($values as $value) {
      $value = (string) $value;
      if ($value !== '') {
        $options[$value] = $value;
      }
    }

    return $options;
  }

}
