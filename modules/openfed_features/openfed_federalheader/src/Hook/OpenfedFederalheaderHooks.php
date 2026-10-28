<?php

namespace Drupal\openfed_federalheader\Hook;

use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for openfed_federalheader.
 */
class OpenfedFederalheaderHooks {

  /**
   * Implements hook_theme().
   */
  #[Hook('theme')]
  public function theme($existing, $type, $theme, $path): array {
    return [
      'federalheader_block' => [
        'variables' => [
          'module_path' => NULL,
          'other_information' => NULL,
        ],
      ],
    ];
  }

}
