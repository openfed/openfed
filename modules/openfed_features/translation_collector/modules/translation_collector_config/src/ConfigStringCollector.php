<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config;

use Drupal\Component\Utility\NestedArray;
use Drupal\Core\Config\TypedConfigManagerInterface;
use Drupal\Core\Language\LanguageInterface;
use Drupal\Core\Language\LanguageManagerInterface;
use Drupal\Core\TypedData\TraversableTypedDataInterface;
use Drupal\Core\TypedData\TypedDataInterface;
use Drupal\language\Config\LanguageConfigFactoryOverrideInterface;
use Drupal\translation_collector\CollectorInterface;
use Drupal\translation_collector\TranslationCollectorActivationChecker;

/**
 * Collects config translation strings from config objects accessed during a request.
 *
 * Implements CollectorInterface so the base module persist subscriber can
 * retrieve items at terminate time.
 */
final class ConfigStringCollector implements CollectorInterface {

  /**
   * Constructs a ConfigStringCollector.
   */
  public function __construct(
    private readonly TranslationCollectorActivationChecker $settingsChecker,
    private readonly ResponseConfigNameCollector $responseConfigNameCollector,
    private readonly ConfigNameCollector $configNameCollector,
    private readonly TypedConfigManagerInterface $typedConfigManager,
    private readonly LanguageConfigFactoryOverrideInterface $languageConfigOverride,
    private readonly LanguageManagerInterface $languageManager,
  ) {}

  /**
   * {@inheritdoc}
   */
  public function isActive(): bool {
    return $this->settingsChecker->isActive();
  }

  /**
   * {@inheritdoc}
   */
  public function getCollectedItems(): array {
    // Prefer response cache tags because they represent output-relevant config.
    $configNames = $this->responseConfigNameCollector->getCollectedConfigNames();

    // Include config names that were actually loaded during the request.
    $configNames = array_merge($configNames, $this->configNameCollector->getCollectedConfigNames());

    $configNames = array_values(array_unique($configNames));

    if (empty($configNames)) {
      return [];
    }

    $langcode = $this->languageManager->getCurrentLanguage(LanguageInterface::TYPE_INTERFACE)->getId();
    return $this->resolveConfigTranslationStrings($configNames, $langcode);
  }


  /**
   * Resolves config translation strings from collected config names.
   *
   * @param string[] $configNames
   *   Config names accessed during the request.
   * @param string $langcode
   *   The target language code.
   *
   * @return array
   *   Array of items with keys: source, langcode, context, is_translated, location, string_type.
   */
  private function resolveConfigTranslationStrings(array $configNames, string $langcode): array {
    $results = [];
    $overrideStorage = $this->languageConfigOverride->getStorage($langcode);

    foreach ($configNames as $name) {
      if (!$this->typedConfigManager->hasConfigSchema($name)) {
        continue;
      }

      try {
        $typed = $this->typedConfigManager->get($name);
      }
      catch (\Exception) {
        continue;
      }

      if (!$typed instanceof TraversableTypedDataInterface) {
        continue;
      }

      $translatableElements = [];
      $this->findTranslatableElements($typed, '', $translatableElements);

      if (empty($translatableElements)) {
        continue;
      }

      $override = $overrideStorage->read($name);

      foreach ($translatableElements as $path => $source) {
        $is_translated = FALSE;
        if ($override !== FALSE && is_array($override)) {
          $is_translated = $this->nestedKeyExists($override, $path);
        }

        $location = $name . ':' . $path;
        $key = $langcode . '|' . $location . '|' . $source;

        if (!isset($results[$key])) {
          $results[$key] = [
            'source' => $source,
            'langcode' => $langcode,
            'context' => '',
            'location' => $location,
            'is_translated' => $is_translated,
            'string_type' => 'config',
          ];
        }
      }
    }

    return array_values($results);
  }

  /**
   * Recursively finds translatable elements in typed config.
   */
  private function findTranslatableElements(TypedDataInterface $element, string $path, array &$results): void {
    if ($element instanceof TraversableTypedDataInterface) {
      foreach ($element as $key => $property) {
        $child_path = $path === '' ? (string) $key : $path . '.' . $key;
        $this->findTranslatableElements($property, $child_path, $results);
      }
    }
    else {
      $value = $element->getValue();
      $definition = $element->getDataDefinition();
      if (!empty($definition['translatable']) && $value !== '' && $value !== NULL) {
        $results[$path] = (string) $value;
      }
    }
  }

  /**
   * Checks if a nested key exists in a config override array.
   */
  private function nestedKeyExists(array $data, string $path): bool {
    $exists = FALSE;
    $value = NestedArray::getValue($data, explode('.', $path), $exists);

    return $exists && $value !== '' && $value !== NULL;
  }

}
