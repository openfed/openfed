<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Export;

use Drupal\Component\Gettext\PoItem;
use Drupal\Core\Database\Connection;
use Drupal\Core\Datetime\DateFormatterInterface;
use Drupal\Core\File\FileSystemInterface;
use PhpOffice\PhpSpreadsheet\Spreadsheet;
use PhpOffice\PhpSpreadsheet\Writer\Xlsx;

/**
 * Builds XLSX exports for collected translation strings.
 */
final class StringsExportManager {

  /**
   * Constructs a StringsExportManager.
   */
  public function __construct(
    private readonly Connection $database,
    private readonly DateFormatterInterface $dateFormatter,
    private readonly FileSystemInterface $fileSystem,
  ) {}

  /**
   * Creates an XLSX export file and returns the absolute path.
   *
   * @param array<string, string|int|array|null> $filters
   *   Optional filters matching the view's exposed filter keys.
   */
  public function createExportFile(array $filters = []): string {
    $spreadsheet = new Spreadsheet();
    $sheet = $spreadsheet->getActiveSheet();
    $sheet->setTitle('Collected strings');

    $headers = [
      'ID',
      'Source (singular)',
      'Source (plural)',
      'Context',
      'Langcode',
      'Type',
      'Location',
      'Is translated',
      'Last seen',
      'URL',
      'Target (singular)',
      'Target (plural)',
    ];
    $sheet->fromArray($headers, NULL, 'A1', TRUE);

    $rowIndex = 2;
    foreach ($this->getRows($filters) as $row) {
      [$sourceSingular, $sourcePlural] = $this->splitPluralSource((string) $row->source, (string) $row->string_type);

      $sheet->fromArray([
        (int) $row->id,
        $this->sanitizeCell($sourceSingular),
        $this->sanitizeCell($sourcePlural),
        $this->sanitizeCell((string) $row->context),
        $this->sanitizeCell((string) $row->langcode),
        $this->sanitizeCell((string) $row->string_type),
        $this->sanitizeCell((string) $row->location),
        ((int) $row->is_translated) === 1 ? 'Yes' : 'No',
        $this->formatTimestamp((int) $row->last_seen),
        $this->sanitizeCell((string) $row->url),
        '',
        '',
      ], NULL, 'A' . $rowIndex, TRUE);
      $rowIndex++;
    }

    $sheet->freezePane('A2');

    foreach (range('A', 'L') as $column) {
      $sheet->getColumnDimension($column)->setAutoSize(TRUE);
    }

    $path = $this->createTempFilePath();
    $writer = new Xlsx($spreadsheet);
    $writer->save($path);

    $spreadsheet->disconnectWorksheets();
    unset($spreadsheet);

    return $path;
  }

  /**
   * Returns query results for export.
   *
   * @param array<string, string|int|array|null> $filters
   *   Exposed filter values from the view.
   *
   * @return iterable<object>
   *   Database result rows.
   */
  private function getRows(array $filters): iterable {
    $query = $this->database->select('translation_collector_strings', 't');
    $query->fields('t', [
      'id',
      'source',
      'context',
      'langcode',
      'string_type',
      'location',
      'is_translated',
      'last_seen',
      'url',
    ]);

    if (!empty($filters['source']) && is_string($filters['source'])) {
      $query->condition('t.source', '%' . $this->database->escapeLike($filters['source']) . '%', 'LIKE');
    }

    $langcodes = $this->normalizeInFilterValues($filters['langcode'] ?? NULL);
    if ($langcodes !== []) {
      if (count($langcodes) === 1) {
        $query->condition('t.langcode', $langcodes[0]);
      }
      else {
        $query->condition('t.langcode', $langcodes, 'IN');
      }
    }

    $stringTypes = $this->normalizeInFilterValues($filters['string_type'] ?? NULL);
    if ($stringTypes !== []) {
      if (count($stringTypes) === 1) {
        $query->condition('t.string_type', $stringTypes[0]);
      }
      else {
        $query->condition('t.string_type', $stringTypes, 'IN');
      }
    }

    $translatedFilter = $this->normalizeTranslatedFilter($filters['is_translated'] ?? NULL);
    if ($translatedFilter !== NULL) {
      $query->condition('t.is_translated', $translatedFilter);
    }

    $query->orderBy('t.last_seen', 'DESC');

    return $query->execute();
  }

  /**
   * Normalizes values used by in-operator exposed filters.
   *
   * @return string[]
   *   Sanitized list of selected values.
   */
  private function normalizeInFilterValues(mixed $value): array {
    if ($value === NULL || $value === '' || $value === 'All') {
      return [];
    }

    if (is_scalar($value)) {
      return [(string) $value];
    }

    if (!is_array($value)) {
      return [];
    }

    $normalized = [];
    foreach ($value as $item) {
      if (!is_scalar($item)) {
        continue;
      }
      $item = (string) $item;
      if ($item !== '' && $item !== 'All') {
        $normalized[] = $item;
      }
    }

    return array_values(array_unique($normalized));
  }

  /**
   * Normalizes translated filter value.
   */
  private function normalizeTranslatedFilter(mixed $value): ?int {
    if ($value === NULL || $value === '' || $value === 'All') {
      return NULL;
    }

    if (is_scalar($value) && in_array((string) $value, ['0', '1'], TRUE)) {
      return (int) $value;
    }

    return NULL;
  }

  /**
   * Creates an export file path in Drupal temporary storage.
   */
  private function createTempFilePath(): string {
    $directory = 'temporary://translation-collector-exports';
    $this->fileSystem->prepareDirectory($directory, FileSystemInterface::CREATE_DIRECTORY | FileSystemInterface::MODIFY_PERMISSIONS);

    $realDirectory = $this->fileSystem->realpath($directory);
    if ($realDirectory === FALSE) {
      throw new \RuntimeException('Unable to resolve temporary export directory.');
    }

    $tempPath = tempnam($realDirectory, 'translation_collector_');
    if ($tempPath === FALSE) {
      throw new \RuntimeException('Unable to create temporary export file.');
    }

    $xlsxPath = $tempPath . '.xlsx';
    if (!rename($tempPath, $xlsxPath)) {
      throw new \RuntimeException('Unable to prepare temporary XLSX file path.');
    }

    return $xlsxPath;
  }

  /**
   * Formats a Unix timestamp for export.
   */
  private function formatTimestamp(int $timestamp): string {
    if ($timestamp <= 0) {
      return '';
    }

    return $this->dateFormatter->format(
      $timestamp,
      'custom',
      'Y-m-d H:i:s',
      NULL,
      'en'
    );
  }

  /**
   * Prevents spreadsheet formula execution for untrusted cell values.
   */
  private function sanitizeCell(string $value): string {
    if ($value === '') {
      return '';
    }

    $firstChar = $value[0];
    if (in_array($firstChar, ['=', '+', '-', '@'], TRUE)) {
      return "'" . $value;
    }

    return $value;
  }

  /**
   * Splits combined plural source into singular/plural columns for export.
   *
   * @return array{0:string,1:string}
   *   Singular and plural source values.
   */
  private function splitPluralSource(string $source, string $stringType): array {
    if ($stringType !== 'interface' || !str_contains($source, PoItem::DELIMITER)) {
      return [$source, ''];
    }

    $parts = explode(PoItem::DELIMITER, $source, 2);
    return [
      $parts[0] ?? $source,
      $parts[1] ?? '',
    ];
  }

}
