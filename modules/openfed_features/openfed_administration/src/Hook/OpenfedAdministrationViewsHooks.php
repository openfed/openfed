<?php

namespace Drupal\openfed_administration\Hook;

use Drupal\Core\Hook\Attribute\Hook;
use Drupal\Core\StringTranslation\StringTranslationTrait;

/**
 * Hook implementations for openfed_administration.
 */
class OpenfedAdministrationViewsHooks {

  use StringTranslationTrait;

  /**
   * Implements hook_views_data_alter().
   */
  #[Hook('views_data_alter')]
  public function viewsDataAlter(array &$data): void {
    $entities = \Drupal::entityTypeManager()->getDefinitions();
    foreach ($entities as $entity => $entity_definition) {
      $data[$entity . '_field_data']['entity_translations'] = [
        'title' => $this->t('@entity translation links', [
          '@entity' => ucfirst($entity),
        ]),
        'field' => [
          'title' => $this->t('@entity translation links', [
            '@entity' => ucfirst($entity),
          ]),
          'help' => $this->t('Displays a list of translations for each entity, linking to the edit form.'),
          'id' => 'entity_translations',
        ],
      ];
    }
  }

}
