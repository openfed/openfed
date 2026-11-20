<?php

declare(strict_types=1);

namespace OpenfedProject\composer;

use Composer\Script\Event;
use RuntimeException;
use stdClass;
use Throwable;

class Openfed14Preparation {

  public static function prepare(Event $event): void {
    if (self::main($event->getArguments()) !== 0) {
      throw new RuntimeException('Openfed 14 preparation failed; see the error above.');
    }
  }

  public static function readComposerObject(string $path): stdClass {
    $contents = file_get_contents($path);
    if ($contents === false) {
      throw new RuntimeException("Cannot read $path");
    }
    $data = json_decode($contents, false, 512, JSON_THROW_ON_ERROR);
    if (!$data instanceof stdClass) {
      throw new RuntimeException("$path must contain a JSON object.");
    }
    return $data;
  }

  private static function objectSection(stdClass $data, string $key): stdClass {
    if (!property_exists($data, $key)) {
      $data->$key = new stdClass();
    }
    if (!$data->$key instanceof stdClass) {
      throw new RuntimeException("$key must be an object; review this custom configuration manually.");
    }
    return $data->$key;
  }

  private static function setMigrationValue(stdClass $data, string $key, mixed $value): void {
    if (property_exists($data, $key) && $data->$key !== $value) {
      throw new RuntimeException("Conflicting $key setting; review this custom configuration manually.");
    }
    $data->$key = $value;
  }

  public static function prepareOpenfed14(array $files, string $target): array {
    if (!preg_match('/^14\.\d+\.\d+(?:-(?:alpha|beta|rc)\d+)?$/', $target)) {
      throw new RuntimeException('Target must be an explicit Openfed 14 release, for example 14.0.0-alpha2.');
    }
    $root = $files['composer.json'];
    $openfed = $files['composer.openfed.json'];
    $requirements = self::objectSection($openfed, 'require');
    $current = $requirements->{'openfed/openfed'} ?? '';
    if (!is_string($current) || !preg_match('/^13\.6\.(?:\*|\d+)$|^14\.\d+\.(?:\*|\d+(?:-(?:alpha|beta|rc)\d+)?)$/', $current)) {
      throw new RuntimeException("Unsupported Openfed constraint: " . json_encode($current));
    }
    if (!str_contains($current, '*') && version_compare($target, $current, '<')) {
      throw new RuntimeException("Target $target would downgrade Openfed from $current.");
    }
    if (isset($root->require->{'openfed/openfed'})) {
      throw new RuntimeException('Openfed is also required in composer.json; resolve the duplicate constraint first.');
    }
    $merge = self::objectSection(self::objectSection($root, 'extra'), 'merge-plugin');
    if (!isset($merge->require) || !is_array($merge->require) || !in_array('composer.openfed.json', $merge->require, true)) {
      throw new RuntimeException('Expected merge-plugin.require to load composer.openfed.json.');
    }
    $platform = $root->config->platform->php ?? null;
    if ($platform !== null && (!is_string($platform) || version_compare($platform, '8.3', '<'))) {
      throw new RuntimeException('Openfed 14 requires PHP 8.3 or newer. Review config.platform.php first.');
    }
    $requirements->{'openfed/openfed'} = $target;
    $requirements->{'cweagans/composer-patches'} = '^2.0';
    $requirements->{'szeidler/composer-patches-cli'} = '^1.1.2';
    $patchesConfig = self::objectSection(self::objectSection($root, 'extra'), 'composer-patches');
    self::setMigrationValue($patchesConfig, 'patches-file', 'composer.patches.json');
    $depths = self::objectSection($patchesConfig, 'package-depths');
    self::setMigrationValue($depths, 'drupal/core', 2);

    foreach ([$root, $openfed] as $file) {
      if (isset($file->{'require-dev'}->{'oomphinc/composer-installers-extender'})) {
        throw new RuntimeException('Legacy installer is also in require-dev; resolve that custom requirement first.');
      }
      $require = self::objectSection($file, 'require');
      unset($require->{'oomphinc/composer-installers-extender'});
      // Root requirements take precedence over those from the merged file.
      foreach (['cweagans/composer-patches' => '^2.0', 'szeidler/composer-patches-cli' => '^1.1.2'] as $package => $constraint) {
        if (isset($require->$package)) {
          $require->$package = $constraint;
        }
      }
      if (($file->description ?? '') === 'Project template for Drupal 10 sites built with the Openfed distribution.') {
        $file->description = 'Project template for Drupal 11 sites built with the Openfed distribution.';
      }
      $extra = self::objectSection($file, 'extra');
      if (isset($extra->{'patches-file'}) && $extra->{'patches-file'} !== 'composer.patches.json') {
        throw new RuntimeException('Custom legacy patches-file: migrate it manually before continuing.');
      }
      if (isset($extra->patchLevel)) {
        if (!$extra->patchLevel instanceof stdClass) {
          throw new RuntimeException('patchLevel must be an object.');
        }
        foreach ($extra->patchLevel as $package => $level) {
          if (!is_string($level) || !preg_match('/^-p(\d+)$/', $level, $match)) {
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
        $extra->{'installer-types'} = array_values(array_diff($extra->{'installer-types'}, ['openfed-ckeditor-plugin', 'openfed-ckeditor-template']));
        if (!in_array('theme-library', $extra->{'installer-types'}, true)) {
          $extra->{'installer-types'}[] = 'theme-library';
        }
      }
      $libraryPathFound = false;
      $paths = self::objectSection($extra, 'installer-paths');
      foreach ($paths as $path => $selectors) {
        if (!is_array($selectors)) {
          throw new RuntimeException("Installer path $path must contain an array.");
        }
        $selectors = array_values(array_diff($selectors, ['type:openfed-ckeditor-plugin', 'type:openfed-ckeditor-template']));
        if (in_array('type:drupal-library', $selectors, true)) {
          $libraryPathFound = true;
          if (!in_array('type:theme-library', $selectors, true)) {
            $selectors[] = 'type:theme-library';
          }
        }
        if ($selectors === []) {
          unset($paths->$path);
        } else {
          $paths->$path = $selectors;
        }
      }
      if (!$libraryPathFound) {
        throw new RuntimeException('No Drupal library installer path found; review the project layout manually.');
      }
    }
    $plugins = self::objectSection(self::objectSection($root, 'config'), 'allow-plugins');
    $plugins->{'oomphinc/composer-installers-extender'} = false;
    foreach (['mnsami/composer-custom-directory-installer', 'symfony/runtime', 'cweagans/composer-patches'] as $plugin) {
      self::setMigrationValue($plugins, $plugin, true);
    }
    $webroot = rtrim($root->extra->{'drupal-scaffold'}->locations->{'web-root'} ?? './docroot', '/');
    $libraries = preg_replace('#^\./#', '', $webroot) . '/modules/contrib/webform/composer.libraries.json';
    if (in_array($libraries, $merge->require, true)) {
      $merge->include ??= [];
      if (!is_array($merge->include)) {
        throw new RuntimeException('merge-plugin.include must be an array.');
      }
      $merge->require = array_values(array_diff($merge->require, [$libraries]));
      if (!in_array($libraries, $merge->include, true)) {
        $merge->include[] = $libraries;
      }
    }
    $patches = $files['composer.patches.json'];
    if (($patches->patches ?? null) === []) {
      $patches->patches = new stdClass();
    } elseif (!isset($patches->patches) || !$patches->patches instanceof stdClass) {
      throw new RuntimeException('Expected patches to be an object; review the patch file manually.');
    }
    return $files;
  }

  private static function migrationDiff(mixed $before, mixed $after, string $path): void {
    if ($before instanceof stdClass && $after instanceof stdClass) {
      foreach (array_unique([...array_keys(get_object_vars($before)), ...array_keys(get_object_vars($after))]) as $key) {
        self::migrationDiff($before->$key ?? null, $after->$key ?? null, "$path/$key");
      }
    } elseif (json_encode($before) !== json_encode($after)) {
      echo '- ' . $path . ': ' . json_encode($before, JSON_UNESCAPED_SLASHES) . PHP_EOL;
      echo '+ ' . $path . ': ' . json_encode($after, JSON_UNESCAPED_SLASHES) . PHP_EOL;
    }
  }

  public static function runPreparation(array $arguments): int {
    $apply = false;
    $project = getcwd();
    $target = '14.0.0-alpha2';
    foreach ($arguments as $argument) {
      if ($argument === '--apply') {
        $apply = true;
      } elseif (str_starts_with($argument, '--project=')) {
        $project = substr($argument, 10);
      } elseif (str_starts_with($argument, '--target=')) {
        $target = substr($argument, 9);
      } elseif ($argument === '--help') {
        echo "Usage: composer project-prepare14 -- [--project=PATH] [--target=14.0.0-alpha2] [--apply]\n";
        echo "Default: preview only. --apply backs up changed files and runs composer update -W --dry-run --no-scripts.\n";
        return 0;
      } else {
        throw new RuntimeException("Unknown argument: $argument");
      }
    }
    $project = realpath($project);
    if ($project === false) {
      throw new RuntimeException('Project directory does not exist.');
    }
    $original = $files = [];
    foreach (['composer.json', 'composer.openfed.json', 'composer.patches.json'] as $name) {
      $files[$name] = self::readComposerObject("$project/$name");
      $original[$name] = file_get_contents("$project/$name");
    }
    $before = unserialize(serialize($files));
    $files = self::prepareOpenfed14($files, $target);
    $changes = [];
    foreach ($files as $name => $data) {
      if (json_encode($before[$name]) !== json_encode($data)) {
        self::migrationDiff($before[$name], $data, $name);
        $changes[$name] = json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_THROW_ON_ERROR) . "\n";
      }
    }
    if (!$apply) {
      echo $changes === [] ? "Already prepared; no changes.\n" : "Preview only. Run with --apply to save and check dependency resolution.\n";
      return 0;
    }
    if ($changes !== []) {
      $backup = $project . '/.openfed14-backup-' . date('Ymd-His') . '-' . bin2hex(random_bytes(4));
      if (!mkdir($backup, 0700)) {
        throw new RuntimeException('Cannot create backup directory.');
      }
      foreach ($changes as $name => $contents) {
        if (file_put_contents("$backup/$name", $original[$name]) !== strlen($original[$name])) {
          throw new RuntimeException("Cannot back up $name; project files have not been changed.");
        }
        if (!is_writable("$project/$name")) {
          throw new RuntimeException("$name is not writable; project files have not been changed.");
        }
      }
      echo "Backups: $backup\n";
      foreach ($changes as $name => $contents) {
        if (file_put_contents("$project/$name", $contents, LOCK_EX) !== strlen($contents)) {
          throw new RuntimeException("Cannot write $name. Restore originals from $backup before retrying.");
        }
      }
    } else {
      echo "Already prepared; no files changed.\n";
    }
    echo "Checking dependencies only; no installation or database updates.\n";
    $process = proc_open(['composer', 'update', '-W', '--dry-run', '--no-scripts', '--no-interaction'], [STDIN, STDOUT, STDERR], $pipes, $project);
    if (!is_resource($process)) {
      throw new RuntimeException('Cannot start Composer. Configuration remains prepared; run the dependency check manually.');
    }
    $status = proc_close($process);
    if ($status !== 0) {
      throw new RuntimeException('Composer dependency check failed. Prepared files and backups are retained; resolve the reported blockers.');
    }
    echo "Ready to run composer update -W, then drush updb and drush cr after installation succeeds.\n";
    return 0;
  }

  public static function main(array $arguments): int {
    try {
      return self::runPreparation($arguments);
    } catch (Throwable $error) {
      fwrite(STDERR, 'Preparation failed: ' . $error->getMessage() . PHP_EOL);
      return 1;
    }
  }

}
