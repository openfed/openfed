api = 2
core = 7.x

projects[drupal][version] = "7.21"

; Allow install profiles to change the system requirements
; see http://drupal.org/node/1772316
projects[drupal][patch][] = http://drupal.org/files/allow_change_system-requirements-1772316-4.patch

; Tests for: $info['fields'] not always set?
; see http://drupal.org/node/1400256
projects[drupal][patch][] = http://drupal.org/files/1400256-field_info_collate_fields-7.patch

; Registry rebuild should not parse the same file twice in the same request
; see http://drupal.org/node/1470656
projects[drupal][patch][] = http://drupal.org/files/drupal-1470656-14.patch


; Download the openfed install profile and recursively build all its dependencies
projects[openfed][type] = profile
projects[openfed][download][url] = http://git.drupal.org/sandbox/bart.hanssens/1813432.git
projects[openfed][download][branch] = 7.x-0.x
