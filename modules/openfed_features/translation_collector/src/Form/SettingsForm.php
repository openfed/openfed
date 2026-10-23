<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Form;

use Drupal\Core\Condition\ConditionManager;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Configuration form for the translation inventory.
 */
final class SettingsForm extends ConfigFormBase {

  /**
   * Constructs a settings form.
   */
  public function __construct(
    ConfigFactoryInterface $configFactory,
    private readonly ConditionManager $conditionManager,
  ) {
    parent::__construct($configFactory);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container): self {
    return new self(
      $container->get('config.factory'),
      $container->get('plugin.manager.condition'),
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames(): array {
    return ['translation_collector.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId(): string {
    return 'translation_collector_settings';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state): array {
    $config = $this->config('translation_collector.settings');

    $form['enabled'] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Enable string collection'),
      '#description' => $this->t('When enabled, translatable strings are logged during page requests.'),
      '#default_value' => $config->get('enabled'),
    ];

    $role_condition = $this->conditionManager->createInstance('user_role', [
      'roles' => $config->get('roles') ?? [],
      'negate' => FALSE,
    ]);
    $role_condition_form = $role_condition->buildConfigurationForm([], $form_state);
    $form['roles'] = $role_condition_form['roles'];
    $form['roles']['#title'] = $this->t('Collect strings for these roles');
    $form['roles']['#description'] = $this->t('If no roles are selected, strings are collected for all users. Select specific roles (e.g. Anonymous) to limit collection.');

    $request_path_condition = $this->conditionManager->createInstance('request_path', [
      'pages' => implode("\n", $config->get('exclude_paths') ?? []),
      'negate' => FALSE,
    ]);
    $request_path_condition_form = $request_path_condition->buildConfigurationForm([], $form_state);
    $form['pages'] = $request_path_condition_form['pages'];
    $form['pages']['#title'] = $this->t('Exclude paths');
    $form['pages']['#description'] = $this->t("One path pattern per line. Uses Drupal request path matching with '*' wildcards. Use <front> for the front page. Examples:<br><code>/admin/*</code><br><code>/sites/default/files/*</code><br><code>/user/*</code>");

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state): void {
    $role_condition = $this->conditionManager->createInstance('user_role');
    $role_condition->validateConfigurationForm($form, $form_state);

    $request_path_condition = $this->conditionManager->createInstance('request_path');
    $request_path_condition->validateConfigurationForm($form, $form_state);

    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state): void {
    $roles = array_values(array_filter($form_state->getValue('roles')));
    $exclude_paths = array_values(array_filter(array_map('trim', explode("\n", $form_state->getValue('pages') ?? ''))));

    $this->config('translation_collector.settings')
      ->set('enabled', $form_state->getValue('enabled'))
      ->set('roles', $roles)
      ->set('exclude_paths', $exclude_paths)
      ->save();

    parent::submitForm($form, $form_state);
  }

}
