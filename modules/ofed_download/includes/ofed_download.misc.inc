<?php

/**
 * Return the list of custom menu + main menu.
 * @param type $nid The node id.
 * @return array 
 */
function _ofed_download_force_download($nid) {
  // Get the node.
  if($nid) {
    $node = node_load($nid);
    if(!$node) {
      // Redirect to the 404 page.
      drupal_goto('404');
    }
    
    // Force download...
    // Disable output compression (required for ie).
    if(ini_get('zlib.output_compression')) {
      ini_set('zlib.output_compression', FALSE);
    }

    $file = $node->field_ofed_download_file[LANGUAGE_NONE][0];
    header('Pragma: public');
    header('Expires: 0');
    header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
    header('Last-Modified: ' . gmdate('D, d M Y H:i:s', $file['timestamp']) . ' GMT');
    header('Cache-Control: private', FALSE);
    header('Content-Type: ' . $file['filemime']);
    header('Content-Disposition: attachment; filename="' . basename($file['filename']) . '"');
    header('Content-Transfer-Encoding: binary');
    header('Content-Length: ' . $file['filesize']);
    header('Connection: close');
    readfile($file['uri']); 
    exit();
  }
  else {
    // Redirect to the 404 page.
    drupal_goto('404');
  }
}