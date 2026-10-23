<?php

declare(strict_types=1);

namespace Drupal\translation_collector;

/**
 * Interface for request-scoped translation string collectors.
 *
 * Submodules implement this to provide collected strings at terminate time.
 * Services implementing this interface should be tagged with
 * 'translation_collector.collector'.
 */
interface CollectorInterface {

  /**
   * Whether collection is currently active for this request.
   *
   * @return bool
   *   TRUE if collecting, FALSE otherwise.
   */
  public function isActive(): bool;

  /**
   * Returns all collected translation items for persistence.
   *
   * Each item is an associative array with keys:
   *   - source: (string) The source string.
   *   - langcode: (string) The target language code.
   *   - context: (string) Translation context.
   *   - is_translated: (bool) Whether a translation exists.
   *   - location: (string) Optional location info.
   *   - string_type: (string) Either 'interface' or 'config'.
   *
   * @return array
   *   Array of collected translation items.
   */
  public function getCollectedItems(): array;

}
