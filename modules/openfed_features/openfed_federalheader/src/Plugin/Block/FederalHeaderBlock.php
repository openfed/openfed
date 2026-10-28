<?php

namespace Drupal\openfed_federalheader\Plugin\Block;

use Drupal\Core\Block\Attribute\Block;
use Drupal\Core\Block\BlockBase;
use Drupal\Core\StringTranslation\TranslatableMarkup;

/**
 * Provides a Federal header block.
 */
#[Block(
  id: 'federal_header_block',
  admin_label: new TranslatableMarkup('Federal header'),
)]
class FederalHeaderBlock extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build(): array {
    $langcode = \Drupal::languageManager()->getCurrentLanguage()->getId();
    return [
      '#theme' => 'federalheader_block',
      '#module_path' => base_path() . \Drupal::service('extension.list.module')->getPath('openfed_federalheader'),
      '#other_information' => t('Other information and services: <span><a href=":link">www.belgium.be</a></span>', [':link' => 'https://www.belgium.be/' . $langcode]),
      '#attached' => [
        'library' => [
          'openfed_federalheader/header',
        ],
      ],
    ];
  }

}
