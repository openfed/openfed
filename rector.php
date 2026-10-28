<?php

declare(strict_types=1);

use DrupalRector\Set\DrupalSetProvider;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
  ->withPaths([
    __DIR__ . '/modules/openfed_features',
  ])
  ->withPreparedSets(typeDeclarations: TRUE)
  ->withSetProviders(DrupalSetProvider::class)
  ->withComposerBased(twig: TRUE, phpunit: TRUE, symfony: TRUE, drupal: TRUE);
