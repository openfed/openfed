<?php

/**
 * @file
 * Module's blocks.
 */

/**
 * Obtains the 'easy_breadcrumb' block.
 *
 * @return array
 *   resulting renderizable array.
 */
function _easy_breadcrumb_block() {

  // Array storing the breadcrumb's segments.
  $breadcrumb = array();
  // Default classes for the segments.
  $segments_classes = array('easy-breadcrumb_segment');
  // Gets the flag saying if the front page segment should be included.
  $include_front_page_segment = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT, TRUE);

  // Conditionally include the front page segment in the breadcrumb.
  if ($include_front_page_segment) {
    $front_text = _easy_breadcrumb_obtain_home_title();
    // Marks the front--segment with an identifier class (useful for CSS).
    $segments_classes[1] = 'easy-breadcrumb_segment-front';
    // Adds a segment for the front page.
    $breadcrumb[] = _easy_breadcrumb_build_item($front_text, $segments_classes, '<front>');
  }

  // There won't be more segments if visiting the front page, the don't waste resources.
  if (!drupal_is_front_page()) {

    // Gets the flag saying the capitalizator mode.
    $capitalizator_mode = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE, 'ucwords');

    // List of words to be ignored by the capitalizator.
    $capitalizator_ignored_words = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS,
    EasyBreadcrumbConstants::defaultIgnoredWords());

    // Flag for including invalid paths as plain-text segments.
    $include_invalid_paths = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS, TRUE);

    // List of path to be excluded while generating segments.
    $excluded_paths_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS,
      EasyBreadcrumbConstants::defaultExcludedPaths());

    // Obtains the alias of the current path.
    $alias = drupal_get_path_alias();

    // Get the segments of the current path.
    $alias_arr = explode('/', $alias);

    // Get the quantity of segments in the current path.
    $segments_quantity = count($alias_arr);

    $segment_url_arr = array();

    // Iterates over the segments of the current URL
    // ("blog/article/hello-world") excepting the last segment
    // (the title, 'hello-world' in that case).
    for ($idx_0 = 0, $idx_1 = 1; $idx_1 < $segments_quantity; ++$idx_0, ++$idx_1) {

      // Build an array containing the URL of the segment being currently
      // processed. E.g., having $alias as "blog/article/hello-world", at the
      // first iteration this array will be array('blog'), the second
      // (and last in that case) the array will be array('blog','article').
      $segment_url_arr[] = $alias_arr[$idx_0];
      // String with the potential-path of the segment being processed (e.g. 'blog/article').
      $segment_url = implode('/', $segment_url_arr);

      // Jump to the next segment if this url is configured to be excluded.
      $excluded_path = _easy_breadcrumb_check_excluded_path($segment_url);
      if ($excluded_path) {
        continue;
      }

      $segments_classes[1] = 'easy-breadcrumb_segment-' . $idx_1;
      // Obtain the internal path it represents.
      $segment_normal_path = drupal_get_normal_path($segment_url);

      // Check if this is a valid path.
      $segment_valid_path = _easy_breadcrumb_validate_segment_path($segment_normal_path);

      // Get the segment's raw text from the URL.
      $segment_text = $alias_arr[$idx_0];
      // Normalized segment's text (e.g. 'Blog');
      $segment_title = _easy_breadcrumb_obtain_segment_title($segment_normal_path,
              $segment_valid_path, $segment_text);

      if ($segment_valid_path || $include_invalid_paths) {
        $breadcrumb[] = _easy_breadcrumb_build_item($segment_title, $segments_classes, $segment_url, $segment_valid_path);
      }
    }

    // Gets the flag saying if the title should be appended to the breadcrumb.
    $include_page_title_segment = variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT, TRUE);

    // Adds the page's title to the breadcrumb.
    if ($include_page_title_segment) {
      // Marks the page's-title-segment with an identifier class (useful for CSS).
      $segments_classes[1] = 'easy-breadcrumb_segment-title';
      // The title is the last segment in the URL.
      $segment_text = $alias_arr[$segments_quantity - 1];
      $segment_title = _easy_breadcrumb_obtain_page_title($segment_text);
      $title_segment_as_link = variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK, FALSE);
      // If the page's title will be a link or just a text.
      $breadcrumb[] = _easy_breadcrumb_build_item($segment_title, $segments_classes, $alias, $title_segment_as_link);
    }
  }

  // Gets the configured segments separator.
  $separator = variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '>>');
  $separator = check_plain($separator);
  $segments_quantity = count($breadcrumb);

  $build = array();
  $build['easy_breadcrumb'] = array(
      '#theme' => 'easy_breadcrumb',
      '#breadcrumb' => $breadcrumb,
      '#segments_quantity' => $segments_quantity,
      '#separator' => $separator,
  );

  return $build;
}
