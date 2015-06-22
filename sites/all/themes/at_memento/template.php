<?php
// AT Memento

/**
 * Override or insert variables into the html template.
 */
function at_memento_preprocess_html(&$vars) {
  global $theme_key;

  $theme_name = 'at_memento';
  $path_to_theme = drupal_get_path('theme', $theme_name);

  // Add class for the active theme
  $vars['classes_array'][] = drupal_html_class($theme_key);

  // Add theme settings classes
  $settings_array = array(
    'main_background_overlay',
    'features_overlay',
    'footer_overlay',
    'header_layout',
    'menu_bullets',
    'main_menu_alignment',
    'corner_radius_form_input_text',
    'corner_radius_form_input_submit',
  );
  foreach ($settings_array as $setting) {
    $vars['classes_array'][] = theme_get_setting($setting);
  }

  // Content display settings - grids
  // Content displays
  $show_frontpage_grid = theme_get_setting('content_display_grids_frontpage') == 1 ? TRUE : FALSE;
  $show_taxopage_grid = theme_get_setting('content_display_grids_taxonomy_pages') == 1 ? TRUE : FALSE;
  if ($show_frontpage_grid == TRUE || $show_taxopage_grid == TRUE) {drupal_add_js($path_to_theme . '/js/equalheights.js');}
  if ($show_frontpage_grid == TRUE) {
    $cols_fpg = theme_get_setting('content_display_grids_frontpage_colcount');
    $vars['classes_array'][] = $cols_fpg;
    drupal_add_js($path_to_theme . '/js/eq.fp.grid.js');
  }
  if ($show_taxopage_grid == TRUE) {
    $cols_tpg = theme_get_setting('content_display_grids_taxonomy_pages_colcount');
    $vars['classes_array'][] = $cols_tpg;
    drupal_add_js($path_to_theme . '/js/eq.tp.grid.js');
  }

  // Special case for PIE htc rounded corners, not all themes include this
  if (theme_get_setting('ie_corners') == 1) {
    drupal_add_css($path_to_theme . '/css/ie-htc.css', array(
      'group' => CSS_THEME,
      'browsers' => array(
        'IE' => 'lte IE 8',
        '!IE' => FALSE,
        ),
      'preprocess' => FALSE,
      )
    );
  }
}

/**
 * Override or insert variables into the html template.
 */
function at_memento_process_html(&$vars) {
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Override or insert variables into the page template.
 */
function at_memento_process_page(&$vars) {
  if (module_exists('color')) {
    _color_page_alter($vars);
  }

  if ($vars['is_front']) {
    $vars['title'] = '';
  }

  // We some extra classes to support the fancy branding layouts
  $branding_classes = array();
  $branding_classes[] = $vars['linked_site_logo'] ? 'with-logo' : 'no-logo';
  $branding_classes[] = !$vars['hide_site_name'] ? 'with-site-name' : 'site-name-hidden';
  $branding_classes[] = $vars['site_slogan'] ? 'with-site-slogan' : 'no-slogan';
  $vars['branding_classes'] = implode(' ', $branding_classes);
}

/**
 * Override or insert variables into the node template.
 */
function at_memento_preprocess_node(&$vars) {
  // Remove the horrid inline class, it does wanky things like display:inline on the UL, whack eh?
  $vars['content']['links']['#attributes']['class'] = 'links';

  // Content grids - nuke links off teasers if we in a grid view
  if ($vars['view_mode'] == 'teaser') {
    $show_frontpage_grid = theme_get_setting('content_display_grids_frontpage') == 1 ? TRUE : FALSE;
    $show_taxopage_grid = theme_get_setting('content_display_grids_taxonomy_pages') == 1 ? TRUE : FALSE;
    if ($show_frontpage_grid == TRUE || $show_taxopage_grid == TRUE) {
      unset($vars['content']['links']);
    }
  }

  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $vars['submitted'] = t('Submitted by !username !datetime',
      array(
        '!username' => $vars['name'],
        '!datetime' => '<time datetime="' . $vars['datetime'] . '" pubdate="pubdate">' . $vars['date'] . '</time>',
      )
    );
  }

}

/**
 * Override or insert variables into the comment template.
 */
function at_memento_preprocess_comment(&$vars) {
  // Remove the horrid inline class, again, for fucks sake.
  $vars['content']['links']['#attributes']['class'] = 'links';
}

/**
 * Override or insert variables into the block template.
 */
function at_memento_preprocess_block(&$vars) {
  if ($vars['block']->module == 'superfish' || $vars['block']->module == 'nice_menu') {
    $vars['content_attributes_array']['class'][] = 'clearfix';
  }
  if (!$vars['block']->subject) {
    $vars['content_attributes_array']['class'][] = 'no-title';
  }
  if ($vars['block']->region == 'menu_bar' || $vars['block']->region == 'menu_bar_top') {
    $vars['title_attributes_array']['class'][] = 'element-invisible';
  }
}


/**
 * Override or insert variables into the field template.
 */
/*
function at_memento_preprocess_field(&$vars) {
  $element = $vars['element'];
  $vars['classes_array'][] = 'view-mode-'. $element['#view_mode'];
  $vars['image_caption_teaser'] = FALSE;
  $vars['image_caption_full'] = FALSE;
  if(theme_get_setting('image_caption_teaser') == 1) {
    $vars['image_caption_teaser'] = TRUE;
  }
  if(theme_get_setting('image_caption_full') == 1) {
    $vars['image_caption_full'] = TRUE;
  }
  $vars['field_view_mode'] = '';
  $vars['field_view_mode'] = $element['#view_mode'];
}
*/

/**
 * Returns HTML for a breadcrumb trail.
 */
function at_memento_breadcrumb($vars) {
  $breadcrumb = $vars['breadcrumb'];
  $show_breadcrumb = theme_get_setting('breadcrumb_display');
  if ($show_breadcrumb == 'yes') {
    $show_breadcrumb_home = theme_get_setting('breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }
    if (!empty($breadcrumb)) {
      $heading = '<h2>' . t('You are here: ') . '</h2>';
      $separator = filter_xss(theme_get_setting('breadcrumb_separator'));
      $output = '';
      foreach ($breadcrumb as $key => $val) {
        if ($key == 0) {
          $output .= '<li class="crumb">' . $val . '</li>';
        }
        else {
          $output .= '<li class="crumb"><span>' . $separator . '</span>' . $val . '</li>';
        }
      }
      return $heading . '<ol id="crumbs">' . $output . '</ol>';
    }
  }
  return '';
}

/**
 * Returns HTML for fieldsets.
 */
function at_memento_fieldset($vars) {
  $element = $vars['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  // add a class to the fieldset wrapper if a legend exists, in some instances they do not
  $class = "without-legend";
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
    // add a class to the fieldset wrapper if a legend exists, in some instances they do not
    $class = 'with-legend';
  }
  $output .= '<div class="fieldset-wrapper ' . $class  . '">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}
