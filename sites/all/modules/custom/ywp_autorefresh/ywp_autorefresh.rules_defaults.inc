<?php


/**
 * Implements hook_default_rules_configuration().
 */
function ywp_autorefresh_default_rules_configuration() {
  $items['ywp_autorefresh_statuses'] = rules_import('{
  "ywp_autorefresh_statuses" : {
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
              "a:2:{s:4:\u0022name\u0022;s:12:\u0022statuses_all\u0022;s:10:\u0022display_id\u0022;s:6:\u0022page_1\u0022;}" : "a:2:{s:4:\u0022name\u0022;s:12:\u0022statuses_all\u0022;s:10:\u0022display_id\u0022;s:6:\u0022page_1\u0022;}",
              "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022block_1\u0022;}" : "a:2:{s:4:\u0022name\u0022;s:15:\u0022statuses_stream\u0022;s:10:\u0022display_id\u0022;s:7:\u0022block_1\u0022;}"
            }
          }
        }
      }
    ]
  }
}');

  $items['rules_new_comment'] = rules_import('{
  "rules_new_comment" : {
    "LABEL" : "New comment",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "rules", "privatemsg_rules", "fbss_rules", "fbsmp" ],
    "ON" : { "statuses_save" : [], "fbsmp_add_status" : [] },
    "DO" : [
      { "entity_fetch" : {
          "USING" : { "type" : "node", "id" : [ "status:recipient" ] },
          "PROVIDE" : { "entity_fetched" : { "node_fetched" : "Node" } }
        }
      },
      { "privatemsg_rules_new" : {
          "USING" : {
            "recipient" : [ "node-fetched:author" ],
            "author" : "1",
            "subject" : "New comment on [node-fetched:title]",
            "body" : "The user [status:sender] posted a new comment on [node-fetched:title].\r\n\r\n[node-fetched:url]"
          },
          "PROVIDE" : { "thread_id" : { "thread_id" : "ID of new thread" } }
        }
      }
    ]
  }
}');

  return $items;
}
