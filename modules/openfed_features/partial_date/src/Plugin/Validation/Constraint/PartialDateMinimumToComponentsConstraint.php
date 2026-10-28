<?php

namespace Drupal\partial_date\Plugin\Validation\Constraint;

use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Validation\Attribute\Constraint as ConstraintAttribute;
use Symfony\Component\Validator\Constraint;

/**
 * Provides a constraint for a valid partial to date.
 *
 * This only validates the "to" portion of a partial date range instead of the
 * entire range as it is used in combination with PartialDateConstraint instead
 * of replacing it.
 */
#[ConstraintAttribute(
  id: 'PartialDateMinimumToComponents',
  label: new TranslatableMarkup('Partial date minimum to components', [], ['context' => 'Validation']),
)]
class PartialDateMinimumToComponentsConstraint extends Constraint {

}
