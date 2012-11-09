<?php

/**
 * Implements hook_block_info().
 */
function ofed_federal_header_block_info() {
  $blocks = array();
  $blocks['federal_header'] = array(
      'info' => t('Belgian Federal header'),
      'cache' => DRUPAL_NO_CACHE,//DRUPAL_CACHE_GLOBAL,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function ofed_federal_header_block_view($delta = '') {
  $block = array();
  switch($delta) {
    case 'federal_header':
      $block['subject'] = t('Belgian Federal header');
      $block['content'] = _ofed_federal_header_render_content();
      break;
  }
  return $block;
}

/**
 * Return the content of the block.
 * 
 * @return string.
 */
function _ofed_federal_header_render_content() {
  // Load style.
  drupal_add_css(drupal_get_path('module', 'ofed_federal_header') . '/assets/styles/ofed_federal_header.css');

  // Initialize.
  $output = '';
  // Get theme.
  $output .= theme('ofed_federal_header_block', array());
  // Return.
  return $output;
}