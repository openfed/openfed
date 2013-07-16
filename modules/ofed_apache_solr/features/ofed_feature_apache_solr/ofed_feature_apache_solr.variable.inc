<?php
/**
 * @file
 * ofed_feature_apache_solr.variable.inc
 */

/**
 * Implements hook_variable_realm_default_variables().
 */
function ofed_feature_apache_solr_variable_realm_default_variables() {
$realm_variables = array();
  $realm_variables['language_solr_version']['en:1.4.x'] = array();
  $realm_variables['language_solr_version']['en:3.5.x'] = array();
  $realm_variables['language_solr_version']['fr:1.4.x'] = array();
  $realm_variables['language_solr_version']['fr:3.5.x'] = array();
  $realm_variables['language_solr_version']['nl:1.4.x'] = array();
  $realm_variables['language_solr_version']['nl:3.5.x'] = array();
  $realm_variables['solr_version']['1.4.x'] = array();
  $realm_variables['solr_version']['3.5.x'] = array();

return $realm_variables;
}
