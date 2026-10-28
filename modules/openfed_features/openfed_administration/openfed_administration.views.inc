<?php

/**
 * @file
 * Provide Views data for the Openfed Administration module.
 *
 * @ingroup views_module_handlers
 */

use Drupal\Core\Hook\Attribute\LegacyHook;
use Drupal\openfed_administration\Hook\OpenfedAdministrationViewsHooks;

/**
 * @file
 * Provide Views fields to ease content administration.
 */

/**
 * Implements hook_views_data_alter().
 */
#[LegacyHook]
function openfed_administration_views_data_alter(array &$data): void {
  \Drupal::service(OpenfedAdministrationViewsHooks::class)->viewsDataAlter($data);
}
