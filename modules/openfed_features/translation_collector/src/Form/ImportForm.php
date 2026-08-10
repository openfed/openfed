<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Form;

use Drupal\Core\DependencyInjection\DependencySerializationTrait;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Link;
use Drupal\Core\Queue\QueueFactory;
use Drupal\Core\Url;
use Drupal\file\FileInterface;
use Drupal\translation_collector\Import\StringsImportManager;
use Drupal\translation_collector\Plugin\QueueWorker\StringsImportQueueWorker;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Form for uploading XLSX files for translation import.
 */
final class ImportForm extends FormBase {

  use DependencySerializationTrait;

  /**
   * File entity storage access.
   */
  protected EntityTypeManagerInterface $entityTypeManager;

  /**
   * Queue factory service.
   */
  protected QueueFactory $queueFactory;

  /**
   * Import manager service.
   */
  protected StringsImportManager $importManager;

  /**
   * Constructs an ImportForm.
   */
  public function __construct(
    EntityTypeManagerInterface $entityTypeManager,
    QueueFactory $queueFactory,
    StringsImportManager $importManager,
  ) {
    $this->entityTypeManager = $entityTypeManager;
    $this->queueFactory = $queueFactory;
    $this->importManager = $importManager;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container): self {
    return new self(
      $container->get('entity_type.manager'),
      $container->get('queue'),
      $container->get('translation_collector.import_manager'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId(): string {
    return 'translation_collector_import_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state): array {
    $stringsLink = Link::fromTextAndUrl(
      $this->t('collected strings view'),
      Url::fromRoute('view.translation_collector_strings.overview')
    )->toRenderable();
    $localeSettingsLink = Link::fromTextAndUrl(
      $this->t('Locale settings'),
      Url::fromRoute('locale.settings')
    )->toRenderable();

    $form['description'] = [
      '#type' => 'container',
      'prefix' => [
        '#plain_text' => (string) $this->t('Upload an XLSX file exported from the '),
      ],
      'strings_link' => $stringsLink,
      'middle' => [
        '#plain_text' => (string) $this->t('. Rows with empty target columns are skipped. Imports are queued and processed asynchronously. Interface string overwrites follow '),
      ],
      'locale_link' => $localeSettingsLink,
      'suffix' => [
        '#plain_text' => (string) $this->t(' for overwriting customized/non-customized translations.'),
      ],
    ];

    $form['import_file'] = [
      '#type' => 'managed_file',
      '#title' => $this->t('XLSX file'),
      '#upload_location' => 'temporary://translation-collector-imports',
      '#upload_validators' => [
        'file_validate_extensions' => ['xlsx'],
      ],
      '#required' => TRUE,
      '#description' => $this->t('Only .xlsx files are supported.'),
    ];

    $form['batch_size'] = [
      '#type' => 'number',
      '#title' => $this->t('Rows processed per queue item'),
      '#default_value' => 200,
      '#min' => 25,
      '#max' => 1000,
      '#step' => 25,
      '#description' => $this->t('Larger values process faster but consume more memory per queue run.'),
    ];

    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Queue import'),
      '#button_type' => 'primary',
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state): void {
    $fids = $form_state->getValue('import_file');
    if (!is_array($fids) || empty($fids[0])) {
      $form_state->setErrorByName('import_file', $this->t('Please upload an XLSX file.'));
    }

    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state): void {
    $fids = $form_state->getValue('import_file');
    $file = $this->loadFile((int) ($fids[0] ?? 0));
    if ($file === NULL) {
      $this->messenger()->addError($this->t('The uploaded file could not be loaded.'));
      return;
    }

    $file->setPermanent();
    $file->save();

    $batchSize = (int) $form_state->getValue('batch_size');
    $queueItem = $this->importManager->buildQueueItem($file->getFileUri(), $batchSize);
    $queueItem['uid'] = (int) $this->currentUser()->id();
    $queueItem['filename'] = $file->getFilename();

    $this->queueFactory->get(StringsImportQueueWorker::QUEUE_ID)->createItem($queueItem);

    $this->messenger()->addStatus($this->t('Import queued for %file. Run cron (or `drush queue:run translation_collector_import`) to process it.', [
      '%file' => $file->getFilename(),
    ]));
  }

  /**
   * Loads an uploaded file entity.
   */
  private function loadFile(int $fid): ?FileInterface {
    if ($fid <= 0) {
      return NULL;
    }

    $file = $this->entityTypeManager->getStorage('file')->load($fid);
    return $file instanceof FileInterface ? $file : NULL;
  }

}
