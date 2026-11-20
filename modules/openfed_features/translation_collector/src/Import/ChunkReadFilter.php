<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Import;

use PhpOffice\PhpSpreadsheet\Reader\IReadFilter;

/**
 * Limits XLSX reads to a specific row range.
 */
final class ChunkReadFilter implements IReadFilter {

  /**
   * Constructs a chunk read filter.
   */
  public function __construct(
    private readonly int $startRow,
    private readonly int $endRow,
  ) {}

  /**
   * {@inheritdoc}
   */
  public function readCell($columnAddress, $row, $worksheetName = ''): bool {
    // Always include the header row for predictable worksheet metadata.
    if ((int) $row === 1) {
      return TRUE;
    }

    return $row >= $this->startRow && $row <= $this->endRow;
  }

}
