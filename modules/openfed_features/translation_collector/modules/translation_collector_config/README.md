# Translation Collector: Config Strings

`translation_collector_config` is a submodule of `translation_collector`.
It inventories translatable configuration text from config objects loaded during requests.

## Request flow

### During rendering

1. `ResponseCacheTagSubscriber` captures response cache tags and extracts `config:*` tags.
2. `ConfigTranslationCollector` observes loaded config names through `ConfigFactoryOverrideInterface` as a fallback source.
3. Only config names are recorded in memory (no schema traversal or persistence during render).

### On terminate (`KernelEvents::TERMINATE`)

4. `ConfigStringCollector` starts with response-tag-derived config names (output-relevant).
5. If `include_config_prefixes` is configured, it adds names discovered from those configured prefixes.
6. It resolves names through typed config schema.
7. Translatable schema paths are converted into inventory items.
8. Items are returned to the base persist subscriber and written to `translation_collector_strings`.

## Services

| Service | Purpose |
|---|---|
| `translation_collector_config.response_cache_tag_subscriber` | Extracts `config:*` tags from the response as page-relevant config names. |
| `translation_collector_config.response_config_name_collector` | Request-scoped in-memory list of unique config names derived from response cache tags. |
| `translation_collector_config.config_translation_overrider` | Observes config loads and records config names. |
| `translation_collector_config.config_name_collector` | Request-scoped in-memory list of unique config names. |
| `translation_collector_config.collector` | Resolves translatable config strings for terminate-time persistence. |

## Configuration

Uses shared settings from:

`/admin/config/regional/translation-collector`

`include_config_prefixes` is applied as a whitelist before names are resolved.

- Empty list: collect only response cache-tag-derived config names.
- Populated list: response names are augmented with configured-prefix config names and filtered by those prefixes.

## Notes

- Designed for production-safe collection: heavy work runs after response delivery.
- Collected rows are stored with `string_type = config`.
- Location is stored as `config_name:property.path` to distinguish config entries.
