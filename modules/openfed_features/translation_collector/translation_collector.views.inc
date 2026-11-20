<?php

declare(strict_types=1);

/**
 * @file
 * Views integration for translation_collector.
 */

/**
 * Implements hook_views_data().
 */
function translation_collector_views_data(): array {
  $data = [];

  $data['translation_collector_strings']['table']['group'] = t('Translation collector');
  $data['translation_collector_strings']['table']['provider'] = 'translation_collector';
  $data['translation_collector_strings']['table']['base'] = [
    'field' => 'id',
    'title' => t('Translation collector strings'),
    'help' => t('Collected translation strings.'),
  ];

  $data['translation_collector_strings']['id'] = [
    'title' => t('ID'),
    'help' => t('Primary key.'),
    'field' => ['id' => 'numeric'],
    'filter' => ['id' => 'numeric'],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['source'] = [
    'title' => t('Source'),
    'help' => t('The source string.'),
    'field' => ['id' => 'standard'],
    'filter' => ['id' => 'string'],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['context'] = [
    'title' => t('Context'),
    'help' => t('The translation context.'),
    'field' => ['id' => 'standard'],
    'filter' => ['id' => 'string'],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['langcode'] = [
    'title' => t('Language code'),
    'help' => t('The language code.'),
    'field' => ['id' => 'standard'],
    'filter' => [
      'id' => 'in_operator',
      'options callback' => 'Drupal\\translation_collector\\Views\\TranslationCollectorViewsOptions::getDistinctOptions',
      'options arguments' => ['langcode'],
    ],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['is_translated'] = [
    'title' => t('Translated'),
    'help' => t('Whether a translation exists.'),
    'field' => ['id' => 'boolean'],
    'filter' => [
      'id' => 'boolean',
      'type' => 'yes-no',
    ],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['string_type'] = [
    'title' => t('Type'),
    'help' => t('The string type.'),
    'field' => ['id' => 'standard'],
    'filter' => [
      'id' => 'in_operator',
      'options callback' => 'Drupal\\translation_collector\\Views\\TranslationCollectorViewsOptions::getDistinctOptions',
      'options arguments' => ['string_type'],
    ],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['location'] = [
    'title' => t('Location'),
    'help' => t('Additional location information.'),
    'field' => ['id' => 'standard'],
    'filter' => ['id' => 'string'],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['url'] = [
    'title' => t('Last URL'),
    'help' => t('The last URL where this string was encountered.'),
    'field' => ['id' => 'standard'],
    'filter' => ['id' => 'string'],
    'sort' => ['id' => 'standard'],
  ];

  $data['translation_collector_strings']['last_seen'] = [
    'title' => t('Last seen'),
    'help' => t('Timestamp of last encounter.'),
    'field' => ['id' => 'date'],
    'filter' => ['id' => 'numeric'],
    'sort' => ['id' => 'standard'],
  ];

  return $data;
}
