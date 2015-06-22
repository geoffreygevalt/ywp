<?php

/**
 * @file
 *   Provide views data and handlers for the Facebook-style Micropublisher.
 */

/**
 * Implements hook_views_data().
 */
function fbsmp_views_data() {

  $data['fbsmp']['table']['group']  = t('Facebook-style Micropublisher');

  $data['fbsmp']['table']['join'] = array(
    'statuses' => array(
      'left_field' => 'sid',
      'field' => 'sid',
    ),
    'users' => array(
      'left_table' => 'statuses',
      'left_field' => 'sid',
      'field' => 'sid',
    ),
  );

  $data['fbsmp']['sid'] = array(
    'title' => t('Status ID'),
    'help' => t('The ID of the FBSS status.'),
  );

  $data['fbsmp']['type'] = array(
    'title' => t('Attachment type'),
    'help' => t('The type of plugin for the attachment.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['fbsmp']['attachment'] = array(
    'title' => t('Themed attachment'),
    'help' => t('The themed attachment for the Statuses status.'),
    'field' => array(
      'field' => 'data',
      'handler' => 'fbsmp_views_handler_field_themed_attachment',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['fbsmp']['empty_status_attachment'] = array(
    'title' => t('Do not show empty status'),
    'help' => t('Do not show a status without a status text or attachment'),
    'filter' => array(
      'field' => 'data',
      'handler' => 'fbsmp_views_handler_filter_empty_status_attachment',
     ),
  );

  return $data;

}
