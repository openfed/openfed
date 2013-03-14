<?php
/**
 * @file
 * ofed_feature_address.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ofed_feature_address_default_rules_configuration() {
  $items = array();
  $items['rules_force_update_address_content'] = entity_import('rules_config', '{ "rules_force_update_address_content" : {
      "LABEL" : "Force update address content",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ofed_address" : "ofed_address" } }
          }
        },
        { "AND" : [] },
        { "data_is" : {
            "data" : [ "node:field-ofed-address-update-force" ],
            "value" : [ "node:field-ofed-address-update-force" ]
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "node:field-ofed-address-update" ], "value" : "now" } }
      ]
    }
  }');
  return $items;
}
