<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config;

use Drupal\Core\Config\ConfigFactoryInterface;

/**
 * Provides access to config-collection settings.
 */
final class Settings {

  /**
   * Constructs settings helper.
   */
  public function __construct(
    private readonly ConfigFactoryInterface $configFactory,
  ) {}

  /**
   * Returns config name prefixes that should be included in collection.
   *
   * @return string[]
   *   Array of config name prefixes.
   */
  public function getIncludeConfigPrefixes(): array {
    $config = $this->configFactory->get('translation_collector_config.settings');
    $prefixes = $config->get('include_config_prefixes');

    if (is_array($prefixes)) {
      return $prefixes;
    }

    return [];
  }

}
