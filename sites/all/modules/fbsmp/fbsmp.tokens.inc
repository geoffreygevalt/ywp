<?php

/**
 * @file
 * Builds placeholder replacement tokens for status micropublisher-related data.
 */

/**
 * Implements of hook_token_info().
 */
function fbsmp_token_info() {
  $types = array();
  $tokens = array();

  // FBSMP tokens.
  $types['fbsmp'] = array(
    'name' => t('Statuses Micropublisher'),
    'description' => t('Tokens related to Statuses Micropublisher'),
    'needs-data' => 'fbsmp',
  );
  $tokens['fbsmp']['attachment-type'] = array(
    'name' => t('Attachment type'),
    'description' => t('The type of the attachment for this status.'),
  );
  $tokens['fbsmp']['attachment-data'] = array(
    'name' => t('Attachment data'),
    'description' => t('The raw serialized attachment data.'),
  );
  $tokens['fbsmp']['attachment-themed'] = array(
    'name' => t('Themed attachment'),
    'description' => t('The themed attachment.'),
  );

  foreach (fbsmp_get_plugins() as $plugin => $info) {
    if ($function = fbsmp_load_function($plugin, 'token list')) {
      $tokens['fbsmp'] = array_merge($tokens['fbsmp'], $function());
    }
  }

  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function fbsmp_tokens($type, $tokens, array $data = array(), array $options = array()) {
  if ($type != 'fbsmp' || empty($data['fbsmp'])) {
    return;
  }
  $sanitize = !empty($options['sanitize']);
  $replacements = array();
  $attachment = $data['fbsmp'];

  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'attachment-type':
        $replacements[$original] = $attachment->type;
        break;
      case 'attachment-data':
        $replacements[$original] = serialize($attachment->data);
        break;
      case 'attachment-themed':
        $replacements[$original] = fbsmp_render_attachment($attachment);
        break;
    }
  }

  foreach (fbsmp_get_plugins() as $plugin => $info) {
    if ($function = fbsmp_load_function($plugin, 'token values')) {
      $replacements = array_merge($replacements, $function($tokens, $attachment));
    }
  }

  return $replacements;
}
