CHANGELOG
=========

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
