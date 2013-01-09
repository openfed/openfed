<?php
/**
 * Updatd the Full format for ckeditor 
 */
  $arr = array();
  $arr['filebrowser'] = 'imce';
  $arr['filebrowser_image'] = '';
  $arr['filebrowser_flash'] = '';
  $arr['quickupload'] = 'f';
  $arr['ss'] = "2";
  $arr['filters']['full_html'] = 1;
  $arr['default'] = "t";
  $arr['show_toggle'] = "t";
  $arr['popup'] = variable_get('ckeditor_popup', 0) ? "t" : "f";
  $arr['skin'] = "kama";
  $arr['toolbar'] = "
[
    ['Source'],
    ['Cut','Copy','Paste','PasteText','PasteFromWord','-','SpellChecker', 'Scayt'],
    ['Undo','Redo','Find','Replace','-','SelectAll','RemoveFormat'],
    ['Image','Flash','Table','HorizontalRule','Iframe','SpecialChar'],
    '/',
    ['Styles'],
    ['Bold','Italic','Underline','Strike','-','Subscript','Superscript'],
    ['NumberedList','BulletedList','-','Outdent','Indent','Blockquote'],
    ['JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock','-','BidiLtr','BidiRtl'],
    ['Link','Unlink','Anchor']
]
  ";
  $arr['expand'] = "t"; // toolbar startup
  $arr['width'] = "100%"; // width
  $arr['lang'] = "en"; // lang
  $arr['auto_lang'] = "t"; // auto detect
  $arr['language_direction'] = "default"; // direction
  $arr['enter_mode'] = "p";
  $arr['shift_enter_mode'] = "br";
  $arr['font_format'] = 'p;div;h2;h3;h4;h5;h6';
  $arr['format_source'] = "t";
  $arr['format_output'] = "t";
  $arr['custom_formatting'] = "f";
  $arr['formatting']['custom_formatting_options'] = array('indent' => 'indent', 'breakBeforeOpen' => 'breakBeforeOpen', 'breakAfterOpen' => 'breakAfterOpen', 'breakAfterClose' => 'breakAfterClose', 'breakBeforeClose' => '', 'pre_indent' => '');
  $arr['css_mode'] = "self";
  $arr['css_path'] = "%t../nerra/assets/ckeditor/ckeditor.custom.css";
  $arr['css_style'] = "self";
  $arr['styles_path'] = "%t../nerra/assets/ckeditor/ckeditor.custom.js";
  

  $arr['UserFilesPath'] = '%b%f/content/';
  $arr['UserFilesAbsolutePath'] = '%d%b%f/content/';
  $arr['ckeditor_load_method'] = "ckeditor.js";
  $arr['ckeditor_load_time_out'] = 0;
  $arr['forcePasteAsPlainText'] = "t";
  $arr['html_entities'] = "t";
  $arr['scayt_autoStartup'] = "f";
  $arr['theme_config_js'] = "f";
  $arr['js_conf'] = "";
  
  $loadPlugins = array(
//    'autogrow' => 0,
//    'counter' => 0,
//    'drupalbreaks' => 'drupalbreaks',
//    'mediaembed' => 0,
//    'stylesheetparser' => 0,
  );
  if (module_exists('ckeditor_link') ) {
    $loadPlugins['ckeditor_link'] = 'ckeditor_link';
  }
  if (module_exists('imce') ) {
    $loadPlugins['imce'] = 'imce';
  }
  if (module_exists('tableresize') ) {
    $loadPlugins['tableresize'] = 'tableresize';
  }
  
  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');
  $plugin_list = ckeditor_load_plugins();
  $arr['loadPlugins'] = array();
  if (!empty($loadPlugins)) {
      foreach (array_keys($loadPlugins) as $plugin) {
          if ($loadPlugins[$plugin] != '0') {
              $arr['loadPlugins'][$plugin] = $plugin_list[$plugin];
          }
      }
  }

  db_update('ckeditor_settings')
                    ->fields(array(
                        'settings' => serialize($arr),
                    ))
                    ->condition('name', 'Full', '=')
                    ->execute();
  
  
  
  
  
/**
 * Updatd the Advanced format for ckeditor 
 */
  $arr = array();
  $arr['filebrowser'] = 'none';
  $arr['filebrowser_image'] = '';
  $arr['filebrowser_flash'] = '';
  $arr['quickupload'] = 'f';
  $arr['ss'] = "2";
  $arr['filters']['filtered_html'] = 1;
  $arr['default'] = "t";
  $arr['show_toggle'] = "t";
  $arr['skin'] = "kama";
  $arr['toolbar'] = "
[
    ['Source'],
    ['Cut','Copy','Paste','PasteText','PasteFromWord','-','SpellChecker', 'Scayt'],
    ['Undo','Redo','Find','Replace'],
    ['BidiLtr','BidiRtl','-','Maximize'],
    '/',
    ['Styles'],
    ['Bold','Italic','Underline'],
    ['NumberedList','BulletedList','-','Outdent','Indent','Blockquote'],
    ['JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock'],
    ['Link','Unlink','Anchor']
]
  ";
  $arr['expand'] = "t"; // toolbar startup
  $arr['width'] = "100%"; // width
  $arr['lang'] = "en"; // lang
  $arr['auto_lang'] = "t"; // auto detect
  $arr['language_direction'] = "default"; // direction
  $arr['enter_mode'] = "p";
  $arr['shift_enter_mode'] = "br";
  $arr['font_format'] = 'p;div;h2;h3;h4;h5;h6';
  $arr['format_source'] = "t";
  $arr['format_output'] = "t";
  $arr['custom_formatting'] = "f";
  $arr['formatting']['custom_formatting_options'] = array('indent' => 'indent', 'breakBeforeOpen' => 'breakBeforeOpen', 'breakAfterOpen' => 'breakAfterOpen', 'breakAfterClose' => 'breakAfterClose', 'breakBeforeClose' => '', 'pre_indent' => '');
  $arr['css_mode'] = "self";
  $arr['css_path'] = "%t../nerra/assets/ckeditor/ckeditor.custom.css";
  $arr['css_style'] = "self";
  $arr['styles_path'] = "%t../nerra/assets/ckeditor/ckeditor.custom.js";
  

  $arr['UserFilesPath'] = '%b%f/content/';
  $arr['UserFilesAbsolutePath'] = '%d%b%f/content/';
  $arr['ckeditor_load_method'] = "ckeditor.js";
  $arr['ckeditor_load_time_out'] = 0;
  $arr['forcePasteAsPlainText'] = "t";
  $arr['html_entities'] = "t";
  $arr['scayt_autoStartup'] = "f";
  $arr['theme_config_js'] = "f";
  $arr['js_conf'] = "";
  
  $loadPlugins = array(
//    'autogrow' => 0,
//    'counter' => 0,
//    'drupalbreaks' => 'drupalbreaks',
//    'mediaembed' => 0,
//    'stylesheetparser' => 0,
  );
  if (module_exists('ckeditor_link') ) {
    $loadPlugins['ckeditor_link'] = 'ckeditor_link';
  }
  if (module_exists('tableresize') ) {
    $loadPlugins['tableresize'] = 'tableresize';
  }
  
  module_load_include('inc', 'ckeditor', 'includes/ckeditor.lib');
  $plugin_list = ckeditor_load_plugins();
  $arr['loadPlugins'] = array();
  if (!empty($loadPlugins)) {
      foreach (array_keys($loadPlugins) as $plugin) {
          if ($loadPlugins[$plugin] != '0') {
              $arr['loadPlugins'][$plugin] = $plugin_list[$plugin];
          }
      }
  }

  db_update('ckeditor_settings')
                    ->fields(array(
                        'settings' => serialize($arr),
                    ))
                    ->condition('name', 'Advanced', '=')
                    ->execute();