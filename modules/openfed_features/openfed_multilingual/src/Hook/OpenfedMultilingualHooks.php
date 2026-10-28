<?php

namespace Drupal\openfed_multilingual\Hook;

use Drupal\Core\Url;
use Drupal\Core\Hook\Attribute\Hook;

/**
 * Hook implementations for openfed_multilingual.
 */
class OpenfedMultilingualHooks {

  /**
   * Implements hook_language_switch_links_alter().
   *
   * This will override language switch block links, removing the link and
   * setting a "disabled" class on non-translated content.
   */
  #[Hook('language_switch_links_alter')]
  public function languageSwitchLinksAlter(array &$links, $type, $path): void {
    /** @var Drupal\node\Entity\Node $node */
    if ($node = \Drupal::routeMatch()->getParameter('node')) {
      foreach ($links as $langcode => $link) {
        if ($node && !array_key_exists($langcode, $node->getTranslationLanguages(TRUE)) || $node->getTranslation($langcode) && !$node->getTranslation($langcode)
          ->access('view')) {
          // Set the URL to a non-link to disable the language switch for
          // untranslated content.
          $links[$langcode]['url'] = new Url('<nolink>');
          // And do something with attributes (eg. add class).
          $links[$langcode]['attributes']['class'][] = 'disabled';
        }
      }
    }
  }

}
