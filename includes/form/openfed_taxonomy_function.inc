<?php

/**
 * Return the form for taxonomy set up
 * @return array 
 */
function openfed_taxonomy_form() {
  drupal_set_title(st('Enable taxonomy'));
  $form = array();
  $form['intro'] = array(
    '#markup' => '<p>' . st('Select this option if there will be taxonomy vocabularies in the websites, that will be used to re-group items. <br> If this option is not checked, the vocabulary will have to be created manually.') . '</p>',
  );
  $form['taxonomy_list'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Taxonomy'),
    '#options' => _openfed_return_taxonomy_list(),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  return $form;
}

/**
 * manage the submit of the form
 * @param array $form
 * @param array $form_state 
 */
function openfed_taxonomy_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $blocks = array();
  if (!empty($values['taxonomy_list'])) {
    if ($values['taxonomy_list']['categories'] === 'categories') {
      // Create a default vocabulary named "Category".
      $vocabulary = (object) array(
          'name' => st('Categories'),
          'description' => st('Use tags to group content into categories.'),
          'machine_name' => 'categories',
          'help' => st('Enter a comma-separated list of words to categorise your content.'),
      );
      taxonomy_vocabulary_save($vocabulary);
    }
  }
}
