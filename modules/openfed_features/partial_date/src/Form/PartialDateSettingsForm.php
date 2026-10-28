<?php

namespace Drupal\partial_date\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Configuration form for Partial Date module and field settings.
 */
class PartialDateSettingsForm extends ConfigFormBase {
  const string SETTINGS = 'partial_date.settings';

  /**
   * {@inheritdoc}
   */
  public function getFormId(): string {
    return 'partial_date_settings_form';
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames(): array {
    return [self::SETTINGS];
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config(self::SETTINGS);

    // Only show setting you actually want users to edit.
    // @todo these are just for demo, probably should not be modified by users.
    $form['txt_inline_styles'] = [
      '#type' => 'textfield',
      '#title' => 'Text inline styles',
      '#default_value' => $config->get('partial_date_component_field_txt_inline_styles'),
    ];
    $form['inline_styles'] = [
      '#type' => 'textfield',
      '#title' => 'Inline styles',
      '#default_value' => $config->get('partial_date_component_field_inline_styles'),
    ];

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state): void {
    $config = $this->config(self::SETTINGS);
    // Save any changes.
    $config->set('partial_date_component_field_txt_inline_styles', $form_state->getValue('txt_inline_styles'));
    $config->set('partial_date_component_field_inline_styles', $form_state->getValue('inline_styles'));
    $config->save();
    parent::submitForm($form, $form_state);
  }

}
