<?php

/**
 * variable for configuration page at "admin/structure/ds/list/extras"
 */
variable_set('ds_extras_fields_extra', FALSE);
variable_set('ds_extras_fields_extra_list', '');
variable_set('ds_extras_field_permissions', TRUE);
variable_set('ds_extras_field_template', TRUE);
variable_set('ds_extras_flag', TRUE);
variable_set('ds_extras_hidden_region', FALSE);
variable_set('ds_extras_hide_page_sidebars', TRUE);
variable_set('ds_extras_hide_page_title', TRUE);
variable_set('ds_extras_region_to_block', FALSE);
variable_set('ds_extras_switch_field', FALSE);
variable_set('ds_extras_switch_view_mode', TRUE);
variable_set('ds_extras_vd', TRUE);
variable_set('ft-default', 'theme_ds_field_minimal');



/**
 * variable for configuration page at "admin/structure/ds/list/search"
 */
variable_set('ds_search_type', 'node');
variable_set('ds_search_path', 'content');
variable_set('ds_search_view_mode', 'search_result');
variable_set('ds_search_variables', 'search_totals_plus_keywords');
variable_set('ds_search_show_title', TRUE);
variable_set('ds_search_language', TRUE);
variable_set('ds_search_highlight', TRUE);
variable_set('ds_search_highlight_selector', '.view-mode-search_result');
variable_set('ds_search_group_by_type', FALSE);
variable_set('ds_search_group_by_type_other', 'Other');
variable_set('ds_search_group_by_type_other_wrapper', 'markup');
variable_set('ds_search_group_by_type_settings', array(
    'panel' => array( 'status' => 1, 'label' => 'Results for panel', 'wrapper' => 'markup', 'weight' => 0 ),
    'webform' => array( 'status' => 1, 'label' => 'Results for webform', 'wrapper' => 'markup', 'weight' => 0 )
  )
);
variable_set('ds_search_node_form_alter', FALSE);
variable_set('ds_search_node_limit', '10');


/**
 * variable for configuration page at "admin/structure/ds/classes"
 */
variable_set('ds_classes_fields', 'align-left|Align left
align-right|Align right
align-center|Align center
clear-block|Clear block
float-left|Float left
float-right|Float right
focus|Focus
headline|Headline
highlight-heavy|Highlight Heavy
highlight-medium|Highlight Medium
highlight-light|Highlight Light
');

variable_set('ds_classes_regions', '');

/**
 * VIEW MODES 
 */

$view_mode = new StdClass();
$view_mode->view_mode = 'page_list';
$view_mode->label = 'Page list';
$view_mode->entities = array ( 'node' => 'node' );
drupal_write_record('ds_view_modes', $view_mode);

$view_mode = new StdClass();
$view_mode->view_mode = 'block_list';
$view_mode->label = 'Block list';
$view_mode->entities = array ( 'node' => 'node' );
drupal_write_record('ds_view_modes', $view_mode);

$view_mode = new StdClass();
$view_mode->view_mode = 'block_column';
$view_mode->label = 'Block column';
$view_mode->entities = array ( 'node' => 'node' );
drupal_write_record('ds_view_modes', $view_mode);

$view_mode = new StdClass();
$view_mode->view_mode = 'block_element';
$view_mode->label = 'Block element';
$view_mode->entities = array ( 'node' => 'node' );
drupal_write_record('ds_view_modes', $view_mode);

$view_mode = new StdClass();
$view_mode->view_mode = 'references';
$view_mode->label = 'References';
$view_mode->entities = array ( 'node' => 'node' );
drupal_write_record('ds_view_modes', $view_mode);


/**
 * CODE FIELD 
 */
$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  $pathinfo = pathinfo($file["0"]["filename"]);
  echo "<span class=\"file-type-".strip_tags($pathinfo["extension"])."\">".strip_tags($pathinfo["extension"])."</span>";
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'file_type';
$field->label = 'File Type';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);


$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo "<span class=\"file-size\">".format_size($file["0"]["filesize"])."</span>";
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'file_size';
$field->label = 'File Size';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);


$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  $pathinfo = pathinfo($file["0"]["filename"]);
  echo "<span class=\"file-name\">".$pathinfo["filename"]."</span>";
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'file_name';
$field->label = 'File Name';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);


$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("View file"), file_create_url($file["0"]["uri"]), array("attributes" => array("class" => "file-url-open", "target" => "_blank")) );
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'file_url_open';
$field->label = 'File url open';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);


$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("Share file"), "download-file/".$entity->nid, array("attributes" => array("target" => "_blank")) );
  echo "<span class=\"url-file-persistent\">".url("download-file/".$entity->nid, array("absolute" => TRUE))."</span>";
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'file_url_persistent';
$field->label = 'File url persistent';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);


$field = new StdClass();
$field->properties = array(
    'code' => array(
      'value' => '<?php 
foreach($entity->field_ofed_download_file as $file) {
  echo l( t("Save file"), "download-file/".$entity->nid, array("attributes" => array("class" => "file-url-save")) );
}
?>',
      'format' => 'ds_code'
    ),
    'use_token' => FALSE
);
$field->field = 'url_file_save';
$field->label = 'File url save';
$field->ui_limit = 'ofed_download|*';
$field->entities = array ( 'node' => 'node' );
$field->field_type = DS_FIELD_TYPE_CODE;
drupal_write_record('ds_fields', $field);