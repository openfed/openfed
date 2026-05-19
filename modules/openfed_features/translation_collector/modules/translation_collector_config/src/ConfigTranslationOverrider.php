<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config;

use Drupal\Core\Cache\CacheableMetadata;
use Drupal\Core\Config\ConfigFactoryOverrideInterface;
use Drupal\Core\Config\StorageInterface;
use Drupal\translation_collector\TranslationCollectorActivationChecker;

/**
 * Config factory override that collects accessed config names.
 *
 * This override does NOT modify any config values. It only observes which
 * config objects are loaded during a request and records their names for
 * later processing at terminate time.
 */
final class ConfigTranslationOverrider implements ConfigFactoryOverrideInterface {

  /**
   * Re-entrancy guard to prevent infinite recursion.
   */
  private bool $collecting = FALSE;

  /**
   * Constructs the collector.
   */
  public function __construct(
    private readonly ConfigNameCollector $configNameCollector,
    private readonly TranslationCollectorActivationChecker $settingsChecker,
    private readonly Settings $settings,
  ) {}

  /**
   * {@inheritdoc}
   */
  public function loadOverrides($names): array {
    if ($this->collecting) {
      return [];
    }

    $this->collecting = TRUE;
    try {
      if ($this->settingsChecker->isActive()) {
        $includePrefixes = $this->settings->getIncludeConfigPrefixes();
        foreach ($names as $name) {
          if ($this->isIncludedConfig($name, $includePrefixes)) {
            $this->configNameCollector->addConfigName($name);
          }
        }
      }
    }
    finally {
      $this->collecting = FALSE;
    }

    return [];
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheSuffix(): string {
    return 'translation_collector_config';
  }

  /**
   * {@inheritdoc}
   */
  public function createConfigObject($name, $collection = StorageInterface::DEFAULT_COLLECTION) {
    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheableMetadata($name): CacheableMetadata {
    return new CacheableMetadata();
  }

  /**
   * Checks if a config name matches the include whitelist.
   *
   * @param string $name
   *   The config name.
   * @param string[] $prefixes
   *   Include prefixes.
   *
   * @return bool
   *   TRUE if the config should be collected.
   */
  private function isIncludedConfig(string $name, array $prefixes): bool {
    foreach ($prefixes as $prefix) {
      if (str_starts_with($name, $prefix)) {
        return TRUE;
      }
    }

    return FALSE;
  }

}
