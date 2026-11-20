<?php

declare(strict_types=1);

namespace OpenfedProject\composer;

use Composer\Script\Event;
use Drupal\Component\Utility\NestedArray;
use RuntimeException;
use stdClass;

/**
 * A class to update composer files to the newer version of Openfed.
 */
class OpenfedUpdate {

  private const OPENFED_14_CONSTRAINT = '/^14\.\d+\.(?:\*(?:@alpha)?|\d+(?:-(?:alpha|beta|rc)\d+)?)$/iD';

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
    $arguments = $event->getArguments();
    if (array_diff($arguments, ['--force'])) {
      throw new RuntimeException('Usage: composer run-script project-upgrade -- [--force]');
    }

    self::getCurrentVersion();
    self::setLatestOpenfedVersion(true);
    self::overwriteFiles(TRUE, in_array('--force', $arguments, TRUE));
  }

  private static function prepareOpenfed14(array $defaults, string $target, bool $force): void {
    self::checkOpenfed14Source(self::$currentOpenfedVersion, $target, $force);
    echo "Target Openfed constraint: $target\n";
    $changes = [];
    foreach (['composer.json', 'composer.openfed.json', 'composer.patches.json'] as $name) {
      $files[$name] = self::decodeManifest(self::readContents($name), $name);
      $before[$name] = json_encode($files[$name], JSON_THROW_ON_ERROR);
    }
    self::migrateOpenfed14($files, $defaults, $target);

    foreach ($files as $name => $data) {
      if ($before[$name] !== json_encode($data, JSON_THROW_ON_ERROR)) {
        if (!is_writable($name)) {
          throw new RuntimeException("$name is not writable; no files were changed.");
        }
        $changes[$name] = json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_THROW_ON_ERROR) . "\n";
      }
    }
    foreach ($changes as $name => $contents) {
      if (file_put_contents($name, $contents, LOCK_EX) !== strlen($contents)) {
        throw new RuntimeException("Cannot write $name. Check git diff before retrying.");
      }
    }
    echo "Review the Composer changes before running composer update -W.\n";
  }

  private static function readContents(string $path): string {
    $context = stream_context_create(['http' => ['timeout' => 15]]);
    $contents = @file_get_contents($path, FALSE, $context);
    if ($contents === FALSE) {
      throw new RuntimeException("Cannot read $path.");
    }
    return $contents;
  }

  private static function decodeManifest(string $contents, string $name): stdClass {
    $manifest = json_decode($contents, FALSE, 512, JSON_THROW_ON_ERROR);
    if (!$manifest instanceof stdClass) {
      throw new RuntimeException("$name must contain a JSON object.");
    }
    return $manifest;
  }

  private static function checkOpenfed14Source(mixed $current, string $target, bool $force): void {
    if ($force) {
      return;
    }
    if (!is_string($current) || (!preg_match('/^13\.6\.(?:\*|\d+)$/D', $current) && !preg_match(self::OPENFED_14_CONSTRAINT, $current))) {
      throw new RuntimeException('Unsupported Openfed constraint: ' . json_encode($current) . '. Use --force to replace it anyway.');
    }
    // A wildcard names a release series, not a version.
    $targetVersion = $target;
    $currentVersion = $current;
    if (str_contains($target, '*') || str_contains($current, '*')) {
      $targetVersion = implode('.', array_slice(explode('.', $target), 0, 2));
      $currentVersion = implode('.', array_slice(explode('.', $current), 0, 2));
    }
    if (version_compare($targetVersion, $currentVersion, '<')) {
      throw new RuntimeException("Target $target would downgrade Openfed from $current. Use --force to proceed anyway.");
    }
  }

  private static function readTemplateManifest(\ZipArchive $zip, string $directory, string $name): stdClass {
    $contents = $zip->getFromName("$directory/$name");
    if ($contents === FALSE) {
      throw new RuntimeException("The project template is missing $name.");
    }
    return self::decodeManifest($contents, $name);
  }

  private static function withTemplateArchive(string $tag, callable $useArchive): mixed {
    $url = self::$openfedZip . $tag . '.zip';
    $archive = tmpfile();
    if ($archive === FALSE) {
      throw new RuntimeException('Cannot create temporary template archive.');
    }
    try {
      $contents = self::readContents($url);
      if (fwrite($archive, $contents) !== strlen($contents)) {
        throw new RuntimeException('Cannot write the downloaded project template.');
      }
      $zip = new \ZipArchive();
      if ($zip->open(stream_get_meta_data($archive)['uri'], \ZipArchive::RDONLY) !== TRUE) {
        throw new RuntimeException("Cannot open the openfed-project $tag archive.");
      }
      try {
        return $useArchive($zip);
      }
      finally {
        $zip->close();
      }
    }
    finally {
      fclose($archive);
    }
  }

  private static function objectSection(stdClass $data, string $key): stdClass {
    if (!property_exists($data, $key)) {
      $data->$key = new stdClass();
    }
    if (!$data->$key instanceof stdClass) {
      throw new RuntimeException("$key must be an object; review this configuration manually.");
    }
    return $data->$key;
  }

  private static function setMigrationValue(stdClass $data, string $key, mixed $value): void {
    if (property_exists($data, $key) && $data->$key !== $value) {
      throw new RuntimeException("Conflicting $key setting; review this configuration manually.");
    }
    $data->$key = $value;
  }

  private static function migrateOpenfed14(array $files, array $defaults, string $target): void {
    $root = $files['composer.json'];
    $openfed = $files['composer.openfed.json'];
    $template = $defaults['composer.json'];
    $templateOpenfed = $defaults['composer.openfed.json'];
    $patchDefaults = $template->extra->{'composer-patches'} ?? NULL;
    $minimumPhp = $template->config->platform->php ?? NULL;
    if (!$patchDefaults instanceof stdClass || !is_string($minimumPhp)) {
      throw new RuntimeException("Expected an openfed-project template for Openfed $target with patch and PHP defaults.");
    }
    if (isset($root->require->{'openfed/openfed'})) {
      throw new RuntimeException('Openfed is also required in composer.json; resolve the duplicate constraint first.');
    }
    $rootExtra = self::objectSection($root, 'extra');
    $merge = self::objectSection($rootExtra, 'merge-plugin');
    if (!is_array($merge->require ?? NULL) || !in_array('composer.openfed.json', $merge->require, TRUE)) {
      throw new RuntimeException('Expected merge-plugin.require to load composer.openfed.json.');
    }
    $platform = $root->config->platform->php ?? NULL;
    if ($platform !== NULL && (!is_string($platform) || version_compare($platform, $minimumPhp, '<'))) {
      throw new RuntimeException("Openfed $target requires PHP $minimumPhp or newer. Review config.platform.php first.");
    }

    $patchConfig = self::objectSection($rootExtra, 'composer-patches');
    $patchFile = $patchDefaults->{'patches-file'} ?? NULL;
    if ($patchFile !== 'composer.patches.json' || !(($patchDefaults->{'package-depths'} ?? NULL) instanceof stdClass)) {
      throw new RuntimeException('The project template is missing expected Composer Patches defaults.');
    }
    self::setMigrationValue($patchConfig, 'patches-file', $patchFile);
    $depths = self::objectSection($patchConfig, 'package-depths');
    foreach ($patchDefaults->{'package-depths'} as $package => $depth) {
      self::setMigrationValue($depths, $package, $depth);
    }

    self::objectSection($openfed, 'require')->{'openfed/openfed'} = $target;
    foreach ($files as $name => $file) {
      if ($name === 'composer.patches.json') {
        continue;
      }
      unset($file->scripts->{'project-validate-update12'});
      $require = self::objectSection($file, 'require');
      if (isset($file->{'require-dev'}->{'oomphinc/composer-installers-extender'})) {
        throw new RuntimeException('Legacy installer is in require-dev; remove that custom requirement manually.');
      }
      unset($require->{'oomphinc/composer-installers-extender'});
      foreach (['cweagans/composer-patches', 'szeidler/composer-patches-cli'] as $package) {
        $constraint = $templateOpenfed->require->$package ?? NULL;
        if (!is_string($constraint)) {
          throw new RuntimeException("The project template is missing the $package requirement.");
        }
        if ($file === $openfed || isset($require->$package)) {
          $require->$package = $constraint;
        }
      }
      if (($file->description ?? '') === 'Project template for Drupal 10 sites built with the Openfed distribution.') {
        $file->description = $defaults[$name]->description;
      }
      $extra = self::objectSection($file, 'extra');
      if (isset($extra->{'patches-file'}) && $extra->{'patches-file'} !== $patchFile) {
        throw new RuntimeException('Custom legacy patches-file: migrate it manually before continuing.');
      }
      if (isset($extra->patchLevel)) {
        foreach (self::objectSection($extra, 'patchLevel') as $package => $level) {
          if (!is_string($level) || !preg_match('/^-p(\d+)$/D', $level, $match)) {
            throw new RuntimeException("Unsupported patch level for $package.");
          }
          self::setMigrationValue($depths, $package, (int) $match[1]);
        }
      }
      unset($extra->patchLevel, $extra->{'enable-patching'}, $extra->{'patches-file'});
      if (isset($extra->{'installer-types'})) {
        if (!is_array($extra->{'installer-types'})) {
          throw new RuntimeException('installer-types must be an array.');
        }
        $extra->{'installer-types'} = array_values(array_unique(array_merge(
          array_diff($extra->{'installer-types'}, ['openfed-ckeditor-plugin', 'openfed-ckeditor-template']),
          $defaults[$name]->extra->{'installer-types'},
        )));
      }

      $libraryPathFound = FALSE;
      $paths = self::objectSection($extra, 'installer-paths');
      foreach ($paths as $path => $selectors) {
        if (!is_array($selectors)) {
          throw new RuntimeException("Installer path $path must contain an array.");
        }
        $selectors = array_values(array_diff($selectors, ['type:openfed-ckeditor-plugin', 'type:openfed-ckeditor-template']));
        if (in_array('type:drupal-library', $selectors, TRUE)) {
          $libraryPathFound = TRUE;
          if (!in_array('type:theme-library', $selectors, TRUE)) {
            $selectors[] = 'type:theme-library';
          }
        }
        if ($selectors === []) {
          unset($paths->$path);
        }
        else {
          $paths->$path = $selectors;
        }
      }
      if (!$libraryPathFound) {
        throw new RuntimeException('No Drupal library installer path found; review the project layout manually.');
      }
    }

    $plugins = self::objectSection(self::objectSection($root, 'config'), 'allow-plugins');
    $plugins->{'oomphinc/composer-installers-extender'} = FALSE;
    foreach (['mnsami/composer-custom-directory-installer', 'symfony/runtime', 'cweagans/composer-patches'] as $plugin) {
      $allowed = $template->config->{'allow-plugins'}->$plugin ?? NULL;
      if (!is_bool($allowed)) {
        throw new RuntimeException("The project template is missing an allow-plugins default for $plugin.");
      }
      self::setMigrationValue($plugins, $plugin, $allowed);
    }

    $webroot = rtrim($rootExtra->{'drupal-scaffold'}->locations->{'web-root'} ?? './docroot', '/');
    $libraries = preg_replace('#^\./#', '', $webroot) . '/modules/contrib/webform/composer.libraries.json';
    if (in_array($libraries, $merge->require, TRUE)) {
      $merge->include ??= [];
      if (!is_array($merge->include)) {
        throw new RuntimeException('merge-plugin.include must be an array.');
      }
      $merge->require = array_values(array_diff($merge->require, [$libraries]));
      if (!in_array($libraries, $merge->include, TRUE)) {
        $merge->include[] = $libraries;
      }
    }
    $patches = $files['composer.patches.json'];
    if (($patches->patches ?? NULL) === []) {
      $patches->patches = new stdClass();
    }
    elseif (!(($patches->patches ?? NULL) instanceof stdClass)) {
      throw new RuntimeException('Expected patches to be an object; review the patch file manually.');
    }
  }

  private static function overwriteFiles(bool $upgrade = FALSE, bool $force = FALSE): void {
    $extractPath = self::$latestOpenfedVersion;
    $directory = "openfed-project-$extractPath";
    $extracted = self::withTemplateArchive($extractPath, static function (\ZipArchive $zip) use ($directory, $extractPath, $upgrade, $force): bool {
      if ($upgrade) {
        $profile = self::readTemplateManifest($zip, $directory, 'composer.openfed.json');
        $target = $profile->require->{'openfed/openfed'} ?? NULL;
        if (is_string($target) && str_starts_with($target, '14.')) {
          if (!preg_match(self::OPENFED_14_CONSTRAINT, $target)) {
            throw new RuntimeException('The project template must declare an Openfed 14 release or a patch wildcard (optionally with @alpha).');
          }
          self::prepareOpenfed14([
            'composer.json' => self::readTemplateManifest($zip, $directory, 'composer.json'),
            'composer.openfed.json' => $profile,
          ], $target, $force);
          return FALSE;
        }
        if (!self::newVersionExists()) {
          return FALSE;
        }
      }
      echo "\n\n---- Project files will be updated using openfed-project $extractPath\n";
      if (!$zip->extractTo($extractPath)) {
        throw new RuntimeException("Cannot extract the openfed-project $extractPath archive.");
      }
      return TRUE;
    });
    if (!$extracted) {
      return;
    }

    // Remove files that should be ignored during the update process.
    $projectDir = $extractPath . DIRECTORY_SEPARATOR . 'openfed-project-' . self::$latestOpenfedVersion . DIRECTORY_SEPARATOR;
    $filesToRemove = ['.gitignore', 'README.md', 'CHANGELOG.md'];

    foreach ($filesToRemove as $file) {
      $filePath = $projectDir . $file;
      if (file_exists($filePath)) {
        unlink($filePath);
      }
    }

    // Composer.json and composer.patches.json, if exists, will be merged.
    // This is a best effort merge and should be manually confirmed.
    $composerFiles = ['composer.json', 'composer.patches.json'];

    foreach ($composerFiles as $composerFile) {
      $sourcePath = $projectDir . $composerFile;
      $targetPath = '.' . DIRECTORY_SEPARATOR . $composerFile;

      if (file_exists($sourcePath)) {
        self::mergeComposer($sourcePath, $targetPath);
        unlink($sourcePath);
      }
    }

    // All the remaining files will be copied as is (i.e.
    // composer.openfed.json)
    self::recurseCopy($projectDir, '.');
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
    $latest_openfed_version = self::availableTemplateTags();
    if (!$upgrade) {
      // Get the current major version.
      $current_major_version = strstr(self::$currentOpenfedVersion,'.', true) . '.';

      // On updates we need to filter openfed versions that match the current
      // major version.
      $latest_openfed_version = array_filter($latest_openfed_version, function($version) use ($current_major_version) {
        return !str_contains($version, '-') && str_starts_with($version, $current_major_version);
      });
    }

    self::$latestOpenfedVersion = current($latest_openfed_version);
    if ($upgrade && self::$latestOpenfedVersion === FALSE) {
      throw new RuntimeException('No openfed-project release tags found.');
    }
  }

  private static function availableTemplateTags(): array {
    $result = [];
    exec("git -c 'versionsort.suffix=-' ls-remote --tags --refs --sort='-v:refname' " . escapeshellarg(self::$openfedRepo), $result, $status);
    if ($status !== 0) {
      throw new RuntimeException('Cannot list openfed-project tags.');
    }
    $tags = [];
    foreach ($result as $line) {
      if (preg_match('#\srefs/tags/((?:\d+\.){2}\d+(?:-(?:alpha|beta|rc)\d+)?)$#iD', $line, $match)) {
        $tags[] = $match[1];
      }
    }
    return $tags;
  }

}
