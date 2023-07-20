<?php

namespace OpenfedProject\composer;

use Composer\Script\Event;
use Drupal\Core\DrupalKernel;
use Symfony\Component\HttpFoundation\Request;

/**
 * A class to do several validations before updating to Openfed 12.x.
 *
 * This will help maintainers to do an informed update.
 *
 * This file is present in Openfed 11.2+ so composer can early call it in
 * Openfed 12 and make a check before having to update Openfed. As such,
 * this file is not supposed to be used by Openfed 11.1 and bellow.
 */
class OpenfedValidations {

  /**
   * Validates if Openfed can be updated to version 12.
   */
  public static function validateUpdate12(Event $event) {

    // This check will assure that other checks will be performed only if this
    // is a Drupal site, otherwise they will be ignored (like for first time
    // installations).
    if (!self::isDrupalSite()) {
      return;
    }

    // We should run the validations only on Openfed 11.2 when we're
    // updating from Openfed <= 11.1.
    if (!self::checkProjectVersion()) {
      return;
    }

    // Composer.json requires some manual updates, this will check if those
    // updates were done.
    // self::checkComposerFile();

    // Some modules were removed from Openfed 12 and they should be deleted
    // before updating to this version.
    // self::checkDeprecatedModules();

    // Twig Tweak module was updated so, if used, it should be checked for
    // compatibility issues.
    self::checkTwigTweak3Compatibility();
  }

  /**
   * Check if current site is a Drupal site.
   *
   * @return bool
   *   TRUE if drupal is bootstrapped.
   */
  private static function isDrupalSite() {
    $output = trim(shell_exec('drush status --field="Drupal bootstrap"'));
    if (empty($output)) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Checks if the current version is at least Openfed 11.2.
   *
   * @return bool
   *   Return true if current version is 11.2 or more, false otherwise.
   */
  private static function checkProjectVersion() {
    $composer_openfed = json_decode(file_get_contents('composer.openfed.json'), TRUE);
    $current_version = $composer_openfed['require']['openfed/openfed'];
    preg_match('/(?:[\d+\.?]+[a-zA-Z0-9-]*)/', $current_version, $matches);

    // If current version is dev, we should ignore version check.
    if (strpos($current_version, 'dev') !== FALSE) {
      return FALSE;
    }

    return version_compare($matches[0], '11.2.x', '>=');
  }

  /**
   * Checks if composer file was updated as it should.
   *
   * @throws \ErrorException
   *   Exception when composer.json is not up-to-date.
   */
  private static function checkComposerFile() {
    // We'll make sure that the composer merge is updated in the old composer
    // file.
    $composer_file = json_decode(file_get_contents('composer.json'), TRUE);
    $merged_composers = array_search('composer.libraries.json', $composer_file['extra']['merge-plugin']['require']);
    if (strpos($composer_file['require']['wikimedia/composer-merge-plugin'], '^1.') !== FALSE || $merged_composers !== FALSE) {
      throw new \ErrorException("Your composer.json doesn't seem to be up to date.");
    }
  }

  /**
   * Checks if deprecated modules are enabled and stops update if true.
   *
   * @throws \ErrorException
   *   Exception when deprecated modules are enabled.
   */
  private static function checkDeprecatedModules() {
    $modules_to_check = [
      'toolbar_themes',
      'sharemessage',
      'simple_gmap',
      'scheduled_updates',
      'field_default_token',
      'contact_storage_clear',
      'yamlform_clear',
      'features',
    ];
    foreach ($modules_to_check as $module) {
      $output = trim(shell_exec('drush pml --field="status" --filter="name~=#(' . $module . ')#i"'));
      if ($output == 'Enabled') {
        throw new \ErrorException("You can't proceed with Openfed update until you uninstall $module. See Openfed 12 release notes.");
      }
    }
  }

  /**
   * Checks if Twig Tweak is enabled.
   *
   * @return bool
   *   TRUE if twig is enabled.
   */
  private static function isTwigTweakEnabled() {
    $module = 'twig_tweak';
    $output = trim(shell_exec('drush pml --field="status" --filter="' . $module . '"'));
    if ($output == 'Enabled') {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Initiates Drupal container.
   *
   * @throws \Exception
   */
  private static function initDrupalContainer() {
    $autoloader = require_once getcwd() . '/docroot/autoload.php';
    $request = Request::createFromGlobals();
    $kernel = DrupalKernel::createFromRequest($request, $autoloader, 'prod');
    $kernel->boot();
    $kernel->preHandle($request);
    if (PHP_SAPI !== 'cli') {
      $request->setSession($kernel->getContainer()->get('session'));
    }
  }

  /**
   * Check template for Twig Tweak 3.x compatibility issues.
   *
   * See https://git.drupalcode.org/project/twig_tweak/-/blob/3.x/docs/migration-to-3.x.md.
   *
   * @throws \ErrorException
   *   Exception when twig tweak 3 compatibility fails.
   */
  private static function checkTwigTweak3Compatibility() {
    if (self::isTwigTweakEnabled()) {
      self::initDrupalContainer();

      // 1. Check for drupal_entity() and drupal_field() with second argument
      // as null or not present.
      $entityFieldSearch = shell_exec('find ./docroot/themes/ ./config/ -name "*.twig" | xargs grep -hiP "drupal_(entity|field)\([\'\"].*?[\'\"](,\s*null)?\)"');
      $entityFieldPattern = '/drupal_(entity|field)\([\'\"]([^,]*)[\'\"](,\s*null)?\)/';
      preg_match_all($entityFieldPattern, $entityFieldSearch, $entityFieldMatches);

      if (!empty($entityFieldMatches[0])) {
        throw new \ErrorException("In your theme, drupal_entity() or drupal_field() is used with the second argument as null or missing. Convert your theme to Twig Tweak 3.x before updating Openfed. See https://git.drupalcode.org/project/twig_tweak/-/blob/3.x/docs/migration-to-3.x.md.");
      }
    }
  }

}
