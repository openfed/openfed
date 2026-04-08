<?php

namespace Drupal\openfed_conditional_fields_content_translation;

use Drupal\Core\Entity\ContentEntityFormInterface;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Element;
use Drupal\content_translation\ContentTranslationHandler as ContentTranslationHandlerBase;

/**
 * Content translation handler that restores conditional field access.
 *
 * The Conditional Fields module hides dependent field widgets by setting
 * #access = FALSE when the controlling field is not in its triggering state.
 * On translation forms the base handler also hides untranslatable fields.
 * This class re-opens access for conditional field dependents at every form
 * element level and, on non-source translation forms, marks the leaf inputs
 * as disabled via #states so the JS conditional logic still works.
 */
class ContentTranslationHandler extends ContentTranslationHandlerBase {

  /**
   * {@inheritdoc}
   */
  public function entityFormSharedElements($element, FormStateInterface $form_state, $form): array {
    $element = parent::entityFormSharedElements($element, $form_state, $form);

    $element['#after_build'][] = [$this, 'overrideAccessForConditionalFields'];

    return $element;
  }

  /**
   * After-build callback: restores access for conditional field dependents.
   *
   * @param array $element
   *   The form element.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current form state.
   *
   * @return array
   *   The modified form element.
   */
  public function overrideAccessForConditionalFields(array $element, FormStateInterface $form_state): array {
    if (empty($element['#conditional_fields'])) {
      return $element;
    }

    /** @var \Drupal\Core\Entity\ContentEntityFormInterface $form_object */
    $form_object = $form_state->getFormObject();
    if (!$form_object instanceof ContentEntityFormInterface) {
      return $element;
    }

    /** @var \Drupal\Core\Entity\ContentEntityInterface $entity */
    $entity = $form_object->getEntity();
    if (!$entity instanceof ContentEntityInterface) {
      return $element;
    }

    $form_langcode = $form_object->getFormLangcode($form_state);
    $entity_langcode = $entity->getUntranslated()->language()->getId();

    // Mirror the base entityFormAlter() logic: a non-source translation form
    // is identified by comparing the form langcode to the source langcode.
    // form_state 'translation_form' is unreliable for add-translation forms
    // when the user has update access, so we do not use it here.
    $is_translation = $entity->isNewTranslation() || ($form_langcode !== $entity_langcode);

    // Mirror the parent entityFormSharedElements() logic to identify which
    // conditional field dependents had their #access set to FALSE purely
    // because they are untranslatable fields on a translation form. Only those
    // fields need their access restored so the conditional field JS can work;
    // fields hidden for any other reason are left untouched.
    $hide_untranslatable_fields = $entity->isDefaultTranslationAffectedOnly()
      && !$entity->isDefaultTranslation();

    if (!$hide_untranslatable_fields) {
      return $element;
    }

    // Reconstruct the same set the parent uses: all field definitions minus
    // those excluded from translation change detection (e.g. revision_log).
    $hidden_field_definitions = array_diff_key(
      $entity->getFieldDefinitions(),
      array_flip($this->getFieldsToSkipFromTranslationChangesCheck($entity))
    );

    foreach ($element['#conditional_fields'] as $dependent => $dependent_info) {
      if (empty($dependent_info['dependents'])) {
        continue;
      }
      if (!isset($element[$dependent]) || !is_array($element[$dependent])) {
        continue;
      }

      // Only restore access for fields whose #access was set to FALSE by the
      // parent's $hide_untranslatable_fields logic. The parent hides a field
      // only when it is in the field definitions list (not skip-listed) AND
      // the field element is non-multilingual — which in practice means the
      // underlying field definition is not translatable. We check both the
      // field definition's translatability (authoritative) and the form
      // element's #multilingual flag (set by the widget layer) to be safe.
      if (!isset($hidden_field_definitions[$dependent])) {
        continue;
      }
      if ($hidden_field_definitions[$dependent]->isTranslatable()) {
        continue;
      }
      if (!empty($element[$dependent]['#multilingual'])) {
        continue;
      }

      $this->overrideAccessRecursively($element[$dependent], $is_translation);
    }

    return $element;
  }

  /**
   * Ensures conditional field access is enabled on all levels of form elements.
   *
   * Sets #access = TRUE on the current element and recurses into children,
   * so both parents and leaves have their access restored. The #states
   * disabled rule is only added on leaf elements that carry a #name, and only
   * when editing a translation (not the source language entity).
   *
   * @param array $element
   *   The form element to process, passed by reference.
   * @param bool $is_translation
   *   TRUE when the form is for a non-source translation, FALSE otherwise.
   */
  protected function overrideAccessRecursively(array &$element, bool $is_translation): void {
    // Restore access at every level, not just at the deepest leaf.
    if (array_key_exists('#access', $element) && empty($element['#access'])) {
      $element['#access'] = TRUE;
    }

    $children = Element::children($element);

    if (empty($children)) {
      // Leaf element: only apply the disabled state on translation forms.
      if ($is_translation && !empty($element['#name'])) {
        $element['#states']['disabled'] = [
          ':input[name="' . $element['#name'] . '"]' => ['checked' => TRUE],
        ];
      }
      return;
    }

    foreach ($children as $child_key) {
      if (isset($element[$child_key]) && is_array($element[$child_key])) {
        $this->overrideAccessRecursively($element[$child_key], $is_translation);
      }
    }
  }

}
