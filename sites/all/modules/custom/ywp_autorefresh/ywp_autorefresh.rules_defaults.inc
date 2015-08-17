<?php


/**
 * Implements hook_default_rules_configuration().
 */
function ywp_autorefresh_default_rules_configuration() {
  $items['ywp_autorefresh_statuses'] = rules_import('{
    "rules_statuses_nodejs" : {
      "LABEL" : "Statuses NodeJS",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "views_nodejs", "fbss_rules", "fbss_comments_rules", "fbsmp" ],
      "ON" : {
        "statuses_save" : [],
        "fbss_comments_save" : [],
        "fbsmp_add_status" : []
      },
      "DO" : [
        { "views_nodejs" : { "views" : { "value" : {
                "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022block_1\u0022;}" : "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022block_1\u0022;}",
                "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022default\u0022;}" : "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022default\u0022;}"
              }
            }
          }
        }
      ]
    }
  }');

  return $items;
}
