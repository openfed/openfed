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
#[FormElement('partial_datetime_element')]
class PartialDateElement extends FormElementBase {

  /**
   * {@inheritdoc}
   */
  public function getInfo(): array {
    return [
      '#input' => TRUE,
      '#process' => [[get_class($this), 'process']],
      '#default_value' => FALSE,
      '#granularity' => FALSE,
      '#minimum_components' => [],
      '#increments' => [],
      '#theme_wrappers' => [
        0 => 'form_element',
        'container' => [
          '#attributes' => [
            'class' => ['partial-date-element', 'clearfix', 'container-inline'],
          ],
        ],
      ],
    ];
  }

  /**
   * Process callback.
   */
  public static function process(array &$element, FormStateInterface $form_state, &$complete_form): array {
    $granularity = $element['#granularity'];
    $fieldSufix = $element['#field_sufix'];
    $increments = $element['#increments'];
    $increments += [
      'second' => 1,
      'minute' => 1,
    ];
    $element['#tree'] = TRUE;
    foreach (partial_date_components() as $key => $label) {
      if (!empty($granularity[$key])) {
        $fieldName = $key . $fieldSufix;
        $element[$key] = [
          '#title' => $label,
          '#placeholder' => $label,
          '#title_display' => 'invisible',
          '#fieldName' => $fieldName,
          '#value' => empty($element['#value'][$key]) ? '' : $element['#value'][$key],
          '#attributes' => [
            'class' => ['partial_date_component'],
            'fieldName' => $fieldName,
          ],
        ];
        if ($key == 'year') {
          $element[$key]['#type'] = 'textfield';
          $element[$key]['#attributes']['size'] = 5;
        }
        else {
          $inc = empty($increments[$key]) ? 1 : $increments[$key];
          $blank_option = ['' => $label];
          $element[$key]['#type'] = 'select';
          $element[$key]['#options'] = partial_date_granularity_field_options($key, $blank_option, $inc);
        }
      }
    }

    return $element;
  }

}
