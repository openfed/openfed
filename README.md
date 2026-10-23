# Openfed

OpenFed is a general-purpose, multilingual Drupal 9 distribution.

It is developed by/for the Belgian Federal Public Service for ICT (Fedict) as
part of the Fast2Web offering.

## Usage

### Installation

The recommended way to install Openfed is using
[Composer](https://getcomposer.org/doc/00-intro.md#installation-linux-unix-osx).

You can use our [Openfed Project](https://github.com/openfed/openfed-project/tree/11.x) template like:

```
composer create-project openfed/openfed-project MY_PROJECT
```

After that you can just install Openfed like any other distribution.

### Server requirements

Openfed <= 11.1.x requires PHP 7.3.
Openfed 11.2.x requires PHP 8.1.

### Composer installers

The current installer configuration requires PHP 8.1+ and Composer 2.3+.
`composer/installers` handles Drupal packages; its custom path support does not
extend to arbitrary package types. Openfed uses
`mnsami/composer-custom-directory-installer` ^2.3 for the configured
`theme-library` and `simplesamlphp-module` types.
Enable both plugins in the root project's `config.allow-plugins`.

Openfed replaces version 2 of `oomphinc/composer-installers-extender` because
the Openfed library repository still declares it as a requirement, including
for the Sass framework. The replacement plugin supplies the custom-type and
path handling used by those packages; the old extender must not also be enabled.
This replacement declaration can be removed once the library metadata no longer
requires the extender.

Installer settings belong in the **root project's** `composer.json`; dependency
`extra` settings are not inherited. To extract the Sass framework inside a
custom theme, require `smillart/framework-sass-source-files` and merge this rule
into the root project's existing `extra` settings:

```json
{
    "installer-types": ["theme-library", "simplesamlphp-module"],
    "installer-paths": {
        "docroot/themes/custom/example_theme/{$name}": [
            "smillart/framework-sass-source-files"
        ]
    }
}
```

The framework's `extra.installer-name` is `_sass-framework`, so its archive is
extracted into `docroot/themes/custom/example_theme/_sass-framework`.
Without a theme-specific rule, Openfed's default is
`docroot/libraries/_sass-framework`. Package-name matches take precedence over
type matches with the replacement plugin, regardless of rule order.
`InstalledVersions::getInstalledPackagesByType()` can discover packages but does
not extract or relocate them into a theme.

For SimpleSAMLphp, the existing configuration is retained: `simplesamlphp-module`
remains in `extra.installer-types`, with this custom installation rule:

```json
"docroot/libraries/simplesamlphp/modules/{$name}": [
    "type:simplesamlphp-module"
]
```

This preserves the configured custom path rather than migrating SimpleSAMLphp
placement as part of the installer replacement. The native
`simplesamlphp/composer-module-installer` also remains enabled and can take
precedence: in the clean-install check, it installed modules under
`vendor/simplesamlphp/simplesamlphp/modules/<module>` and assets under
`vendor/simplesamlphp/simplesamlphp/public/assets/`. The retained custom rule
therefore does not guarantee that modules are installed under `docroot/libraries`;
verify the effective paths for the deployment's installed plugins.

### Composer patches

Composer Patches ^2.0 accepts the existing compact description-to-URL definitions
under `extra.patches`. Core's patch depth is configured as integer `2` under
`extra.composer-patches.package-depths.drupal/core`; the legacy `patchLevel`
and `enable-patching` keys are no longer used.

Keep the root project's generated `patches.lock.json` under version control.
After changing patches, run `ddev composer patches-relock`, followed by
`ddev composer patches-repatch` to apply them to existing installations.
Patch format compatibility does not guarantee that an individual patch still
applies to the selected Drupal release.

## Bug Report

You should use, preferably, Drupal.org [Openfed issue queue](https://www.drupal.org/project/issues/openfed).
