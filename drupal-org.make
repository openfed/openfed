api = 2
core = 7.x

;
; Libraries
; Please fill the following out. Type may be one of get, git, bzr or svn, and url is the url of the download.
;

; CK Editor
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.2.2/ckeditor_4.2.2_full.zip"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"

; Colorbox
libraries[colorbox][download][type] = "git"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox.git"
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][type] = "library"

; jquery.cycle
libraries[jquery.cycle][download][type] = "get"
libraries[jquery.cycle][download][url] = "https://github.com/malsup/cycle/archive/master.zip"
libraries[jquery.cycle][directory_name] = "jquery.cycle"
libraries[jquery.cycle][type] = "library"

; jquery.imagesloaded
libraries[jquery.imagesloaded][download][type] = "file"
libraries[jquery.imagesloaded][download][request_type] = "get"
libraries[jquery.imagesloaded][download][url] = "https://github.com/desandro/imagesloaded/raw/v2.1.2/jquery.imagesloaded.min.js"
libraries[jquery.imagesloaded][directory_name] = "jquery.imagesloaded"
libraries[jquery.imagesloaded][type] = "library"

; jquery.jcarousel
libraries[jquery.jcarousel][download][type] = "get"
libraries[jquery.jcarousel][download][url] = "https://github.com/jsor/jcarousel/raw/0.2.8/lib/jquery.jcarousel.min.js"
libraries[jquery.jcarousel][destination] = "libraries/jquery.jcarousel"
libraries[jquery.jcarousel][directory_name] = "lib"
libraries[jquery.jcarousel][type] = "library"

;
; OpenFed Modules
; Please fill the following out. Type may be one of get, git, bzr or svn, and url is the url of the download.
;

projects[addemar_subscription][version] = "1.0"
projects[addemar_subscription][subdir] = contrib

projects[ofed_admin_menu][download][type] = git
projects[ofed_admin_menu][download][branch] = "7.x-1.x"
projects[ofed_admin_menu][download][revision] = d598aa2
projects[ofed_admin_menu][subdir] = contrib

projects[ofed_menu_dam][version] = "1.0"
projects[ofed_menu_dam][subdir] = contrib

projects[ofed_switcher][download][type] = git
projects[ofed_switcher][download][branch] = "7.x-1.x"
projects[ofed_switcher][download][revision] = 6605d5b 
projects[ofed_switcher][subdir] = contrib

projects[ofed_vmcd][version] = "1.0"
projects[ofed_vmcd][subdir] = contrib

projects[ofed_theme_nerra][download][type] = git
projects[ofed_theme_nerra][download][branch] = "7.x-1.x"
projects[ofed_theme_nerra][download][revision] = ffd7a6c
projects[ofed_theme_nerra][subdir] = contrib

projects[ofed_theme_cms][download][type] = git
projects[ofed_theme_cms][download][branch] = "7.x-1.x"
projects[ofed_theme_cms][download][revision] = 1919886
projects[ofed_theme_cms][subdir] = contrib

projects[ofed_theme_maintenance][version] = "1.0"
projects[ofed_theme_maintenance][subdir] = contrib

;
; Modules
; Please fill the following out. Type may be one of get, git, bzr or svn, and url is the url of the download.
;

projects[addanother][version] = "2.1"
projects[addanother][subdir] = contrib

projects[admin_language][download][type] = git
projects[admin_language][download][branch] = "7.x-1.x"
projects[admin_language][download][revision] = 6f0a6e5
projects[admin_language][subdir] = contrib

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = contrib

projects[admin_theme][version] = "1.0"
projects[admin_theme][subdir] = contrib

projects[apachesolr][version] = "1.4"
projects[apachesolr][subdir] = contrib

projects[apachesolr_attachments][version] = "1.3"
projects[apachesolr_attachments][subdir] = contrib

projects[apachesolr_autocomplete][version] = "1.3"
projects[apachesolr_autocomplete][subdir] = contrib

projects[apachesolr_multilingual][version] = "1.0-beta2"
projects[apachesolr_multilingual][subdir] = contrib

projects[backup_migrate][version] = "2.7"
projects[backup_migrate][subdir] = contrib

projects[beididp][version] = "1.0-alpha2"
projects[beididp][subdir] = contrib

projects[calendar][version] = "3.4"
projects[calendar][subdir] = contrib

projects[ckeditor][version] = "1.13"
projects[ckeditor][subdir] = contrib

projects[ckeditor_link][version] = "2.3"
projects[ckeditor_link][subdir] = contrib

projects[colorbox][version] = "2.4"
projects[colorbox][subdir] = contrib

projects[comment_goodness][version] = "1.4"
projects[comment_goodness][subdir] = contrib

projects[content_access][version] = "1.2-beta2"
projects[content_access][subdir] = contrib

projects[countries][version] = "2.1"
projects[countries][subdir] = contrib

projects[ctools][version] = "1.3"
projects[ctools][subdir] = contrib

projects[date][version] = "2.6"
projects[date][subdir] = contrib

projects[devel][version] = "1.3"
projects[devel][subdir] = contrib

projects[diff][version] = "3.2"
projects[diff][subdir] = contrib

projects[draggableviews][version] = "2.0"
projects[draggableviews][subdir] = contrib

projects[ds][version] = "2.6"
projects[ds][subdir] = contrib

projects[easy_breadcrumb][version] = "2.7"
projects[easy_breadcrumb][subdir] = contrib
projects[easy_breadcrumb][patch][2071747] = "http://drupal.org/files/easy_breadcrumb-home-breadcrumb-does-not-get-translated-2071747-3.patch"

projects[elements][version] = "1.4"
projects[elements][subdir] = contrib

projects[email][version] = "1.2"
projects[email][subdir] = contrib

projects[emfield][version] = "1.0-alpha2"
projects[emfield][subdir] = contrib

projects[entity][version] = "1.2"
projects[entity][subdir] = contrib

projects[entityreference][version] = "1.0"
projects[entityreference][subdir] = contrib
projects[entityreference][patch][1916376] = "http://drupal.org/files/entityreference-devel-generate-fix.diff"

projects[entity_translation][version] = "1.0-beta3"
projects[entity_translation][subdir] = contrib

projects[extlink][version] = "1.13"
projects[extlink][subdir] = contrib

projects[facetapi][version] = "1.3"
projects[facetapi][subdir] = contrib

projects[facetapi_i18n][version] = "1.0-beta2"
projects[facetapi_i18n][subdir] = contrib

projects[features][version] = "2.0"
projects[features][subdir] = contrib

projects[features_override][version] = "2.0-rc1"
projects[features_override][subdir] = contrib

projects[field_collection][version] = "1.0-beta5"
projects[field_collection][subdir] = contrib

projects[field-conditional-state][version] = "1.1"
projects[field-conditional-state][subdir] = contrib

projects[field_group][version] = "1.3"
projects[field_group][subdir] = contrib

projects[field_permissions][version] = "1.0-beta2"
projects[field_permissions][subdir] = contrib

projects[field_slideshow][version] = "1.82"
projects[field_slideshow][subdir] = contrib

projects[flag][version] = "2.1"
projects[flag][subdir] = contrib

projects[globalredirect][version] = "1.5"
projects[globalredirect][subdir] = contrib

projects[google_analytics][version] = "1.4"
projects[google_analytics][subdir] = contrib

projects[hierarchical_select][version] = "3.0-alpha6"
projects[hierarchical_select][subdir] = contrib

projects[html5_tools][version] = "1.2"
projects[html5_tools][subdir] = contrib

projects[i18n][version] = "1.10"
projects[i18n][subdir] = contrib

projects[i18nviews][download][type] = git
projects[i18nviews][download][branch] = "7.x-3.x"
projects[i18nviews][download][revision] = 26bd52c
projects[i18nviews][subdir] = contrib

projects[imagecache_actions][version] = "1.4"
projects[imagecache_actions][subdir] = contrib

projects[imce][version] = "1.7"
projects[imce][subdir] = contrib

projects[imce_mkdir][version] = "1.0"
projects[imce_mkdir][subdir] = contrib

projects[jquery_plugin][version] = "1.0"
projects[jquery_plugin][subdir] = contrib

projects[jquery_update][version] = "2.3"
projects[jquery_update][subdir] = contrib

projects[l10n_client][version] = "1.3"
projects[l10n_client][subdir] = contrib

projects[l10n_update][download][type] = git
projects[l10n_update][download][branch] = "7.x-1.x"
projects[l10n_update][download][revision] = 8c85a9f
projects[l10n_update][subdir] = contrib
projects[l10n_update][patch][1671570] = "http://drupal.org/files/l10n_update-fetch-module-update-1671570-18_0.patch"

projects[language_cookie][version] = "1.7"
projects[language_cookie][subdir] = contrib

projects[language_selection_page][download]type] = git
projects[language_selection_page][download][branch] = "7.x-1.x"
projects[language_selection_page][download][revision] = 1990c41
projects[language_selection_page][subdir] = contrib
projects[language_selection_page][patch][2118689] = "http://drupal.org/files/expose_urls.patch"
projects[language_selection_page][patch][2119439] = "http://drupal.org/files/language_selection_page.code_.2119439-1.patch"
projects[language_selection_page][patch][2119463] = "http://drupal.org/files/language_selection_page.globalredirect.patch"

projects[lexicon][version] = "1.10"
projects[lexicon][subdir] = contrib

projects[libraries][version] = "2.1"
projects[libraries][subdir] = contrib

projects[link][version] = "1.1"
projects[link][subdir] = contrib
projects[link][patch][1914286] = "http://drupal.org/files/Fixed_title_value_in_link_field_update_instance_undefined-1914286-3.patch"

projects[linkchecker][version] = "1.1"
projects[linkchecker][subdir] = contrib

projects[logintoboggan][version] = "1.3"
projects[logintoboggan][subdir] = contrib
projects[logintoboggan][patch][1142808] = "http://drupal.org/files/logintoboggan-minpasswordlength-1142808-9.patch"

projects[media][version] = "1.3"
projects[media][subdir] = contrib

projects[media_dailymotion][version] = "1.1"
projects[media_dailymotion][subdir] = contrib

projects[media_vimeo][version] = "1.0-beta5"
projects[media_vimeo][subdir] = contrib

projects[media_youtube][version] = "2.0-rc3"
projects[media_youtube][subdir] = contrib

projects[menu_attributes][version] = "1.0-rc2"
projects[menu_attributes][subdir] = contrib

projects[menu_block][version] = "2.3"
projects[menu_block][subdir] = contrib

projects[menu_firstchild][version] = "1.1"
projects[menu_firstchild][subdir] = contrib

projects[menu_position][version] = "1.1"
projects[menu_position][subdir] = contrib

projects[metatag][version] = "1.0-beta7"
projects[metatag][subdir] = contrib

projects[mollom][version] = "2.7"
projects[mollom][subdir] = contrib

projects[multiple_node_menu][version] = "1.0-beta1"
projects[multiple_node_menu][subdir] = contrib

projects[multiselect][version] = "1.9"
projects[multiselect][subdir] = contrib

projects[navigation404][version] = "1.0"
projects[navigation404][subdir] = contrib
projects[navigation404][patch][1844830] = "http://drupal.org/files/navigation404-undefined_index_site_404-1844830-0.patch"

projects[override_node_options][version] = "1.12"
projects[override_node_options][subdir] = contrib

projects[page_title][version] = "2.7"
projects[page_title][subdir] = contrib
projects[page_title][patch][1024624] = "http://drupal.org/files/1024624-11-include_once.patch"
projects[page_title][patch][1282564] = "http://drupal.org/files/issues/pass_by_value-1282564-1.patch"

projects[panels][version] = "3.3"
projects[panels][subdir] = contrib

projects[partial_date][version] = "1.0-beta1"
projects[partial_date][subdir] = contrib

projects[path_breadcrumbs][version] = "2.0-beta17"
projects[path_breadcrumbs][subdir] = contrib

projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = contrib
projects[pathauto][patch][290421] = "http://drupal.org/files/290421-pathauto-DRUPAL-7--1-x.patch"
projects[pathauto][patch][1993462] = "http://drupal.org/files/pathauto-path_alias_for_taxonomy_terms_always_created_in_default_language-1993462-0.patch"

projects[print][version] = "1.2"
projects[print][subdir] = contrib

projects[quiz][version] = "4.0-beta1"
projects[quiz][subdir] = contrib
;projects[quiz][patch][1899654] = "http://drupal.org/files/quiz-cant_view_long_answer_questions-1899654-1.patch"
projects[quiz][patch][1827880] = "http://drupal.org/files/undefined_index_group_by-1827880-7.patch"

projects[redirect][version] = "1.0-rc1"
projects[redirect][subdir] = contrib
projects[redirect][patch][1796596] = "http://drupal.org/files/redirect.circular-loops.1796596-104.patch"

projects[registration][version] = "1.2"
projects[registration][subdir] = contrib

projects[robotstxt][version] = "1.1"
projects[robotstxt][subdir] = contrib

projects[role_delegation][version] = "1.1"
projects[role_delegation][subdir] = contrib

projects[rules][version] = "2.5"
projects[rules][subdir] = contrib

projects[scheduler][version] = "1.1"
projects[scheduler][subdir] = contrib

projects[search_config][version] = "1.0"
projects[search_config][subdir] = contrib

projects[seckit][version] = "1.7"
projects[seckit][subdir] = contrib

projects[securelogin][version] = "1.4"
projects[securelogin][subdir] = contrib
;projects[securelogin][patch][2044839] = "http://drupal.org/files/securelogin-access_denied_during_install_process_when_installed_with_profile-2044839-0.patch"

projects[security_review][version] = "1.1"
projects[security_review][subdir] = contrib

projects[sharethis][version] = "2.5"
projects[sharethis][subdir] = contrib
projects[sharethis][patch][2044081] = "http://drupal.org/files/sharethis-2.5-2044081-3.patch"

projects[simple_gmap][version] = "1.0"
projects[simple_gmap][subdir] = contrib
projects[sharethis][patch][2070277] = "https://drupal.org/files/simple_gmap-use_https-2070277-9.patch"

projects[site_map][version] = "1.0"
projects[site_map][subdir] = contrib

projects[site_verify][version] = "1.0"
projects[site_verify][subdir] = contrib

projects[special_menu_items][version] = "2.0"
projects[special_menu_items][subdir] = contrib

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = contrib

projects[table_altrow][version] = "1.2"
projects[table_altrow][subdir] = contrib

projects[text_resize][version] = "1.8"
projects[text_resize][subdir] = contrib

projects[token][version] = "1.5"
projects[token][subdir] = contrib

projects[translation_helpers][version] = "1.0"
projects[translation_helpers][subdir] = contrib

projects[translation_overview][version] = "2.0-beta1"
projects[translation_overview][subdir] = contrib

projects[translation_table][version] = "1.0-beta1"
projects[translation_table][subdir] = contrib

projects[transliteration][version] = "3.1"
projects[transliteration][subdir] = contrib

projects[twitter_block][version] = "2.1"
projects[twitter_block][subdir] = contrib

projects[username_enumeration_prevention][version] = "1.0"
projects[username_enumeration_prevention][subdir] = contrib

projects[variable][version] = "2.3"
projects[variable][subdir] = contrib

projects[view_unpublished][version] = "1.1"
projects[view_unpublished][subdir] = contrib
projects[view_unpublished][patch][1192074] = "http://drupal.org/files/view_unpublished_content_admin-1192074-57_1.patch"

projects[views][version] = "3.7"
projects[views][subdir] = contrib

projects[views_data_export][version] = "3.0-beta6"
projects[views_data_export][subdir] = contrib

projects[views_bulk_operations][version] = "3.1"
projects[views_bulk_operations][subdir] = contrib

projects[views_slideshow][version] = "3.0"
projects[views_slideshow][subdir] = contrib

projects[webform][version] = "3.19"
projects[webform][subdir] = contrib

projects[webform_rules][version] = "1.6"
projects[webform_rules][subdir] = contrib

projects[weight][version] = "2.3"
projects[weight][subdir] = contrib

projects[xmlsitemap][version] = "2.0-rc2"
projects[xmlsitemap][subdir] = contrib
