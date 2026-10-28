<?php

namespace Drupal\openfed_administration\Service;

use Drupal\content_translation\ContentTranslationManagerInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\workflows\WorkflowInterface;

/**
 * Provides helper methods for content types managements.
 */
class ContentTypeManager {

  /**
   * The entity type manager.
   */
  protected EntityTypeManagerInterface $entityTypeManager;

  /**
   * The content translation manager.
   */
  protected ContentTranslationManagerInterface $contentTranslationManager;

  /**
   * Constructs a ContentTypeManager object.
   *
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entity_type_manager
   *   The entity type manager.
   * @param \Drupal\content_translation\ContentTranslationManagerInterface $content_translation_manager
   *   The content translation manager.
   */
  public function __construct(EntityTypeManagerInterface $entity_type_manager, ContentTranslationManagerInterface $content_translation_manager) {
    $this->entityTypeManager = $entity_type_manager;
    $this->contentTranslationManager = $content_translation_manager;
  }

  /**
   * Adds a content type to the openfed content moderation workflow.
   *
   * @param string $content_type_name
   *   The machine name of the content type.
   */
  public function addWorkflowToBundle(string $content_type_name): void {
    $workflow = $this->entityTypeManager->getStorage('workflow')->load('openfed_workflow');

    if (!$workflow instanceof WorkflowInterface) {
      return;
    }

    $workflow->getTypePlugin()->addEntityTypeAndBundle('node', $content_type_name);
    $workflow->save();
  }

  /**
   * Assign default content moderation permissions for the given content type.
   *
   * This will assign content moderation permissions.
   *
   * @param string $content_type_name
   *   The machine name of the content type.
   *
   * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
   * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
   */
  public function assignPermissionsToRoles(string $content_type_name): void {
    $roles = $this->entityTypeManager->getStorage('user_role')->loadMultiple([
      'content_editor',
      'content_author',
    ]);

    /** @var \Drupal\user\RoleInterface $role */
    foreach ($roles as $role) {
      $issue_access_permissions = [
        "translate $content_type_name node",
        "create $content_type_name content",
        "delete any $content_type_name content",
        "edit any $content_type_name content",
        "view $content_type_name revisions",
        "override $content_type_name authored by option",
        "override $content_type_name authored on option",
        "override $content_type_name published option",
        "override $content_type_name revision option",
      ];

      if ($role->id() === 'content_editor') {
        $issue_access_permissions[] = "revert $content_type_name revisions";
      }

      foreach ($issue_access_permissions as $permission) {
        $role->grantPermission($permission);
      }
      $role->save();
    }

  }

  /**
   * Enables translation for a node type.
   *
   * @param string $content_type_name
   *   The machine name of the content type.
   */
  public function enableTranslation(string $content_type_name): void {
    $this->contentTranslationManager->setEnabled('node', $content_type_name, TRUE);
  }

}
