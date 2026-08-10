<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Plugin\QueueWorker;

use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Queue\QueueFactory;
use Drupal\Core\Queue\QueueWorkerBase;
use Drupal\translation_collector\Import\StringsImportManager;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Queue worker for importing translated strings from XLSX.
 *
 * @QueueWorker(
 *   id = "translation_collector_import",
 *   title = @Translation("Translation collector XLSX import"),
 *   cron = {"time" = 60}
 * )
 */
final class StringsImportQueueWorker extends QueueWorkerBase implements ContainerFactoryPluginInterface {

  /**
   * Queue id used by this worker.
   */
  public const QUEUE_ID = 'translation_collector_import';

  /**
   * Constructs a StringsImportQueueWorker.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly StringsImportManager $importManager,
    private readonly QueueFactory $queueFactory,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): self {
    return new self(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('translation_collector.import_manager'),
      $container->get('queue'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function processItem($data): void {
    if (!is_array($data)) {
      return;
    }

    $result = $this->importManager->processQueueItem($data);

    if (!empty($result['has_more'])) {
      $next = $data;
      $next['start_row'] = (int) ($result['next_row'] ?? ((int) ($data['start_row'] ?? 2) + 1));
      $this->queueFactory->get(self::QUEUE_ID)->createItem($next);
    }
  }

}
