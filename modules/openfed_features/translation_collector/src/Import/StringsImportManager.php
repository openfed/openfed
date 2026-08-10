<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Import;

use Drupal\Component\Gettext\PoItem;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Config\ImmutableConfig;
use Drupal\Core\Database\Connection;
use Drupal\Core\File\FileSystemInterface;
use Drupal\Core\Logger\LoggerChannelFactoryInterface;
use Drupal\language\Config\LanguageConfigFactoryOverrideInterface;
use Drupal\locale\StringStorageInterface;
use PhpOffice\PhpSpreadsheet\Reader\Xlsx;
use Psr\Log\LoggerInterface;

/**
 * Imports translated values from XLSX rows.
 */
final class StringsImportManager {

  /**
   * Logger channel for import reporting.
   */
  private LoggerInterface $logger;

  /**
   * Locale settings used for overwrite policy checks.
   */
  private ImmutableConfig $localeSettings;

  /**
   * Constructs a StringsImportManager.
   */
  public function __construct(
    private readonly FileSystemInterface $fileSystem,
    private readonly StringStorageInterface $localeStorage,
    private readonly LanguageConfigFactoryOverrideInterface $languageConfigOverride,
    private readonly Connection $database,
    ConfigFactoryInterface $configFactory,
    LoggerChannelFactoryInterface $loggerFactory,
  ) {
    $this->localeSettings = $configFactory->get('locale.settings');
    $this->logger = $loggerFactory->get('translation_collector');
  }

  /**
   * Builds an initial queue payload for an XLSX import file.
   */
  public function buildQueueItem(string $fileUri, int $batchSize = 200): array {
    $realPath = $this->resolveRealPath($fileUri);

    $reader = new Xlsx();
    $worksheetInfo = $reader->listWorksheetInfo($realPath);
    $maxRow = isset($worksheetInfo[0]['totalRows']) ? (int) $worksheetInfo[0]['totalRows'] : 1;

    return [
      'file_uri' => $fileUri,
      'start_row' => 2,
      'max_row' => max(1, $maxRow),
      'batch_size' => max(25, $batchSize),
    ];
  }

  /**
   * Processes one queue chunk and returns status for possible continuation.
   */
  public function processQueueItem(array $item): array {
    $fileUri = (string) ($item['file_uri'] ?? '');
    $startRow = max(2, (int) ($item['start_row'] ?? 2));
    $maxRow = max(1, (int) ($item['max_row'] ?? 1));
    $batchSize = max(25, (int) ($item['batch_size'] ?? 200));

    $stats = [
      'processed' => 0,
      'imported' => 0,
      'skipped' => 0,
      'failed' => 0,
    ];

    if ($fileUri === '' || $startRow > $maxRow) {
      return [
        'stats' => $stats,
        'has_more' => FALSE,
        'next_row' => $startRow,
      ];
    }

    $endRow = min($maxRow, $startRow + $batchSize - 1);

    $reader = new Xlsx();
    $reader->setReadDataOnly(TRUE);
    $reader->setReadFilter(new ChunkReadFilter($startRow, $endRow));

    $realPath = $this->resolveRealPath($fileUri);
    $spreadsheet = $reader->load($realPath);
    $sheet = $spreadsheet->getActiveSheet();

    for ($row = $startRow; $row <= $endRow; $row++) {
      $source = $this->normalizeImportedKeyValue((string) $sheet->getCell('B' . $row)->getValue());
      $sourcePlural = $this->normalizeImportedKeyValue((string) $sheet->getCell('C' . $row)->getValue());
      $context = $this->normalizeImportedKeyValue((string) $sheet->getCell('D' . $row)->getValue());
      $langcode = $this->normalizeImportedKeyValue((string) $sheet->getCell('E' . $row)->getValue());
      $stringType = strtolower($this->normalizeImportedKeyValue((string) $sheet->getCell('F' . $row)->getValue()));
      $location = $this->normalizeImportedKeyValue((string) $sheet->getCell('G' . $row)->getValue());
      $translation = trim((string) $sheet->getCell('K' . $row)->getValue());
      $translationPlural = trim((string) $sheet->getCell('L' . $row)->getValue());

      if ($source === '' && $sourcePlural === '' && $langcode === '' && $stringType === '' && $location === '' && $translation === '' && $translationPlural === '') {
        continue;
      }

      $stats['processed']++;

      if ($translation === '' && $translationPlural === '') {
        $stats['skipped']++;
        continue;
      }

      try {
        $imported = $this->importRow($source, $sourcePlural, $context, $langcode, $stringType, $location, $translation, $translationPlural);
        if ($imported) {
          $stats['imported']++;
        }
        else {
          $stats['skipped']++;
        }
      }
      catch (\Throwable $e) {
        $stats['failed']++;
        $this->logger->error('Translation import failed on row @row in @file: @message', [
          '@row' => $row,
          '@file' => $fileUri,
          '@message' => $e->getMessage(),
        ]);
      }
    }

    $spreadsheet->disconnectWorksheets();
    unset($spreadsheet);

    return [
      'stats' => $stats,
      'has_more' => $endRow < $maxRow,
      'next_row' => $endRow + 1,
    ];
  }

  /**
   * Imports a single row based on string type.
   */
  private function importRow(string $source, string $sourcePlural, string $context, string $langcode, string $stringType, string $location, string $translation, string $translationPlural): bool {
    if ($source === '' || $langcode === '') {
      return FALSE;
    }

    if ($stringType === 'interface') {
      [$storedSource, $written] = $this->importInterfaceTranslation($source, $sourcePlural, $context, $langcode, $translation, $translationPlural);
      if (!$written) {
        return FALSE;
      }
      $this->markAsTranslated($storedSource, $context, $langcode, 'interface', $location);
      return TRUE;
    }

    if ($stringType === 'config') {
      if ($location === '' || !str_contains($location, ':')) {
        return FALSE;
      }

      [$configName, $path] = explode(':', $location, 2);
      $configName = trim($configName);
      $path = trim($path);
      if ($configName === '' || $path === '') {
        return FALSE;
      }

      $this->languageConfigOverride
        ->getOverride($langcode, $configName)
        ->set($path, $translation)
        ->save();

      $this->markAsTranslated($source, $context, $langcode, 'config', $location);
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Imports one interface string translation into locale storage.
   *
   * @return array{0:string,1:bool}
   *   Source key used for collector updates and whether a write was performed.
   */
  private function importInterfaceTranslation(string $source, string $sourcePlural, string $context, string $langcode, string $translation, string $translationPlural): array {
    [$source, $translation] = $this->buildInterfaceSourceAndTranslation(
      $source,
      $sourcePlural,
      $context,
      $langcode,
      $translation,
      $translationPlural,
    );

    $sourceString = $this->localeStorage->findString([
      'source' => $source,
      'context' => $context,
    ]);

    if ($sourceString === NULL) {
      $sourceString = $this->localeStorage
        ->createString([
          'source' => $source,
          'context' => $context,
        ])
        ->save();
    }

    $translationString = $this->localeStorage->findTranslation([
      'language' => $langcode,
      'source' => $source,
      'context' => $context,
      'translated' => TRUE,
    ]);

    if ($translationString === NULL) {
      $translationString = $this->localeStorage->createTranslation([
        'lid' => $sourceString->getId(),
        'language' => $langcode,
      ]);
    }
    else {
      if (!$this->canOverwriteExistingTranslation($translationString)) {
        return [$source, FALSE];
      }

      // Ensure required key values are set before saving updates.
      $translationString->setValues([
        'lid' => $sourceString->getId(),
        'language' => $langcode,
      ], FALSE);
    }

    $translationString
      ->setString($translation)
      ->setCustomized(TRUE)
      ->save();

    return [$source, TRUE];
  }

  /**
   * Builds the source key and translation payload for interface imports.
   *
   * @return array{0:string,1:string}
   *   Source key and translation value for locale storage.
   */
  private function buildInterfaceSourceAndTranslation(string $source, string $sourcePlural, string $context, string $langcode, string $translation, string $translationPlural): array {
    if ($sourcePlural === '' && !str_contains($source, PoItem::DELIMITER)) {
      return [$source, $translation];
    }

    $sourceParts = $sourcePlural !== ''
      ? [$source, $sourcePlural]
      : explode(PoItem::DELIMITER, $source, 2);

    $sourceParts[0] = (string) ($sourceParts[0] ?? '');
    $sourceParts[1] = (string) ($sourceParts[1] ?? '');
    $combinedSource = implode(PoItem::DELIMITER, $sourceParts);

    $existing = $this->localeStorage->findTranslation([
      'language' => $langcode,
      'source' => $combinedSource,
      'context' => $context,
      'translated' => TRUE,
    ]);

    $translationParts = $sourceParts;
    if ($existing !== NULL) {
      $loadedParts = explode(PoItem::DELIMITER, (string) $existing->getString());
      if (isset($loadedParts[0]) && $loadedParts[0] !== '') {
        $translationParts[0] = $loadedParts[0];
      }
      if (isset($loadedParts[1]) && $loadedParts[1] !== '') {
        $translationParts[1] = $loadedParts[1];
      }
    }

    if ($translation !== '') {
      $translationParts[0] = $translation;
    }
    if ($translationPlural !== '') {
      $translationParts[1] = $translationPlural;
    }

    $combinedTranslation = implode(PoItem::DELIMITER, $translationParts);

    return [$combinedSource, $combinedTranslation];
  }

  /**
   * Marks the collected row as translated in collector storage.
   */
  private function markAsTranslated(string $source, string $context, string $langcode, string $stringType, string $location): void {
    $query = $this->database->update('translation_collector_strings')
      ->fields([
        'is_translated' => 1,
      ])
      ->condition('source_hash', hash('sha256', $source))
      ->condition('context', $context)
      ->condition('langcode', $langcode)
      ->condition('string_type', $stringType);

    if ($location !== '') {
      $query->condition('location', $location);
    }

    $query->execute();
  }

  /**
   * Resolves a managed file URI to an absolute path.
   */
  private function resolveRealPath(string $fileUri): string {
    $realPath = $this->fileSystem->realpath($fileUri);
    if (!is_string($realPath) || $realPath === '') {
      throw new \RuntimeException(sprintf('Cannot resolve file path for URI "%s".', $fileUri));
    }

    return $realPath;
  }

  /**
   * Normalizes imported key values that were apostrophe-escaped for XLSX safety.
   */
  private function normalizeImportedKeyValue(string $value): string {
    $value = trim($value);

    if (
      strlen($value) > 1
      && $value[0] === "'"
      && in_array($value[1], ['=', '+', '-', '@'], TRUE)
    ) {
      return substr($value, 1);
    }

    return $value;
  }

  /**
   * Checks whether existing translation may be overwritten per locale settings.
   */
  private function canOverwriteExistingTranslation(object $translationString): bool {
    $overwriteCustomized = (bool) $this->localeSettings->get('translation.overwrite_customized');
    $overwriteNotCustomized = (bool) $this->localeSettings->get('translation.overwrite_not_customized');

    $customized = (int) ($translationString->customized ?? \LOCALE_NOT_CUSTOMIZED);
    if ($customized === \LOCALE_CUSTOMIZED) {
      return $overwriteCustomized;
    }

    return $overwriteNotCustomized;
  }

}
