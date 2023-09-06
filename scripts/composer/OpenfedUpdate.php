<?php

namespace OpenfedProject\composer;

use Composer\Script\Event;
use Drupal\Component\Utility\NestedArray;
use Drupal\Core\DrupalKernel;
use Symfony\Component\HttpFoundation\Request;

/**
 * A class to update composer files to the newer version of Openfed.
 */
class OpenfedUpdate {

  /**
   * Openfed project github URL.
   *
   * @var string
   */
  protected static $openfedRepo = 'https://github.com/openfed/openfed-project';

  /**
   * Openfed project github archive tags URL.
   *
   * @var string
   */
  protected static $openfedZip = 'https://github.com/openfed/openfed-project/archive/refs/tags/';

  /**
   * The latest Openfed version.
   *
   * @var string
   */
  protected static $latestOpenfedVersion;

  /**
   * @var string
   */
  protected static $currentOpenfedVersion;

  /**
   * Update current openfed project files.
   *
   * @param \Composer\Script\Event $event
   *   The composer script event.
   */
  public static function update(Event $event) {
    self::getCurrentVersion();
    self::setLatestOpenfedVersion();

    // Check if there's a new Openfed version and update if so.
    if (self::newVersionExists()) {
      self::overwriteFiles();
    }
  }

  /**
   * Update current openfed project files.
   *
   * @param \Composer\Script\Event $event
   *   The composer script event.
   */
  public static function upgrade(Event $event) {
    self::getCurrentVersion();
    self::setLatestOpenfedVersion(true);

    // Check if there's a new Openfed version and update if so.
    if (self::newVersionExists()) {
      self::overwriteFiles();
    }
  }

  private static function overwriteFiles() {
    echo "\n\n---- Project files will be updated to Openfed version " . self::$latestOpenfedVersion . "\n";

    $url = self::$openfedZip . self::$latestOpenfedVersion . '.zip';
    $zipFile = self::$latestOpenfedVersion . '.zip';
    $extractPath = self::$latestOpenfedVersion;

    $zip_resource = fopen($zipFile, "w");

    self::initDrupalContainer();
    /** @var GuzzleHttp\Psr\Response $response */
    $response = \Drupal::httpClient()->get($url, ['sink' => $zip_resource]);

    if (!$response) {
      echo "Error :- Cannot connect.";
    }

    $zip = new \ZipArchive();
    if ($zip->open($zipFile) != "true") {
      throw new \ErrorException("Error :- Unable to open the Zip File.");
    }

    $zip->extractTo($extractPath);
    $zip->close();

    // We'll merge the contents of the zip archive, but we'll ignore some
    // files. Those files will be removed/unlink.
    unlink($zipFile);
    unlink($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . '.gitignore');
    unlink($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . 'README.md');

    // Composer.json and composer.patches.json, if exists, will be merged.
    // This is a best effort merge and should be manually confirmed.
    self::mergeComposer($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . 'composer.json', '.' . DIRECTORY_SEPARATOR . 'composer.json');
    unlink($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . 'composer.json');
    self::mergeComposer($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . 'composer.patches.json', '.' . DIRECTORY_SEPARATOR . 'composer.patches.json');
    unlink($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR . 'composer.patches.json');

    // All the remaining files will be copied as is (i.e.
    // composer.openfed.json)
    self::recurseCopy($extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion, '.');
    self::deleteDirectory($extractPath);

    echo "---- Files updated. You still have to check your composer.json manually.\n\n";
  }

  /**
   * Merge composer files, keeping existing values.
   *
   * @param string $new
   *   New composer file, from github repo.
   * @param string $old
   *   Old composer file, the one in the filesystem.
   */
  private static function mergeComposer($new, $old) {
    $new_composer = json_decode(file_get_contents($new), TRUE);
    $old_composer = json_decode(file_get_contents($old), TRUE);

    $updated_composer = NestedArray::mergeDeepArray([
      $old_composer,
      $new_composer,
    ], TRUE);
    file_put_contents($old, json_encode($updated_composer, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES));
  }

  /**
   * Copy files from one dir to another.
   *
   * @param string $src
   *   Source directory.
   * @param string $dst
   *   Destination directory.
   */
  private static function recurseCopy($src, $dst) {
    $dir = opendir($src);
    @mkdir($dst);
    while (FALSE !== ($file = readdir($dir))) {
      if (($file != '.') && ($file != '..')) {
        if (is_dir($src . DIRECTORY_SEPARATOR . $file)) {
          self::recurseCopy($src . DIRECTORY_SEPARATOR . $file, $dst . DIRECTORY_SEPARATOR . $file);
        }
        else {
          copy($src . DIRECTORY_SEPARATOR . $file, $dst . DIRECTORY_SEPARATOR . $file);
        }
      }
    }
    closedir($dir);
  }

  /**
   * Delete directory from filesystem.
   *
   * @param string $dir
   *   The directory to remove.
   *
   * @return bool
   *   True on success, false otherwise.
   */
  public static function deleteDirectory($dir) {
    if (!file_exists($dir)) {
      return TRUE;
    }
    if (!is_dir($dir)) {
      return unlink($dir);
    }
    foreach (scandir($dir) as $item) {
      if ($item == '.' || $item == '..') {
        continue;
      }
      if (!self::deleteDirectory($dir . DIRECTORY_SEPARATOR . $item)) {
        return FALSE;
      }
    }
    return rmdir($dir);
  }

  /**
   * Checks if there's a more recent version of Openfed.
   *
   * @return bool
   *   True if there's a new version, false otherwise.
   */
  private static function newVersionExists() {
    $current_version = self::$currentOpenfedVersion;

    // If current version is dev, we don't need to check if there's a newer
    // version.
    if (strpos($current_version, 'dev') !== FALSE) {
      return FALSE;
    }

    return version_compare(self::$latestOpenfedVersion, $current_version, '>');
  }

  /**
   * Checks if there's a more recent version of Openfed.
   *
   * @return bool
   *   True if there's a new version, false otherwise.
   */
  private static function getCurrentVersion() {
    $composer_openfed = json_decode(file_get_contents('composer.openfed.json'), TRUE);
    $current_version = $composer_openfed['require']['openfed/openfed'];

    self::$currentOpenfedVersion = $current_version;
  }

  /**
   * Set the latest openfed version variable.
   */
  private static function setLatestOpenfedVersion($upgrade = false) {
    $available_openfed_version = $latest_openfed_version = explode("\n", trim(shell_exec("git -c 'versionsort.suffix=-' ls-remote --tags --sort='-v:refname' " . self::$openfedRepo . " | cut -d '/' -f 3 | grep -v -")));

    // If this is an upgrade, we don't need to filter by the current major
    // version.
    if (!$upgrade) {
      // Get the current major version.
      $current_major_version = strstr(self::$currentOpenfedVersion,'.', true) . '.';

      // On updates we need to filter openfed versions that match the current
      // major version.
      $latest_openfed_version = array_filter($available_openfed_version, function($version) use ($current_major_version) {
        return (strpos($version, $current_major_version) === 0 ? true : false);
      });
    }

    self::$latestOpenfedVersion = current($latest_openfed_version);
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

}
