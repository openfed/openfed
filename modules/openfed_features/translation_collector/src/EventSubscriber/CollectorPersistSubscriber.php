<?php

declare(strict_types=1);

namespace Drupal\translation_collector\EventSubscriber;

use Drupal\Component\Datetime\TimeInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Language\LanguageInterface;
use Drupal\Core\Language\LanguageManagerInterface;
use Drupal\translation_collector\CollectorInterface;
use Drupal\translation_collector\TranslationCollectorActivationChecker;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\TerminateEvent;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Persists collected translatable strings to the database on request terminate.
 *
 * All DB work happens after the response has been sent to the client.
 */
final class CollectorPersistSubscriber implements EventSubscriberInterface {

  /**
   * The registered collectors.
   *
   * @var \Drupal\translation_collector\CollectorInterface[]
   */
  private array $collectors = [];

  /**
   * Constructs a CollectorPersistSubscriber.
   */
  public function __construct(
    private readonly TranslationCollectorActivationChecker $settingsChecker,
    private readonly Connection $database,
    private readonly TimeInterface $time,
    private readonly LanguageManagerInterface $languageManager,
  ) {}

  /**
   * Adds a collector (called by the service container via method calls).
   */
  public function addCollector(CollectorInterface $collector): void {
    $this->collectors[] = $collector;
  }

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents(): array {
    return [
      KernelEvents::TERMINATE => ['onTerminate', -100],
    ];
  }

  /**
   * Persists collected strings using UPSERT (merge query).
   */
  public function onTerminate(TerminateEvent $event): void {
    if (!$this->settingsChecker->isActive()) {
      return;
    }

    $langcode = $this->languageManager->getCurrentLanguage()->getId();
    $defaultLangcode = $this->languageManager->getDefaultLanguage()->getId();

    // Skip entirely if viewing in the default language.
    if ($langcode === $defaultLangcode) {
      return;
    }

    $url = $event->getRequest()->getRequestUri();
    $timestamp = $this->time->getRequestTime();

    foreach ($this->collectors as $collector) {
      if (!$collector->isActive()) {
        continue;
      }

      $items = $collector->getCollectedItems();
      foreach ($items as $item) {
        $this->persistString($item, $url, $timestamp);
      }
    }
  }

  /**
   * Persists a single string record via UPSERT.
   */
  private function persistString(array $item, string $url, int $timestamp): void {
    $source_hash = hash('sha256', $item['source']);
    $this->database->merge('translation_collector_strings')
      ->keys([
        'source_hash' => $source_hash,
        'context' => $item['context'],
        'langcode' => $item['langcode'],
      ])
      ->insertFields([
        'source' => $item['source'],
        'source_hash' => $source_hash,
        'context' => $item['context'],
        'langcode' => $item['langcode'],
        'is_translated' => (int) $item['is_translated'],
        'string_type' => $item['string_type'],
        'location' => $item['location'] ?? '',
        'url' => $url,
        'last_seen' => $timestamp,
      ])
      ->updateFields([
        'string_type' => $item['string_type'],
        'is_translated' => (int) $item['is_translated'],
        'location' => $item['location'] ?? '',
        'url' => $url,
        'last_seen' => $timestamp,
      ])
      ->execute();
  }

}
