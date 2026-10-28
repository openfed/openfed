<?php

namespace Drupal\openfed_file_entity\Hook;

use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for openfed_file_entity.
 */
class OpenfedFileEntityHooks {

  /**
   * Implements hook_modules_installed().
   */
  #[Hook('modules_installed')]
  public function modulesInstalled($modules, $is_syncing): void {
    if (in_array('file_entity', $modules)) {
      $view_id = 'file_entity_files';
      /** @var \Drupal\views\Entity\View $view */
      if ($view = \Drupal::entityTypeManager()->getStorage('view')->load($view_id)) {
        // We disable the file_entity_files view to avoid confusion with the
        // files overview from core.
        $view->setStatus(FALSE);
        $view->save();
      }
    }
  }

}
