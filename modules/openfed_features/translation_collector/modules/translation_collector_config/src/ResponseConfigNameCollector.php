<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config;

/**
 * Request-scoped collector for config names derived from response cache tags.
 */
final class ResponseConfigNameCollector {

  /**
   * Config names collected during this request, keyed by name for dedup.
   *
   * @var array<string, true>
   */
  private array $configNames = [];

  /**
   * Records a config name extracted from a response cache tag.
   */
  public function addConfigName(string $name): void {
    $this->configNames[$name] = TRUE;
  }

  /**
   * Returns all unique config names collected for this request.
   *
   * @return string[]
   *   Config names.
   */
  public function getCollectedConfigNames(): array {
    return array_keys($this->configNames);
  }

}
