# Openfed Leaflet

This module adds a custom token type to render Leaflet maps directly in token-enabled text fields.

## What it does

`openfed_leaflet` provides dynamic tokens with this format:

`[openfed-leaflet:map:MAP_BUNDLE:lat-lng-zoom-height:LAT+LNG[+ZOOM[+HEIGHT]]]`

When the token is rendered, the module builds a Leaflet map with one
point marker and outputs the rendered map markup.

## Requirements

From `openfed_leaflet.info.yml`:

- Drupal core `^10 || ^11`
- `leaflet` module
- `geofield` module

## Enable the module

Enable it like any Drupal module (UI or Drush).

```bash
drush en openfed_leaflet -y
```

## Token syntax

General syntax:

`[openfed-leaflet:map:<map_bundle>:lat-lng-zoom-height:<latitude>+<longitude>[+<zoom>[+<height>]]]`

### Arguments

- `<map_bundle>`: Leaflet map machine name (must exist in Leaflet map config).
- `<latitude>`: decimal latitude.
- `<longitude>`: decimal longitude.
- `<zoom>`: optional integer zoom level.
- `<height>`: optional integer map height in pixels.

> If `zoom` or `height` is omitted or invalid, the map defaults are used.

## Examples

```text
[openfed-leaflet:map:osm_mapnik:lat-lng-zoom-height:50.860827+4.356167+16+250]
```

```text
[openfed-leaflet:map:osm_mapnik:lat-lng-zoom-height:50.860827+4.356167]
```

## Where to use it

Use this token in any Drupal field or configuration that supports token replacement (for example, token-enabled text outputs).

## Troubleshooting

- Check the map bundle machine name is correct.
- Ensure latitude/longitude are provided and valid decimal values.
- Ensure zoom/height values are numeric integers when provided.
- If no map appears, verify Leaflet and Geofield modules are enabled and configured.

