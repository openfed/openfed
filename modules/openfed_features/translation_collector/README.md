# Translation Collector

`translation_collector` is the base module for the translation inventory stack.
It provides shared settings, interface string collection, collector wiring, and persistence.

## Installation

* Download and install
  [PHPOffice/SpreadSheet](https://github.com/PHPOffice/PhpSpreadsheet). The preferred
  installation method is to [use Composer](https://www.drupal.org/node/2404989).

## Module layout

```text
translation_collector/
├── src/...
├── modules/
│   └── translation_collector_config/  # Config string collector
```

`translation_collector_config` can be enabled independently when configuration
string collection is needed.

## Shared responsibilities

| Component | Purpose |
|---|---|
| `CollectorInterface` | Contract for collector services used by submodules. |
| `translation_collector.settings_checker` | Central activation checks (enabled flag, role filter, excluded paths). |
| `translation_collector.persist_subscriber` | Persists collector output on `KernelEvents::TERMINATE`. |
| `TranslationCollectorServiceProvider` | Auto-registers services tagged `translation_collector.collector`. |
| `translation_collector_strings` | Shared storage table for interface and config items. |

## Runtime flow

1. Enabled collectors (base interface collector and optional config collector)
   collect data in request memory.
2. Response is sent to the client.
3. The base persist subscriber runs on `KernelEvents::TERMINATE`.
4. Collected items are persisted with UPSERT behavior.

## Configuration

Shared settings are managed at:

`/admin/config/regional/translation-collector`

Collected strings can be viewed at:

`/admin/config/regional/translation-collector/strings`

From that page, use **Export XLSX** to download all matching rows as an `.xlsx`
file.

Use **Import XLSX** to upload a translated export file.

Import path:

`/admin/config/regional/translation-collector/strings/import`

Imports are queued (Queue API) to handle large files safely. Queue processing can
run through cron or manually with:

`drush queue:run translation_collector_import`

## XLSX export format

The export file contains these columns:

`ID`, `Source (singular)`, `Source (plural)`, `Context`, `Langcode`, `Type`,
`Location`, `Is translated`, `Last seen`, `URL`, `Target (singular)`,
`Target (plural)`

For non-plural strings, plural columns are empty.

## Notes

- Designed for production-safe collection: persistence runs after response delivery.
- Persistence is skipped when the current interface language is the site's default language.
- Shared settings are applied uniformly across all enabled collectors.
- `string_type` distinguishes interface and config rows in the same table.
