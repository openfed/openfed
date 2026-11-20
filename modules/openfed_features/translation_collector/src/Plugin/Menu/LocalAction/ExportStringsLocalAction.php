<?php

declare(strict_types=1);

namespace Drupal\translation_collector\Plugin\Menu\LocalAction;

use Drupal\Core\Menu\LocalActionDefault;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Routing\RouteProviderInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\RequestStack;

/**
 * Adds current exposed filter query arguments to the XLSX export action.
 */
final class ExportStringsLocalAction extends LocalActionDefault {

  /**
   * Constructs an export local action.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    RouteProviderInterface $route_provider,
    private readonly RequestStack $requestStack,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, $route_provider);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): self {
    return new self(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('router.route_provider'),
      $container->get('request_stack'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getOptions(RouteMatchInterface $route_match): array {
    $options = parent::getOptions($route_match);

    $request = $this->requestStack->getCurrentRequest();
    if ($request === NULL) {
      return $options;
    }

    $allowed = ['source', 'langcode', 'string_type', 'is_translated'];
    $query = [];
    foreach ($allowed as $key) {
      $value = $request->query->get($key);
      if (is_scalar($value) && $value !== '') {
        $query[$key] = (string) $value;
      }
    }

    if (!empty($query)) {
      $options['query'] = ($options['query'] ?? []) + $query;
    }

    return $options;
  }

}

