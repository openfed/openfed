<?php

/**
* Describes data tables (or the equivalent) to Views.
*
* This hook should be placed in MODULENAME.views.inc and it will be
* auto-loaded. MODULENAME.views.inc must be in the directory specified by the
* 'path' key returned by MODULENAME_views_api(), or the same directory as the
* .module file, if 'path' is unspecified.
*
* @return
* An associative array describing the data structure. Primary key is the
* name used internally by Views for the table(s) – usually the actual table
* name. The values for the key entries are described in detail below.
*/ 
function ofed_views_data() {
  $data = array();

  $data['node']['ofed_add_link'] = array(
    'title' => t('openFED - Add link'),
    'help' => t('Add a link to create an item. Note: filter type must be add to see something.'),
    'area' => array(
      'handler' => 'ofed_area_add_link',
    ),
  );
  
  $data['node']['ofed_show_results_count'] = array(
    'title' => t('openFED - Show results count'),
    'help' => t('Show the count of the displayed items. Note: filter type must be add to see something.'),
    'area' => array(
      'handler' => 'ofed_area_show_results_count',
    ),
  );

  $data['node']['ofed_url_taxonomy'] = array(
    'title' => t('openFED - Taxonomy terms'),
    'help' => t('Taxonomy terms description.'),
    'argument' => array(
      'handler' => 'ofed_argument_taxonomy_terms',
    ),
  );
  
  return $data;
}