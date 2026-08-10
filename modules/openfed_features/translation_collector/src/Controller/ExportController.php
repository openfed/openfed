<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\translation_collector\Export\StringsExportManager;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\BinaryFileResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\ResponseHeaderBag;

/**
 * Controller for exporting collected strings as XLSX.
 */
final class ExportController extends ControllerBase {

  /**
   * Constructs an ExportController.
   */
  public function __construct(
    private readonly StringsExportManager $exportManager,
  ) {}

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container): self {
    return new self(
      $container->get('translation_collector.export_manager'),
    );
  }

  /**
   * Exports collected strings to an XLSX file.
   */
  public function export(Request $request): BinaryFileResponse {
    $filters = $this->extractFilters($request);

    $path = $this->exportManager->createExportFile($filters);

    $response = new BinaryFileResponse($path);
    $response->setContentDisposition(
      ResponseHeaderBag::DISPOSITION_ATTACHMENT,
      'translation-collector-strings.xlsx'
    );
    $response->headers->set('Content-Type', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet');
    $response->deleteFileAfterSend(TRUE);

    return $response;
  }

  /**
   * Extracts exposed filter values from request query or referrer query.
   */
  private function extractFilters(Request $request): array {
    $query = $request->query->all();
    $filters = [
      'source' => $this->normalizeFilterValue('source', $query['source'] ?? NULL),
      'langcode' => $this->normalizeFilterValue('langcode', $query['langcode'] ?? NULL),
      'string_type' => $this->normalizeFilterValue('string_type', $query['string_type'] ?? NULL),
      'is_translated' => $this->normalizeFilterValue('is_translated', $query['is_translated'] ?? NULL),
    ];

    // Local action links may not preserve exposed filter query args.
    $hasDirectFilter = array_filter($filters, static function (mixed $value): bool {
      if (is_array($value)) {
        return $value !== [];
      }
      return $value !== NULL && $value !== '';
    });
    if (!empty($hasDirectFilter)) {
      return $filters;
    }

    $referrer = $request->headers->get('referer');
    if (!is_string($referrer) || $referrer === '') {
      return $filters;
    }

    $referrerQuery = parse_url($referrer, PHP_URL_QUERY);
    if (!is_string($referrerQuery) || $referrerQuery === '') {
      return $filters;
    }

    parse_str($referrerQuery, $params);
    if (!is_array($params)) {
      return $filters;
    }

    foreach (array_keys($filters) as $key) {
      if (isset($params[$key])) {
        $filters[$key] = $this->normalizeFilterValue($key, $params[$key]);
      }
    }

    return $filters;
  }

  /**
   * Normalizes exposed filter values from request input.
   */
  private function normalizeFilterValue(string $key, mixed $value): string|array|null {
    if (!in_array($key, ['source', 'langcode', 'string_type', 'is_translated'], TRUE)) {
      return NULL;
    }

    if (is_array($value)) {
      if (!in_array($key, ['langcode', 'string_type'], TRUE)) {
        return NULL;
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

    if (!is_scalar($value)) {
      return NULL;
    }

    $value = (string) $value;
    if ($value === '') {
      return NULL;
    }

    if (in_array($key, ['langcode', 'string_type'], TRUE) && $value === 'All') {
      return NULL;
    }

    return $value;
  }

}
