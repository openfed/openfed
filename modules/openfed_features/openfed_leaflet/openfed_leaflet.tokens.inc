<?php

/**
 * @file
 * Builds placeholder replacement maptiler tokens.
 */

use Drupal\Core\Hook\Attribute\LegacyHook;
use Drupal\openfed_leaflet\Hook\OpenfedLeafletTokensHooks;
use Drupal\Core\Render\BubbleableMetadata;

/**
 * Implements hook_token_info().
 */
#[LegacyHook]
function openfed_leaflet_token_info(): array {
  return \Drupal::service(OpenfedLeafletTokensHooks::class)->tokenInfo();
}

/**
 * Implements hook_tokens().
 */
#[LegacyHook]
function openfed_leaflet_tokens(string $type, array $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata): array {
  return \Drupal::service(OpenfedLeafletTokensHooks::class)->tokens($type, $tokens, $data, $options, $bubbleable_metadata);
}
