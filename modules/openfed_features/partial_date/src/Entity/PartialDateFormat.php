<?php

namespace Drupal\partial_date\Entity;

use Drupal\Component\Utility\SortArray;
use Drupal\Core\Config\Entity\ConfigEntityBase;
use Drupal\Core\Entity\Attribute\ConfigEntityType;
use Drupal\Core\StringTranslation\TranslatableMarkup;

/**
 * Defines the FormatType config entity.
 *
 * @author CosminFr
 */
#[ConfigEntityType(
  id: 'partial_date_format',
  label: new TranslatableMarkup('Partial date format'),
  handlers: [
    'list_builder' => 'Drupal\partial_date\Controller\PartialDateFormatListBuilder',
    'form' => [
      'add' => 'Drupal\partial_date\Form\PartialDateFormatEditForm',
      'edit' => 'Drupal\partial_date\Form\PartialDateFormatEditForm',
      'delete' => 'Drupal\Core\Entity\EntityDeleteForm',
    ],
    'route_provider' => [
      'html' => 'Drupal\Core\Entity\Routing\DefaultHtmlRouteProvider',
    ],
  ],
  config_prefix: 'format',
  admin_permission: 'administer site configuration',
  entity_keys: ['id' => 'id', 'label' => 'label'],
  links: [
    'collection' => '/admin/config/regional/partial-date-format',
    'add-form' => '/admin/config/regional/partial-date-format/add',
    'edit-form' => '/admin/config/regional/partial-date-format/manage/{partial_date_format}',
    'delete-form' => '/admin/config/regional/partial-date-format/manage/{partial_date_format}/delete',
  ],
  config_export: ['id', 'label', 'meridiem', 'year_designation', 'display', 'components', 'separator'],
)]
class PartialDateFormat extends ConfigEntityBase implements PartialDateFormatInterface {

  /**
   * The ID of the partial date format.
   *
   * @var string
   */
  protected $id;

  /**
   * The meridiem of the partial date format.
   *
   * @var string
   */
  protected $meridiem = 'a';

  /**
   * The year designation of the partial date format.
   *
   * This controls how year designation is handled:
   *   1BC = 1BCE = -1 and 1AD = 1CE = 1.
   *
   * @var string
   */
  protected $year_designation = 'ce';

  /**
   * The display type of the partial date format.
   *
   * @var array
   */
  protected array $display = [
    'year' => 'estimate_label',
    'month' => 'estimate_label',
    'day' => 'estimate_label',
    'hour' => 'estimate_label',
    'minute' => 'estimate_label',
    'second' => 'none',
    'timezone' => 'none',
  ];

  /**
   * The components of the partial date format.
   *
   * @var array
   */
  protected array $components = [
    'year' => ['format' => 'y-ce', 'empty' => '', 'weight' => 0],
    'month' => ['format' => 'm', 'empty' => '', 'weight' => 1],
    'day' => ['format' => 'j', 'empty' => '', 'weight' => 2],
    'hour' => ['format' => 'H', 'empty' => '', 'weight' => 3],
    'minute' => ['format' => 'i', 'empty' => '', 'weight' => 4],
    'second' => ['format' => 's', 'empty' => '', 'weight' => 5],
    'timezone' => ['format' => 'T', 'empty' => '', 'weight' => 6],
    'approx' => ['value' => '', 'weight' => -1],
    'c1' => ['value' => '', 'weight' => 7],
    'c2' => ['value' => '', 'weight' => 8],
    'c3' => ['value' => '', 'weight' => 9],
  ];

  /**
   * The separators of the partial date format.
   *
   * @var array
   *   An array with specific separators.
   */
  protected array $separator = [
    'date' => '/',
    'time' => ':',
    'datetime' => ' ',
    'range' => ' to ',
    'other' => ' ',
  ];

  /**
   * {@inheritdoc}
   */
  public function getMeridiem() {
    return $this->get('meridiem');
  }

  /**
   * {@inheritdoc}
   */
  public function getYearDesignation() {
    return $this->get('year_designation');
  }

  /**
   * {@inheritdoc}
   */
  public function getDisplay($component) {
    assert('in_array($component, ["year", "month", "day", "hour", "minute", "second", "timezone"], TRUE)');
    return $this->get('display')[$component];
  }

  /**
   * {@inheritdoc}
   */
  public function getComponent($component_name) {
    assert('in_array($component, ["year", "month", "day", "hour", "minute", "second", "timezone", "approx", "c1", "c2", "c3"], TRUE)');
    return $this->get('components')[$component_name];
  }

  /**
   * {@inheritdoc}
   */
  public function getComponents() {
    $components = $this->get('components');
    uasort($components, [SortArray::class, 'sortByWeightElement']);
    return $components;
  }

  /**
   * {@inheritdoc}
   */
  public function getSeparator($component) {
    assert('in_array($component, ["date", "time", "datetime", "range", "other"], TRUE)');
    return $this->get('separator')[$component];
  }

}
