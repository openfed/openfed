CHANGELOG
=========

07 November 2025 - Version 12.5.1
------------------------------
- Fixed patch order for paragraphs_asymmetric_translation_widgets module.

06 November 2025 - Version 12.5.0
------------------------------
- Security updates:
  - Colorbox - Moderately critical - Cross Site Scripting - SA-CONTRIB-2025-041
    https://www.drupal.org/sa-contrib-2025-041
  - Drupal core - Moderately critical - Cross Site Scripting - SA-CORE-2025-004
    https://www.drupal.org/sa-core-2025-004
  - EU Cookie Compliance (GDPR Compliance) - Moderately critical - Cross Site Scripting - SA-CONTRIB-2025-072
    https://www.drupal.org/sa-contrib-2025-072
  - Matomo Analytics - Moderately critical - Cross site request forgery - SA-CONTRIB-2025-008
    https://www.drupal.org/sa-contrib-2025-008
  - Panels - Critical - Access bypass - SA-CONTRIB-2025-033
    https://www.drupal.org/sa-contrib-2025-033
  - Search API Solr - Moderately critical - Cross Site Request Forgery - SA-CONTRIB-2025-046
    https://www.drupal.org/sa-contrib-2025-046
  - Simple XML sitemap - Moderately critical - Cross-site Scripting - SA-CONTRIB-2025-083
    https://www.drupal.org/sa-contrib-2025-083
  - Real-time SEO for Drupal - Moderately critical - Cross-site Scripting - SA-CONTRIB-2025-091
    https://www.drupal.org/sa-contrib-2025-091
- Modules added:
  - https://www.drupal.org/project/page_cache_query_ignore
  - https://www.drupal.org/project/robotstxt
  - https://www.drupal.org/project/svg_image
  - https://www.drupal.org/project/tfa
- Modules removed:
  - https://www.drupal.org/project/account_field_split
  - https://www.drupal.org/project/ckeditor_media_resize
  - https://www.drupal.org/project/ckeditor5_paste_filter
  - https://www.drupal.org/project/content_browser
  - https://www.drupal.org/project/content_translation_workflow
  - https://www.drupal.org/project/eu_cookie_compliance
  - https://www.drupal.org/project/fast_404
  - https://www.drupal.org/project/fences
  - https://www.drupal.org/project/matomo
  - https://www.drupal.org/project/media_file_bulk_archive
  - https://www.drupal.org/project/url_embed
  - https://www.drupal.org/project/xmlrpc

06 November 2025 - Version 12.3.5
------------------------------
- Openfed Social was updated to 1.8.
- Fixed checkVersion in the validateUpdate12 script.
- Removed the validateUpdate12 script from pre-update-cmd because of conflicts with the composer-patches plugin.
  The script should now be run manually via `composer run project-validate-update12` which is included in the
  openfed-project project.

21 October 2025 - Version 12.3.4
------------------------------
- Field labels in paragraphs now show the correct translation.
- Fixed javascript issue caused by the Yoast SEO module upgrade.
- More flexibility is added to choose which menu link attributes are configurable.

10 September 2025 - Version 12.3.3
------------------------------
- Bump KISO to version 3.1.x

09 September 2025 - Version 12.3.2
------------------------------
- Drupal core to version 10.3.14
- Module updates:
  - Block Class to version 4.0.1
  - Colorbox to version 2.1.4
  - Conditional Fields to version 4.0.0-alpha6
  - Matomo to version 1.25
  - Panels to version 4.9
  - Redirect to version 1.11
  - Search API to version 1.38
  - Search API Solr to version 4.3.10
- CKEditor Accordion: Fixed accessibility issue
- CKEditor Upload Image: Fixed undefined array key warning and deprecated function message
- KISO: A new release of KISO is made available with several fixes and improvements
- Openfed Multilingual: Show links to other languages, even if the translation is not available
- Openfed Social: New social networks added (Bluesky, Threads and Mastodon)
- Page Manager: Fixed issue with page variant titles taking entity label instead of variant title
- Webform: Fixed issue where authenticated users were unable to downloads encrypted Webform uploads
- Yoast SEO: Disable automatic refresh after content change

13 March 2025 - Version 12.3.1
------------------------------
- Fixed issue with menu_link_weight module
- Updated page_manager/panels modules and patches
- Updated rules and typed_data modules

20 February 2025 - Version 12.3.0
------------------------------
- Update drupal/core-recommended due to SA-CORE-2025-001,SA-CORE-2025-002 and SA-CORE-2025-003
- Fix Openfed update validations
- Add drupal/ckeditor_media_resize
- Update drupal/honeypot module
- Update openfed_admin theme to remove empty link items

29 November 2024 - Version 12.2.7
------------------------------
- Update drupal/core-recommended due to SA-CORE-2024-003,SA-CORE-2024-004,SA-CORE-2024-006,SA-CORE-2024-007 and SA-CORE-2024-008
- Update drupal core to 10.2.12 to fix Twig issue #3487031
- Fix drupal core version to 10.2.12 instead of using wildcard for minor versions.
- Update honeypot module to version 2.1.4 to fix pontential future issues related with #3468450

21 November 2024 - Version 12.2.6
------------------------------
- Small change to the validation script to make it compatible with more systems.
- Update info and CHANGELOG

28 October 2024 - Version 12.2.5
------------------------------
- Update drupal/core-recommended due to CVE-2024-45440.
- Update drupal/facets due to SA-CONTRIB-2024-047
- Update drupal/seckit due to SA-CONTRIB-2024-039
- Update drupal/diff due to SA-CONTRIB-2024-042

03 October 2024 - Version 12.2.4
------------------------------
- Update the version of menu_link_field_attributes module.

30 September 2024 - Version 12.2.3
------------------------------
- Partially revert commit b6734ed, which introduced issues when uploading new media items for new installations
- Add ckeditor5_paste_filter module
- Add metatag module patch for issue 3469872
- Add Orejime Video to Openfed
- Add and enable media_library_edit module

17 July 2024 - Version 12.2.2
------------------------------
- Add hook_update to install twig_real_content on existing projects, due to the new dependency

16 July 2024 - Version 12.2.1
------------------------------
Several fixes and updates:
- Issue #31: Default Workflow overriden when enabling Openfed Workflow module
- Issue #42: update page_manager patches to fix page title
- Issue #65: issue creating a new content type using default config
- Issue #70: fix Claro issues
- Enable drupal/twig_real_content to be used with Kiso (Kiso issue 64)
- Updates due to psa-2024-06-26
- Remove leftover config for display suite
- Update leaflet_maptiler module to version 2.0.0
- Update menu_link_weight module to version 2.0-alpha6
- Add translatable_menu_link_uri module
- Add drupal/twig_real_content

22 May 2024 - Version 12.2.0
------------------------------
First stable release of version 12.2

11 April 2024 - Version 12.2.0-beta1
------------------------------
- Update Drupal core to version 10.2.x
- Updated contrib modules
- Update default config install to use core allowed_formats
- Add update hook for allowed_formats
- Add post_update to disable allowed_formats module
- Add patch for alertbox D10 compatibility
- Add patch for leaflet_maptiler compatibility with latest leaflet
- Add validation script to check for deprecated twig functions
- Remove Openfed install dependency on several modules
- Add an installation option for Openfed federal header module
- Remove installation option for securelogin
- Cleanup code

29 November 2023 - Version 12.1.0
------------------------------

- Removed 2 ckeditor related hard-coded contrib modules
- Updated contrib modules

06 September 2023 - Version 12.1.0-beta4
------------------------------
  Update install hooks

26 July 2023 - Version 12.1.0-beta3
------------------------------
  Skip openfed_admin deprecated theme check during composer openfed validations process.


26 July 2023 - Version 12.1.0-beta2
------------------------------
  Move openfed_admin block configurations into openfed_admin theme folder.


26 July 2023 - Version 12.1.0-beta1
------------------------------
  Update core to version 10.1.1
