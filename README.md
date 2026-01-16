# Openfed

OpenFed is a general-purpose, multilingual Drupal 9 distribution.

It is developed by/for the Belgian Federal Public Service for ICT (Fedict) as
part of the Fast2Web offering.

## Recommendations for Deprecated Modules

Openfed marks some contributed modules as **deprecated**. These modules may still be present for backwards compatibility, but they are not recommended for new builds and will be removed in a future Openfed version.

| Module (machine name) | Status in Openfed | Recommendation |
| --- | --- | --- |
| `ckeditor_templates` | Deprecated | Migrate to CKEditor 5 templates (via Openfed’s CKEditor 4 → 5 migration) and uninstall this module. |
| `ckeditor4_codemirror` | Deprecated | Use CKEditor 5 alternatives (for example, Source Editing) and uninstall this module. |
| `anchor_link` | Deprecated | Use the CKEditor 5 Bookmark plugin and uninstall this module. |
| `fakeobjects` | Deprecated | Dependency of deprecated CKEditor 4 tooling; uninstall when no longer needed. |
| `ckeditor_config` | Deprecated | Use CKEditor 5 configuration and uninstall this module. |
| `ckeditor` | Deprecated | Use CKEditor 5 and uninstall CKEditor 4. |

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

## Bug Report

You should use, preferably, Drupal.org [Openfed issue queue](https://www.drupal.org/project/issues/openfed).
