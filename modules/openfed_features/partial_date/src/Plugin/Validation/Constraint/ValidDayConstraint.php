<?php

namespace Drupal\partial_date\Plugin\Validation\Constraint;

use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Validation\Attribute\Constraint as ConstraintAttribute;
use Symfony\Component\Validator\Constraint;

/**
 * Provides a constraint for a valid day.
 */
#[ConstraintAttribute(
  id: 'ValidDay',
  label: new TranslatableMarkup('Valid day', [], ['context' => 'Validation']),
)]
class ValidDayConstraint extends Constraint {

  /**
   * The name of the property that holds the partial date components.
   *
   * @var string
   */
  public $property;

}
