<?php

/**
 * Implements hook_block_info().
 */
function ofed_slider_block_info() {
  $blocks = array();
  $blocks['slide_images'] = array(
    'info' => t('Slider: slider'),
    'cache' => DRUPAL_NO_CACHE,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function ofed_slider_block_view($delta = '') {
  $block = array();
  switch ($delta) {
    case 'slide_images':
      $block['subject'] = t('Slider: slider');
      $block['content'] = _ofed_slider_render_content($delta);
      break;
  }
  return $block;
}

/**
 * @todo Need to be documented.
 * @param type $delta
 * @return type
 */
function _ofed_slider_render_content($delta) {
  if (drupal_is_front_page()) {
    $path = '<front>';
  }
  else {
    $path = $_GET['q'];
  }

  if (_ofed_slider_menu_link_exist($path)) {
    $mlid = _ofed_slider_menu_link_exist($path);
    $nid = _ofed_slider_node_slider_exist($mlid);

    if ($nid) {
      $nodeload = node_load($nid, NULL, TRUE);
      if ($nid != '') {
        return _ofed_slider_render_node($nodeload, $delta);
      }
      else {
        return _ofed_slider_lookup($path, $delta);
      }
    }
  }
  else {

    return _ofed_slider_lookup($path, $delta);
  }
}

/**
 * @todo Need to be documented.
 * @param type $path
 * @param type $delta
 * @return type
 */
function _ofed_slider_lookup($path, $delta) {
  $lookup = drupal_lookup_path('alias', $path);
  $split = explode('/', $lookup);
  $counts = count($split);
  if ($counts > 1) {
    $checksplit = $split;

    for ($i = 0, $count = count($split) - 1; $i < $counts; $i++) {
      $id = $count - $i;
      $link_path = '';
      foreach ($checksplit as $key) {
        $link_path .= $key . '/';
      }
      $link_path = substr($link_path, 0, -1);
      $node_path = drupal_lookup_path('source', $link_path);
      unset($checksplit[$id]);

      $mlid = _ofed_slider_menu_link_exist($node_path);
      $nid = _ofed_slider_node_slider_exist($mlid);

      if ($nid) {
        $nodeload = node_load($nid, NULL, TRUE);
        $fieldname = 'field_ofed_' . $delta;
        if ($nid != '' && !empty($nodeload->$fieldname)) {
          return _ofed_slider_render_node($nodeload, $delta);
        }
      }
    }
  }

  $nid = _ofed_slider_node_slider_exist('-1');
  if ($nid) {
    $nodeload = node_load($nid, NULL, TRUE);
    $fieldname = 'field_ofed_' . $delta;
    if ($nid != '' && !empty($nodeload->$fieldname)) {
      return _ofed_slider_render_node($nodeload, $delta);
    }
  }
}

/**
 * @todo Need to be documented.
 * @param type $nodeload
 * @param type $delta
 * @return type
 */
function _ofed_slider_render_node($nodeload, $delta) {
  return theme('ofed_slider_block', array('sliders' => node_view($nodeload, 'default')));
}

/**
 * @todo Need to be documented.
 * @param type $path
 * @return type
 */
function _ofed_slider_menu_link_exist($path) {
  $option_menu = _ofed_slider_list_options_menu();
  $in_menu = array_keys($option_menu);

  $query_menu = db_select('menu_links', 'ml');
  $query_menu->condition('ml.link_path', $path, '=');
  //$query_menu->condition('ml.menu_name' , 'main-menu', '=');

  $query_menu->condition('ml.menu_name', $in_menu, 'IN');
  $query_menu->fields('ml', array('mlid'));

  return $query_menu->execute()->fetchField();
}

/**
 * @todo Need to be documented.
 * @param type $mlid
 * @return type
 */
function _ofed_slider_node_slider_exist($mlid) {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_ofed_slider_menu', 'd', 'd.entity_id = n.nid');
  $query->condition('n.type', 'ofed_slider', '=');
  $query->condition('d.field_ofed_slider_menu_value', $mlid, '=');
  $query->fields('n', array('nid'));

  return $query->execute()->fetchField();
}