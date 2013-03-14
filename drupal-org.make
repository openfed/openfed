; This file was auto-generated by drush make
api = 2
core = 7.x

;
; Libraries
; Please fill the following out. Type may be one of get, git, bzr or svn, and url is the url of the download.
;

; CK Editor
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.zip"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"

; Colorbox
libraries[colorbox][download][type] = "git"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox.git"
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][type] = "library"

; jquery.cycle
libraries[jquery.cycle][download][type] = "git"
libraries[jquery.cycle][download][url] = "https://github.com/malsup/cycle.git"
libraries[jquery.cycle][directory_name] = "jquery.cycle"
libraries[jquery.cycle][type] = "library"

; jquery.imagesloaded
libraries[jquery.imagesloaded][download][type] = "git"
libraries[jquery.imagesloaded][download][url] = "https://github.com/desandro/imagesloaded.git"
libraries[jquery.imagesloaded][directory_name] = "jquery.imagesloaded"
libraries[jquery.imagesloaded][type] = "library"

; jquery.jcarousel
libraries[jquery.jcarousel][download][type] = "get"
libraries[jquery.jcarousel][download][url] = "https://github.com/jsor/jcarousel/tree/0.3.0-beta.2/dist"
libraries[jquery.jcarousel][destination] = "libraries/jquery.jcarousel"
libraries[jquery.jcarousel][directory_name] = "lib"
libraries[jquery.jcarousel][type] = "library"

;
; Modules
; Please fill the following out. Type may be one of get, git, bzr or svn, and url is the url of the download.
;

projects[addanother][version] = "2.1"
projects[addanother][subdir] = contrib 

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = contrib 

projects[admin_path][version] = "1.0"
projects[admin_path][subdir] = contrib 

projects[admin_theme][version] = "1.0"
projects[admin_theme][subdir] = contrib 

projects[backup_migrate][version] = "2.4"
projects[backup_migrate][subdir] = contrib 

projects[beididp][version] = "0.7"
projects[beididp][subdir] = contrib 

projects[calendar][version] = "3.4"
projects[calendar][subdir] = contrib 

projects[ckeditor][version] = "1.12"
projects[ckeditor][subdir] = contrib 

projects[ckeditor_link][version] = "2.3"
projects[ckeditor_link][subdir] = contrib 

projects[colorbox][version] = "2.3"
projects[colorbox][subdir] = contrib 

projects[content_access][version] = "1.2-beta1"
projects[content_access][subdir] = contrib 

projects[countries][version] = "2.1"
projects[countries][subdir] = contrib 

projects[ctools][version] = "1.2"
projects[ctools][subdir] = contrib
projects[ctools][patch][] = "http://drupal.org/files/ctools-fix-warning-message-1739718-32.patch"

projects[date][version] = "2.6"
projects[date][subdir] = contrib 

projects[devel][version] = "1.3"
projects[devel][subdir] = contrib 

projects[diff][version] = "3.2"
projects[diff][subdir] = contrib 

projects[draggableviews][version] = "2.0"
projects[draggableviews][subdir] = contrib 

projects[ds][version] = "2.0"
projects[ds][subdir] = contrib 

projects[easy_breadcrumb][version] = "2.1"
projects[easy_breadcrumb][subdir] = contrib 

projects[elements][version] = "1.2"
projects[elements][subdir] = contrib 

projects[email][version] = "1.2"
projects[email][subdir] = contrib 

projects[entity][version] = "1.0"
projects[entity][subdir] = contrib 

projects[entityreference][version] = "1.0"
projects[entityreference][subdir] = contrib 

projects[extlink][version] = "1.12"
projects[extlink][subdir] = contrib 

projects[features][version] = "1.0"
projects[features][subdir] = contrib
projects[features][patch][] = "http://drupal.org/files/features_static_caches-1063204-32.patch"

projects[features_override][version] = "2.0-beta1"
projects[features_override][subdir] = contrib 

projects[field_group][version] = "1.1"
projects[field_group][subdir] = contrib 

projects[field_permissions][version] = "1.0-beta2"
projects[field_permissions][subdir] = contrib 

projects[field_field_collection][version] = "1.0-beta5"
projects[field_field_collection][subdir] = contrib 

projects[flag][version] = "2.0"
projects[flag][subdir] = contrib 

projects[globalredirect][version] = "1.5"
projects[globalredirect][subdir] = contrib 

projects[google_analytics][version] = "1.3"
projects[google_analytics][subdir] = contrib 

projects[hierarchical_select][version] = "3.0-alpha5"
projects[hierarchical_select][subdir] = contrib 

projects[html5_tools][version] = "1.2"
projects[html5_tools][subdir] = contrib 

projects[i18n][version] = "1.8"
projects[i18n][subdir] = contrib 

projects[imagecache_actions][version] = "1.1"
projects[imagecache_actions][subdir] = contrib 

projects[imce][version] = "1.7"
projects[imce][subdir] = contrib 

projects[imce_mkdir][version] = "1.0"
projects[imce_mkdir][subdir] = contrib 

projects[jquery_plugin][version] = "1.0"
projects[jquery_plugin][subdir] = contrib 

projects[jquery_update][version] = "2.2"
projects[jquery_update][subdir] = contrib 

projects[l10n_client][version] = "1.1"
projects[l10n_client][subdir] = contrib 

projects[lexicon][version] = "1.10"
projects[lexicon][subdir] = contrib

projects[libraries][version] = "2.0"
projects[libraries][subdir] = contrib

projects[link][version] = "1.0"
projects[link][subdir] = contrib

projects[linkchecker][version] = "1.0"
projects[linkchecker][subdir] = contrib

projects[logintoboggan][version] = "1.3"
projects[logintoboggan][subdir] = contrib

projects[media][version] = "1.2"
projects[media][subdir] = contrib 

projects[menu_attributes][version] = "1.0-rc2"
projects[menu_attributes][subdir] = contrib

projects[menu_block][version] = "2.3"
projects[menu_block][subdir] = contrib

projects[menu_firstchild][version] = "1.1"
projects[menu_firstchild][subdir] = contrib

projects[menu_position][version] = "1.1"
projects[menu_position][subdir] = contrib

projects[metatag][version] = "1.0-beta4"
projects[metatag][subdir] = contrib
projects[metatag][patch][] = "http://drupal.org/files/metatag-fix_theme_hook_mismatch-1846978-0.patch"

projects[module_filter][version] = "1.7"
projects[module_filter][subdir] = contrib

projects[mollom][version] = "2.4"
projects[mollom][subdir] = contrib

projects[multiple_node_menu][version] = "1.0-beta1"
projects[multiple_node_menu][subdir] = contrib

projects[multiselect][version] = "1.9"
projects[multiselect][subdir] = contrib

projects[navigation404][version] = "1.0"
projects[navigation404][subdir] = contrib
projects[navigation404][patch][] = "http://drupal.org/files/navigation404-undefined_index_site_404-1844830-0.patch"

projects[override_node_options][version] = "1.12"
projects[override_node_options][subdir] = contrib

projects[page_title][version] = "2.7"
projects[page_title][subdir] = contrib
projects[page_title][patch][] = "http://drupal.org/files/1024624-11-include_once.patch"

projects[panels][version] = "3.3"
projects[panels][subdir] = contrib

projects[partial_date][version] = "1.0-beta1"
projects[partial_date][subdir] = contrib

projects[path_breadcrumbs][version] = "2.0-beta17"
projects[path_breadcrumbs][subdir] = contrib

projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = contrib

projects[performance][version] = "1.6"
projects[performance][subdir] = contrib

projects[print][version] = "1.2"
projects[print][subdir] = contrib

projects[redirect][version] = "1.0-rc1"
projects[redirect][subdir] = contrib

projects[robotstxt][version] = "1.0"
projects[robotstxt][subdir] = contrib

projects[role_delegation][version] = "1.1"
projects[role_delegation][subdir] = contrib

projects[rules][version] = "2.2"
projects[rules][subdir] = contrib

projects[scheduler][version] = "1.0"
projects[scheduler][subdir] = contrib
projects[scheduler][patch][] = "http://drupal.org/files/1660192-expand-options-03.patch"

projects[search_config][version] = "1.0"
projects[search_config][subdir] = contrib

projects[seckit][version] = "1.5"
projects[seckit][subdir] = contrib

projects[securelogin][version] = "1.3"
projects[securelogin][subdir] = contrib

projects[security_review][version] = "1.0"
projects[security_review][subdir] = contrib

projects[sharethis][version] = "2.5"
projects[sharethis][subdir] = contrib

projects[simple_gmap][version] = "1.0"
projects[simple_gmap][subdir] = contrib

projects[site_map][version] = "1.0"
projects[site_map][subdir] = contrib

projects[site_verify][version] = "1.0"
projects[site_verify][subdir] = contrib

projects[special_menu_items][version] = "2.0"
projects[special_menu_items][subdir] = contrib

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = contrib

projects[sweaver][version] = "1.3"
projects[sweaver][subdir] = contrib

projects[table_altrow][version] = "1.2"
projects[table_altrow][subdir] = contrib

projects[text_resize][version] = "1.7"
projects[text_resize][subdir] = contrib
projects[text_resize][patch][] = "http://drupal.org/files/text_resize_reset-1119994-6.patch"

projects[token][version] = "1.4"
projects[token][subdir] = contrib

projects[translation_helpers][version] = "1.0"
projects[translation_helpers][subdir] = contrib

projects[translation_overview][version] = "2.0-beta1"
projects[translation_overview][subdir] = contrib

projects[translation_table][version] = "1.0-beta1"
projects[translation_table][subdir] = contrib

projects[transliteration][version] = "3.1"
projects[transliteration][subdir] = contrib

projects[variable][version] = "2.2"
projects[variable][subdir] = contrib

projects[view_unpublished][version] = "1.1"
projects[view_unpublished][subdir] = contrib

projects[views][version] = "3.5"
projects[views][subdir] = contrib

projects[views_bulk_operations][version] = "3.1"
projects[views_bulk_operations][subdir] = contrib

projects[views_slideshow][version] = "3.0"
projects[views_slideshow][subdir] = contrib

projects[webform][version] = "3.18"
projects[webform][subdir] = contrib

projects[weight][version] = "2.1"
projects[weight][subdir] = contrib

projects[xmlsitemap][version] = "2.0-rc2"
projects[xmlsitemap][subdir] = contrib
