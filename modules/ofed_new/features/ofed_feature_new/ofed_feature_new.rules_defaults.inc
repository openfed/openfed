<?php
/**
 * @file
 * ofed_feature_new.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ofed_feature_new_default_rules_configuration() {
  $items = array();
  $items['rules_force_update_new_content'] = entity_import('rules_config', '{ "rules_force_update_new_content" : {
      "LABEL" : "Force update news content",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ofed_new" : "ofed_new" } }
          }
        },
        { "AND" : [] },
        { "data_is" : {
            "data" : [ "node:field-ofed-new-update-force" ],
            "value" : [ "node:field-ofed-new-update-force" ]
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "node:field-ofed-new-update" ], "value" : "now" } }
      ]
    }
  }');
  return $items;
}
