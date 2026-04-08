# Openfed Conditional Fields Content Translation

## What this module does

This submodule keeps **Conditional Fields** working on content translation forms.

On translation forms, Drupal's content translation handler can hide untranslatable
fields by setting `#access = FALSE`. When those fields are conditional dependents,
that can break Conditional Fields behavior because the dependent widgets are no
longer present in the form tree.

This module provides a custom content translation handler that:

- restores `#access` for conditional dependent fields that were hidden only by
  the "hide untranslatable fields" translation logic;
- restores access recursively for all nested element levels;
- on non-source translation forms, applies a `#states['disabled']` rule on leaf
  inputs so conditional JS behavior still runs while the translated field remains
  non-editable.

## Disabled feature: currently supported trigger state

The disabled behavior currently adds this state condition:

- `checked => TRUE`

That means the current implementation supports trigger elements that expose a
**checked** state in Drupal `#states`, i.e.:

- checkboxes;
- radio inputs.

At the moment, this disabled-state implementation does **not** include dedicated
support for other trigger states such as `value`, `empty`, or `filled`.

## Implementation reference

See:

- `src/ContentTranslationHandler.php`

