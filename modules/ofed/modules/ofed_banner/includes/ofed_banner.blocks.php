<?php

/**
 * Implements hook_block_info().
 */
function ofed_banner_block_info() {
  $blocks = array();
  $blocks['banner_images'] = array(
      'info' => t('Banner: Banner block'),
      'cache' => DRUPAL_NO_CACHE,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function ofed_banner_block_view($delta = '') {
  $block = array();
  switch($delta) {
    case 'banner_images':
      $block['subject'] = t('Banner: Banner block');
      $block['content'] = _ofed_banner_render_content($delta);
      break;
  }
  return $block;
}

/**
 * @todo Need to be documented.
 * @param type $delta
 * @return type 
 */
function _ofed_banner_render_content($delta) {
  if(drupal_is_front_page()) {
    $path = '<front>';
  }
  else {
    $path = $_GET['q'];
  }

  if(_ofed_banner_menu_link_exist($path)) {
    $mlid = _ofed_banner_menu_link_exist($path);
    $nid = _ofed_banner_node_banner_exist($mlid);
    if($nid) {
      $nodeload = node_load($nid, null, true);

      $fieldname = 'field_ofed_' . $delta;
      if($nid != '' && !empty($nodeload->$fieldname)) {
        return _ofed_banner_render_node($nodeload, $delta);
      }
      else {
        return _ofed_banner_lookup($path, $delta);
      }
    }
  }
  else {

    return _ofed_banner_lookup($path, $delta);
  }
}

/**
 * @todo Need to be documented.
 * @param type $path
 * @param type $delta
 * @return type 
 */
function _ofed_banner_lookup($path, $delta) {
  $lookup = drupal_lookup_path('alias', $path);
  $split = explode('/', $lookup);
  $counts = count($split);
  if($counts > 1) {
    $checksplit = $split;

    for($i = 0, $count = count($split) - 1; $i < $counts; $i++) {
      $id = $count - $i;
      $link_path = '';
      foreach($checksplit as $key) {
        $link_path .= $key . '/';
      }
      $link_path = substr($link_path, 0, -1);
      $node_path = drupal_lookup_path('source', $link_path);
      unset($checksplit[$id]);

      $mlid = _ofed_banner_menu_link_exist($node_path);
      $nid = _ofed_banner_node_banner_exist($mlid);

      if($nid) {
        $nodeload = node_load($nid, null, true);

        $fieldname = 'field_ofed_' . $delta;
        if($nid != '' && !empty($nodeload->$fieldname)) {
          return _ofed_banner_render_node($nodeload, $delta);
        }
      }
    }
  }

  $nid = _ofed_banner_node_banner_exist('-1');
  if($nid) {
    $nodeload = node_load($nid, null, true);
    $fieldname = 'field_ofed_' . $delta;
    if($nid != '' && !empty($nodeload->$fieldname)) {
      return _ofed_banner_render_node($nodeload, $delta);
    }
  }
}

/**
 * @todo Need to be documented.
 * @param type $nodeload
 * @param type $delta
 * @return type 
 */
function _ofed_banner_render_node($nodeload, $delta) {
  return theme('ofed_banner_block', array('banners' => node_view($nodeload, 'teaser')));
}

/**
 * @todo Need to be documented.
 * @param type $path
 * @return type 
 */
function _ofed_banner_menu_link_exist($path) {
  $in_menu = array();
  $option_menu = _ofed_banner_list_options_menu();
  foreach($option_menu as $k => $v) {
    $in_menu[] = $k;
  }

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
function _ofed_banner_node_banner_exist($mlid) {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_ofed_banner_menu', 'd', 'd.entity_id = n.nid');
  $query->condition('n.type', 'ofed_banner', '=');
  $query->condition('d.field_ofed_banner_menu_value', $mlid, '=');
  $query->fields('n', array('nid'));

  return $query->execute()->fetchField();
}