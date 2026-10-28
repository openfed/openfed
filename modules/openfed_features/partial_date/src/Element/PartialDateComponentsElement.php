<?php

namespace Drupal\partial_date\Element;

use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Attribute\FormElement;
use Drupal\Core\Render\Element\FormElementBase;

/**
 * Provides a form element for partial date widget.
 *
 * @author CosminFr
 */
#[FormElement('partial_date_components_element')]
class PartialDateComponentsElement extends FormElementBase {

  /**
   * {@inheritdoc}
   */
  public function getInfo(): array {
    return [
      '#input' => TRUE,
      '#process' => [[get_class($this), 'process']],
      '#tree' => TRUE,
      '#theme_wrappers' => [
        0 => 'form_element',
        'container' => [
          '#attributes' => [
            'class' => ['partial-date-element', 'clearfix', 'container-inline'],
          ],
        ],
      ],
      '#options' => partial_date_components(['timezone']),
      '#show_time' => TRUE,
      '#time_states' => FALSE,
    ];
  }

  /**
   * Process callback.
   */
  public static function process(array &$element, FormStateInterface $form_state, &$complete_form): array {
    if (!$element['#show_time']) {
      unset($element['#options']['hour'], $element['#options']['minute'], $element['#options']['second']);
    }
    foreach ($element['#options'] as $key => $label) {
      $element[$key] = [
        '#type' => 'checkbox',
        '#title' => $label,
        '#value' => in_array($key, $element['#value'], TRUE),
      ];
      if ($element['#time_states'] && _partial_date_component_type($key) == 'time') {
        $element[$key]['#states'] = $element['#time_states'];
      }
    }
    return $element;
  }

  /**
   * {@inheritdoc}
   */
  public static function valueCallback(&$element, $input, FormStateInterface $form_state): array {
    $result = [];
    if ($input === FALSE) {
      $element += ['#default_value' => []];
      $result = $element['#default_value'];
    }
    elseif (is_array($input)) {
      foreach ($input as $key => $value) {
        if (isset($value) && $value != 0) {
          $result[$key] = $value;
        }
      }
    }
    elseif (isset($input)) {
      $result[$input] = $input;
    }
    return array_keys(array_filter($result));
  }

}
