<?php

namespace Drupal\openfed_conditional_fields_content_translation\Hook;

use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for openfed_conditional_fields_content_translation.
 */
class OpenfedConditionalFieldsContentTranslationHooks {

  /**
   * Implements hook_entity_type_alter().
   */
  #[Hook('entity_type_alter')]
  public function entityTypeAlter(array &$entity_types): void {
    foreach ($entity_types as $entity_type) {
      // Replaces the default content translation handler with our custom one
      // that restores access for conditional field dependents on translation
      // forms.
      if ($entity_type->isTranslatable() && $entity_type->hasHandlerClass('translation')) {
        $entity_type->setHandlerClass('translation', 'Drupal\openfed_conditional_fields_content_translation\ContentTranslationHandler');
      }
    }
  }

}
