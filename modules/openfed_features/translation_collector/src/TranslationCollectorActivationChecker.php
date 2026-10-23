<?php

declare(strict_types=1);

namespace Drupal\translation_collector;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Condition\ConditionManager;
use Drupal\Core\Session\AccountProxyInterface;

/**
 * Shared logic to determine whether collection is active for the current request.
 */
final class TranslationCollectorActivationChecker {

  /**
   * Cached result.
   */
  private ?bool $active = NULL;

  /**
   * Re-entrancy guard for nested isActive() calls.
   */
  private bool $evaluating = FALSE;

  /**
   * Constructs a TranslationCollectorActivationChecker.
   */
  public function __construct(
    private readonly ConfigFactoryInterface $configFactory,
    private readonly AccountProxyInterface $currentUser,
    private readonly ConditionManager $conditionManager,
  ) {}

  /**
   * Determines whether collection is active.
   */
  public function isActive(): bool {
    if ($this->active !== NULL) {
      return $this->active;
    }

    // Skip collection for CLI-style executions (Drush, cron, tests, scripts).
    if (PHP_SAPI === 'cli' || PHP_SAPI === 'phpdbg') {
      $this->active = FALSE;
      return FALSE;
    }

    // request_path evaluation may indirectly trigger config loads that call
    // isActive() again (via config overrides). Prevent recursive loops.
    if ($this->evaluating) {
      return FALSE;
    }

    $this->evaluating = TRUE;
    try {
      $config = $this->configFactory->get('translation_collector.settings');
      if (!$config->get('enabled')) {
        $this->active = FALSE;
        return FALSE;
      }

      $allowed_roles = array_values(array_filter($config->get('roles') ?? []));
      if (!empty($allowed_roles)) {
        $role_condition = $this->conditionManager->createInstance('user_role', [
          'roles' => $allowed_roles,
          'negate' => FALSE,
        ]);
        $role_condition->setContextValue('user', $this->currentUser);
        if (!$role_condition->execute()) {
          $this->active = FALSE;
          return FALSE;
        }
      }

      $exclude_paths = array_values(array_filter(array_map('trim', $config->get('exclude_paths') ?? [])));
      if (!empty($exclude_paths)) {
        $condition = $this->conditionManager->createInstance('request_path', [
          'pages' => implode("\n", $exclude_paths),
          'negate' => FALSE,
        ]);
        if ($condition->execute()) {
          $this->active = FALSE;
          return FALSE;
        }
      }

      $this->active = TRUE;
      return TRUE;
    }
    finally {
      $this->evaluating = FALSE;
    }
  }

}
