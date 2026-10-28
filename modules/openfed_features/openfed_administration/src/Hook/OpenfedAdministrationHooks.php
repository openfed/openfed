<?php

namespace Drupal\openfed_administration\Hook;

use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Hook\Attribute\Hook;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\node\NodePreviewMode;

/**
 * Hook implementations for openfed_administration.
 */
class OpenfedAdministrationHooks {

  use StringTranslationTrait;

  /**
   * Implements hook_form_alter().
   *
   * This will add a checkbox to the add content type form. When checked,
   * Content Moderation, default language settings and permissions are added
   * when creating the new Content Type.
   */
  #[Hook('form_alter')]
  public function formAlter(array &$form, FormStateInterface $form_state, string $form_id): void {
    if ($form_id === 'node_type_add_form') {
      $form['name'] += [
        '#weight' => 0,
      ];
      $form['type'] += [
        '#weight' => 1,
      ];
      $form['description'] += [
        '#weight' => 2,
      ];
      $form['copy_default_config'] = [
        '#type' => 'checkbox',
        '#title' => $this->t('Apply the default config to the content type.'),
        '#description' => $this->t('Content moderation settings and permissions will be applied to the content type.'),
        '#weight' => 3,
      ];
      $form['additional_settings'] += [
        '#weight' => 10,
      ];
      // Disable preview by default.
      $form['submission']['preview_mode']['#default_value'] = NodePreviewMode::Disabled->value;
      // Disable "Display author and date information" by default.
      $form['display']['display_submitted']['#default_value'] = FALSE;
      // Disable the promote option by default.
      if (isset($form['workflow']['options']['#default_value']['promote'])) {
        unset($form['workflow']['options']['#default_value']['promote']);
      }
      // Disable menus by default.
      if (isset($form['menu']['menu_options'])) {
        $form['menu']['menu_options']['#default_value'] = [];
      }
      if ($form['language']) {
        $form['language'] += [
          '#description' => "<i>" . $this->t('Field(s) will be/are disabled when the "Apply default config" checkbox is set.') . "</i>",
          '#states' => [
            'disabled' => [
              ':input[name="copy_default_config"]' => [
                'checked' => TRUE,
              ],
            ],
          ],
        ];
      }
      array_unshift($form['actions']['save_continue']['#submit'], 'openfed_administration_node_type_add_form_submit');
    }
  }

}
