<?php

// Regional and language > Regional Settings at "admin/config/regional/settings"
variable_set('date_first_day', 1);

// Regional and language > Multilingual settings > node options at "admin/config/regional/i18n/node"
variable_set('i18n_node_default_language_none', 1);

// Regional and language > Multilingual settings > Variables at "admin/config/regional/i18n/variable"
$arr = array(
  // Other
    'site_map_page_title',
  // User settings
    'logintoboggan_redirect_on_confirm',
    'logintoboggan_redirect_on_register',
    'user_registration_help',
    'user_picture_dimensions',
    'user_picture_guidelines',
  // Menu settings
    
  // Site information
    'site_name',
    'site_slogan',
    'anonymous',
    'site_frontpage',
    'site_403',
    'site_404',
    'maintenance_mode_message',
  // Feed settings
    
  // Regional settings
    'date_first_day',
    'user_default_timezone',
  // Theme settings
    
  // User emails
    'user_mail_register_admin_created_[mail_part]',
    'user_mail_register_no_approval_required_[mail_part]',
    'user_mail_register_pending_approval_[mail_part]',
    'user_mail_password_reset_[mail_part]',
    'user_mail_status_activated_[mail_part]',
    'user_mail_status_blocked_[mail_part]',
    'user_mail_cancel_confirm_[mail_part]',
    'user_mail_status_canceled_[mail_part]'
);

variable_set('variable_realm_list_language', $arr);

// Regional and language > Language > Detection and selection at "admin/config/regional/language/configure"
$arr = Array(
  'locale-url' => Array(
    'callbacks' => Array(
      'language' => 'locale_language_from_url',
      'switcher' => 'locale_language_switcher_url',
      'url_rewrite' => 'locale_language_url_rewrite_url'
    ),
    'file' => 'includes/locale.inc'
  ),
  'language-default' => Array( 
    'callbacks' => Array( 
      'language' => 'language_from_default' 
    )
  )
);
variable_set('language_negotiation_language', $arr);
  



// TODO DEBUG why it redirect to the public website when we active a functionalities in penultimate task install
// 
//$values = array(
//  'fr' => 'French', 
//  'nl' => 'Dutch (Nederlands)'
//);
//
//include_once DRUPAL_ROOT . '/includes/iso.inc';
//$predefined = _locale_get_predefined_list();
//
//foreach( $values as $key => $value ) {
//  
//  locale_add_language($key);
//  drupal_set_message(t('The language %language has been created and can now be used. More information is available on the <a href="@locale-help">help screen</a>.', array('%language' => t($predefined[$key][0]), '@locale-help' => url('admin/help/locale'))));
//
//  if ($batch = locale_batch_by_language($key, '_locale_batch_language_finished')) {
//    batch_set($batch);
//  }
//  
//}