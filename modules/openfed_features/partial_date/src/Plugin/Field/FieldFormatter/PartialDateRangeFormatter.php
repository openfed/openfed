<?php

namespace Drupal\partial_date\Plugin\Field\FieldFormatter;

use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Form\FormStateInterface;

/**
 * Plugin implementation for Partial Date formatter.
 *
 * @FieldFormatter(
 *   id = "partial_date_range_formatter",
 *   module = "partial_date_range",
 *   label = @Translation("Default"),
 *   description = @Translation("Display partial date range."),
 *   field_types = {"partial_date_range"},
 *   quickedit = {
 *     "editor" = "disabled",
 *   },
 * )
 */
class PartialDateRangeFormatter extends PartialDateFormatter {

  /**
   * {@inheritdoc}
   */
  public static function defaultSettings(): array {
    return parent::defaultSettings() + [
      'range_reduce' => TRUE,
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function settingsForm(array $form, FormStateInterface $form_state): array {
    $elements = parent::settingsForm($form, $form_state);

    $elements['range_reduce'] = [
      '#type' => 'checkbox',
      '#title' => t('Reduce common values from range display'),
      '#default_value' => $this->getSetting('range_reduce'),
      '#description' => t('This setting allows a simplified display for range values. For example "2015 Jan-Sep" instead of full specification "2015 Jan-2015 Sep"'),
    ];
    return $elements;
  }

  /**
   * {@inheritdoc}
   */
  public function viewElements(FieldItemListInterface $items, $langcode): array {
    $element = [];
    foreach ($items as $delta => $item) {
      $override = $this->getTextOverride($item);
      if ($override) {
        $element[$delta] = ['#markup' => $override];
      }
      else {
        $from = $item->from;
        $to = $item->to;
        if ($this->getSetting('range_reduce')) {
          $this->reduceRange($from, $to);
        }

        if ($from && $to) {
          $element[$delta] = [
            '#theme' => 'partial_date_range',
            '#from' => $from,
            '#to' => $to,
            '#format' => $this->getFormat(),
          ];
        }
        elseif ($from) {
          $element[$delta] = [
            '#theme' => 'partial_date',
            '#date' => $from,
            '#format' => $this->getFormat(),
          ];
        }
        elseif ($to) {
          $element[$delta] = [
            '#theme' => 'partial_date',
            '#date' => $from,
            '#format' => $this->getFormat(),
          ];
        }
        else {
          $element[$delta] = ['#markup' => $this->t('N/A')];
        }
      }
    }
    return $element;
  }

  /**
   * Reduce identical range components to simplify the display.
   *
   * The format determines which side to clear based on the display order of
   * year, month, and day. For example, "2015 Jun to 2015 Sep" becomes
   * "2015 Jun to Sep", while "Jun 2015 to Sep 2015" becomes "Jun to Sep 2015".
   *
   * Reduction rules:
   * - If all date components match, clear the right-hand date components and
   *   stop without reducing time components.
   * - Otherwise, if either date has time components, stop to avoid mixing date
   *   and time reduction.
   * - If the years differ, stop. Otherwise, use the format order:
   *   - YYYY / MM: clear the right-hand year (2015 Jun - Sep).
   *   - MM / YYYY: clear the left-hand year (Jun - Sep 2015).
   * - If the months also match, use the format order:
   *   - MM / DD: clear the right-hand month (Jun 15 - 25).
   *   - DD / MM: clear the left-hand month (15 - 25 Jun).
   */
  protected function reduceRange(array &$from, array &$to) {
    $sameDate = ($from['year'] == $to['year']) &&
                ($from['month'] == $to['month']) &&
                ($from['day'] == $to['day']);
    if ($sameDate) {
      $to['year']  = NULL;
      $to['month'] = NULL;
      $to['day']   = NULL;
      return;
    }
    $hasTime = isset($from['hour'])   || isset($to['hour']) ||
                isset($from['minute']) || isset($to['minute']) ||
                isset($from['second']) || isset($to['second']);
    if ($hasTime) {
      return;
    }
    if ($from['year'] == $to['year']) {
      $format = $this->getFormat();
      $year_weight = $format->getComponent('year')['weight'];
      $month_weight = $format->getComponent('month')['weight'];
      // If "year before month" compress right (otherwise left)
      if ($year_weight <= $month_weight) {
        $to['year'] = NULL;
      }
      else {
        $from['year'] = NULL;
      }

      if ($from['month'] == $to['month']) {
        $day_weight = $format->getComponent('month')['weight'];
        // If "month before day" compress right (otherwise left)
        if ($month_weight <= $day_weight) {
          $to['month'] = NULL;
        }
        else {
          $from['month'] = NULL;
        }
      }
    }
  }

}
