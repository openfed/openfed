api = 2
core = 7.x

projects[drupal][version] = "7.23"

; Allow install profiles to change the system requirements
; see http://drupal.org/node/1772316
;projects[drupal][patch][1772316] = http://drupal.org/files/allow_change_system-requirements-1772316-4.patch
projects[drupal][patch][1772316] = https://drupal.org/files/drupal7-allow_change_system-requirements-1772316-18.patch

; Tests for: $info['fields'] not always set?
; see http://drupal.org/node/1400256
; projects[drupal][patch][1400256] = http://drupal.org/files/1400256-field_info_collate_fields-7.patch

; Registry rebuild should not parse the same file twice in the same request
; see http://drupal.org/node/1470656
projects[drupal][patch][1470656] = http://drupal.org/files/drupal-1470656-14.patch


; Download the OpenFed install profile and recursively build all its dependencies
projects[openfed][type] = profile
projects[openfed][version] = 1.x-dev
projects[openfed][download][type] = git
projects[openfed][download][branch] = 7.x-1.x

