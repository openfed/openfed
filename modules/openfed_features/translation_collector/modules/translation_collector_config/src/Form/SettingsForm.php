<?php

declare(strict_types=1);

namespace Drupal\translation_collector_config\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Settings form for config prefix inclusion.
 */
final class SettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames(): array {
    return ['translation_collector_config.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId(): string {
    return 'translation_collector_config_settings';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state): array {
    $config = $this->config('translation_collector_config.settings');

    $form['include_config_prefixes'] = [
      '#type' => 'textarea',
      '#title' => $this->t('Include config prefixes (optional whitelist)'),
      '#description' => $this->t('One prefix per line. Cache-tag config names are always collected from rendered responses. When this list is populated, it only whitelists additional request-loaded config names from the config override collector. Examples:<br><code>node.type.</code><br><code>taxonomy.vocabulary.</code><br><code>views.view.</code>'),
      '#default_value' => implode("\n", $config->get('include_config_prefixes') ?? []),
    ];

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state): void {
    $include_config_prefixes = array_values(array_filter(array_map('trim', explode("\n", $form_state->getValue('include_config_prefixes') ?? ''))));

    $this->config('translation_collector_config.settings')
      ->set('include_config_prefixes', $include_config_prefixes)
      ->save();

    parent::submitForm($form, $form_state);
  }

}
