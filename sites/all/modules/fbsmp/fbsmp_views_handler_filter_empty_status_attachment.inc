<?php

/**
 * @file
 *   Filter to allow each status to have at least status text or attachment.
 */

/**
 * Filter handler to show status with at least one of status text or attachment.
 */
class fbsmp_views_handler_filter_empty_status_attachment extends views_handler_filter_boolean_operator {
  function construct() {
    $this->definition['type'] = 'yes-no';
    $this->definition['label'] = t('Show status only if status text is not blank or has an attachment');
    $this->value_value = $this->definition['label'];
    parent::construct();
  }

  function query() {
    if ($this->value) {
      $table = $this->ensure_my_table();
      $status_alias = $this->query->ensure_table('statuses');

      $plugins = fbsmp_get_plugins();
      if (is_array($plugins) && count($plugins) > 0) {
        $db_or = db_or()
          ->condition("$status_alias.message", '', '<>')
          ->condition(db_and()
            ->isNotNull("$table.type")
            ->condition("$table.type", array_keys($plugins), 'IN'));
        $this->query->add_where(0, $db_or);
      }
      else {
        $this->query->add_where(0, "$status_alias.message", '', '<>');
      }
    }
  }
}
