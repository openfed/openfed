<?php
variable_set('sweaver_classes_exclude', "clear
clearfix
sweaver
sweaver-hovered
sweaver-clicked
sweaver-clicked-temp");

variable_set('sweaver_combined_selectors', TRUE);

variable_set('sweaver_ctools_allowed_properties', "-moz-border-radius
-webkit-border-radius
border-top-right-radius
border-bottom-right-radius
border-bottom-left-radius
border-top-left-radius
webkit-border-top-right-radius
webkit-border-bottom-right-radius
webkit-border-bottom-left-radius
webkit-border-top-left-radius
moz-border-radius-topright
moz-border-radius-bottomright
moz-border-radius-bottomleft
moz-border-radius-topleft
position
top
left
bottom
right
border-collapse
border-spacing
list-style-image
list-style-type
min-width
max-width
min-height
max-height
visibility");

variable_set('sweaver_editor_form_configuration', array(
    'one' => array(
      'title' => 'Font',
      'properties' => array(
        '0' => 'font-family',
        '1' => 'font-properties-wrapper',
        '2' => 'vertical-align',
      )
    ),
    'two' => array(
      'title' => 'Background',
      'properties' => array(
        '0' => 'background-color',
        '1' => 'background-image',
        '2' => 'background-repeat',
        '3' => 'background-attachment',
        '4' => 'background-position',
      )
    ),
    'three' => array(
      'title' => 'Borders & Spacing',
      'properties' => array(
        '0' => 'position-settings',
        '1' => 'border-style',
        '2' => 'border-color',
        '3' => 'border-collapse',
        '4' => 'border-spacing',
      )
    ),
    'four' => array(
      'title' => 'Other',
      'properties' => array(
        '0' => 'height',
        '1' => 'width',
      )
    )
));

variable_set('sweaver_enabled', TRUE);

variable_set('sweaver_paths', "admin*
node/add*
node/*/edit
node/*/panel*
panels/ajax*
user/*/edit
batch*
wysiwyg_imageupload/*
media/*
taxonomy/*
imce");

variable_set( 'sweaver_plugins_weight', array(
  'sweaver_plugin_editor' => -49,
  'sweaver_plugin_styles' => -48,
  'sweaver_plugin_palettes' => -46,
  'sweaver_plugin_advanced' => -47,
  'sweaver_plugin_images' => -45,
  'sweaver_plugin_themeswitch' => -44,
  'sweaver_plugin_themesettings' => -43,
  'sweaver_plugin_themeclasses' => -42,
  'sweaver_plugin_fontface' => -41,
  'sweaver_plugin_kb' => -39,
  'sweaver_plugin_toolbar' => -50
));

variable_set('sweaver_plugin_handle_images', "sweaver_plugin_images");

variable_set('sweaver_plugin_images_styles', TRUE);

variable_set('sweaver_plugin_images_tab', TRUE);

//sweaver_plugin_status_sweaver_plugin	b:1;

variable_set('sweaver_plugin_status_sweaver_plugin_advanced', TRUE);


variable_set('sweaver_plugin_status_sweaver_plugin_editor', TRUE);

variable_set('sweaver_plugin_status_sweaver_plugin_fontface', FALSE);

variable_set('sweaver_plugin_status_sweaver_plugin_images', TRUE);

variable_set('sweaver_plugin_status_sweaver_plugin_kb', FALSE);

variable_set('sweaver_plugin_status_sweaver_plugin_palettes', TRUE);

variable_set('sweaver_plugin_status_sweaver_plugin_styles', TRUE);

variable_set('sweaver_plugin_status_sweaver_plugin_themeclasses', FALSE);

variable_set('sweaver_plugin_status_sweaver_plugin_themesettings', FALSE);

variable_set('sweaver_plugin_status_sweaver_plugin_themeswitch', FALSE);

variable_set('sweaver_plugin_status_sweaver_plugin_toolbar', FALSE);

variable_set('sweaver_preview_selection', TRUE);

variable_set('sweaver_selectors_exclude', "#sweaver-frontend
#admin-menu
.colorpicker
#sweaver-messages
#sweaver-popup
#follow-link
#toolbar
#l10n-client");

variable_set('sweaver_selectors_source', TRUE);

variable_set( 'sweaver_selector_order', array(
    'body' => -100,
    'h1' => -99,
    'h2' => -98,
    'h3' => -97,
    'li' => -96,
    'link' => -95,
    'ol' => -94,
    'p' => -93,
    'ul' => -92,
    'form' => -91,
    'label' => -90,
    'input' => -89,
    'textarea' => -88,
    'submit' => -87,
    'allids' => -86,
    'allclasses' => -85,
    'alltags' => -84,
    'span' => -83,
    'div' => -82,
    'menu' => 50,
    'navigation' => 50,
    'read_more' => 51,
));

variable_set('sweaver_skin', "default");

variable_set('sweaver_translate_path', TRUE);