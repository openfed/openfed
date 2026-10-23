<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config;

/**
 * Request-scoped collector for config names accessed during page rendering.
 */
final class ConfigNameCollector {

  /**
   * Config names collected during this request, keyed by name for dedup.
   *
   * @var array<string, true>
   */
  private array $configNames = [];

  /**
   * Records a config name accessed during the current request.
   */
  public function addConfigName(string $name): void {
    $this->configNames[$name] = TRUE;
  }

  /**
   * Returns all unique config names collected during the current request.
   *
   * @return string[]
   *   Config names.
   */
  public function getCollectedConfigNames(): array {
    return array_keys($this->configNames);
  }

}
