<?php

/**
 * @file
 *   Allows users to attach photos with their FBSS status.
 */

fbsmp_include_library('file.inc', 'file');

/**
 * Implementation of hook_fbsmp_admin_settings_form().
 */
function fbsmp_photo_fbsmp_admin_settings_form(&$form_state) {
  $prev_settings = fbsmp_load_plugin_settings('photo');

  $form = array();
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );
  $form['general']['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => $prev_settings['file_extensions'],
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
  );

  $form['general']['max_filesize'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum upload size per file'),
    '#default_value' => $prev_settings['max_filesize'],
    '#description' => t('Specify the size limit that applies to each file separately. Enter a value like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes) in order to restrict the allowed file size. If you leave this this empty the file sizes will be limited only by PHP\'s maximum post and file upload sizes (current limit <strong>%limit</strong>).', array('%limit' => format_size(file_upload_max_size()))),
  );

  $form['general']['max_resolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum resolution for Images'),
    '#default_value' => $prev_settings['max_resolution'],
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The maximum allowed image size expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 for no restriction. If a larger image is uploaded, it will be rejected.'),
  );

  $form['general']['min_resolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum resolution for Images'),
    '#default_value' => $prev_settings['min_resolution'],
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The minimum allowed image size expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 for no restriction. If an image that is smaller than these dimensions is uploaded, it will be rejected.'),
  );

  if (module_exists('image')) {
    $presets_options = array(0 => t('Original image (no preset)'));
    foreach (image_styles() as $presetname => $preset) {
      $presets_options[$presetname . ':default'] = t('@preset image', array('@preset' => $presetname));
      $presets_options[$presetname . ':imagelink'] = t('@preset image linked to image', array('@preset' => $presetname));
      $presets_options[$presetname . ':path'] = t('@preset file path', array('@preset' => $presetname));
      $presets_options[$presetname . ':url'] = t('@preset URL', array('@preset' => $presetname));
    }
    $form['general']['imagecache_preset'] = array(
      '#type' => 'select',
      '#title' => t('Imagecache preset'),
      '#options' => $presets_options,
      '#default_value' => $prev_settings['imagecache_preset'],
      '#description' => t('Select which imagecache preset to use to theme the photo.'),
    );
  }

  //@todo: Integrate it with filefield_paths module
  $form['path_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['path_settings']['file_path'] = array(
    '#type' => 'textfield',
    '#title' => t('File path'),
    '#default_value' => $prev_settings['file_path'],
    '#description' => t('Optional subdirectory within the upload destination where image files will be stored. Do not include preceding or trailing slashes.'),
  );
  
  $form['attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image attributes'),
    '#description' => t('These attributes will be included in the img tag.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['attributes']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => $prev_settings['width'],
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The width attribute of the img tag. Set to 0 for no restriction.'),
  );
  $form['attributes']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => $prev_settings['height'],
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The height attribute of the img tag. Set to 0 for no restriction.'),
  );
  $form['attributes']['alt'] = array(
    '#type' => 'textfield',
    '#title' => t('Default ALT text'),
    '#default_value' => $prev_settings['alt'],
    '#description' => t('The ALT attribute of the img tag.'),
  );
  $form['attributes']['class'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional classes'),
    '#default_value' => $prev_settings['class'],
    '#description' => t('These classes are added to the img tag. Separate them with spaces (as you would in HTML).'),
  );

  return $form;
}

/**
 * Implementation of hook_fbsmp_admin_settings_form_validate().
 */
function fbsmp_photo_fbsmp_admin_settings_form_validate(&$form, &$form_state) {
  // Check that only web images are specified in the callback.
  $form_values = $form_state['values'];
  $extensions = array_filter(explode(' ', $form_values['file_extensions']));
  $web_extensions = array('jpg', 'jpeg', 'gif', 'png');
  if (count(array_diff($extensions, $web_extensions))) {
    form_set_error('file_extensions', t('Only web-standard images (jpg, jpeg, gif, and png) are supported through the Photo plugin.'));
  }
  //Check that set filesize is valid
  if (!empty($form_values['max_filesize']) && !is_numeric(parse_size($form_values['max_filesize']))) {
    form_set_error('max_filesize', t('The "Maximum upload size" option must contain a valid value. You can either leave the text field empty or enter a string like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes).'));
  }

  // Check that set resolutions are valid.
  foreach (array('min_resolution', 'max_resolution') as $resolution) {
    if (!empty($form_values[$resolution]) && !preg_match('/^[0-9]+x[0-9]+$/', $form_values[$resolution])) {
      form_set_error($resolution, t('Please specify a resolution in the format WIDTHxHEIGHT (e.g. 640x480).'));
    }
  }

  //Check the validity of the file path.
  //Strip slashes from the beginning and end of $widget['file_path']
  $form_values['file_path'] = trim($form_values['file_path'], '\\/');

  //Check that set height and width are valid.
  foreach (array('height', 'width') as $attr) {
    if (!empty($form_values[$attr]) && (!is_numeric($form_values[$attr]) || $form_values[$attr] != round($form_values[$attr]) || $form_values[$attr] < 0)) {
      form_set_error($attr, t('The @attribute must be a non-negative integer.', array('@attribute' => $attr)));
    }
  }
  //Check that CSS class is valid.
  if (!empty($form_values['class']) && !preg_match('/^[a-zA-Z]+[_a-zA-Z0-9- ]*$/', $form_values['class'])) {
    form_set_error('class', t('The HTML "class" attribute can only include spaces, underscores, hyphens, and alphanumeric characters.'));
  }

}

/**
 * Implementation of hook_fbsmp_admin_settings_form_submit().
 */
function fbsmp_photo_fbsmp_admin_settings_form_submit(&$form, &$form_state) {
  $form_values = $form_state['values'];
  $settings = array();
  $settings['file_extensions'] = $form_values['file_extensions'];
  $settings['max_filesize'] = $form_values['max_filesize'];
  $settings['min_resolution'] = $form_values['min_resolution'];
  $settings['max_resolution'] = $form_values['max_resolution'];
  if (module_exists('image')) {
	$settings['imagecache_preset'] = $form_values['imagecache_preset'];
  }
  $settings['file_path'] = $form_values['file_path'];
  $settings['width'] = $form_values['width'];
  $settings['height'] = $form_values['height'];
  $settings['alt'] = $form_values['alt'];
  $settings['class'] = $form_values['class'];

  fbsmp_save_plugin_settings($settings, 'photo');
}

/**
 * Implementation of hook_fbsmp_widget_form().
 */
function fbsmp_photo_fbsmp_widget_form(&$form_state) {

  $form = array();
  $settings = fbsmp_load_plugin_settings('photo');
  $settings['file_extensions'] = !empty($settings['file_extensions']) ? $settings['file_extensions'] : 'jpeg jpg png gif';

  $max_filesize = parse_size(file_upload_max_size());
  if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
    $max_filesize = parse_size($settings['max_filesize']);
  }
  $desc[] = t('Allowed Extensions: @ext', array('@ext' => $settings['file_extensions']));
  $desc[] = t('Maximum Filesize: @size', array('@size' => format_size($max_filesize)));

  $form['fbsmp_photo_upload'] = array(
    '#type' => 'file',
    '#description' => implode('<br />', $desc),
    '#size' => 22,
    '#upload_validators' => fbsmp_photo_widget_upload_validators($settings),
    '#settings' => $settings,
  );
  return $form;
}

/**
 * Implementation of hook_fbsmp_widget_form_validate().
 */
function fbsmp_photo_fbsmp_widget_form_validate(&$form, &$form_state) {
  $settings = $form['fbsmp']['fbsmp_photo_upload']['#settings'];
  $upload_name = 'fbsmp_photo_upload';
  $dest = _fbsmp_file_create_path($settings['file_path']);
  if (!_fbsmp_file_check_directory($dest, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp', 'The upload directory %directory could not be created or is not accessible. A newly uploaded photo could not be saved in this directory as a consequence, and the upload was canceled.', array('%directory' => $dest));
    form_set_error($upload_name, t('The photo could not be uploaded.'));
    return 0;
  }
  if ($file = _fbsmp_file_save_upload($upload_name, $form['fbsmp']['fbsmp_photo_upload']['#upload_validators'], $dest)) {
    $form_state['values']['fbsmp_photo_upload'] = $file->fid;
  }
  else {
    form_set_error($upload_name, t('The photo could not be uploaded.'));
  }
}

/**
 * Implementation of hook_fbsmp_widget_form_save().
 */
function fbsmp_photo_fbsmp_widget_form_save($form, $form_state) {
  $fid = $form_state['values']['fbsmp_photo_upload'];
  
  $file = _fbsmp_file_load($fid); //Cache the file.
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
  
  $record = array(
    'fid' => $fid,
  );
  
  return $record;
}

/**
 * Implementation of hook_fbsmp_repost_form().
 */
function fbsmp_photo_fbsmp_repost_form(&$form_state, $attachment) {
  $form = array();
  $form['fbsmp_photo_repost'] = array(
    '#value' => fbsmp_photo_fbsmp_themed_attachment($attachment),
  );

  $form['fbsmp_attachment_object'] = array(
    '#type' => 'value',
    '#value' => $attachment,
  );

  return $form;
}

/**
 * Implementation of hook_fbsmp_widget_form_validate().
 */
function fbsmp_photo_fbsmp_repost_form_validate(&$form, &$form_state) {
  $settings = fbsmp_load_plugin_settings('photo');
  $dest = _fbsmp_file_create_path($settings['file_path']);
  if (!_fbsmp_file_check_directory($dest, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp', 'The upload directory %directory could not be created or is not accessible. A re-posted photo could not be saved in this directory as a consequence.', array('%directory' => $dest));
    form_set_error('fbsmp_photo_repost', t('The photo could not be re-posted.'));
    return 0;
  }

  $orig_attachment = $form_state['values']['fbsmp_attachment_object'];
  $file = (array) _fbsmp_file_load($orig_attachment->data['fid']);
  if (!isset($file['filepath']) || !isset($file['fid'])) {
    form_set_error('fbsmp_photo_repost', t('The photo could not be re-posted.'));
    return 0;
  }

  if ($new_file = _fbsmp_file_save_file($file['filepath'], array(), $dest)) {
    $form_state['values']['fbsmp_photo_repost'] = $new_file->fid;
  }
  else {
    form_set_error('fbsmp_photo_repost', t('The photo could not be re-posted.'));
    return 0;
  }
}

/**
 * Implementation of hook_fbsmp_widget_form_submit().
 */
function fbsmp_photo_fbsmp_repost_form_save(&$form, &$form_state) {
  $fid = $form_state['values']['fbsmp_photo_repost'];
  
  $file = _fbsmp_file_load($fid); //Cache the file.
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
  
  $record = array(
    'fid' => $fid,
  );
  
  return $record;
}

/**
 * Themes a photo using default photo plugin settings.
 *
 * @param $attachment
 *   The attachment object.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - width
 *       An integer specifying the width attribute of the img tag.
 *   - height
 *       An integer specifying the height attribute of the img tag.
 *   - class
 *       A string specifying the class attribute of the img tag.
 *   - alt
 *       A string specifying the alt text for the img tag.
 *   - title
 *       A string specifying the title text for the img tag.
 *
 * @return
 *   Return a themed image, with the specified photo settings.
 */
function theme_fbsmp_photo_attachment_default($variables) {
  $attachment = $variables['attachment'];
  $settings = $variables['settings'];
  
  $attachment_data = $attachment->data;
  $file = (array) _fbsmp_file_load($attachment_data['fid']);
  if (!is_file(drupal_realpath($file['uri']))) {
    return '<!-- File not found: ' . check_plain($file['filename']) . ' -->';
  }
  
  $theme_variables = array();

  if (isset($settings['width']) && $settings['width']) {
    $theme_variables['width'] = $settings['width'];
  }
  if (isset($settings['height']) && $settings['height']) {
    $theme_variables['height'] = $settings['height'];
  }

  if (isset($settings['class']) && $settings['class']) {
    $theme_variables['attributes'] = array('class' => $settings['class']);
  }

  $alt = '';
  if (isset($settings['alt']) && $settings['alt']) {
    $theme_variables['alt'] = $settings['alt'];
  }

  $title = '';
  if (isset($settings['title']) && $settings['title']) {
    $theme_variables['title'] = $settings['title'];
  }
  
  $theme_variables['path'] = file_create_url($file['uri']);
  

  return theme('image', $theme_variables);
}

/**
 * Themes a photo using imagecache preset.
 *
 * @param $presetname
 *   A string specifying the presetname of the imagecache derivative.
 * @param $style
 *   A string specifying one of the following style of the preset:
 *     - 'default'
 *         Themes the image without any style.
 *     - 'imagelink'
 *         Links the themed image to original image.
 *     - 'path'
 *         Returns the path of the imagecached image.
 *     - 'url'
 *         Returns the url of the imagecached image.
 * @param $attachment
 *   The attachment object.
 * @param $alt
 *   A string specifying the alt text for the img tag.
 * @param $title
 *   A string specifying the title text for the img tag.
 * @param attributes
 *   An optional drupal attributes array. If attributes is set, the default imagecache classes
 *   will not be set automatically, you must do this manually.
 *
 * @return
 *   Return the themed image.
 */
function theme_fbsmp_photo_attachment_imagecache($variables) {
  $presetname = $variables['preset'];
  $style = $variables['style'];
  $attachment = $variables['attachment'];
  $alt = $variables['alt'];
  $title = $variables['title'];
  $attributes = $variables['attributes'];
  
  $attachment_data = $attachment->data;
  $file = (array) _fbsmp_file_load($attachment_data['fid']);
  if (!is_file(drupal_realpath($file['uri']))) {
    return '<!-- File not found: ' . check_plain($file['filename']) . ' -->';
  }
  
  switch ($style) {
    case 'default':
      return theme('image_style', array('style_name' => $presetname, 'path' => $file['uri'], 'alt' => $alt, 'title' => $title, 'attributes' => $attributes));
    case 'imagelink':
      $thumbnail = theme('image_style', array('style_name' => $presetname, 'path' => $file['uri'], 'alt' => $alt, 'title' => $title, 'attributes' => $attributes));
      $url =  file_create_url($file['uri']);
      return l($thumbnail, $url, array('html' => TRUE));
    case 'path':
      return image_style_path($presetname, $file['uri']);
    case 'url':
      return image_style_url($presetname, $file['uri']);
  }
}

/**
 * Implementation of hook_fbsmp_themed_attachment().
 */
function fbsmp_photo_fbsmp_themed_attachment($attachment) {
  $settings = fbsmp_load_plugin_settings('photo');
  $attributes = array();
  if (module_exists('image') && $settings['imagecache_preset']) {
    if (isset($settings['class']) && $settings['class']) {
      $attributes = array('class' => $settings['class']);
    }
    list($presetname, $style) = explode(':', $settings['imagecache_preset']);
    return theme('fbsmp_photo_attachment_imagecache', array('preset' => $presetname, 'style' => $style, 'attachment' => $attachment, 'alt' => $settings['alt'], 'title' => '', 'attributes' => $attributes));
  }

  return theme('fbsmp_photo_attachment_default', array('attachment' => $attachment, 'settings' => $settings));
}

/**
 * Implementation of hook_fbsmp_subtheme().
 */
function fbsmp_photo_fbsmp_subtheme() {
  return array(
    'fbsmp_photo_attachment_default'  => array(
      'variables' => array('attachment' => NULL, 'settings' => NULL),
      'file' => 'plugins/photo.inc',
    ),
    'fbsmp_photo_attachment_imagecache'  => array(
      'variables' => array('preset' => NULL, 'style' => NULL, 'attachment' => NULL, 'alt' => NULL, 'title' => NULL, 'attributes' => NULL),
      'file' => 'plugins/photo.inc',
    ),
  );
}

/**
 * Implementation of hook_fbsmp_token_list().
 */
function fbsmp_photo_fbsmp_token_list() {
  $tokens = array();
  $tokens['photo-id'] = array(
    'name' => t('Photo ID'),
    'description' => t('The fid of the saved photo.'),
  );
  $tokens['photo-url'] = array(
    'name' => t('Photo URL'),
    'description' => t('The URL that can be used to download the photo.'),
  );
  return $tokens;
}

/**
 * Implementation of hook_fbsmp_token_values().
 */
function fbsmp_photo_fbsmp_token_values($tokens, $attachment) {
  $attachment_data = $attachment->data;
  $replacements = array();

  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'photo-id':
        $replacements[$original] = $attachment_data['fid'];
        break;
      case 'photo-url':
        $file = (array) _fbsmp_file_load($attachment_data['fid']);
        $file_url = '';
        if (is_file($file['uri'])) {
          $file_url = file_create_url($file['uri']);
        }
        $replacements[$original] = $file_url;
        break;
    }
  }

  return $replacements;
}

/**
 * Break out for fbsmp_fbsmp_delete().
 */
function fbsmp_photo_fbsmp_delete($status) {
  $attachment_data = $status->attachment->data;
  _fbsmp_file_delete(_fbsmp_file_load($attachment_data['fid']));
}

/**
 * Break out for fbsmp_file_download().
 */
function fbsmp_photo_file_download($uri) {
  // Load file information from database
  $file = db_select('file_managed', 'fm')
    ->fields('fm', array('fid', 'filename', 'filemime', 'filesize'))
    ->condition('fm.type', 'image', '=')
    ->condition('fm.uri', $uri, '=')
    ->execute()
    ->fetchObject();

  if (!$file) {
    // We don't really care about this file
    return;
  }

  $records = fbsmp_get_attachments('photo');
  foreach ($records as $record) {
    if ($record['data']['fid'] == $file->fid) {
      // Check if current user has access to this status.
      if (fbsmp_status_can_view(facebook_status_load($record['sid']))) {
        // Access is granted.
        $name = mime_header_encode($file->filename);
        $type = mime_header_encode($file->filemime);
        $disposition = 'inline';

        return array(
          'Content-Type: ' . $type . '; name=' . $name,
          'Content-Length: ' . $file->filesize,
          'Content-Disposition: ' . $disposition . '; filename="' . $name . '"',
         
          // ...and allow the file to be cached for two weeks (matching the
          // value we/ use for the mod_expires settings in .htaccess) and
          // ensure that caching proxies do not share the image with other
          // users.
          'Expires' => gmdate(DATE_RFC1123, REQUEST_TIME + 1209600),
          'Cache-Control' => 'max-age=1209600, private, must-revalidate',
        );
      }

      return -1;
    }
  }
}

/**
 * Get the upload validators for a photo upload field.
 *
 * @param $settings
 *   The settings array for the plugin.
 * @return
 *   An array suitable for passing to file_save_upload() or the file field
 *   element's '#upload_validators' property.
 */
function fbsmp_photo_widget_upload_validators($settings) {
  $max_filesize = parse_size(file_upload_max_size());
  if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
    $max_filesize = parse_size($settings['max_filesize']);
  }

  $validators = array(
    '_fbsmp_file_validate_size' => array($max_filesize),
    '_fbsmp_file_validate_extensions' => array($settings['file_extensions']),
    '_fbsmp_file_validate_is_image' => array(),
  );
  //Add validators for resolutions.
  if (!empty($settings['max_resolution']) || !empty($settings['min_resolution'])) {
    $validators['_fbsmp_file_validate_image_resolution'] = array(
      $settings['max_resolution'],
      $settings['min_resolution'],
    );
  }
  return $validators;
}
