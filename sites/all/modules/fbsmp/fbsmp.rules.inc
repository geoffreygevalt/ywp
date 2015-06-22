<?php

/**
 * @file
 *   Provides Rules integration for Facebook-style Micropublisher.
 */

/**
 * Implements hook_rules_event_info().
 */
function fbsmp_rules_event_info() {
  return array(
    'fbsmp_delete_status' => array(
      'label' => t('User deletes a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
    'fbsmp_edit_status' => array(
      'label' => t('User edits a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The old FBSS status object.')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The old FBSMP attachment object')),
      ),
    ),
    'fbsmp_add_status' => array(
      'label' => t('User adds a FBSS status which has a FBSMP attachment'),
      'group' => t('Facebook-style Micropublisher'),
      'variables' => array(
        'status' => array('type' => 'statuses', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function fbsmp_rules_condition_info() {
  $items = array();

  $items['fbsmp_attachment_is_type'] = array(
    'label' => t('The FBSS attachment is a certain type'),
    'arguments' => array(
      'plugin_types' => array(
        'type' => 'list<text>',
        'label' => t('Plugin type'),
        'options list' => 'fbsmp_attachment_types',
        'optional' => FALSE,
        'restriction' => 'input',
        'description' =>  t('The types of attachment allowed for this condition to be true.'),
      ),
      'attachment' => array(
        'type' => 'fbsmp',
        'label' => t('The FBSMP attachment object.')
      ),
    ),
    'base' => 'fbsmp_check_attachment_type',
    'group' => t('Facebook-style Micropublisher'),
  );
  return $items;
}

/**
 * Generate the options for the fbsmp_attachment_is_type condition.
 */
function fbsmp_attachment_types() {
  $plugins = fbsmp_get_plugins();
  return drupal_map_assoc(array_keys($plugins), 'ucfirst');
}

/**
 * Checks if the attachment is of given plugin type.
 */
function fbsmp_check_attachment_type($plugin_types, $attachment) {
  return !empty($plugin_types[$attachment->type]);
}

/**
 * Implements hook_rules_action_info().
 */
function fbsmp_rules_action_info() {
  return array(
    'fbsmp_load_action' => array(
      'label' => t('Load a FBSMP attachment object'),
      'provides' => array(
        'attachment_loaded' => array(
          'type' => 'fbsmp',
          'label' => t('The loaded FBSMP attachment')
        ),
      ),
      'help' => t('Enter the Status ID of the status for which attachment should be loaded.'),
      'group' => t('Facebook-style Micropublisher'),
      'parameter' => array(
        'sid' => array(
          'type' => 'integer',
          'label' => t('Status ID'),
          'description' => t("Enter the Status ID"),
        ),
      ),
    ),
  );
}

/**
 * Loads a status.
 */
function fbsmp_load_action($sid) {
  return array('attachment_loaded' => fbsmp_load($sid));
}

/**
 * Implements hook_rules_data_info().
 */
function fbsmp_rules_data_info() {
  return array(
    'fbsmp' => array(
      'label' => t('FBSMP attachment to FBSS status'),
      'wrapper class' => 'FBSMPRulesDataWrapper',
      'wrap' => TRUE,
      'property info' => _rules_fbsmp_info(),
    ),
  );
}

/**
 * Defines property info for FBSMP.
 */
function _rules_fbsmp_info() {
  return array(
    'sid' => array(
      'type' => 'integer',
      'label' => t('The Status ID.'),
    ),
    'type' => array(
      'type' => 'text',
      'label' => ('The status attachment type.'),
    ),
    'data' => array(
      'type' => 'struct',
      'label' => t('The attachment data.'),
    ),
  );
}

/**
 * Defines the rules node data type.
 */
class FBSMPRulesDataWrapper extends RulesIdentifiableDataWrapper implements RulesDataWrapperSavableInterface {
  public function save() {
    //@TODO Implement this functionality
    return TRUE;
  }

  protected function load($sid) {
    return fbsmp_load($sid);
  }

  protected function extractIdentifier($attachment) {
    return $attachment->sid;
  }
}
