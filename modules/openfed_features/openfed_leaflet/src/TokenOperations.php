<?php

namespace Drupal\openfed_leaflet;

use Drupal\Component\Render\MarkupInterface;
use Drupal\Core\DependencyInjection\ContainerInjectionInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Logger\LoggerChannelFactoryInterface;
use Drupal\Core\Render\BubbleableMetadata;
use Drupal\Core\Render\RendererInterface;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\Core\Utility\Token;
use Drupal\geofield\WktGeneratorInterface;
use Drupal\leaflet\LeafletService;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Defines a class for reacting to token events.
 */
class TokenOperations implements ContainerInjectionInterface {

  use StringTranslationTrait;

  /**
   * TokenOperations constructor.
   *
   * @param \Drupal\leaflet\LeafletService $leafletService
   *   The Leaflet service.
   * @param \Drupal\geofield\WktGeneratorInterface $wktGenerator
   *   The Wkt Generator service.
   * @param \Drupal\Core\Render\RendererInterface $renderer
   *   The Renderer service.
   * @param \Drupal\Core\Utility\Token $token
   *   The Token service.
   * @param \Drupal\Core\Logger\LoggerChannelFactoryInterface $loggerFactory
   *   The Logger Channel Factory service.
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   *   The entity type manager service.
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $moduleHandler
   *   The module handler service.
   */
  public function __construct(private readonly LeafletService $leafletService, private readonly WktGeneratorInterface $wktGenerator, private readonly RendererInterface $renderer, private readonly Token $token, private readonly LoggerChannelFactoryInterface $loggerFactory, private readonly EntityTypeManagerInterface $entityTypeManager, private readonly ModuleHandlerInterface $moduleHandler) {}

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('leaflet.service'),
      $container->get('geofield.wkt_generator'),
      $container->get('renderer'),
      $container->get('token'),
      $container->get('logger.factory'),
      $container->get('entity_type.manager'),
      $container->get('module_handler'),
    );
  }

  /**
   * Acts on token info phase.
   *
   * @return array
   *   An associative array of available tokens and token types.
   */
  public function tokenInfo(): array {
    // Sets the token group type.
    $type = [
      'name' => $this->t('OpenFed Leaflet'),
      'description' => $this->t('Token for showing a map.'),
    ];

    $tokens = [];

    // Add support for map bundles.
    foreach ($this->leafletService->leafletMapGetInfo() as $map => $map_info) {
      // Create a specific token for each map bundle.
      $tokens['map:' . $map . ':lat-lng-zoom-height'] = [
        'name' => $this->t('Map: @label', ['@label' => $map_info['label']]),
        'description' => $this->t('Renders a "@label" map with specified arguments (latitude+longitude+zoom+height)',
          ['@label' => $map_info['label']]),
        'dynamic' => TRUE,
      ];
    }

    return [
      'types' => ['openfed-leaflet' => $type],
      'tokens' => ['openfed-leaflet' => $tokens],
    ];
  }

  /**
   * Acts on token phase.
   *
   * @param string $type
   *   The machine-readable name of the type (group) of token being replaced.
   * @param array $tokens
   *   An array of tokens to be replaced.
   * @param array $data
   *   An associative array of data objects to be used when
   *   generating replacement values.
   * @param array $options
   *   An associative array of options for token replacement.
   * @param \Drupal\Core\Render\BubbleableMetadata $bubbleable_metadata
   *   The bubbleable metadata.
   *
   * @return array
   *   An associative array of replacement value.
   */
  public function tokens(string $type, array $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata): array {
    $replacements = [];

    if ($type === 'openfed-leaflet') {
      // [openfed-leaflet:map:*] chained tokens.
      if ($map_tokens = $this->token->findWithPrefix($tokens, 'map')) {
        $replacements += $this->token->generate('map', $map_tokens, [], $options, $bubbleable_metadata);
      }
    }

    if ($type === 'map') {
      // Process each leaflet layers token.
      foreach ($tokens as $name => $original) {
        // Parse the token parts.
        $parts = explode(':', $name);

        // Expected token format:
        // [openfed-leaflet:map:{map_bundle}:lat-lng-zoom-height:{latitude}+{longitude}[+{zoom}[+{height}]].
        // Example token:
        // [openfed-leaflet:map:osm_mapnik:lat-lng-zoom-height:50.860827+4.356167+16+250].
        if (count($parts) === 3 && $parts[1] === 'lat-lng-zoom-height') {
          $map_bundle = $parts[0];
          $coordinates = $parts[2];
          $replacements[$original] = $this->renderMap(
            $map_bundle,
            $coordinates,
            $bubbleable_metadata,
          );
        }
      }
    }

    return $replacements;
  }

  /**
   * Helper method to render a map based on map_bundle and arguments.
   *
   * @param string $map_bundle
   *   The map bundle machine name.
   * @param string $args
   *   String with format "latitude+longitude+zoom+height".
   * @param \Drupal\Core\Render\BubbleableMetadata $bubbleable_metadata
   *   The bubbleable metadata.
   *
   * @return \Drupal\Component\Render\MarkupInterface|null
   *   Rendered map markup.
   */
  private function renderMap(string $map_bundle, string $args, BubbleableMetadata $bubbleable_metadata): ?MarkupInterface {
    [$lat, $lon, $zoom, $height] = array_pad(explode('+', $args), 4, NULL);

    // Check if we have at least latitude and longitude.
    if ($lat === NULL || $lon === NULL) {
      return NULL;
    }

    // Generate Point based on longitude and latitude.
    $coordinates = $this->wktGenerator->wktGeneratePoint([
      $lon,
      $lat,
    ]);

    // Process coordinates.
    $points = $this->leafletService->leafletProcessGeofield($coordinates);

    // If no points are generated, return NULL.
    if (empty($points)) {
      return NULL;
    }

    // Get the map info.
    $map = $this->leafletService->leafletMapGetInfo($map_bundle);

    // If a map doesn't exist.
    if (empty($map)) {
      return NULL;
    }

    // Add the map to bubbleable metadata for caching.
    $bubbleable_metadata->addCacheableDependency($map);

    // Add map bundle cacheability only when leaflet_layers is available.
    if ($this->moduleHandler->moduleExists('leaflet_layers') && $this->entityTypeManager->hasDefinition('map_bundle')) {
      $map_bundle_entity = $this->entityTypeManager
        ->getStorage('map_bundle')
        ->load($map_bundle);
      if ($map_bundle_entity) {
        $bubbleable_metadata->addCacheableDependency($map_bundle_entity);
      }
    }

    // Add zoom settings if provided.
    if (!empty($zoom) && ctype_digit($zoom)) {
      $map["settings"]["zoom"] = (int) $zoom;
    }

    // Render the map with custom height or default height.
    if (!empty($height) && ctype_digit($height)) {
      $leafletRenderMap = $this->leafletService->leafletRenderMap($map, [$points[0]], "{$height}px");
    }
    else {
      $leafletRenderMap = $this->leafletService->leafletRenderMap($map, [$points[0]]);
    }

    try {
      return $this->renderer->render($leafletRenderMap);
    }
    catch (\Exception $e) {
      // Log the exception if needed.
      $this->loggerFactory->get('openfed_leaflet')->error($e->getMessage());
    }

    // If rendering fails, return NULL.
    return NULL;
  }

}
