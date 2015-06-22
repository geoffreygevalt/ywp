<?php

/**
 * @file
 *   Common functionality for file handling. Mostly from field_file.inc
 */


/**
 * Load a file from the database.
 *
 * @param $fid
 *   A numeric file id or string containing the file path.
 * @param $reset
 *   Whether to reset the internal file_load cache.
 *
 * @return
 *   A file object.
 */
function _fbsmp_file_load($fid, $reset = NULL) {
  //Reset internal cache.
  if (isset($reset)) {
    _fbsmp_file_cache(NULL, TRUE);
  }

  if (empty($fid)) {
    return array('fid' => 0, 'uri' => '', 'filename' => '', 'filemime' => '', 'filesize' => 0);
  }

  $files = _fbsmp_file_cache();
  //Serve file from internal cache if available.
  if (empty($files[$fid])) {
    if (is_numeric($fid)) {
      $file = db_query('SELECT f.* FROM {file_managed} f WHERE f.fid = :f_fid', array(':f_fid' => $fid))->fetchObject();

    }
    else {
      $file = db_query("SELECT f.* FROM {file_managed} f WHERE f.uri = :f_uri", array(':f_uri' => $fid))->fetchObject();
    }

    if (!$file) {
      $file = array('fid' => 0, 'uri' => '', 'filename' => '', 'filemime' => '', 'filesize' => 0);
      return $file;
    }

    foreach (module_implements('file_load') as $module) {
      $function =  $module . '_file_load';
      $function(array($fid => $file));
    }

    // Cache the fully loaded file for later use.
    $files = _fbsmp_file_cache($file);
  }

  return $files[$fid];
}

/**
 * Save a file upload to a new location.
 *
 * The file will be added to the files table as a temporary file. Temporary
 * files are periodically cleaned. To make the file permanent, change the status
 * save the file.
 *
 * @param $source
 *   A string specifying the name of the upload field to save.
 * @param $validators
 *   An optional, associative array of callback functions used to validate the
 *   file. The keys are function names and the values arrays of callback
 *   parameters which will be passed in after the user and file objects. The
 *   functions should return an array of error messages, an empty array
 *   indicates that the file passed validation. The functions will be called in
 *   the order specified.
 * @param $dest
 *   A string containing the directory $source should be copied to. If this is
 *   not provided or is not writable, the temporary directory will be used.
 *
 * @return
 *   An object containing the file information, or 0 in the event of an error.
 */
function _fbsmp_file_save_upload($source, $validators = array(), $dest = FALSE) {
  if (!$file = file_save_upload($source, $validators, $dest, FILE_EXISTS_RENAME)) {
    return 0;
  }

  _fbsmp_file_cache($file); //Cache the file in order to minimize load queries
  return $file;
}


/**
 * Delete a file and its database record.
 *
 * @param $file
 *   A file object.
 *
 * @return mixed
 *   TRUE for success or FALSE in the event of an error.
 */
function _fbsmp_file_delete($file) {
  $file = (object) $file;

  //Let other modules clean up on delete.
  module_invoke_all('file_delete', $file);

  if (file_delete($file)) {
    _fbsmp_file_cache(NULL, $file); //Delete the file from the cache
    return TRUE;
  }

  return FALSE;
}

/**
 * Internal cache, in order to minimize database queries for loading files.
 */
function _fbsmp_file_cache($file = NULL, $reset = FALSE) {
  static $files = array();

  //Reset internal cache.
  if (is_object($reset)) { // file object, uncache just that one
    unset($files[$reset->fid]);
    unset($files[$reset->uri]);
  }
  elseif ($reset) { // TRUE, delete the whole cache
    $files = array();
  }

  //Cache the file by both fid and uri.
  //Use non-copying objects to save memory.
  if (!empty($file->fid)) {
    $files[$file->fid] = $file;
    $files[$file->uri] = $file;
  }
  return $files;
}

/**
 * A silent version of file.inc's file_check_directory().
 *
 * This function differs from file_check_directory in that it checks for
 * files when doing the directory check and it does not use drupal_set_message()
 * when creating directories.
 *
 * Check that the directory exists and is writable. Directories need to
 * have execute permissions to be considered a directory by FTP servers, etc.
 *
 * @param $directory
 *   A string containing the name of a directory path.
 * @param $mode
 *   A Boolean value to indicate if the directory should be created
 *   if it does not exist or made writable if it is read-only.
 *
 * @return FALSE when directory not found, or TRUE when directory exists.
 */
function _fbsmp_file_check_directory(&$directory, $mode = 0) {
  return file_prepare_directory($directory, $mode);
}

/**
 * Determine the destination directory given a path relative to
 * system files directory.
 *
 * @param $dest
 *   The destination path relative to the system files directory without
 *   preceeding or trailing slashes.
 * @param $account
 *   The user account object to calculate the file path for.
 * @return
 *   The destination directory path, with any tokens replaced.
 */
function _fbsmp_file_create_path($dest = '', $account = NULL) {
  $file_path = file_default_scheme() . '://';
  if (!$dest) {
    return $file_path;
  }

  $account = isset($account) ? $account : $GLOBALS['user'];
  //Replace user level tokens.
  if (module_exists('token')) {
    $dest = token_replace($dest, array('user'), (array)$account);
  }
  //Replace nasty characters in the path if possible.
  if (module_exists('transliteration')) {
    module_load_include('inc', 'transliteration');
    $dest_array = array_filter(explode('/', $dest));
    foreach ($dest_array as $key => $directory) {
      $dest_array[$key] = transliteration_clean_filename($directory);
    }
    $dest = implode('/', $dest_array);
  }

  return $file_path . $dest;
}

/**
 * A silent version of file.inc's file_destination().
 *
 * Determines the destination path for a file depending on how replacement of
 * existing files should be handled. It does not uses drupal_set_message() if
 * the file already exists and FILE_EXISTS_ERROR was specified.
 *
 * @param $destination
 *   A string specifying the desired path.
 * @param $replace
 *   Replace behavior when the destination file already exists.
 *   - FILE_EXISTS_REPLACE - Replace the existing file
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *     unique
 *   - FILE_EXISTS_ERROR - Do nothing and return FALSE.
 * @return The destination file path or FALSE if the file already exists and
 *   FILE_EXISTS_ERROR was specified.
 */
function _fbsmp_file_destination($destination, $replace) {
  if (file_exists($destination)) {
    switch ($replace) {
      case FILE_EXISTS_RENAME:
        $basename = basename($destination);
        $directory = dirname($destination);
        $destination = file_create_filename($basename, $directory);
        break;

      case FILE_EXISTS_ERROR:
        return FALSE;
    }
  }
  return $destination;
}

/**
 * Save a file into a file node after running all the associated validators.
 *
 * This function is usually used to move a file from the temporary file
 * directory to a permanent location. It may be used by import scripts or other
 * modules that want to save an existing file into the database.
 *
 * @param $filepath
 *   The local file path of the file to be saved.
 * @param $validators
 *   An optional, associative array of callback functions used to validate the
 *   file. The keys are function names and the values arrays of callback
 *   parameters which will be passed in after the user and file objects. The
 *   functions should return an array of error messages, an empty array
 *   indicates that the file passed validation. The functions will be called in
 *   the order specified.
 * @param $dest
 *   A string containing the directory $source should be copied to. If this is
 *   not provided or is not writable, the temporary directory will be used.
 * @param $account
 *   The user account object that should associated with the uploaded file.
 * @param $replace
 *   Replace behavior when the destination file already exists.
 *   - FILE_EXISTS_REPLACE - Replace the existing file
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *     unique
 *   - FILE_EXISTS_ERROR - Do nothing and return 0.
 *
 * @return
 *   An object containing the file information, or 0 in the event of an error.
 */
function _fbsmp_file_save_file($filepath, $validators = array(), $dest = FALSE, $replace = FILE_EXISTS_RENAME, $account = NULL) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  //Add in our check of the the file name length.
  $validators['file_validate_name_length'] = array();

  //Begin building file object.
  $file = new stdClass();
  $file->uid = $account->uid;
  $file->filename = basename($filepath);
  $file->filepath = $filepath;
  $file->filemime = module_exists('mimedetect') ? mimedetect_mime($file) : file_get_mimetype($file->filename);

  //Rename potentially executable files, to help prevent exploits.
  if (preg_match('/\.(php|pl|py|cgi|asp|js)$/i', $file->filename) && (substr($file->filename, -4) != '.txt')) {
    $file->filemime = 'text/plain';
    $file->filepath .= '.txt';
    $file->filename .= '.txt';
  }

  //If the destination is not provided, or is not writable, then use the
  //temporary directory.
  if (empty($dest) || _fbsmp_file_check_directory($dest) === FALSE) {
    $dest = file_directory_temp();
  }

  $file->source = '_fbsmp_file_save_file';
  $file->destination = _fbsmp_file_destination(($dest . '/' . $file->filename), $replace);
  $file->filesize = filesize($filepath);

  //Call the validation functions.
  $errors = array();
  foreach ($validators as $function => $args) {
    array_unshift($args, $file);
    $errors = array_merge($errors, call_user_func_array($function, $args));
  }

  // Check for validation errors.
  if (!empty($errors)) {
    $message = t('The selected file %name could not be saved.', array('%name' => $file->filename));
    if (count($errors) > 1) {
      $message .= '<ul><li>' . implode('</li><li>', $errors) . '</li></ul>';
    }
    else {
      $message .= ' ' . array_pop($errors);
    }
    form_set_error($file->source, $message);
    return 0;
  }

  if (!$file = _fbsmp_file_copy($file, $file->destination, $replace)) {
    watchdog('file', 'Upload error. Could not move file %file to destination %destination.', array('%file' => $file->filename, '%destination' => $file->destination));
    return 0;
  }

  // If we made it this far it's safe to record this file in the database.
  $file->status = ~FILE_STATUS_PERMANENT;
  $file->timestamp = REQUEST_TIME;

  // Let modules add additional properties to the yet barebone file object.
  foreach (module_implements('file_insert') as $module) {
    $function =  $module . '_file_insert';
    $function($file);
  }

  _fbsmp_file_cache($file); // cache the file in order to minimize load queries
  return $file;
}

/**
 * An #upload_validators callback. Check the file matches an allowed extension.
 *
 * If the mimedetect module is available, this will also validate that the
 * content of the file matches the extension. User #1 is included in this check.
 *
 * @param $file
 *   A Drupal file object.
 * @param $extensions
 *   A string with a space separated list of allowed extensions.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_extensions($file, $extensions) {
  global $user;
  $errors = array();

  if (!empty($extensions)) {
    $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
    $matches = array();
    if (preg_match($regex, $file->filename, $matches)) {
      $extension = $matches[1];
      //If the extension validates, check that the mimetype matches.
      if (module_exists('mimedetect')) {
        $type = mimedetect_mime($file);
        if ($type != $file->filemime) {
          $errors[] = t('The file contents (@type) do not match its extension (@extension).', array('@type' => $type, '@extension' => $extension));
        }
      }
    }
    else {
      $errors[] = t('Only files with the following extensions are allowed: %files-allowed.', array('%files-allowed' => $extensions));
    }
  }

  return $errors;
}


/**
 * An #upload_validators callback. Check the file size does not exceed a limit.
 *
 * @param $file
 *   A Drupal file object.
 * @param $file_limit
 *   An integer value limiting the maximum file size in bytes.
 * @param $file_limit
 *   An integer value limiting the maximum size in bytes a user can upload on
 *   the entire site.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_size($file, $file_limit = 0, $user_limit = 0) {
  global $user;

  $errors = array();

  if ($file_limit && $file->filesize > $file_limit) {
    $errors[] = t('The file is %filesize exceeding the maximum file size of %maxsize.', array('%filesize' => format_size($file->filesize), '%maxsize' => format_size($file_limit)));
  }

  //Bypass user limits for uid = 1.
  if ($user->uid != 1) {
    $total_size = file_space_used($user->uid) + $file->filesize;
    if ($user_limit && $total_size > $user_limit) {
      $errors[] = t('The file is %filesize which would exceed your disk quota of %quota.', array('%filesize' => format_size($file->filesize), '%quota' => format_size($user_limit)));
    }
  }
  return $errors;
}

/**
 * An #upload_validators callback. Check that a file is an image.
 *
 * Check that the file is recognized by image_get_info() as an image.
 *
 * @param $file
 *   A Drupal file object.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_is_image($file) {
  return file_validate_is_image($file);
}

/**
 * An #upload_validators callback. Check an image resolution.
 *
 * @param $file
 *   A Drupal file object.
 * @param $max_size
 *   A string in the format WIDTHxHEIGHT. If the image is larger than this size
 *   the image will be scaled to fit within these dimensions.
 * @param $min_size
 *   A string in the format WIDTHxHEIGHT. If the image is smaller than this size
 *   a validation error will be returned.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_image_resolution($file, $maximum_dimensions = 0, $minimum_dimensions = 0) {
  $errors = array();

  //Check first that the file is an image.
  if ($info = image_get_info($file->uri)) {
    if ($maximum_dimensions) {
      list($max_width, $max_height) = explode('x', $maximum_dimensions);
      //Check that it is larger than the given dimensions.
      if ($info['width'] > $max_width || $info['height'] > $max_height) {
        $errors[] = t('The image is too large; the maximum dimensions are %dimensions pixels.', array('%dimensions' => $maximum_dimensions));
      }
    }
    if ($minimum_dimensions && empty($errors)) {
      list($min_width, $min_height) = explode('x', $minimum_dimensions);
      //Check that it is smaller than the given dimensions.
      if ($info['width'] < $min_width || $info['height'] < $min_height) {
        $errors[] = t('The image is too small; the minimum dimensions are %dimensions pixels.', array('%dimensions' => $minimum_dimensions));
      }
    }
  }

  return $errors;
}


/**
 * Silent version of of file.inc's file_copy()
 *
 * Handles file using file path. Building URI on destination.
 *
 * Copies a file to a new location and adds a file record to the database.
 *
 * This function should be used when manipulating files that have records
 * stored in the database. This is a powerful function that in many ways
 * performs like an advanced version of copy().
 * - Checks if $source and $destination are valid and readable/writable.
 * - Checks that $source is not equal to $destination; if they are an error
 *   is reported.
 * - If file already exists in $destination either the call will error out,
 *   replace the file or rename the file based on the $replace parameter.
 * - Adds the new file to the files database. If the source file is a
 *   temporary file, the resulting file will also be a temporary file. See
 *   file_save_upload() for details on temporary files.
 *
 * @param $source
 *   A file object.
 * @param $destination
 *   A string containing the destination that $source should be copied to.
 *   This must be a stream wrapper URI.
 * @param $replace
 *   Replace behavior when the destination file already exists:
 *   - FILE_EXISTS_REPLACE - Replace the existing file. If a managed file with
 *       the destination name exists then its database entry will be updated. If
 *       no database entry is found then a new one will be created.
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *       unique.
 *   - FILE_EXISTS_ERROR - Do nothing and return FALSE.
 *
 * @return
 *   File object if the copy is successful, or FALSE in the event of an error.
 *
 * @see file_unmanaged_copy()
 * @see hook_file_copy()
 */
function _fbsmp_file_copy($source, $destination, $replace) {

  if (!$source->filepath) {
    watchdog('file', 'File %file (%realpath) could not be copied, because the destination %destination is invalid. This is often caused by improper use of file_copy() or a missing stream wrapper.', array('%file' => $source->filename, '%realpath' => $source->filepath, '%destination' => $destination));
    drupal_set_message(t('The specified file %file could not be copied, because the destination is invalid. More information is available in the system log.', array('%file' => $source->uri)), 'error');
    return FALSE;
  }

  if ($file_path = _fbsmp_file_unmanaged_copy($source->filepath, $destination, $replace)) {
    $file = clone $source;
    $file->fid = NULL;
    $file->uri = file_build_uri(basename($file_path));
    $file->filename = basename($file->uri);
    // If we are replacing an existing file re-use its database record.
    if ($replace == FILE_EXISTS_REPLACE) {
      $existing_files = file_load_multiple(array(), array('uri' => $uri));
      if (count($existing_files)) {
        $existing = reset($existing_files);
        $file->fid = $existing->fid;
        $file->filename = $existing->filename;
      }
    }
    // If we are renaming around an existing file (rather than a directory),
    // use its basename for the filename.
    elseif ($replace == FILE_EXISTS_RENAME && is_file($destination)) {
      $file->filename = basename($destination);
    }

    $file->timestamp = REQUEST_TIME;
    $file->filesize = filesize($file_path);

    return $file;
  }
  return FALSE;
}

/**
 *
 * Silent version of of file.inc's file_unmanaged_copy()
 *
 * Copies a file to a new location without invoking the file API.
 *
 * This is a powerful function that in many ways performs like an advanced
 * version of copy().
 * - Checks if $source and $destination are valid and readable/writable.
 * - Checks that $source is not equal to $destination; if they are an error
 *   is reported.
 * - If file already exists in $destination either the call will error out,
 *   replace the file or rename the file based on the $replace parameter.
 * - Provides a fallback using realpaths if the move fails using stream
 *   wrappers. This can occur because PHP's copy() function does not properly
 *   support streams if safe_mode or open_basedir are enabled. See
 *   https://bugs.php.net/bug.php?id=60456
 *
 * @param $source
 *   A string specifying the filepath or URI of the source file.
 * @param $destination
 *   A URI containing the destination that $source should be copied to. The
 *   URI may be a bare filepath (without a scheme) and in that case the default
 *   scheme (file://) will be used. If this value is omitted, Drupal's default
 *   files scheme will be used, usually "public://".
 * @param $replace
 *   Replace behavior when the destination file already exists:
 *   - FILE_EXISTS_REPLACE - Replace the existing file.
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *       unique.
 *   - FILE_EXISTS_ERROR - Do nothing and return FALSE.
 *
 * @return
 *   The path to the new file, or FALSE in the event of an error.
 *
 * @see _fbsmb_file_copy()
 */
function _fbsmp_file_unmanaged_copy($source, $destination, $replace) {
  $original_source = $source;
  $original_destination = $destination;

  // Assert that the source file actually exists.
  if (!file_exists($source)) {
    watchdog('file', 'File %file could not be copied because it does not exist.', array('%file' => $original_source));
    return FALSE;
  }

  // Build a destination URI if necessary.
  if (!isset($destination)) {
    $destination = file_build_uri(basename($source));
  }


  // Prepare the destination directory.
  if (file_prepare_directory($destination)) {
    // The destination is already a directory, so append the source basename.
    $destination = file_stream_wrapper_uri_normalize($destination . '/' . basename($source));
  }
  else {
    // Perhaps $destination is a dir/file?
    $dirname = drupal_dirname($destination);
    if (!file_prepare_directory($dirname)) {
      // The destination is not valid.
      watchdog('file', 'File %file could not be copied, because the destination directory %destination is not configured correctly.', array('%file' => $original_source, '%destination' => $dirname));
      drupal_set_message(t('The specified file %file could not be copied, because the destination directory is not properly configured. This may be caused by a problem with file or directory permissions. More information is available in the system log.', array('%file' => $original_source)), 'error');
      return FALSE;
    }
  }

  // Determine whether we can perform this operation based on overwrite rules.
  $destination = file_destination($destination, $replace);
  if ($destination === FALSE) {
    drupal_set_message(t('The file %file could not be copied because a file by that name already exists in the destination directory.', array('%file' => $original_source)), 'error');
    watchdog('file', 'File %file could not be copied because a file by that name already exists in the destination directory (%directory)', array('%file' => $original_source, '%destination' => $destination));
    return FALSE;
  }

  // Assert that the source and destination filenames are not the same.
  $real_source = $source;
  $real_destination = drupal_realpath($destination);
  if ($source == $destination || ($real_source !== FALSE) && ($real_source == $real_destination)) {
    drupal_set_message(t('The specified file %file was not copied because it would overwrite itself.', array('%file' => $source)), 'error');
    watchdog('file', 'File %file could not be copied because it would overwrite itself.', array('%file' => $source));
    return FALSE;
  }
  // Make sure the .htaccess files are present.
  file_ensure_htaccess();
  // Perform the copy operation.
  if (!@copy($source, $destination)) {
    // If the copy failed and realpaths exist, retry the operation using them
    // instead.
    if ($real_source === FALSE || $real_destination === FALSE || !@copy($real_source, $real_destination)) {
      watchdog('file', 'The specified file %file could not be copied to %destination.', array('%file' => $source, '%destination' => $destination), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  // Set the permissions on the new file.
  drupal_chmod($destination);

  return $destination;
}
