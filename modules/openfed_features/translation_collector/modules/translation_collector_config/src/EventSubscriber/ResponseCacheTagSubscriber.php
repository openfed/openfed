<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config\EventSubscriber;

use Drupal\Core\Cache\CacheableResponseInterface;
use Drupal\translation_collector\TranslationCollectorActivationChecker;
use Drupal\translation_collector_config\ResponseConfigNameCollector;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\ResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Extracts output-relevant config names from response cache tags.
 */
final class ResponseCacheTagSubscriber implements EventSubscriberInterface {

  /**
   * Constructs the subscriber.
   */
  public function __construct(
    private readonly ResponseConfigNameCollector $responseConfigNameCollector,
    private readonly TranslationCollectorActivationChecker $settingsChecker,
  ) {}

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents(): array {
    return [
      KernelEvents::RESPONSE => ['onResponse'],
    ];
  }

  /**
   * Collects config names from response cache tags.
   */
  public function onResponse(ResponseEvent $event): void {
    if (!$this->settingsChecker->isActive()) {
      return;
    }

    $cacheTags = [];
    $response = $event->getResponse();

    if ($response instanceof CacheableResponseInterface) {
      $cacheTags = array_merge($cacheTags, $response->getCacheableMetadata()->getCacheTags());
    }

    $headerValue = $response->headers->get('X-Drupal-Cache-Tags');
    if (is_string($headerValue) && $headerValue !== '') {
      $headerTags = preg_split('/\s+/', trim($headerValue)) ?: [];
      $cacheTags = array_merge($cacheTags, $headerTags);
    }

    if (empty($cacheTags)) {
      return;
    }

    foreach (array_unique($cacheTags) as $cacheTag) {
      if (!is_string($cacheTag) || !str_starts_with($cacheTag, 'config:')) {
        continue;
      }

      $configName = substr($cacheTag, 7);
      if ($configName === '') {
        continue;
      }

      $this->responseConfigNameCollector->addConfigName($configName);
    }
  }

}
