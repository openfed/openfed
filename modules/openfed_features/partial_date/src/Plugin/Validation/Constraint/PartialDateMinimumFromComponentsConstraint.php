<?php

namespace Drupal\partial_date\Plugin\Validation\Constraint;

use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Validation\Attribute\Constraint as ConstraintAttribute;
use Symfony\Component\Validator\Constraint;

/**
 * Provides a constraint for the minimum from components of a partial date.
 */
#[ConstraintAttribute(
  id: 'PartialDateMinimumFromComponents',
  label: new TranslatableMarkup('Partial date minimum from components', [], ['context' => 'Validation']),
)]
class PartialDateMinimumFromComponentsConstraint extends Constraint {

}
