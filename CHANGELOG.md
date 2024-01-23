CHANGELOG
=========

22 January 2024 - Version 11.2.1
------------------------------
  Updated onomasticon version and patches.
  Added splidejs/splide library.
  Added ten1seven/what-input library.
  Require kiso 3.0.*.
  Created LICENSE.
  Fixed patches for menu_trail_by_path module.


06 September 2023 - Version 11.2.0
------------------------------
  Downgrade patch for page_manager issue https://www.drupal.org/project/page_manager/issues/2858877 since it throws an error when combining with patch from issue https://www.drupal.org/project/panels/issues/3183258.
  Add deprecated themes validation before upgrading to openfed 12.
  Fix method to check openfed version during composer update
  Fix deprecated function drupal_get_path() in FederalHeaderBlock.php.
  Include changes from release 11.1.9
  Remove deprecated modules from openfed.info.yml
  Fix version comparison during openfed update validation.
  Show exception message about deprecated modules when trying to update from Openfed 11 to 12 version.
  Improvements in composer scripts.
  Update core to version 9.5.10
  Update contrib modules to version compatible with Drupal 10
  Force PHP version 8.1 in composer


06 September 2023 - Version 11.1.10
------------------------------
  Issue #48: update script to take the current major version in consideration

17 July 2023 - Version 11.1.9
------------------------------
  Security, outdated and unsupported module update:
    - update kiso
    - update admin_toolbar
    - update google_analytics
    - update office_hours
    - update linkit
    - update leaflet
    - update leaflet_maptiler
    - update editor_advanced_link
  Hook update for office_hours legacy support:
    - openfed_update_91110()

21 April 2023 - Version 11.1.8
------------------------------
  Update leaflet_maptiler due to incompatibilities with new version

20 April 2023 - Version 11.1.7
------------------------------
  Revert update for smart_trim module due to PHP7.3 incompatibilities

20 April 2023 - Version 11.1.6
------------------------------
  Update bootstrap theme
  Update editor_advanced_link module
  Update field_encrypt module
  Update leaflet module
  Update smart_trim module
  Update twig_field_value module

12 April 2023 - Version 11.1.5
------------------------------
  Update Core
  Update Alertbox module to fix D9/D10 compatibility

23 March 2023 - Version 11.1.3
------------------------------
  Update leaflet_maptiler due to leaflet_maptiler_token incompatibility
  Update partial_date due to D9 limitations
  Add core patch for #3260652

20 March 2023 - Version 11.1.2
------------------------------
  Downgrade smart_trim due to PHP compatibility.

20 March 2023 - Version 11.1.1
------------------------------
  Update several contrib modules to their latest version.

20 December 2022 - Version 11.1.0
------------------------------
  Initial Openfed 11.1 release, using Drupal Core 9.4

24 August 2022 - Version 11.0.8
------------------------------
  Update Address module to fix drupal.org issue 2949352

12 June 2022 - Version 11.0.7
------------------------------
  Update Drupal core due to SA-CORE-2022-011
  Update Better Exposed Filters module

03 June 2022 - Version 11.0.6
------------------------------
  Fix an issue with pathauto update hook

03 June 2022 - Version 11.0.5
------------------------------
  Update lock file with latest core version
  Update embed due to SA-CONTRIB-2022-042
  Update allowed_formats, cshs, field_formatter, honeypot, inline_entity_form, menu_block, moderated_content_bulk_publish, paragraphs, pathauto and scheduler_content_moderation_integration

11 May 2022 - Version 11.0.4
------------------------------
  Fix Openfed Update script to make it work with old versions of 'cut'
  Fix Openfed Update script to include composer.patches.json in the merge
  Update menu_link to fix some known issues
  Update facets

26 April 2022 - Version 11.0.3
------------------------------
  Issue #16: Fix file entity 'Other' mime types.
  Issue #15: Create default menus for main and header navigation.
  Fix bug in the update script

21 March 2022 - Version 11.0.2
------------------------------
  Set a fixed module version to avoid versioning issues
  Remove unsuported moderated_content_bulk_publish patch until there's a new version of it

21 March 2022 - Version 11.0.1
------------------------------
  Remove dblog from the default modules as this shouldn't be there on live sites
  Make optional the node edit form confirmation dialog
  Update validation scripts to make it compatible with older versions of grep and more flexible
  Fix issue with openfed update validation

09 March 2022 - First stable release
------------------------------
  Initial Openfed 11 release, using Drupal Core 9.3

21 September 2021 - Version dev
------------------------------
  Initial commit.
