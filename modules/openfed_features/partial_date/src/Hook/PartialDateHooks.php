<?php

namespace Drupal\partial_date\Hook;

use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Hook\Attribute\Hook;
use Drupal\Core\StringTranslation\StringTranslationTrait;

/**
 * Hook implementations for partial_date.
 */
class PartialDateHooks {

  use StringTranslationTrait;

  /**
   * Implements hook_help().
   */
  #[Hook('help')]
  public function help($route_name, RouteMatchInterface $route_match) {
    switch ($route_name) {
      // Main module help for partial_date module.
      case 'help.page.partial_date':
        $output = '<h3>' . $this->t('About') . '</h3>';
        $output .= '<p>' . $this->t('The <i>Partial Date</i> module provides the ability to store incomplete dates (like Year & Month only). For more information see the <a href=":doc">online documentation</a>.', [':doc' => 'https://www.drupal.org/project/partial_date']) . '</p>';
        $output .= '<h3>' . $this->t('Uses') . '</h3>';
        $output .= '<dl>';
        $output .= '<dt>' . $this->t('Partial date formats') . '</dt>';
        $output .= '<dd>' . $this->t('Three formats are provided by default (<i>short</i>, <i>medium</i> & <i>long</i>). You may addapt them to your needs or create additional ones through <a href=":doc">configuration page</a>.', [':doc' => '/admin/config/regional/partial-date-formats']) . '</dd>';
        $output .= '<dt>' . $this->t('Estimates') . '</dt>';
        $output .= '<dd>' . $this->t('The module allow users to enter a more readable text value, for example, "<i>The stone age </i>" or "<i>Jurrassic period </i>". These estimate values are optional and can be disabled.') . '</dd>';
        $output .= '<dt>' . $this->t('Timezone') . '</dt>';
        $output .= '<dd>' . $this->t('Currently a timezone may be available to users. However, it is for informational uses only. Not timezone conversion is performed. This may change in the future.') . '</dd>';
        $output .= '</dl>';
        return $output;
    }
  }

  /**
   * Implements hook_theme().
   */
  #[Hook('theme')]
  public function theme(): array {
    return [
      'partial_date' => [
        'variables' => [
          'date' => [],
          'format' => NULL,
        ],
        'file' => 'partial_date.theme.inc',
      ],
      'partial_date_range' => [
        'variables' => [
          'from' => [],
          'to' => [],
          'format' => NULL,
        ],
        'file' => 'partial_date.theme.inc',
      ],
      'checkbox_with_options' => [
        'render element' => 'element',
      ],
    ];
  }

}
