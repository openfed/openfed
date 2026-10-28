<?php

namespace Drupal\openfed_leaflet\Hook;

use Drupal\Core\Render\BubbleableMetadata;
use Drupal\openfed_leaflet\TokenOperations;
use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for openfed_leaflet.
 */
class OpenfedLeafletTokensHooks {

  /**
   * Implements hook_token_info().
   */
  #[Hook('token_info')]
  public function tokenInfo(): array {
    return \Drupal::classResolver()->getInstanceFromDefinition(TokenOperations::class)->tokenInfo();
  }

  /**
   * Implements hook_tokens().
   */
  #[Hook('tokens')]
  public function tokens(string $type, array $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata): array {
    return \Drupal::classResolver()->getInstanceFromDefinition(TokenOperations::class)->tokens($type, $tokens, $data, $options, $bubbleable_metadata);
  }

}
