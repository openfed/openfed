api = 2
core = 7.x

; Drupal core
projects[drupal][type] = core
projects[drupal][version] = 7.23
projects[drupal][translations][] = nl
projects[drupal][translations][] = fr
projects[drupal][translations][] = de

; Allow install profiles to change the system requirements
; see http://drupal.org/node/1772316
projects[drupal][patch][1772316] = https://drupal.org/files/drupal7-allow_change_system-requirements-1772316-18.patch

; Registry rebuild should not parse the same file twice in the same request
; see http://drupal.org/node/1470656
projects[drupal][patch][1470656] = http://drupal.org/files/drupal-1470656-14.patch

