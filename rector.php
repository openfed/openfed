<?php

declare(strict_types=1);

use DrupalRector\Services\DrupalRectorSettings;
use DrupalRector\Set\Drupal10SetList;
use DrupalRector\Set\Drupal11SetList;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->paths([__DIR__ . '/modules/openfed_features']);
    $rectorConfig->sets([
        Drupal10SetList::DRUPAL_10,
        Drupal11SetList::DRUPAL_11,
    ]);
    $rectorConfig->singleton(DrupalRectorSettings::class, static fn () => (new DrupalRectorSettings())
        ->disableBackwardCompatibility()
        ->setMinimumCoreVersionSupported('11.4.0')
    );
    $rectorConfig->autoloadPaths([
        __DIR__ . '/modules/openfed_features',
        __DIR__ . '/docroot/core',
        __DIR__ . '/docroot/modules',
        __DIR__ . '/docroot/profiles',
    ]);
    $rectorConfig->fileExtensions(['php', 'module', 'install', 'inc', 'profile', 'theme', 'engine']);
    $rectorConfig->importNames(true, false);
    $rectorConfig->importShortClasses(false);
};
