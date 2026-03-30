<?php

/**
 * @file
 * Builds placeholder replacement maptiler tokens.
 */

use Drupal\Core\Render\BubbleableMetadata;
use Drupal\openfed_leaflet\TokenOperations;

/**
 * Implements hook_token_info().
 */
function openfed_leaflet_token_info() {
  return \Drupal::classResolver()
    ->getInstanceFromDefinition(TokenOperations::class)
    ->tokenInfo();
}

/**
 * Implements hook_tokens().
 */
function openfed_leaflet_tokens($type, $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata) {
  return \Drupal::classResolver()
    ->getInstanceFromDefinition(TokenOperations::class)
    ->tokens($type, $tokens, $data, $options, $bubbleable_metadata);
}
