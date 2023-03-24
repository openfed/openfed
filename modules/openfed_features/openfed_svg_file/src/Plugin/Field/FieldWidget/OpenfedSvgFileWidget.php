<?php

namespace Drupal\openfed_svg_file\Plugin\Field\FieldWidget;

use Drupal\Component\Utility\NestedArray;
use Drupal\Core\Access\AccessResultInterface;
use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\file\Element\ManagedFile;
use Drupal\file\Plugin\Field\FieldWidget\FileWidget;

/**
 * Plugin implementation of the 'openfed_svg_file' widget.
 *
 * @FieldWidget(
 *   id = "openfed_svg_file_widget",
 *   label = @Translation("Openfed SVG File Widget"),
 *   field_types = {
 *     "openfed_svg_file"
 *   }
 * )
 */
class OpenfedSvgFileWidget extends FileWidget {

  /**
   * {@inheritdoc}
   */
  public static function defaultSettings() {
    return [
      'progress_indicator' => 'throbber',
    ] + parent::defaultSettings();
  }

  /**
   * {@inheritdoc}
   */
  public function formElement(FieldItemListInterface $items, $delta, array $element, array &$form, FormStateInterface $form_state) {
    $element = parent::formElement($items, $delta, $element, $form, $form_state);

    return $element;
  }

  /**
   * Form API callback: Processes a openfed_svg_file field element.
   *
   * Expands the openfed_svg_file type to include some attribute fields.
   *
   * This method is assigned as a #process callback in formElement() method.
   */
  public static function process($element, FormStateInterface $form_state, $form) {
    $item = $element['#value'];
    $item['fids'] = $element['fids']['#value'];

    // Add the image preview.
    if (!empty($element['#files'])) {
      $file = reset($element['#files']);
      $field_id = $element['#name'];
      $attributes['width'] = 100;
      $attributes['height'] = 100;
      $attributes['alt'] = 'preview';
      $attributes['title'] = $attributes['alt'];

      $element['field_content_wrapper'] = [
        '#type' => 'item',
      ];
      $element['field_content_wrapper']['#wrapper_attributes']['class'][] = 'flex-container';
      $element['field_content_wrapper']['#attached']['library'][] = 'openfed_svg_file/openfed_svg_file.form_edit';

      $element['field_content_wrapper']['preview'] = [
        '#theme' => 'openfed_svg_file__image',
        '#attributes' => $attributes,
        '#uri' => $file->getFileUri(),
        '#svg_data' => NULL,
        '#prefix' => '<div class="openfed_svg_file_image_preview">',
        '#suffix' => '</div>',
        '#weight' => '-20',
      ];

      $element['field_content_wrapper']['output_type'] = [
        '#type' => 'item',
      ];

      $element['field_content_wrapper']['output_type']['type'] = [
        '#type' => 'radios',
        '#title' => t('Output type'),
        '#default_value' => $item['type'] ?? 'image',
        '#options' => get_output_types(),
        '#required' => TRUE,
        '#attributes' => [
          'class' => ['openfed_svg_file_type'],
        ],
      ];
      $element['field_content_wrapper']['output_type']['width'] = [
        '#type' => 'number',
        '#title' => t('Width'),
        '#default_value' => $item['width'] ?? 100,
        '#field_suffix' => 'px',
        '#size' => 4,
        '#min' => 1,
        '#required' => TRUE,
        '#attributes' => [
          'class' => ['openfed_svg_file_width'],
        ],
      ];
      $element['field_content_wrapper']['output_type']['height'] = [
        '#type' => 'number',
        '#title' => t('Height'),
        '#default_value' => $item['height'] ?? 100,
        '#field_suffix' => 'px',
        '#size' => 4,
        '#min' => 1,
        '#required' => TRUE,
        '#attributes' => [
          'class' => ['openfed_svg_file_height'],
        ],
      ];
      $element['field_content_wrapper']['output_type']['title'] = [
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#value' => $item['title'] ?? '',
        '#disabled' => TRUE,
        '#states' => [
          'visible' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'iframe']],
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'image']],
          ],
          'enabled' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'iframe']],
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'image']],
          ],
          'required' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'iframe']],
          ],
        ],
      ];
      $element['field_content_wrapper']['output_type']['alt'] = [
        '#type' => 'textfield',
        '#title' => t('Alt'),
        '#value' => $item['alt'] ?? '',
        '#disabled' => TRUE,
        '#states' => [
          'visible' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'object']],
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'image']],
          ],
          'enabled' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'object']],
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'image']],
          ],
          'required' => [
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'object']],
            [':input[name="' . $field_id . '[field_content_wrapper][output_type][type]"]' => ['value' => 'image']],
          ],
        ],
      ];
    }

    return parent::process($element, $form_state, $form);
  }

  /**
   * Form API callback. Retrieves the value for the file_generic field element.
   *
   * This method is assigned as a #value_callback in formElement() method.
   */
  public static function value($element, $input, FormStateInterface $form_state) {
    if ($input) {
      // Checkboxes lose their value when empty.
      // If the display field is present make sure its unchecked value is saved.
      if (empty($input['display'])) {
        $input['display'] = $element['#display_field'] ? 0 : 1;
      }
      if (isset($input['field_content_wrapper'])) {
        $input = array_merge($input, $input['field_content_wrapper']['output_type']);
      }
    }

    // We depend on the managed file element to handle uploads.
    $return = ManagedFile::valueCallback($element, $input, $form_state);

    // Ensure that all the required properties are returned even if empty.
    $return += [
      'fids' => [],
      'display' => 1,
      'description' => '',
    ];

    return $return;
  }

  /**
   * Form element validation handler for #type 'number'.
   */
  public static function element_validate_integer_positive(&$element, FormStateInterface $form_state, &$complete_form) {
    $value = $element['#value'];
    if ($value !== '' && (!is_numeric($value) || intval($value) != $value || $value < 0)) {
      $form_state->setError($element, t('%name must be a positive integer.', ['%name' => $element['#title']]));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function extractFormValues(FieldItemListInterface $items, array $form, FormStateInterface $form_state) {
    $field_name = $this->fieldDefinition->getName();

    $field_state = static::getWidgetState($form['#parents'], $field_name, $form_state);
    $widget = NestedArray::getValue($form, $field_state['array_parents']);

    // Require an access validation to avoid submitting locked fields, as is the
    // case when working with moderated content and translations and
    // non-translated fields are used.
    $access = $widget['#access'] ?? TRUE;
    if ($access === FALSE || ($access instanceof AccessResultInterface && !$access->isAllowed())) {
      $path = array_merge($form['#parents'], [$field_name]);
      $values = $form_state->getValues();
      NestedArray::unsetValue($values, $path);
      $form_state->setValues($values);
    }
    parent::extractFormValues($items, $form, $form_state);

  }

}
