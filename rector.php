<?php

declare(strict_types=1);

use DrupalRector\Drupal10\Rector\Deprecation\AnnotationToAttributeRector;
use DrupalRector\Drupal10\Rector\ValueObject\AnnotationToAttributeConfiguration;
use DrupalRector\Set\DrupalSetProvider;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
  ->withPaths([
    __DIR__ . '/modules/openfed_features',
  ])
  ->withPreparedSets(typeDeclarations: TRUE)
  ->withSetProviders(DrupalSetProvider::class)
  ->withComposerBased(twig: TRUE, phpunit: TRUE, symfony: TRUE, drupal: TRUE)
  ->withConfiguredRule(AnnotationToAttributeRector::class, [
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'Block', 'Drupal\Core\Block\Attribute\Block'),
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'FieldType', 'Drupal\Core\Field\Attribute\FieldType'),
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'FieldWidget', 'Drupal\Core\Field\Attribute\FieldWidget'),
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'FieldFormatter', 'Drupal\Core\Field\Attribute\FieldFormatter'),
    new AnnotationToAttributeConfiguration('11.1.0', '12.0.0', 'ConfigEntityType', 'Drupal\Core\Entity\Attribute\ConfigEntityType'),
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'Constraint', 'Drupal\Core\Validation\Attribute\Constraint'),
    new AnnotationToAttributeConfiguration('10.2.0', '12.0.0', 'ViewsField', 'Drupal\views\Attribute\ViewsField'),
    new AnnotationToAttributeConfiguration('10.3.0', '12.0.0', 'FormElement', 'Drupal\Core\Render\Attribute\FormElement'),
    new AnnotationToAttributeConfiguration('10.3.0', '12.0.0', 'FormElementBase', 'Drupal\Core\Render\Attribute\FormElement'),
  ]);
