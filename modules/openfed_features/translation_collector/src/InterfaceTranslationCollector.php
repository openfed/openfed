<?php

namespace Drupal\translation_collector;

use Drupal\Component\Gettext\PoItem;
use Drupal\Core\StringTranslation\Translator\TranslatorInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\DependencyInjection\Exception\ServiceCircularReferenceException;

/**
 * String translation listener to collect data.
 */
class InterfaceTranslationCollector implements TranslatorInterface, CollectorInterface {

  /**
   * Constructs an InterfaceTranslationCollector.
   */
  public function __construct(
    private readonly TranslatorInterface $localeTranslation,
    private readonly ContainerInterface $container,
  ) {}

  /**
   * String that were attempted to be looked up in this request.
   *
   * @var array
   */
  private array $strings = [];

  /**
   * Cached activation result for this request lifecycle.
   */
  private ?bool $active = NULL;

  /**
   * {@inheritdoc}
   */
  public function getStringTranslation($langcode, $string, $context) {
    if (!$this->isActive()) {
      return FALSE;
    }

    if ($langcode != 'en' || locale_is_translatable('en')) {
      $count = count(explode(PoItem::DELIMITER, $string));
      $location = $count > 1 ? 'plural' : '';
      $key = $langcode . '|' . $context . '|' . $location . '|' . $string;
      if (!isset($this->strings[$key])) {
        $this->strings[$key] = [
          'source' => $string,
          'langcode' => $langcode,
          'context' => $context,
          'location' => $location,
        ];
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function reset(): void {
    $this->strings = [];
  }

  /**
   * {@inheritdoc}
   */
  public function isActive(): bool {
    if ($this->active !== NULL) {
      return $this->active;
    }

    if (!$this->container->has('translation_collector.activation_checker')) {
      $this->active = FALSE;
      return FALSE;
    }

    try {
      $checker = $this->container->get('translation_collector.activation_checker');
      $this->active = $checker instanceof TranslationCollectorActivationChecker
        ? $checker->isActive()
        : FALSE;
    }
    catch (ServiceCircularReferenceException) {
      // During early container construction, disable collection to avoid loops.
      $this->active = FALSE;
    }

    return $this->active;
  }

  /**
   * {@inheritdoc}
   */
  public function getCollectedItems(): array {
    if (empty($this->strings)) {
      return [];
    }

    $items = [];
    foreach ($this->strings as $item) {
      // Query the locale lookup translator directly to mark whether this source
      // string has an existing translation for the given language and context.
      // Locale lookups are cached by Drupal, so this does not trigger a DB query
      // on every call once the relevant entries are warm.
      $translation = $this->localeTranslation->getStringTranslation($item['langcode'], $item['source'], $item['context']);
      $items[] = [
        'source' => $item['source'],
        'langcode' => $item['langcode'],
        'context' => $item['context'],
        'is_translated' => $translation,
        'location' => $item['location'] ?? '',
        'string_type' => 'interface',
      ];
    }
    return $items;
  }

}
