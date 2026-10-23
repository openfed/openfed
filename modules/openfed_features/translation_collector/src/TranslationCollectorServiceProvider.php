<?php

declare(strict_types=1);

namespace Drupal\translation_collector;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\DependencyInjection\ServiceProviderBase;
use Symfony\Component\DependencyInjection\Reference;

/**
 * Registers tagged collectors with the persist subscriber.
 */
final class TranslationCollectorServiceProvider extends ServiceProviderBase {

  /**
   * {@inheritdoc}
   */
  public function alter(ContainerBuilder $container): void {
    if (!$container->hasDefinition('translation_collector.persist_subscriber')) {
      return;
    }

    $subscriber = $container->getDefinition('translation_collector.persist_subscriber');

    foreach ($container->findTaggedServiceIds('translation_collector.collector') as $id => $tags) {
      $subscriber->addMethodCall('addCollector', [new Reference($id)]);
    }
  }

}
