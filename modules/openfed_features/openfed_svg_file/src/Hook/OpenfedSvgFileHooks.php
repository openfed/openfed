<?php

namespace Drupal\openfed_svg_file\Hook;

use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Hook\Attribute\Hook;
use Drupal\Core\StringTranslation\StringTranslationTrait;

/**
 * Hook implementations for openfed_svg_file.
 */
class OpenfedSvgFileHooks {

  use StringTranslationTrait;

  /**
   * Implements hook_help().
   */
  #[Hook('help')]
  public function help($route_name, RouteMatchInterface $route_match): string {
    switch ($route_name) {
      // Main module help for the svg_formatter module.
      case 'help.page.openfed_svg_file':
        $output = '';
        $output .= '<h3>' . $this->t('About') . '</h3>';
        $output .= '<p>' . $this->t('Add SVG field, widget, formatter.') . '</p>';
        return $output;

      default:
        return '';
    }
  }

  /**
   * Implements hook_theme().
   */
  #[Hook('theme')]
  public function theme(): array {
    $theme = [];
    foreach (get_output_types() as $type => $label) {
      $theme += [
        'openfed_svg_file__' . $type => [
          'variables' => [
            'svg_data' => NULL,
            'attributes' => NULL,
            'alt_text' => NULL,
            'uri' => NULL,
          ],
        ],
      ];
    }
    return $theme;
  }

}
